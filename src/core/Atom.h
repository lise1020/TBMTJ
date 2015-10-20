#ifndef ATOM_H
#define ATOM_H
#include "general.h"
#include "lib.h"



class Atom
{
public:

    double gamma, bias;
    double e_up, e_dn;
    double t_up, t_dn;
    OnsiteEnergy onsiteE;
    HoppingElement hopping;

    Atom(){};
    Atom(double e_up, double e_dn, double t_up, double t_dn, double gamma, double bias);
};



#endif // ATOM_H
