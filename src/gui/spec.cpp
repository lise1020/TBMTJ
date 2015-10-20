#include "spec.h"



QVariant MaterialSpec::toQVariant()
{
    QHash<QString, QVariant> value;
    value.insert("e_up", QVariant(e_up));
    value.insert("e_dn", QVariant(e_dn));
    value.insert("t_up", QVariant(t_up));
    value.insert("t_dn", QVariant(t_dn));
    value.insert("gamma", QVariant(gamma));
    value.insert("thickness", QVariant(thickness));
    value.insert("temperature", QVariant(temperature));
    value.insert("lBias", QVariant(lBias));
    value.insert("rBias", QVariant(rBias));

    return QVariant(value);
}



QVariant ChainSpec::toQVariant()
{
    QVector<QVariant> m;
    QVector<QVariant> c;

    for(int i=0; i<materials.length(); i++)
        m.append(materials[i].toQVariant());

    for(int i=0; i<couplings.length(); i++)
        c.append(QVariant(couplings[i]));

    QHash<QString, QVariant> value;
    value.insert("materials", QVariant(m.toList()));
    value.insert("couplings", QVariant(c.toList()));

    return QVariant(value);
}


