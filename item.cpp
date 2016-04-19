#include "item.h"

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QPainter>

void Item::drawItem( QPointF position, int radius, QPointF velocity, QColor pen, QColor fill )
{
    setPosition    ( position );
    setRadius      ( radius );
    setVelocity    ( velocity );
    setColorPen    ( pen );
    setColorFill   ( fill );
}

