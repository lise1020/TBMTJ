#include "Insulator.h"



Insulator::Insulator(double e_up, double e_dn, double t_up, double t_dn, int numAtom, double gamma, double bias_l, double bias_r)
{
    this->gamma = gamma;
    this->numAtom = numAtom;
    this->bias_l = bias_l;
    this->bias_r = bias_r;
    this->atoms = this->initAtoms(e_up, e_dn, t_up, t_dn, gamma, numAtom, bias_l, bias_r);
}



vector<Atom> Insulator::initAtoms(double e_up, double e_dn, double t_up, double t_dn, double gamma, double numAtom, double bias_l, double bias_r)
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



mat Insulator::H(double o1, double o2)
{
    mat* arrE = new mat[numAtom];
    mat* arrT = new mat[numAtom-1];
    //unique_ptr< mat[] > arrE( new mat[numAtom] );
    //unique_ptr< mat[] > arrT( new mat[numAtom-1] );

    //---------------------------//
    // pure H terms

    for(int i=0; i<numAtom; i++)
    {
        arrE[i] = this->atoms[i].onsiteE.inKspace(o1, o2);
    }
    for(int i=0; i<numAtom-1; i++)
    {
        arrT[i] = this->atoms[i].hopping;
    }


    if(numAtom <= 1) return arrE[0];
    mat E = blockDiag(numAtom,arrE);
    mat T = blockDiag(numAtom-1,arrT);

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


