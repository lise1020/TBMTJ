#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <tbproject.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    TBProject* project;
    QString currentFile;

protected:
    void closeEvent(QCloseEvent* event);

private:
    bool loadFile(const QString& filename);
    bool saveFile(const QString& filename);
    void setCurrentFile(const QString& filename);
    bool okToContinue();

private slots:
    void onClick_newProject();
    void onClick_openProject();
    void onClick_openExample();
    bool onClick_save();
    bool onClick_saveAs();
    void onClick_about();
};

#endif // MAINWINDOW_H
