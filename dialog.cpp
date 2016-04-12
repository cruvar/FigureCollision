#include "dialog.h"
#include "item.h"
#include "ui_dialog.h"
#include <QPainter>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->start( 50 );
    connect( this->timer, SIGNAL( timeout() ), this, SLOT( on_timeOut() ) );

    //квадраты
    for( int i(0); i < 5; ++i )
    {
        Item item;
        item.setVelocityX(0.25);
        item.setVelocityY(0.25);
        item.setColorPen    ( QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255 ) );
        item.setColorFill   ( QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255 ) );
        item.setPosition    ( QPointF(qrand() % this->rect().width(), qrand() % this->rect().height() ) );
        item.setGeometry    ( { QPoint( -25,25 ), QPoint( -25,-25 ),
                                QPoint( 25,-25 ), QPoint( 25,25 ),
                                QPoint( -25,25 ) } );
        QPainterPath path;
        path.addPolygon     ( item.getGeometry() );
        item.setPath        ( path );
        items.push_back     ( item );
    }

    //треугольники
    for( int i(0); i < 5; ++i )
    {
        Item item;
        item.setVelocityX(0.5);
        item.setVelocityY(0.5);
        item.setColorPen    ( QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255 ) );
        item.setColorFill   ( QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255 ) );
        item.setPosition    ( QPointF(qrand() % this->rect().width(), qrand() % this->rect().height()) );
        item.setGeometry    ( {QPoint(0,30), QPoint(-25,-15),
                               QPoint(25,-15), QPoint(0,30),
                              } );
        QPainterPath path;
        path.addPolygon     ( item.getGeometry() );
        item.setPath        ( path );
        items.push_back     ( item );
    }

    //кружочки
    for( int i(0); i < 5; ++i )
    {
        Item item;
        item.setVelocityX(0.75);
        item.setVelocityY(0.75);
        item.setColorPen    ( QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255 ) );
        item.setColorFill   ( QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255 ) );
        item.setPosition    ( QPointF(qrand() % this->rect().width(), qrand() % this->rect().height()) );

        int n = 20;
        QPolygonF polygon;
        for( int i(0); i <= n; ++i)
        {
            qreal fAngle = 2 * 3.14 * i / n;
            qreal x      = 0 + cos( fAngle ) * 20;
            qreal y      = 0 + sin( fAngle ) * 20;
            //item.setGeometry( {QPoint( x, y )} );
            polygon << QPointF(x,y);
        }

        QPainterPath path;
        path.addPolygon     ( polygon );
        item.setPath        ( path );
        items.push_back     ( item );

    }

}

void Dialog::on_timeOut()
{
    for( Item & item:items )
        {
            item.setPosition( QPointF( item.getPosition().x() + item.getVelocityX(), item.getPosition().y() + item.getVelocityY() ) );

            qDebug() << item.getPosition();
            qDebug() << item.getVelocityX();
            qDebug() << item.getVelocityY();
        }

    update();
}


void Dialog::paintEvent( QPaintEvent *event )
{
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing );
    QPen penRed = QPen( Qt::red, 5 );
    painter.setPen( penRed );

    painter.drawLine( this->rect().topLeft(), this->rect().topRight() );
    painter.drawLine( this->rect().topRight(), this->rect().bottomRight() );
    painter.drawLine( this->rect().bottomRight(), this->rect().bottomLeft() );
    painter.drawLine( this->rect().bottomLeft(), this->rect().topLeft() );


    foreach( const Item & item,items )
    {
        painter.save();     // сохранили состояние пеинтера
        painter.translate   ( item.getPosition() );
        painter.setPen      ( { item.getColorPen(), 2 } );
        painter.fillPath    ( item.getPath(), item.getColorFill() );
        painter.drawPath    ( item.getPath() );
        painter.restore();  // вернули в прежнее состояние
    }

    Q_UNUSED( event );
}

Dialog::~Dialog()
{
    delete ui;
}
