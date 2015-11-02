#include "tbproject.h"
#include "PythonQtScriptingConsole.h"
#include <QDir>
#include <QApplication>
#include <PythonQt.h>
#include <QXmlStreamWriter>



TBProject::TBProject()
{
    //
}



TBProject::TBProject(QString filename)
{
    projectFilename = filename;
}



void TBProject::loadProject(QString filename)
{
    projectFilename = filename;


    //// Open file
    QDomDocument dom;
    QFile* file = new QFile(projectFilename);
    if (file->open(QIODevice::ReadOnly)) dom.setContent(file);
    file->close();
    delete file;


    /// Get terms: Lead
    QDomNodeList leads = dom.elementsByTagName("lead");
    for(int i=0; i<2; i++)
    {
        LeadSpec leadSpec = LeadSpec();

        QDomNode lead = leads.item(i);
        leadSpec.name = lead.toElement().attribute("name");
        leadSpec.e_up = lead.toElement().attribute("e_up");
        leadSpec.e_dn = lead.toElement().attribute("e_dn");
        leadSpec.t_up = lead.toElement().attribute("t_up");
        leadSpec.t_dn = lead.toElement().attribute("t_dn");
        leadSpec.gamma = lead.toElement().attribute("gamma");
        leadSpec.temperature = lead.toElement().attribute("temperature");

        userParameters.leads.append(leadSpec);
    }


    /// Get terms: Barrier
    QDomNodeList barriers = dom.elementsByTagName("barrier");
    for(int i=0; i<barriers.count(); i++)
    {
        BarrierSpec barrierSpec = BarrierSpec();

        QDomNode barrier = barriers.item(i);
        barrierSpec.name = barrier.toElement().attribute("name");
        barrierSpec.e_up = barrier.toElement().attribute("e_up");
        barrierSpec.e_dn = barrier.toElement().attribute("e_dn");
        barrierSpec.t_up = barrier.toElement().attribute("t_up");
        barrierSpec.t_dn = barrier.toElement().attribute("t_dn");
        barrierSpec.gamma = barrier.toElement().attribute("gamma");

        userParameters.barriers.append(barrierSpec);
    }
}



bool TBProject::saveProject()
{
    /// Open file
    QFile file(projectFilename);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Error: Cannot write file: "
                 << qPrintable(file.errorString());
        return false;
    }


    /// Write to file
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("project");
    for(int i=0; i<userParameters.leads.count(); i++)
    {
        LeadSpec lead = userParameters.leads[i];
        xmlWriter.writeStartElement("lead");
        xmlWriter.writeAttribute("e_up",lead.e_up);
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();


    /// Close file
    file.close();
    if (file.error())
    {
        qDebug() << "Error: Cannot write file: "
                 << qPrintable(file.errorString());
        return false;
    }
    return true;
}



ChainSpec TBProject::getUserParameters()
{
    return this->userParameters;
}



void TBProject::setUserParameters(const ChainSpec& data)
{
    userParameters = data;
}



void TBProject::run()
{
    std::cout << "Run!" << std::endl;
    PythonQt::init();
    PythonQtObjectPtr mainModule = PythonQt::self()->getMainModule();
    PythonQtScriptingConsole console(NULL, mainModule);
    //console.show();


    QDir rootDir = QDir( QCoreApplication::applicationDirPath() );
    rootDir.cdUp();
    QString libPath = rootDir.path() + "/lib";
    mainModule.evalScript(QString("import sys\n"));
    mainModule.evalScript(QString("sys.path.append('%1')\n").arg(libPath));
    mainModule.evalScript(QString("sys.path.append('%1')\n").arg("/usr/local/lib/python3.4/dist-packages"));
    mainModule.evalScript(QString("sys.path.append('%1')\n").arg("/usr/lib/python3/dist-packages"));



    //mainModule.addVariable("userParameters_c", userParameters.toQVariant());
    mainModule.evalFile(":TBApp.py");
}

