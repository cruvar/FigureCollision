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
    void setPosition( QPoint pos )                    { this->position = pos; }
    void setGeometry( const QVector<QPoint> &points ) { this->geometry = points; }
    void setPath( const QPainterPath & path )         { this->path = path; }


    const QColor & getColorPen() const   { return this->colorPen; }
    const QColor & getColorFill() const  { return this->colorFill; }
    const QPoint & getPosition() const   { return this->position; }
    const QPolygon & getGeometry() const { return this->geometry; }
    const QPainterPath & getPath() const { return this->path; }



private:

    QPainterPath path;
    QColor colorPen;
    QColor colorFill;
    QBrush brush;
    QPoint position;
    QPolygon geometry;

};

#endif // ITEM_H
