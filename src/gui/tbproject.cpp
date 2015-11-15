#include "tbproject.h"
#include "ui_tbproject.h"
#include "schema3layer.h"
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>



TBProject::TBProject(QWidget *parent): QWidget(parent), ui(new Ui::TBProject)
{
    ui->setupUi(this);
}



TBProject::~TBProject()
{
    delete ui;
}



bool TBProject::readProject(const QString &filename)
{
    QString fileInString = readFileToString(filename);
    if(fileInString.isNull()) return false;

    QJsonObject root = QJsonDocument::fromJson(fileInString.toUtf8()).object();
    QJsonArray material = root.value("material").toArray();
    QJsonArray coupling = root.value("coupling").toArray();

    QJsonValue v;
    {
        QJsonObject lead = material[0].toObject();
        ui->lineEdit_lead1_1->setText( (v=lead.value("e_up"))       .isString()? v.toString(): QString::number(v.toDouble()) );
        ui->lineEdit_lead1_2->setText( (v=lead.value("e_dn"))       .isString()? v.toString(): QString::number(v.toDouble()) );
        ui->lineEdit_lead1_3->setText( (v=lead.value("t_up"))       .isString()? v.toString(): QString::number(v.toDouble()) );
        ui->lineEdit_lead1_4->setText( (v=lead.value("t_dn"))       .isString()? v.toString(): QString::number(v.toDouble()) );
        ui->lineEdit_lead1_5->setText( (v=lead.value("gamma"))      .isString()? v.toString(): QString::number(v.toDouble()) );
        ui->lineEdit_lead1_7->setText( (v=lead.value("temperature")).isString()? v.toString(): QString::number(v.toDouble()) );
    }
    {
        QJsonObject lead = material[2].toObject();
        ui->lineEdit_lead2_1->setText( (v=lead.value("e_up"))       .isString()? v.toString(): QString::number(v.toDouble()) );
        ui->lineEdit_lead2_2->setText( (v=lead.value("e_dn"))       .isString()? v.toString(): QString::number(v.toDouble()) );
        ui->lineEdit_lead2_3->setText( (v=lead.value("t_up"))       .isString()? v.toString(): QString::number(v.toDouble()) );
        ui->lineEdit_lead2_4->setText( (v=lead.value("t_dn"))       .isString()? v.toString(): QString::number(v.toDouble()) );
        ui->lineEdit_lead2_5->setText( (v=lead.value("gamma"))      .isString()? v.toString(): QString::number(v.toDouble()) );
        ui->lineEdit_lead2_7->setText( (v=lead.value("temperature")).isString()? v.toString(): QString::number(v.toDouble()) );
    }
    {
        QJsonObject lead = material[1].toObject();
        ui->lineEdit_B1_1->setText( (v=lead.value("e_up"))       .isString()? v.toString(): QString::number(v.toDouble()) );
        ui->lineEdit_B1_2->setText( (v=lead.value("e_dn"))       .isString()? v.toString(): QString::number(v.toDouble()) );
        ui->lineEdit_B1_3->setText( (v=lead.value("t_up"))       .isString()? v.toString(): QString::number(v.toDouble()) );
        ui->lineEdit_B1_4->setText( (v=lead.value("t_dn"))       .isString()? v.toString(): QString::number(v.toDouble()) );
        ui->lineEdit_B1_5->setText( (v=lead.value("gamma"))      .isString()? v.toString(): QString::number(v.toDouble()) );
        ui->lineEdit_B1_6->setText( (v=lead.value("thickness"))  .isString()? v.toString(): QString::number(v.toDouble()) );
    }
    {
        ui->lineEdit_coupling_1->setText(coupling[0].toString());
        ui->lineEdit_coupling_2->setText(coupling[1].toString());
    }


    return true;
}



bool TBProject::writeProject(const QString &filename)
{
    QJsonArray material;
    QJsonArray coupling;
    {
        QJsonObject lead;
        lead["e_up"]        = ui->lineEdit_lead1_1->text();
        lead["e_dn"]        = ui->lineEdit_lead1_2->text();
        lead["t_up"]        = ui->lineEdit_lead1_3->text();
        lead["t_dn"]        = ui->lineEdit_lead1_4->text();
        lead["gamma"]       = ui->lineEdit_lead1_5->text();
        lead["temperature"] = ui->lineEdit_lead1_7->text();
        material.append(lead);
    }
    {
        QJsonObject barrier;
        barrier["e_up"]        = ui->lineEdit_B1_1->text();
        barrier["e_dn"]        = ui->lineEdit_B1_2->text();
        barrier["t_up"]        = ui->lineEdit_B1_3->text();
        barrier["t_dn"]        = ui->lineEdit_B1_4->text();
        barrier["gamma"]       = ui->lineEdit_B1_5->text();
        barrier["thickness"]   = ui->lineEdit_B1_6->text();
        material.append(barrier);
    }
    {
        QJsonObject lead;
        lead["e_up"]        = ui->lineEdit_lead2_1->text();
        lead["e_dn"]        = ui->lineEdit_lead2_2->text();
        lead["t_up"]        = ui->lineEdit_lead2_3->text();
        lead["t_dn"]        = ui->lineEdit_lead2_4->text();
        lead["gamma"]       = ui->lineEdit_lead2_5->text();
        lead["temperature"] = ui->lineEdit_lead2_7->text();
        material.append(lead);
    }
    {
        coupling.append( ui->lineEdit_coupling_1->text() );
        coupling.append( ui->lineEdit_coupling_2->text() );
    }

    QJsonObject root;
    root["material"] = material;
    root["coupling"] = coupling;
    QString jdoc = QJsonDocument(root).toJson(QJsonDocument::Indented);
    return writeStringToFile(filename, jdoc);
}



QString TBProject::readFileToString(const QString& filename)
{
    /// Open file and read
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, tr("TB Project"), tr("Cannot read file %1:\n%2.").arg(file.fileName()).arg(file.errorString()));
        return QString();
    }
    QString fileInString = file.readAll();


    /// Close file and return
    file.close();
    if(file.error())
    {
        QMessageBox::warning(this, tr("TB Project"), tr("Cannot write file %1:\n%2.").arg(file.fileName()).arg(file.errorString()));
        return QString();
    }
    return fileInString;
}



bool TBProject::writeStringToFile(const QString& filename, const QString& string)
{
    /// Open file and write
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, tr("TB Project"), tr("Cannot write file %1:\n%2.").arg(file.fileName()).arg(file.errorString()));
        return false;
    }
    file.write(string.toStdString().c_str());


    /// Close file and return
    file.close();
    if(file.error())
    {
        QMessageBox::warning(this, tr("TB Project"), tr("Cannot write file %1:\n%2.").arg(file.fileName()).arg(file.errorString()));
        return false;
    }
    return true;
}
