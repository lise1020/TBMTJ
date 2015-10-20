#ifndef TB_LIB_H
#define TB_LIB_H
#include "general.h"



class OnsiteEnergy: public mat22
{
public:

    double e_up, e_dn;
    double t_up, t_dn;
    double gamma;

    OnsiteEnergy(){};
    OnsiteEnergy(double e_up, double e_dn, double t_up, double t_dn, double gamma);
    mat22 inKspace(double o1, double o2);
};



class HoppingElement: public mat22
{
public:

    HoppingElement(){};
    HoppingElement(double t_up, double t_dn, double gamma);
};



const double d = 1E-6;

/// 2x2 GF in spin space G' = U.inv * G * U
mat22 toSpinSpace(double up, double dn, double gamma);

/// Fermi-Dirac distribution
double fermiD(double E, double T);



/// Unitary trasformation A' = U * A * U.H
template <class MAT> MAT unitaryTransform(const MAT& M, const double gamma)
{
    auto U = [](double g) -> MAT { MAT A = {cos(g/2), sin(g/2), -sin(g/2), cos(g/2)}; return A; };
    return U(gamma).i() * M * U(gamma);
}



/// Block Diagnal (two terms)
template<typename MAT> MAT blockDiag(const MAT& M1, const MAT& M2)
{
    int n_rows = M1.n_rows + M2.n_rows;
    int n_cols = M1.n_cols + M2.n_cols;
    MAT result = zeros<MAT>(n_rows,n_cols);

    result.submat( 0,0, M1.n_rows-1, M1.n_cols-1 ) = M1;
    result.submat( M1.n_rows, M1.n_cols, n_rows-1, n_cols-1 ) = M2;

    return result;
}



/// Block Diagnal (array terms)
template<typename MAT,size_t N> MAT blockDiag(const MAT (&M)[N])
{
    int n_rows = 0, n_cols = 0;

    for(unsigned i=0; i<N; i++)
    {
        n_rows += M[i].n_rows;
        n_cols += M[i].n_cols;
    }
    MAT result = zeros<MAT>(n_rows,n_cols);

    //-------------------------//

    for(unsigned i=0, posRow=0, posCol=0, posEndRow=0, posEndCol=0; i<N; i++)
    {
        posEndRow += M[i].n_rows;
        posEndCol += M[i].n_cols;

        result.submat( posRow, posCol, posEndRow-1, posEndCol-1 ) = M[i];

        posRow = posEndRow;
        posCol = posEndCol;
    }

    return result;
}



/// Block Diagnal (array terms with known size)
template<typename MAT> MAT blockDiag(const int& num, const MAT* M)
{
    int n_rows = 0, n_cols = 0;

    for(int i=0; i<num; i++)
    {
        n_rows += M[i].n_rows;
        n_cols += M[i].n_cols;
    }
    MAT result = zeros<MAT>(n_rows,n_cols);

    //-------------------------//

    for(int i=0, posRow=0, posCol=0, posEndRow=0, posEndCol=0; i<num; i++)
    {
        posEndRow += M[i].n_rows;
        posEndCol += M[i].n_cols;

        result.submat( posRow, posCol, posEndRow-1, posEndCol-1 ) = M[i];

        posRow = posEndRow;
        posCol = posEndCol;
    }

    return result;
}



#endif //TB_LIB_H


