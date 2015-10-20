#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QCoreApplication>
#include <QLabel>
#include "tbproject.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void renewParameterPanel();

private slots:
    void onClick_openExample();
    void onClick_runProject();
    void onClick_plot();
    //void onClick_newProject();
    //void onClick_openProject();

private:
    Ui::MainWindow *ui;
    TBProject myProject;
};

#endif // MAINWINDOW_H
