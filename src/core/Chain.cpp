#include "Chain.h"
#include <cstdarg>



Chain::Chain(const Lead& lL, const arma::mat& T1, const Insulator& B, const arma::mat& T2, const Lead& lR)
{
    this->leadL = lL;
    this->leadR = lR;
    this->barrier = B;

    this->T1 = T1;
    this->T2 = T2;
}



Chain::Chain(const Lead& lL, const std::string& T1, const Insulator& B, const std::string& T2, const Lead& lR)
{
    this->leadL = lL;
    this->leadR = lR;
    this->barrier = B;

    this->T1 = mat22(T1);
    this->T2 = mat22(T2);
}



Chain Chain::operator<<(const Lead& obj)
{
    this->leadL = obj;
}

Chain Chain::operator<<(const Insulator& obj)
{
    this->barrier2.push_back(obj);
}

Chain Chain::operator<<(const std::string& obj)
{
    this->TT.push_back(obj);
}



mat Chain::H(const double o1, const double o2)
{
    //---------------------------//
    // pure H terms

    mat H_L = leadL.H(o1, o2);
    mat H_R = leadR.H(o1, o2);
    mat H_B = barrier.H(o1, o2);

    mat tmp[] = {H_L, H_B, H_R};
    mat H = blockDiag(tmp);

    //---------------------------//
    // pure T terms

    int sizeBarrier = 2*(barrier.numAtom);
    mat tmp2[] = {T1, zeros<mat>(sizeBarrier-2,sizeBarrier-2), T2};
    mat T = blockDiag(tmp2);

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

    cx_mat S_L = this->leadL.S(o1, o2, E);
    cx_mat S_R = this->leadR.S(o1, o2, E);

    int sizeBarrier = 2*(this->barrier.numAtom);
    cx_mat tmp[] = {S_L, zeros<cx_mat>(sizeBarrier,sizeBarrier), S_R};
    cx_mat S = blockDiag(tmp);

    return (EI - H - S).i();
}



cx_mat Chain::G_L(const double o1, const double o2, const double E)
{
    //----------------------//
    // Sigma in 2x2

    double fL = fermiD(E-barrier.bias_l, leadL.temperature);
    double fR = fermiD(E-barrier.bias_r, leadR.temperature);

    cx_mat22 S_L = leadL.S(o1, o2, E);
    cx_mat22 S_R = leadR.S(o1, o2, E);

    cx_mat22 S0_lesser_L = fL*(S_L.t() - S_L);
    cx_mat22 S0_lesser_R = fR*(S_R.t() - S_R);

    //----------------------//
    // the Big Sigma

    int dim_L = 2*(leadL.numAtom + barrier.numAtom);
    int dim_R = 2*(leadR.numAtom + barrier.numAtom);
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









