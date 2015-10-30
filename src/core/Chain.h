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

    vector<Insulator> barrier2;
    vector<mat22> TT;
    vector<Lead> lead;


    /// (lL)-(T1)-(B)-(T2)-(lR)
    Chain(const Lead& lL, const arma::mat& T1, const Insulator& B, const arma::mat& T2, const Lead& lR);
    Chain(const Lead& lL, const std::string& T1, const Insulator& B, const std::string& T2, const Lead& lR);

    Chain& operator<<(const Lead& obj);
    Chain& operator<<(const Insulator& obj);
    Chain& operator<<(const std::string& obj);

       mat H(const double o1, const double o2);
    cx_mat G_R(const double o1, const double o2, const double E);
  //cx_mat G_A(const double o1, const double o2, const double E);
    cx_mat G_L(const double o1, const double o2, const double E);

	//TODO
    double unname_x(double o1, double o2, double E);
    double unname_y(double o1, double o2, double E);
    double unname_z(double o1, double o2, double E);
    std::vector<double> unname2(double o1, double o2, double E);


/*private:

	   mat   _H;
	cx_mat _G_R;
	cx_mat _G_L;*/

};



#endif // CHAIN_H
