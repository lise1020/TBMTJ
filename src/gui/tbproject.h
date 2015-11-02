#ifndef TBPROJECT_H
#define TBPROJECT_H
#include <QMap>
#include <QDomNode>
#include "spec.h"



class TBProject
{
public:
    TBProject();
    TBProject(QString filename);
    ChainSpec getUserParameters();
    void setUserParameters(const ChainSpec &data);
    void loadProject(QString filename);
    bool saveProject();
    void run(); // ?

private:
    ChainSpec userParameters = ChainSpec();
    QString projectFilename = "";
};



#endif // TBPROJECT_H
