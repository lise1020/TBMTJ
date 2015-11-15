#include "Lead.h"



Lead::Lead(const double e_up, const double e_dn, const double t_up, const double t_dn, const double temperature, const double gamma, const double bias):
Atom(e_up, e_dn, t_up, t_dn, gamma, bias)
{
    this->numAtom = 1;
    this->temperature = temperature;
}



cx_mat22 Lead::G_inf(const double x1, const double x2, const double o1, const double o2, const double E)
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



cx_mat22 Lead::G_sinf(const double x1, const double x2, const double o1, const double o2, const double E)
{
    map<string,cx_mat22> G = {

        { "x1x2", this->G_inf(x1, x2, o1, o2, E) },
        { "x1 0", this->G_inf(x1,  0, o1, o2, E) },
        { "x1-1", this->G_inf(x1, -1, o1, o2, E) },
        { "-8-1", this->G_inf(-8, -1, o1, o2, E) },
        { "-8 0", this->G_inf(-8,  0, o1, o2, E) },
        { "-1x2", this->G_inf(-1, x2, o1, o2, E) }
    };
    /*G["x1x2"] = this->G_inf(x1, x2, o1, o2, E);
    G["x1 0"] = this->G_inf(x1,  0, o1, o2, E);
    G["x1-1"] = this->G_inf(x1, -1, o1, o2, E);
    G["-8-1"] = this->G_inf(-8, -1, o1, o2, E);
    G["-8 0"] = this->G_inf(-8,  0, o1, o2, E);
    G["-1x2"] = this->G_inf(-1, x2, o1, o2, E);*/ ///TODO SAVE about 0.1 sec for 1000 runs

    cx_mat22 innerTerm = G["x1 0"] - G["-8 0"]*G["-8-1"].i()*G["x1-1"];
    return G["x1x2"] - innerTerm*this->hopping*G["-1x2"];
}



cx_mat22 Lead::S(const double o1, const double o2, const double E)
{
    HoppingElement T = this->hopping;
    cx_mat22 g = this->G_sinf(0, 0, o1, o2, E);
    return T*g*T;
}



mat22 Lead::H(const double o1, const double o2)
{
    return this->onsiteE.inKspace(o1, o2);
}



