#ifndef ITEM_H
#define ITEM_H

#include <QPainterPath>
#include <QColor>
#include <QPointF>


struct Item
{
    QPainterPath path;
    QColor colorPen;
    QColor colorFill;
    QPointF position;
    QPointF velocity;

    int radius;
};

#endif // ITEM_H
