#include "Lead.h"



Lead::Lead(double e_up, double e_dn, double t_up, double t_dn, double temperature, double gamma, double bias):
Atom(e_up, e_dn, t_up, t_dn, gamma, bias)
{
    this->numAtom = 1;
    this->temperature = temperature;
}



cx_mat22 Lead::G_inf(double x1, double x2, double o1, double o2, double E)
{
    cx_double Ed(E,d);

    auto get_gf = [&](double t, double e0) -> cx_double
    {
        double e = e0 + 2 * t * (cos(o1) + cos(o2));
        cx_double term1 = (Ed - e) / (2*t);
        cx_double n = term1 + cx_double(0,1) * sqrt( 1.0 - pow(term1,2) );
        cx_double d = sqrt( 4*pow(t,2) - pow(Ed-e,2) );
        return -cx_double(0,1) * pow(n, abs(x1-x2)) / d;
    };


    cx_double g_up = get_gf(this->t_up, this->e_up);
    cx_double g_dn = get_gf(this->t_dn, this->e_dn);

    cx_mat22 G_E = {g_up, 0, 0, g_dn};
    return unitaryTransform(G_E,this->gamma);
}



cx_mat22 Lead::G_sinf(double x1, double x2, double o1, double o2, double E)
{
    map<string,cx_mat22> G = {

        { "x1x2", this->G_inf(x1, x2, o1, o2, E) },
        { "x1 0", this->G_inf(x1,  0, o1, o2, E) },
        { "x1-1", this->G_inf(x1, -1, o1, o2, E) },
        { "-8-1", this->G_inf(-8, -1, o1, o2, E) },
        { "-8 0", this->G_inf(-8,  0, o1, o2, E) },
        { "-1x2", this->G_inf(-1, x2, o1, o2, E) }
    };

    cx_mat22 innerTerm = G["x1 0"] - G["-8 0"]*G["-8-1"].i()*G["x1-1"];
    return G["x1x2"] - innerTerm*this->hopping*G["-1x2"];
}



cx_mat22 Lead::S(double o1, double o2, double E)
{
    HoppingElement T = this->hopping;
    cx_mat22 g = this->G_sinf(0, 0, o1, o2, E);
    return T*g*T;
}



mat22 Lead::H(double o1, double o2)
{
    return this->onsiteE.inKspace(o1, o2);
}



