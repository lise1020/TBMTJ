#ifndef PORTALWINDOW_H
#define PORTALWINDOW_H

#include <QDialog>

namespace Ui {
class PortalWindow;
}

class PortalWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PortalWindow(QWidget *parent = 0);
    ~PortalWindow();

private:
    Ui::PortalWindow *ui;
};

#endif // PORTALWINDOW_H
