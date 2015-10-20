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

    Lead(){};
    Lead(double e_up, double e_dn, double t_up, double t_dn, double temperature, double gamma=0.0, double bias=0.0);
    cx_mat22 G_inf(double x1, double x2, double o1, double o2, double E);
    cx_mat22 G_sinf(double x1, double x2, double o1, double o2, double E);
    cx_mat22 S(double o1, double o2, double E);
    mat22 H(double o1, double o2);
};



#endif // LEAD_H
