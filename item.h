#ifndef ITEM_H
#define ITEM_H

#include <QDialog>
#include <QtCore>


class Item
{
public:

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
    inline const int getRadius()                { return this->radius; }
    inline const QPointF getVelocity()          { return this->velocity; }

    inline void generateRandomItem(int origin_x, int origin_y,
                                   int limit_x, int limit_y,
                                   int minVelocity, int maxVelocity)
    {
        setPosition    ( QPointF( origin_x + qrand() % limit_x,
                                  origin_y + qrand() % limit_y ) );

        setVelocity    ( QPointF( minVelocity + qrand() % maxVelocity,
                                  minVelocity + qrand() % maxVelocity ) );
    }


    inline void generateRandomColor()
    {
        setColorFill   ( QColor( qrand() % 255, qrand() % 255, qrand() % 255 ));
        setColorPen    ( QColor( qrand() % 255, qrand() % 255, qrand() % 255 ));
    }


private:

    QPainterPath path;
    QColor colorPen;
    QColor colorFill;
    QPointF position;
    QPointF velocity;

    int radius;

};

#endif // ITEM_H
