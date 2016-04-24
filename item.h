#ifndef ITEM_H
#define ITEM_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QPainter>


class Item
{
public:

    Item( QPointF position, int radius, QPointF velocity, QColor pen, QColor fill );

    inline void setColorPen( QColor color )            { this->colorPen = color; }
    inline void setColorFill( QColor color )           { this->colorFill = color; }
    inline void setPosition( QPointF pos )             { this->position = pos; }
    inline void setPath( const QPainterPath & path )   { this->path = path; }
    inline void setRadius( int radius )                { this->radius = radius; }
    inline void setVelocity( QPointF velocity )        { this->velocity = velocity; }

    inline const QColor & getColorPen() const   { return this->colorPen; }
    inline const QColor & getColorFill() const  { return this->colorFill; }
    inline const QPointF & getPosition() const  { return this->position; }
    inline const QPainterPath & getPath() const { return this->path; }
    inline int getRadius()                      { return this->radius; }
    inline QPointF getVelocity()                { return this->velocity; }


private:

    QPainterPath path;
    QColor colorPen;
    QColor colorFill;
    QPointF position;
    QPointF velocity;

    int radius;

};

#endif // ITEM_H
