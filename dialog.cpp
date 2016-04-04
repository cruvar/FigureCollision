#include "dialog.h"
#include "item.h"
#include "ui_dialog.h"
#include <QPainter>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    myitem = new Item;

    myitem->setColor(Qt::red);
    myitem->setPosition(this->rect().center());
    QPolygon polygon;
    polygon << QPoint(qrand() % 200, qrand() % 200) << QPoint(qrand() % 200, qrand() % 200);
    QPainterPath path;
    path.addPolygon(polygon);
    myitem->setPath(path);



   // std::vector<Items> target = {};
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

/*
    QPainterPath epath;
    epath.addEllipse(this->rect().center(), 50, 50);
    painter.fillPath(epath,brushYellow);
*/

    painter.translate(myitem->getPosition());
    painter.drawPath( myitem->getPath() );
}

Dialog::~Dialog()
{
    delete ui;
}
