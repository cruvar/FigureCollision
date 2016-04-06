#include "dialog.h"
#include "item.h"
#include "ui_dialog.h"
#include <QPainter>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //квадраты
    for( int i(0); i < 5; ++i )
    {
        Item item;
        item.setColorPen(QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255));
        item.setColorFill(QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255));
        item.setPosition(QPoint(qrand() % 300, qrand() % 300));
        item.setGeometry({QPoint(10,10), QPoint(10,50),
                          QPoint(50,50), QPoint(50,10),
                          QPoint(10,10)} );
        QPainterPath path;
        path.addPolygon(item.getGeometry());
        item.setPath(path);
        items.push_back(item);
    }

    //треугольники
    for( int i(0); i < 5; ++i )
    {
        Item item;
        item.setColorPen(QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255));
        item.setColorFill(QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255));
        item.setPosition(QPoint(qrand() % 300, qrand() % 300));
        item.setGeometry({QPoint(30,10), QPoint(10,50),
                          QPoint(50,50), QPoint(30,10),
                          } );
        QPainterPath path;
        path.addPolygon(item.getGeometry());
        item.setPath(path);
        items.push_back(item);
    }
}

void Dialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen penRed = QPen(Qt::red, 5);
    painter.setPen(penRed);

    painter.drawLine(this->rect().topLeft(), this->rect().topRight());
    painter.drawLine(this->rect().topRight(), this->rect().bottomRight());
    painter.drawLine(this->rect().bottomRight(), this->rect().bottomLeft());
    painter.drawLine(this->rect().bottomLeft(), this->rect().topLeft());


    foreach(const Item & item,items)
    {
        painter.save();     // сохранили состояние пеинтера
        painter.translate   ( item.getPosition() );
        painter.setPen      ( {item.getColorPen(), 2} );
        painter.fillPath    ( item.getPath(), item.getColorFill() );
        painter.drawPath    ( item.getPath() );
        painter.restore();  // вернули в прежнее состояние
    }
}

Dialog::~Dialog()
{
    delete ui;
}
