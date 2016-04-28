#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <vector>
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include "item.h"


namespace Ui {
class Dialog;
}

class GameWindow : public QDialog
{
    Q_OBJECT

public:

    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();


private:
    Ui::Dialog *ui;
    Item *myitem;
    QTimer *timer;
    QElapsedTimer *etimer;

    void mousePressEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent * event);
    QString timeElapsed();

    std::vector<Item> items;

signals:
    void noItems();

private slots:
    void newGame();
    void on_timeOut();
    void on_startButton_clicked();

};

#endif // GAMEWINDOW_H
