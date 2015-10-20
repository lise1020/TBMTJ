#include "Atom.h"



Atom::Atom(double e_up, double e_dn, double t_up, double t_dn, double gamma, double bias)
{
    this->gamma = gamma;
    this->bias = bias;
    this->onsiteE = OnsiteEnergy(e_up+bias, e_dn+bias, t_up, t_dn, gamma);
    this->hopping = HoppingElement(t_up, t_dn, gamma);

    this->e_up = e_up + bias;
    this->e_dn = e_dn + bias;
    this->t_up = t_up;
    this->t_dn = t_dn;
}

