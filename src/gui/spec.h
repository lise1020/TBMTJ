#ifndef SPEC
#define SPEC

#include <QVector>
#include <QVariant>



class MaterialSpec
{
public:
    QString name;
    QString thickness;
    QString e_up, e_dn;
    QString t_up, t_dn;
    QString gamma, temperature;
    QString lBias, rBias;
    MaterialSpec(){}
    QVariant toQVariant();
};



class ChainSpec
{
public:
    QVector<MaterialSpec> materials;
    QVector<QString> couplings;
    ChainSpec(){}
    QVariant toQVariant();
};



#endif // SPEC

