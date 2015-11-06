#include "portalwindow.h"
#include "ui_portalwindow.h"



PortalWindow::PortalWindow(QWidget *parent): QDialog(parent), ui(new Ui::PortalWindow)
{
    ui->setupUi(this);
}



PortalWindow::~PortalWindow()
{
    delete ui;
}
