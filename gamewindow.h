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

    inline int random(int min, int max) { return min + rand() % (max - min); }

    inline void randomizeItem           ( Item & item,
                                          int min_x, int min_y,
                                          int max_x, int max_y,
                                          int minVelocity, int maxVelocity );

    void mousePressEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent * event);
    QString timeElapsed();

    std::vector<Item> items;


signals:
    void noItems();

private slots:
    void newGame();
    void endGame();
    void on_timeOut();
    void on_startButton_clicked();

};

#endif // GAMEWINDOW_H
