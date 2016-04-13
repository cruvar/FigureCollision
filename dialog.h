#ifndef DIALOG_H
#define DIALOG_H

#include <vector>
#include <QDialog>
#include "item.h"


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();


private:
    Ui::Dialog *ui;
    Item *myitem;
    QTimer *timer;

    void paintEvent(QPaintEvent *event);

    std::vector<Item> items;

    const int r = 15;

private slots:
    void on_timeOut();
};

#endif // DIALOG_H
