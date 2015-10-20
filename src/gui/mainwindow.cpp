#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setEnabled(false);
    ui->action_Run->setEnabled(false);
    ui->action_Stop->setEnabled(false);

    connect(ui->action_Open_Example, SIGNAL(triggered(bool)), this, SLOT(onClick_openExample()));
    connect(ui->action_Run, SIGNAL(triggered(bool)), this, SLOT(onClick_runProject()));
    connect(ui->pushButton_plot_Tnml, SIGNAL(clicked(bool)), this, SLOT(onClick_plot()));

}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::onClick_openExample()
{
    //TODO
    QDir rootDir = QDir( QCoreApplication::applicationDirPath() );
    rootDir.cdUp();
    QString examplePath = rootDir.path() + "/examples";
    QString filename = QFileDialog::getOpenFileName(this, "Open Example Project", examplePath, "*.xml");
    this->myProject = TBProject(filename);
    this->renewParameterPanel();

    ui->centralwidget->setEnabled(true);
    ui->action_Run->setEnabled(true);
    ui->action_Stop->setEnabled(true);
}



void MainWindow::onClick_runProject()
{
    //QLabel* label = new QLabel("Process running");
    //ui->statusbar->addWidget(label);
    this->myProject.run();
    //ui->statusbar->removeWidget(label);
}



void MainWindow::onClick_plot()
{
    //
}



void MainWindow::renewParameterPanel()
{
    ChainSpec userParameters = myProject.getUserParameters();
    QMap< QString,QDomNode > database = myProject.getDatabase();

    this->ui->lineEdit_1_1->setText( userParameters.materials[0].e_up );
    this->ui->lineEdit_1_2->setText( userParameters.materials[0].e_dn );
    this->ui->lineEdit_1_3->setText( userParameters.materials[0].t_up );
    this->ui->lineEdit_1_4->setText( userParameters.materials[0].t_dn );
    this->ui->lineEdit_1_5->setText( userParameters.materials[0].gamma );
    this->ui->lineEdit_1_6->setText( userParameters.materials[0].thickness );
    this->ui->lineEdit_1_7->setText( userParameters.materials[0].temperature );

    this->ui->lineEdit_2_1->setText( userParameters.materials[1].e_up );
    this->ui->lineEdit_2_2->setText( userParameters.materials[1].e_dn );
    this->ui->lineEdit_2_3->setText( userParameters.materials[1].t_up );
    this->ui->lineEdit_2_4->setText( userParameters.materials[1].t_dn );
    this->ui->lineEdit_2_5->setText( userParameters.materials[1].gamma );
    this->ui->lineEdit_2_6->setText( userParameters.materials[1].thickness );
    this->ui->lineEdit_2_7->setText( userParameters.materials[1].temperature );

    this->ui->lineEdit_3_1->setText( userParameters.materials[2].e_up );
    this->ui->lineEdit_3_2->setText( userParameters.materials[2].e_dn );
    this->ui->lineEdit_3_3->setText( userParameters.materials[2].t_up );
    this->ui->lineEdit_3_4->setText( userParameters.materials[2].t_dn );
    this->ui->lineEdit_3_5->setText( userParameters.materials[2].gamma );
    this->ui->lineEdit_3_6->setText( userParameters.materials[2].thickness );
    this->ui->lineEdit_3_7->setText( userParameters.materials[2].temperature );

    this->ui->lineEdit_coupling_1->setText( userParameters.couplings[0] );
    this->ui->lineEdit_coupling_2->setText( userParameters.couplings[1] );

    //TODO
    this->ui->comboBox_material_1->addItem( userParameters.materials[0].name );
    this->ui->comboBox_material_2->addItem( userParameters.materials[1].name );
    this->ui->comboBox_material_3->addItem( userParameters.materials[2].name );
}
