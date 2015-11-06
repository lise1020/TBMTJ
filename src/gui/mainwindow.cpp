#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "portalwindow.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QCloseEvent>



MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    project = new TBProject;
    setCentralWidget(project);
    setAttribute(Qt::WA_DeleteOnClose);

    connect( ui->action_newProject , SIGNAL(triggered(bool)), this, SLOT(onClick_newProject())  );
    connect( ui->action_openProject, SIGNAL(triggered(bool)), this, SLOT(onClick_openProject()) );
    connect( ui->action_openExample, SIGNAL(triggered(bool)), this, SLOT(onClick_openExample()) );
    connect( ui->action_save       , SIGNAL(triggered(bool)), this, SLOT(onClick_save())        );
    connect( ui->action_saveAs     , SIGNAL(triggered(bool)), this, SLOT(onClick_saveAs())      );
    connect( ui->action_close      , SIGNAL(triggered(bool)), this, SLOT(close())               );
    connect( ui->action_exit       , SIGNAL(triggered(bool)), qApp, SLOT(closeAllWindows())     );
    connect( ui->action_about      , SIGNAL(triggered(bool)), this, SLOT(onClick_about())       );
}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::onClick_newProject()
{
    MainWindow* mainWindow = new MainWindow;
    mainWindow->show();
    //PortalWindow* portal = new PortalWindow(this);
    //portal->show();
    //portal->raise();
    //portal->activateWindow();
    // TODO: portal
}



void MainWindow::onClick_openProject()
{
    QString home = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Project"), home, tr("TBMTJ files (*.tb)"));
    if(!filename.isEmpty()) loadFile(filename);
}



void MainWindow::onClick_openExample()
{
    // TODO: open example
}



bool MainWindow::onClick_save()
{
    if(currentFile.isEmpty()) return onClick_saveAs();
    else return saveFile(currentFile);
}



bool MainWindow::onClick_saveAs()
{
    QString home = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Project"), home, tr("TBMTJ files (*.tb)"));
    if(filename.isEmpty()) return false;
    return saveFile(filename);
}



void MainWindow::onClick_about()
{
    QString msg = tr("<h2>TBMTJ x.x</h2>"
                     "<p>Copyright &copy; 2015 LabSTT"
                     "<p>Powered by LISE");
    QMessageBox::about(this, tr("About TBMTJ"), msg);
}



bool MainWindow::loadFile(const QString& filename)
{
    if(!project->readProject(filename))
    {
        statusBar()->showMessage(tr("Loading canceled"), 2000);
        return false;
    }

    setCurrentFile(filename);
    statusBar()->showMessage(tr("Project loaded"), 2000);
    return true;
}



bool MainWindow::saveFile(const QString &filename)
{
    if(!project->writeProject(filename))
    {
        statusBar()->showMessage(tr("Writing canceled"), 2000);
        return false;
    }

    setCurrentFile(filename);
    statusBar()->showMessage(tr("Project saved"), 2000);
    return true;
}



bool MainWindow::okToContinue()
{
    if(isWindowModified())
    {
        QString msg = tr("The project has been modified.\nDo you want to save your changes?");
        int r = QMessageBox::warning(this, tr("Project"), msg, QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if(r==QMessageBox::Yes) return onClick_save();
        else if(r==QMessageBox::Cancel) return false;
    }
    return true;
}



void MainWindow::setCurrentFile(const QString& filename)
{
    currentFile = filename;
    setWindowModified(false);

    QString shownName = tr("Untitled");
    if(!currentFile.isEmpty())
    {
        QString strippedName = QFileInfo(currentFile).fileName();
        shownName = strippedName;
        // TODO: recent files
    }
    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("TB Project")));
}


// TODO: 沒作用??
void MainWindow::closeEvent(QCloseEvent* event)
{
    if(okToContinue()) event->accept();
    else event->ignore();
}
