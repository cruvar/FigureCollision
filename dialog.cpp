#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

void Dialog::paintEvent(QPaintEvent *event)
{
    QPainter painterBorder(this);
    QPen penRed = QPen(Qt::red, 5);
    painterBorder.setPen(penRed);

    painterBorder.drawLine(this->rect().topLeft(), this->rect().topRight());
    painterBorder.drawLine(this->rect().topRight(), this->rect().bottomRight());
    painterBorder.drawLine(this->rect().bottomRight(), this->rect().bottomLeft());
    painterBorder.drawLine(this->rect().bottomLeft(), this->rect().topLeft());

    QPainter painterEllipse(this);
    QPen penBlack(Qt::black, 2);
    painterEllipse.setPen(penBlack);
    painterEllipse.setBrush(Qt::magenta);
    painterEllipse.drawEllipse(this->rect().center().x(),this->rect().center().y(),50,50);

    QPainter painterRect(this);
    painterRect.setPen(penBlack);

    painterRect.drawRect(this->rect().center().x(),this->rect().center().y(),50,50);

}

Dialog::~Dialog()
{
    delete ui;
}
