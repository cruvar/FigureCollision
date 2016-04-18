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
    timer->start( 10 );
    connect( this->timer, SIGNAL( timeout() ), this, SLOT( on_timeOut() ) );

    //квадратики
    for( int i(0); i < 5; ++i )
    {
        Item item;
        item.setVelocity    ( QPointF(2, 2) );
        item.setRadius      ( 25 );
        item.setColorPen    ( QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255 ) );
        item.setColorFill   ( QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255 ) );
        item.setPosition    ( QPointF(qrand() % this->rect().width(), qrand() % this->rect().height() ) );

        QPainterPath path;
        path.addRect        ( -25, -25, 50, 50 );
        item.setPath        ( path );
        items.push_back     ( item );
    }

    //треугольнички
    for( int i(0); i < 5; ++i )
    {
        Item item;
        item.setVelocity    ( QPointF(0.5, 0.5) );
        item.setRadius      ( 25 );
        item.setColorPen    ( QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255 ) );
        item.setColorFill   ( QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255 ) );
        item.setPosition    ( QPointF(qrand() % this->rect().width(), qrand() % this->rect().height()) );

        QPolygon triangle;
        triangle            << QPoint( 0, 30 ) << QPoint( -25, -15 )
                            << QPoint( 25, -15 ) << QPoint( 0, 30 );

        QPainterPath path;
        path.addPolygon     ( triangle );
        item.setPath        ( path );
        items.push_back     ( item );
    }

    //кружочки
    for( int i(0); i < 5; ++i )
    {
        Item item;
        item.setVelocity    ( QPointF(1.25, 1.25) );
        item.setRadius      ( 25 );
        item.setColorPen    ( QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255 ) );
        item.setColorFill   ( QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255 ) );
        item.setPosition    ( QPointF(qrand() % this->rect().width(), qrand() % this->rect().height()) );

        QPainterPath path;
        path.addEllipse     ( -25, -25, 50, 50 );
        item.setPath        ( path );
        items.push_back     ( item );

    }

}

void Dialog::on_timeOut()
{
    for( Item & item:items )
        {
            item.setPosition( QPointF( item.getPosition().x() + item.getVelocity().x(), item.getPosition().y() + item.getVelocity().y() ) );

            if( item.getPosition().x() > this->width() - item.getRadius() || item.getPosition().x() < item.getRadius() )
                item.setVelocity( QPointF(item.getVelocity().x() * -1, item.getVelocity().y() ) );

            if( item.getPosition().y() > this->height() - item.getRadius() || item.getPosition().y() < item.getRadius() )
                item.setVelocity( QPointF(item.getVelocity().x(), item.getVelocity().y() * -1 ) );
        }

    update();
}

void Dialog::mousePressEvent(QMouseEvent *event)
{
    bool hit = false;
    for (auto item = begin(items); item != end(items); ++item)
    {
        if( item->getPath().contains(event->pos() - item->getPosition())&&event->button() == Qt::LeftButton )
        {

                item->setColorFill(Qt::black);
                qDebug() << event->pos() << "ну ты и ловкач!";
                items.erase(item);
                hit = true;
                update();
                break;
        }
    }

    if( !hit )
    {
        qDebug() << "не попал";
    }
}

void Dialog::paintEvent( QPaintEvent *event )
{
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing );

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
