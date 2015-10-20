#ifndef TBPROJECT_H
#define TBPROJECT_H

#include <QDomNode>
#include <QMap>
#include <QFile>
#include <QDir>
#include <QApplication>
#include <PythonQt.h>
#include "spec.h"

class TBProject
{
public:
    TBProject();
    TBProject(QString filename);
    void asNewProject();
    ChainSpec getUserParameters();
    QMap< QString,QDomNode > getDatabase();
    void run();

private:
    ChainSpec userParameters;
    QMap< QString,QDomNode > database;
    void initDatabase();
};

#endif // TBPROJECT_H
