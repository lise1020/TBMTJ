#include "Atom.h"



Atom::Atom(const double e_up, const double e_dn, const double t_up, const double t_dn, const double gamma, const double bias)
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



OnsiteEnergy& Atom::getOnsiteEnergy()
{
    return onsiteE;
}



HoppingElement& Atom::getHoppingElement()
{
    return hopping;
}
