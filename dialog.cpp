#include "dialog.h"
#include "item.h"
#include "ui_dialog.h"
#include <QPainter>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    for( int i(0); i < 15; ++i )
    {
        Item item;
        item.setColor(QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255));
        item.setPosition(QPoint(qrand() % 400, qrand() % 400));
        QPolygon polygon;
        polygon << QPoint(qrand() % 400, qrand() % 400) << QPoint(qrand() % 400, qrand() % 400);
        QPainterPath path;
        path.addPolygon(polygon);

        item.setPath(path);
        items.push_back(item);
    }
}

void Dialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen penRed = QPen(Qt::red, 5);
    QBrush brushYellow = QBrush(Qt::yellow);
    painter.setPen(penRed);

    painter.drawLine(this->rect().topLeft(), this->rect().topRight());
    painter.drawLine(this->rect().topRight(), this->rect().bottomRight());
    painter.drawLine(this->rect().bottomRight(), this->rect().bottomLeft());
    painter.drawLine(this->rect().bottomLeft(), this->rect().topLeft());

    qDebug() << items.size();

    foreach(const Item & item,items)
    {
        painter.setPen({item.getColor(), 2});
        painter.drawPath( item.getPath() );
        qDebug() << item.getPath();

    }
}

Dialog::~Dialog()
{
    delete ui;
}
