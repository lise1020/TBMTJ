#include "tbproject.h"
#include "ui_tbproject.h"
#include "schema3layer.h"
#include <QMessageBox>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>



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
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, tr("TB Project"), tr("Cannot read file %1:\n%2.").arg(file.fileName()).arg(file.errorString()));
        return false;
    }


    QXmlStreamReader reader(&file);
    //TODO read file



    return true;
}



bool TBProject::writeProject(const QString &filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, tr("TB Project"), tr("Cannot write file %1:\n%2.").arg(file.fileName()).arg(file.errorString()));
        return false;
    }


    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("chain");
    {
        writer.writeStartElement("lead");
        writer.writeAttribute("e_up"       , ui->lineEdit_lead1_1->text());
        writer.writeAttribute("e_dn"       , ui->lineEdit_lead1_2->text());
        writer.writeAttribute("t_up"       , ui->lineEdit_lead1_3->text());
        writer.writeAttribute("t_dn"       , ui->lineEdit_lead1_4->text());
        writer.writeAttribute("angle"      , ui->lineEdit_lead1_5->text());
        writer.writeAttribute("temperature", ui->lineEdit_lead1_7->text());
        writer.writeEndElement();
    }
    {
        writer.writeStartElement("coupling");
        writer.writeAttribute("value",ui->lineEdit_coupling_1->text());
        writer.writeEndElement();
    }
    {
        writer.writeStartElement("barrier");
        writer.writeAttribute("e_up"       , ui->lineEdit_B1_1->text());
        writer.writeAttribute("e_dn"       , ui->lineEdit_B1_2->text());
        writer.writeAttribute("t_up"       , ui->lineEdit_B1_3->text());
        writer.writeAttribute("t_dn"       , ui->lineEdit_B1_4->text());
        writer.writeAttribute("angle"      , ui->lineEdit_B1_5->text());
        writer.writeAttribute("thickness"  , ui->lineEdit_B1_6->text());
        writer.writeEndElement();
    }
    {
        writer.writeStartElement("coupling");
        writer.writeAttribute("value",ui->lineEdit_coupling_2->text());
        writer.writeEndElement();
    }
    {
        writer.writeStartElement("lead");
        writer.writeAttribute("e_up"       , ui->lineEdit_lead2_1->text());
        writer.writeAttribute("e_dn"       , ui->lineEdit_lead2_2->text());
        writer.writeAttribute("t_up"       , ui->lineEdit_lead2_3->text());
        writer.writeAttribute("t_dn"       , ui->lineEdit_lead2_4->text());
        writer.writeAttribute("angle"      , ui->lineEdit_lead2_5->text());
        writer.writeAttribute("temperature", ui->lineEdit_lead2_7->text());
        writer.writeEndElement();
    }
    writer.writeEndElement();
    writer.writeEndDocument();


    file.close();
    if(file.error())
    {
        QMessageBox::warning(this, tr("TB Project"), tr("Cannot write file %1:\n%2.").arg(file.fileName()).arg(file.errorString()));
        return false;
    }
    return true;
}
