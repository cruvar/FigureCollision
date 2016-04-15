#ifndef ITEM_H
#define ITEM_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QPainter>

class Item
{
public:

    void setColorPen( QColor color )            { this->colorPen = color; }
    void setColorFill( QColor color )           { this->colorFill = color; }
    void setPosition( QPointF pos )             { this->position = pos; }
    void setPath( const QPainterPath & path )   { this->path = path; }
    void setRadius( int radius )                { this->radius = radius; }
    void setVelocity( QPointF velocity )        { this->velocity = velocity; }


    const QColor & getColorPen() const   { return this->colorPen; }
    const QColor & getColorFill() const  { return this->colorFill; }
    const QPointF & getPosition() const  { return this->position; }
    const QPainterPath & getPath() const { return this->path; }
    int getRadius()                      { return this->radius; }
    QPointF getVelocity()                { return this->velocity; }


private:

    QPainterPath path;
    QColor colorPen;
    QColor colorFill;
    QPointF position;
    QPointF velocity;

    int radius;


};

#endif // ITEM_H
