#ifndef LEAD_H
#define LEAD_H
#include "general.h"
#include "lib.h"
#include "Atom.h"



class Lead: public Atom
{
public:

    int numAtom;
    double temperature;

    Lead(){}
    Lead(const double e_up, const double e_dn, const double t_up, const double t_dn, const double temperature, const double gamma=0.0, const double bias=0.0);
    cx_mat22 G_inf(const double x1, const double x2, const double o1, const double o2, const double E);
    cx_mat22 G_sinf(const double x1, const double x2, const double o1, const double o2, const double E);
    cx_mat22 S(const double o1, const double o2, const double E);
    mat22 H(const double o1, const double o2);
};



#endif // LEAD_H
