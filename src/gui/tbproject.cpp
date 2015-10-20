#include "tbproject.h"
#include "PythonQtScriptingConsole.h"



TBProject::TBProject()
{

}



void TBProject::initDatabase()
{
    QDir rootDir = QDir( QCoreApplication::applicationDirPath() );
    rootDir.cdUp();
    QString resPath = rootDir.path() + "/res";
    QString filename = resPath + "/database.xml";


    QDomDocument dom;
    QFile *file = new QFile(filename);
    if (file->open(QIODevice::ReadOnly))
    {
        dom.setContent(file); // 此处需做错误判断
    }
    file->close();


    QDomNodeList materials = dom.elementsByTagName("material");
    for(int i=0; i<materials.count(); i++)
    {
        QDomNode material = materials.item(i);
        QString materialName = material.toElement().attribute("name");
        this->database.insert( materialName,material );
    }
}



TBProject::TBProject(QString filename)
{
    this->initDatabase();

    //// Open file
    QDomDocument dom;
    QFile *file = new QFile(filename);
    if (file->open(QIODevice::ReadOnly))
    {
        dom.setContent(file); // 此处需做错误判断
    }
    file->close();


    /// Get terms: general
    //QDomNodeList generals = dom.elementsByTagName("general");
    //QDomNode general = generals.item(0);
    //ui->lineEdit_bias->setText( general.toElement().attribute("bias") );


    this->userParameters = ChainSpec();

    /// Get terms: material
    QDomNodeList materials = dom.elementsByTagName("material");
    for(int i=0; i<materials.count(); i++)
    {
        MaterialSpec materialSpec = MaterialSpec();

        QDomNode material = materials.item(i);
        QString materialName = material.toElement().attribute("name");
        materialSpec.name = materialName;
        materialSpec.e_up = this->database[materialName].toElement().attribute("e_up");
        materialSpec.e_dn = this->database[materialName].toElement().attribute("e_dn");
        materialSpec.t_up = this->database[materialName].toElement().attribute("t_up");
        materialSpec.t_dn = this->database[materialName].toElement().attribute("t_dn");
        materialSpec.gamma = material.toElement().attribute("gamma");
        materialSpec.thickness = material.toElement().attribute("thickness");
        materialSpec.temperature = material.toElement().attribute("temperature");
        materialSpec.lBias = material.toElement().attribute("lBias");
        materialSpec.rBias = material.toElement().attribute("rBias");

        this->userParameters.materials.append(materialSpec);
    }


    /// Get terms: coupling
    QDomNodeList couplings = dom.elementsByTagName("coupling");
    for(int i=0; i<couplings.count(); i++)
    {
        QDomNode coupling = couplings.item(i);
        QString value = coupling.toElement().attribute("value");
        this->userParameters.couplings.append(value);
    }
}



ChainSpec TBProject::getUserParameters()
{
    return this->userParameters;
}

QMap< QString,QDomNode > TBProject::getDatabase()
{
    return this->database;
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



    mainModule.addVariable("userParameters_c", userParameters.toQVariant());
    mainModule.evalFile(":TBApp.py");
}

