#ifndef RECORDSWINDOW_H
#define RECORDSWINDOW_H

#include <QDialog>

namespace Ui {
class RecordsWindow;
}

class RecordsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RecordsWindow(QWidget *parent = 0);
    ~RecordsWindow();

private slots:


private:
    Ui::RecordsWindow *ui;

};

#endif // RECORDSWINDOW_H
