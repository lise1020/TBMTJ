#include "lib.h"



mat22 toSpinSpace(double up, double dn, double gamma)
{
    mat22 T = {up, 0, 0, dn};
    return unitaryTransform(T,gamma);
}



double fermiD(double E, double T)
{
    double kB = 8.6173324E-5;
    return 1.0 / (exp(E / (kB * T)) + 1.0);
}



OnsiteEnergy::OnsiteEnergy(double e_up, double e_dn, double t_up, double t_dn, double gamma):
mat22(toSpinSpace(e_up, e_dn, gamma))
{
    this->gamma = gamma;
    this->e_up = e_up;
    this->e_dn = e_dn;
    this->t_up = t_up;
    this->t_dn = t_dn;
}



mat22 OnsiteEnergy::inKspace(double o1, double o2)
{
    double e_up_k = this->e_up + 2 * this->t_up * (cos(o1) + cos(o2));
    double e_dn_k = this->e_dn + 2 * this->t_dn * (cos(o1) + cos(o2));
    return toSpinSpace(e_up_k, e_dn_k, this->gamma);
}



HoppingElement::HoppingElement(double t_up, double t_dn, double gamma):
mat22(toSpinSpace(t_up, t_dn, gamma))
{
    //nothing
}



