#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <vector>
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QTableWidget>
#include <QSettings>
#include "item.h"
#include "record.h"

namespace Ui {
class Dialog;
}

class GameWindow : public QDialog
{
    Q_OBJECT

public:

    explicit GameWindow( QWidget *parent = 0 );
    ~GameWindow();

private:

    Ui::Dialog *ui;
    QTimer *timer;
    QElapsedTimer *etimer;
    QTableWidget *record_table;
    QSettings *settings;
    int clickCount = 0;
    int maxItems = 45;
    int recordTime;

    void loadRecords();
    void saveRecords();
    void showRecords();

    int getClickCount()                         { return this->clickCount; }
    inline float percentItems( int percent )    { return ( maxItems / 100.0 ) * percent; }
    inline int random( int min, int max )       { return min + rand() % (max - min); }
    inline void randomizeItem( Item & item,
                               int min_x, int min_y,
                               int max_x, int max_y,
                               int minVelocity, int maxVelocity );
    QString timeElapsed();
    QString timeToString( qint64 time );
    void mousePressEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent * event);    

    std::vector<Item> items;
    std::vector<Record> records;

signals:

private slots:

    void newGame();
    void winGame();
    void lossGame();
    void on_timeOut();
    void on_startButton_clicked();
    void on_recordsButton_clicked();
    void on_add_name_Button_clicked();
};

#endif // GAMEWINDOW_H
