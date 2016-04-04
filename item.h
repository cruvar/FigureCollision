#ifndef ITEM_H
#define ITEM_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QPainter>

class Item
{
public:

    void setColor(QColor value)                 { this->color = value; }
    void setPosition(QPoint pos)                { this->position = pos; }
    void setGeometry(const QPolygon & polygon)  { this->geometry = polygon; }
    void setPath(const QPainterPath & path)     { this->path = path; }


    const QColor & getColor() const      { return this->color; }
    const QPoint & getPosition() const   { return this->position; }
    const QPolygon & getGeometry() const { return this->geometry; }
    const QPainterPath & getPath() const { return this->path; }


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
