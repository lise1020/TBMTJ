#ifndef CHAIN_H
#define CHAIN_H
#include "Lead.h"
#include "Insulator.h"



class Chain
{
public:

    Lead leadL, leadR;
    Insulator barrier;
    mat22 T1, T2;

    Chain(const Lead& lL, const arma::mat& T1, const Insulator& B, const arma::mat& T2, const Lead& lR);
    Chain(const Lead& lL, const std::string& T1, const Insulator& B, const std::string& T2, const Lead& lR);
    mat H(double o1, double o2);
    cx_mat G_R(double o1, double o2, double E);
    //cx_mat G_A(double o1, double o2, double E);
    cx_mat G_L(double o1, double o2, double E);

    double unname_x(double o1, double o2, double E);
    double unname_y(double o1, double o2, double E);
    double unname_z(double o1, double o2, double E);
    std::vector<double> unname2(double o1, double o2, double E);
};



#endif // CHAIN_H
