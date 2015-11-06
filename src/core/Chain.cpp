#include "Chain.h"
#include <cstdarg>
#include <cassert>



Chain::Chain(const Lead& lL, const arma::mat& T1, const Insulator& B, const arma::mat& T2, const Lead& lR)
{
    /*this->leadL = lL;
    this->leadR = lR;
    this->barrier = B;

    this->T1 = T1;
    this->T2 = T2;*/

    this->lead.push_back(lL);
    this->lead.push_back(lR);
    this->barrier.push_back(B);
    this->couplingT.push_back(T1);
    this->couplingT.push_back(T2);
}



Chain::Chain(const Lead& lL, const std::string& T1, const Insulator& B, const std::string& T2, const Lead& lR)
{
    /*this->leadL = lL;
    this->leadR = lR;
    this->barrier = B;

    this->T1 = mat22(T1);
    this->T2 = mat22(T2);*/

    this->lead.push_back(lL);
    this->lead.push_back(lR);
    this->barrier.push_back(B);
    this->couplingT.push_back( mat22(T1) );
    this->couplingT.push_back( mat22(T2) );
}



Chain& Chain::operator<<(const Lead& obj)
{
    this->lead.push_back(obj);
    assert(lead.size()<=2);
    return *this;
}

Chain& Chain::operator<<(const Insulator& obj)
{
    this->barrier.push_back(obj);
    _numBarrierAtom+=obj.numAtom;
    return *this;
}

Chain& Chain::operator<<(const std::string& obj)
{
    this->couplingT.push_back( mat22(obj) );
    return *this;
}



mat Chain::H(const double o1, const double o2)
{
    int numLayer = lead.size()+barrier.size();
    int numBarrier = barrier.size();

    //---------------------------//
    // pure H terms

    mat tmp[numLayer];

    tmp[ 0] = lead[0].H(o1, o2);
    for( int i=1; i<=barrier.size(); tmp[i++]=barrier[i-1].H(o1,o2) )
    tmp[numLayer-1] = lead[1].H(o1, o2);

    mat H = blockDiag(numLayer,tmp);

    //---------------------------//
    // pure T terms

    vector<mat> tmp2;

    tmp2.push_back( couplingT[0] );

    for(int i=0, sizeBarrier; i<numBarrier; i++)
    {
        sizeBarrier = 2*(barrier[i].numAtom);
        tmp2.push_back( zeros<mat>(sizeBarrier-2,sizeBarrier-2) );
        tmp2.push_back( couplingT[i+1] );
    }

    mat* tmp22 = &tmp2[0];
    mat T = blockDiag(tmp2.size(),tmp22);

    //---------------------------//

    mat T_up = T;
    mat T_dn = T;

    T_up.insert_cols( 0, 2);
    T_dn.insert_cols( T_dn.n_cols, 2);
    T_up.insert_rows( T_up.n_rows, 2);
    T_dn.insert_rows( 0, 2);

    return T_up + H + T_dn;
}



cx_mat Chain::G_R(const double o1, const double o2, const double E)
{
    mat  H = this->H(o1, o2);
    mat EI = E*eye<mat>(H.n_rows, H.n_cols);

    cx_mat S_L = this->lead[0].S(o1, o2, E);
    cx_mat S_R = this->lead[1].S(o1, o2, E);

    int sizeBarrier = 2*_numBarrierAtom;
    cx_mat tmp[] = {S_L, zeros<cx_mat>(sizeBarrier,sizeBarrier), S_R};
    cx_mat S = blockDiag(tmp);

    return (EI - H - S).i();
}



cx_mat Chain::G_L(const double o1, const double o2, const double E)
{
    //----------------------//
    // Sigma in 2x2

    double fL = fermiD(E-barrier[0].bias_l, lead[0].temperature);
    double fR = fermiD(E-barrier[0].bias_r, lead[1].temperature);

    cx_mat22 S_L = lead[0].S(o1, o2, E);
    cx_mat22 S_R = lead[1].S(o1, o2, E);

    cx_mat22 S0_lesser_L = fL*(S_L.t() - S_L);
    cx_mat22 S0_lesser_R = fR*(S_R.t() - S_R);

    //----------------------//
    // the Big Sigma

    int dim_L = 2*(lead[0].numAtom + _numBarrierAtom);
    int dim_R = 2*(lead[1].numAtom + _numBarrierAtom);
    cx_mat tmp_zeros_L = zeros<cx_mat>(dim_L, dim_L);
    cx_mat tmp_zeros_R = zeros<cx_mat>(dim_R, dim_R);

    cx_mat S_lesser_L = blockDiag((cx_mat)S0_lesser_L, tmp_zeros_L);
    cx_mat S_lesser_R = blockDiag(tmp_zeros_R, (cx_mat)S0_lesser_R);

    //----------------------//
    // Lesser Grees's func. (as left and right term)

    cx_mat Gr = G_R(o1, o2, E);
    cx_mat G_lesser_L = (Gr.t() * S_lesser_L) * Gr;
    cx_mat G_lesser_R = (Gr.t() * S_lesser_R) * Gr;

    return G_lesser_L + G_lesser_R;
}



