#ifndef SPEC
#define SPEC
#include <QVector>



struct LeadSpec
{
    QString name="";
    QString e_up="";
    QString e_dn="";
    QString t_up="";
    QString t_dn="";
    QString gamma="";
    QString temperature="";
};



struct BarrierSpec
{
    QString name="";
    QString e_up="";
    QString e_dn="";
    QString t_up="";
    QString t_dn="";
    QString gamma="";
    QString thickness="";
};



struct ChainSpec
{
    QVector<LeadSpec> leads;
    QVector<BarrierSpec> barriers;
    QVector<QString> couplings;
};



#endif // SPEC
