#ifndef ITEM_H
#define ITEM_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QPainter>

class Item
{
public:

    void setColorPen( QColor color )                  { this->colorPen = color; }
    void setColorFill( QColor color )                 { this->colorFill = color; }
    void setPosition( QPointF pos )                   { this->position = pos; }
    void setGeometry( const QVector<QPoint> &points ) { this->geometry = points; }
    void setPath( const QPainterPath & path )         { this->path = path; }
    void setVelocityX( qreal vx )                     { this->velocityX = vx; }
    void setVelocityY( qreal vy )                     { this->velocityY = vy; }
    void setRadius( int radius )                      { this->radius = radius; }


    const QColor & getColorPen() const   { return this->colorPen; }
    const QColor & getColorFill() const  { return this->colorFill; }
    const QPointF & getPosition() const  { return this->position; }
    const QPolygon & getGeometry() const { return this->geometry; }
    const QPainterPath & getPath() const { return this->path; }
    qreal getVelocityX()                 { return this->velocityX; }
    qreal getVelocityY()                 { return this->velocityY; }
    int getRadius()                      { return this->radius; }


private:

    QPainterPath path;
    QColor colorPen;
    QColor colorFill;
    QBrush brush;
    QPointF position;
    QPolygon geometry;

    int radius;
    qreal velocityX, velocityY;

};

#endif // ITEM_H