double Chain::unname_y(const double o1, const double o2, const double E)
{
    cx_mat G_ls = this->G_L(o1, o2, E);
    cx_mat22 G_bP = zeros<cx_mat>(2,2);  // bar-lead
    cx_mat22 G_Pb = zeros<cx_mat>(2,2);  // lead-bar


    // not check!!! lead-bar
    G_Pb(0, 0) = G_ls(13 - 1, 11 - 1);
    G_Pb(0, 1) = G_ls(13 - 1, 12 - 1);
    G_Pb(1, 0) = G_ls(14 - 1, 11 - 1);
    G_Pb(1, 1) = G_ls(14 - 1, 12 - 1);

    // not check!!! bar-lead
    G_bP(0, 0) = G_ls(11 - 1, 13 - 1);
    G_bP(0, 1) = G_ls(11 - 1, 14 - 1);
    G_bP(1, 0) = G_ls(12 - 1, 13 - 1);
    G_bP(1, 1) = G_ls(12 - 1, 14 - 1);

    cx_mat22 netG = G_Pb - G_bP;
    // netG = netG*np.mat([[0,1],[1,0]]) # pauli x
    netG = netG * cx_mat22({0, -cx_double(0,1), cx_double(0,1), 0});  // pauli y
    cx_double trace_netG = netG(0, 0) + netG(1, 1);


    return (trace_netG).real();
}



double Chain::unname_x(const double o1, const double o2, const double E)
{
    cx_mat G_ls = this->G_L(o1, o2, E);
    cx_mat22 G_bP = zeros<cx_mat>(2,2);  // bar-lead
    cx_mat22 G_Pb = zeros<cx_mat>(2,2);  // lead-bar


    // not check!!! lead-bar
    G_Pb(0, 0) = G_ls(13 - 1, 11 - 1);
    G_Pb(0, 1) = G_ls(13 - 1, 12 - 1);
    G_Pb(1, 0) = G_ls(14 - 1, 11 - 1);
    G_Pb(1, 1) = G_ls(14 - 1, 12 - 1);

    // not check!!! bar-lead
    G_bP(0, 0) = G_ls(11 - 1, 13 - 1);
    G_bP(0, 1) = G_ls(11 - 1, 14 - 1);
    G_bP(1, 0) = G_ls(12 - 1, 13 - 1);
    G_bP(1, 1) = G_ls(12 - 1, 14 - 1);

    cx_mat22 netG = G_Pb - G_bP;
    // netG = netG*np.mat([[0,1],[1,0]]) # pauli x
    netG = netG * cx_mat22({0, 1, 1, 0});  // pauli x
    cx_double trace_netG = netG(0, 0) + netG(1, 1);


    return (trace_netG).real();
}



double Chain::unname_z(const double o1, const double o2, const double E)
{
    cx_mat G_ls = this->G_L(o1, o2, E);
    cx_mat22 G_bP = zeros<cx_mat>(2,2);  // bar-lead
    cx_mat22 G_Pb = zeros<cx_mat>(2,2);  // lead-bar


    // not check!!! lead-bar
    G_Pb(0, 0) = G_ls(13 - 1, 11 - 1);
    G_Pb(0, 1) = G_ls(13 - 1, 12 - 1);
    G_Pb(1, 0) = G_ls(14 - 1, 11 - 1);
    G_Pb(1, 1) = G_ls(14 - 1, 12 - 1);

    // not check!!! bar-lead
    G_bP(0, 0) = G_ls(11 - 1, 13 - 1);
    G_bP(0, 1) = G_ls(11 - 1, 14 - 1);
    G_bP(1, 0) = G_ls(12 - 1, 13 - 1);
    G_bP(1, 1) = G_ls(12 - 1, 14 - 1);

    cx_mat22 netG = G_Pb - G_bP;
    // netG = netG*np.mat([[0,1],[1,0]]) # pauli x
    netG = netG * cx_mat22({1, 0, 0, -1});  // pauli z
    cx_double trace_netG = netG(0, 0) + netG(1, 1);


    return (trace_netG).real();
}


std::vector<double> Chain::unname2(const double o1, const double o2, const double E)
{
    cx_mat G_ls = this->G_L(o1, o2, E);
    cx_mat22 G_bP = zeros<cx_mat>(2,2);  // bar-lead
    cx_mat22 G_Pb = zeros<cx_mat>(2,2);  // lead-bar


    // not check!!! lead-bar
    G_Pb(0, 0) = G_ls(13 - 1, 11 - 1);
    G_Pb(0, 1) = G_ls(13 - 1, 12 - 1);
    G_Pb(1, 0) = G_ls(14 - 1, 11 - 1);
    G_Pb(1, 1) = G_ls(14 - 1, 12 - 1);

    // not check!!! bar-lead
    G_bP(0, 0) = G_ls(11 - 1, 13 - 1);
    G_bP(0, 1) = G_ls(11 - 1, 14 - 1);
    G_bP(1, 0) = G_ls(12 - 1, 13 - 1);
    G_bP(1, 1) = G_ls(12 - 1, 14 - 1);

    cx_mat22 netG = G_Pb - G_bP;




    cx_mat22 netG_x = netG * cx_mat22({0, 1, 1, 0}); // pauli x
    cx_mat22 netG_y = netG * cx_mat22({0, -cx_double(0,1), cx_double(0,1), 0});  // pauli y
    cx_mat22 netG_z = netG * cx_mat22({1, 0, 0, -1}); // pauli z

    cx_double trace_netG_x = netG_x(0, 0) + netG_x(1, 1);
    cx_double trace_netG_y = netG_y(0, 0) + netG_y(1, 1);
    cx_double trace_netG_z = netG_z(0, 0) + netG_z(1, 1);

    std::vector<double> result(3);
    result[0] = trace_netG_x.real();
    result[1] = trace_netG_y.real();
    result[2] = trace_netG_z.real();
    return result;
}









