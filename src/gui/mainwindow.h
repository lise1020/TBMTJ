#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "tbproject.h"
#include <QMainWindow>
#include <QLineEdit>



namespace Ui
{
    class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void renewParameterPanel();
    void setActive(bool state);

private slots:
    void onClick_newProject();
    void onClick_openProject();
    void onClick_openExample();
    void onClick_saveProject();
    void onClick_runProject();
    void onClick_plot();

private:
    Ui::MainWindow *ui;
    TBProject mProject;
    void initUi();
    //QVector<QLineEdit>
};



#endif // MAINWINDOW_H
