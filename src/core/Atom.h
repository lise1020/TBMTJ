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

    Atom(){}
    Atom(const double e_up, const double e_dn, const double t_up, const double t_dn, const double gamma, const double bias);
};



#endif // ATOM_H
