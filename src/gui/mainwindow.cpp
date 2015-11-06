#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardPaths>
#include <QFileDialog>
#include <QCoreApplication>



MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setActive(false);
    mProject = TBProject();

    connect( ui->action_New_Project , SIGNAL(triggered(bool)), this, SLOT(onClick_newProject())  );
    connect( ui->action_Open_Project, SIGNAL(triggered(bool)), this, SLOT(onClick_openProject()) );
    connect( ui->action_Open_Example, SIGNAL(triggered(bool)), this, SLOT(onClick_openExample()) );
    connect( ui->action_Save_File   , SIGNAL(triggered(bool)), this, SLOT(onClick_saveProject()) );

    connect(ui->action_Run, SIGNAL(triggered(bool)), this, SLOT(onClick_runProject()));
}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::initUi()
{

}



void MainWindow::setActive(bool state)
{
    if(state)
    {
        ui->centralwidget->setVisible(true);
        ui->action_Run->setEnabled(true);
        ui->action_Stop->setEnabled(true);
    }
    else
    {
        ui->centralwidget->setVisible(false);
        ui->action_Run->setEnabled(false);
        ui->action_Stop->setEnabled(false);
    }
}



void MainWindow::onClick_newProject()
{
    QString home = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QString filename = QFileDialog::getSaveFileName(this, "New Project", home, "*.tb");
    filename += ".tb";
    mProject = TBProject(filename);
    setActive(true);
}



void MainWindow::onClick_openProject()
{
    QString home = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QString filename = QFileDialog::getOpenFileName(this, "Open Project", home, "*.tb");
    mProject.loadProject(filename);
    renewParameterPanel();
    setActive(true);
}



void MainWindow::onClick_openExample()
{
    QDir rootDir = QDir( QCoreApplication::applicationDirPath() ); rootDir.cdUp();
    QString examplePath = rootDir.path() + "/examples";
    QString filename = QFileDialog::getOpenFileName(this, "Open Example Project", examplePath, "*.tb");
    mProject.loadProject(filename);
    renewParameterPanel();
    setActive(true);
}



void MainWindow::onClick_saveProject()
{
    ChainSpec chainSpec;


    /// Lead
    for(int i=0; i<2; i++)
    {
        LeadSpec lead;
        lead.e_up = ui->lineEdit_1_1->text();
        lead.e_dn = ui->lineEdit_1_2->text();
        lead.t_up = ui->lineEdit_1_3->text();
        lead.t_dn = ui->lineEdit_1_4->text();
        lead.gamma = ui->lineEdit_1_5->text();
        lead.temperature = ui->lineEdit_1_7->text();
        chainSpec.leads.append(lead);
    }


    /// Barrier
    for(int i=0; i<1; i++) //TODO
    {
        BarrierSpec barrier;
        barrier.e_up = ui->lineEdit_2_1->text();
        barrier.e_dn = ui->lineEdit_2_2->text();
        barrier.t_up = ui->lineEdit_2_3->text();
        barrier.t_dn = ui->lineEdit_2_4->text();
        barrier.gamma = ui->lineEdit_2_5->text();
        barrier.thickness = ui->lineEdit_2_6->text();
        chainSpec.barriers.append(barrier);
    }


    mProject.setUserParameters(chainSpec);
    mProject.saveProject();
}



void MainWindow::onClick_runProject()
{
    //QLabel* label = new QLabel("Process running");
    //ui->statusbar->addWidget(label);
    this->mProject.run();
    //ui->statusbar->removeWidget(label);
}



void MainWindow::onClick_plot()
{
    //
}



void MainWindow::renewParameterPanel()
{
    ChainSpec userParameters = mProject.getUserParameters();

    this->ui->lineEdit_1_1->setText( userParameters.leads[0].e_up );
    this->ui->lineEdit_1_2->setText( userParameters.leads[0].e_dn );
    this->ui->lineEdit_1_3->setText( userParameters.leads[0].t_up );
    this->ui->lineEdit_1_4->setText( userParameters.leads[0].t_dn );
    this->ui->lineEdit_1_5->setText( userParameters.leads[0].gamma );
    //this->ui->lineEdit_1_6->setText( userParameters.leads[0].thickness );
    this->ui->lineEdit_1_7->setText( userParameters.leads[0].temperature );

    this->ui->lineEdit_3_1->setText( userParameters.leads[1].e_up );
    this->ui->lineEdit_3_2->setText( userParameters.leads[1].e_dn );
    this->ui->lineEdit_3_3->setText( userParameters.leads[1].t_up );
    this->ui->lineEdit_3_4->setText( userParameters.leads[1].t_dn );
    this->ui->lineEdit_3_5->setText( userParameters.leads[1].gamma );
    //this->ui->lineEdit_3_6->setText( userParameters.leads[1].thickness );
    this->ui->lineEdit_3_7->setText( userParameters.leads[1].temperature );

    this->ui->lineEdit_2_1->setText( userParameters.barriers[0].e_up );
    this->ui->lineEdit_2_2->setText( userParameters.barriers[0].e_dn );
    this->ui->lineEdit_2_3->setText( userParameters.barriers[0].t_up );
    this->ui->lineEdit_2_4->setText( userParameters.barriers[0].t_dn );
    this->ui->lineEdit_2_5->setText( userParameters.barriers[0].gamma );
    this->ui->lineEdit_2_6->setText( userParameters.barriers[0].thickness );
    //this->ui->lineEdit_2_7->setText( userParameters.barriers[0].temperature );

    //this->ui->lineEdit_coupling_1->setText( userParameters.couplings[0] );
    //this->ui->lineEdit_coupling_2->setText( userParameters.couplings[1] );

    //TODO
    //this->ui->comboBox_material_1->addItem( userParameters.materials[0].name );
    //this->ui->comboBox_material_2->addItem( userParameters.materials[1].name );
    //this->ui->comboBox_material_3->addItem( userParameters.materials[2].name );
}
