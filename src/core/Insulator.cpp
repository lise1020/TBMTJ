#include "Insulator.h"



Insulator::Insulator(const double e_up, const double e_dn, const double t_up, const double t_dn, const int numAtom, const double gamma, const double bias_l, const double bias_r)
{
    this->gamma = gamma;
    this->numAtom = numAtom;
    this->bias_l = bias_l;
    this->bias_r = bias_r;
    this->atoms = this->initAtoms(e_up, e_dn, t_up, t_dn, gamma, numAtom, bias_l, bias_r);
}



vector<Atom> Insulator::initAtoms(const double e_up, const double e_dn, const double t_up, const double t_dn, const double gamma, const double numAtom, const double bias_l, const double bias_r)
{
    vector<Atom> atoms;
    double dV;

    for(int i=0; i<numAtom; i++)
    {
        if(numAtom <= 1) dV = 0;
        else dV = (bias_r - bias_l) / (numAtom - 1);

        double e_shift = bias_l + i * dV;
        Atom atom = Atom(e_up, e_dn, t_up, t_dn, gamma, e_shift);
        atoms.push_back(atom);
    }

    return atoms;
}



mat Insulator::H(const double o1, const double o2)
{
    mat* arrE = new mat[this->numAtom];
    mat* arrT = new mat[this->numAtom-1];
    //unique_ptr< mat[] > arrE( new mat[numAtom] );
    //unique_ptr< mat[] > arrT( new mat[numAtom-1] );

    //---------------------------//
    // pure H terms

    for(int i=0; i<numAtom; i++)
    {
        arrE[i] = atoms[i].getOnsiteEnergy().inKspace(o1, o2);
    }
    for(int i=0; i<numAtom-1; i++)
    {
        arrT[i] = atoms[i].getHoppingElement();
    }


    if(numAtom <= 1) return arrE[0];
    mat E = blockDiag(this->numAtom,arrE);
    mat T = blockDiag(this->numAtom-1,arrT);

    delete [] arrE;
    delete [] arrT;

    //---------------------------//
    // pure T terms

    mat T_up = T;
    mat T_dn = T;

    T_up.insert_cols( 0, 2);
    T_dn.insert_cols( T_dn.n_cols, 2);
    T_up.insert_rows( T_up.n_rows, 2);
    T_dn.insert_rows( 0, 2);

    return T_up + E + T_dn;
}


