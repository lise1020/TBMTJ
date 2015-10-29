#ifndef INSULATOR_H
#define INSULATOR_H
#include "general.h"
#include "Atom.h"



class Insulator
{
public:

    double gamma;
    int numAtom;
    double bias_l, bias_r;
    std::vector<Atom> atoms;

    Insulator(){}
    Insulator(const double e_up, const double e_dn, const double t_up, const double t_dn, const int numAtom, const double gamma=0.0, const double bias_l=0, const double bias_r=0);
    mat H(const double o1, const double o2);


private:
    std::vector<Atom> initAtoms(const double e_up, const double e_dn, const double t_up, const double t_dn, const double gamma, const double numAtom, const double bias_l=0, const double bias_r=0);
};



#endif // INSULATOR_H
