#ifndef TBPROJECT_H
#define TBPROJECT_H
#include <QWidget>


namespace Ui {
class TBProject;
}

class TBProject: public QWidget
{
    Q_OBJECT

public:
    explicit TBProject(QWidget* parent = 0);
    ~TBProject();
    bool readProject(const QString& filename);
    bool writeProject(const QString& filename);

private:
    Ui::TBProject *ui;
};

#endif // TBPROJECT_H
