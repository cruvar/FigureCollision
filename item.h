#ifndef ITEM_H
#define ITEM_H


#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QPainter>

class Item
{
public:
    Item();
    QPainter painter;

    void setColor(QColor value)          { this->color = value; }
    void setPosition(QPoint value)       { this->position = value; }
    void setGeometry(const QPolygon & polygon) { this->geometry = polygon; }
    void setPath(const QPainterPath & path)     {this->path = path; }


    QColor getColor()       { return this->color; }
    QPoint getPosition()    { return this->position; }
    QPolygon getGeometry()  { return this->geometry; }
    QPainterPath getPath()  { return this->path; }


private:

    QPainterPath path;
    QColor color;
    QPen pen;
    QBrush brush;
    QPoint position;
    QPolygon geometry;

    qreal angle;
    qreal speed;

};

#endif // ITEM_H
