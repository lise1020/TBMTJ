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

    Insulator(){};
    Insulator(double e_up, double e_dn, double t_up, double t_dn, int numAtom, double gamma=0.0, double bias_l=0, double bias_r=0);
    mat H(double o1, double o2);


private:
    std::vector<Atom> initAtoms(double e_up, double e_dn, double t_up, double t_dn, double gamma, double numAtom, double bias_l=0, double bias_r=0);
};



#endif // INSULATOR_H
