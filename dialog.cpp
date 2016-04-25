#include "dialog.h"
#include "item.h"
#include "ui_dialog.h"
#include <QPainter>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    etimer = new QElapsedTimer();

    timer = new QTimer(this);
    timer->setInterval( 15 );

    connect( ui->startButton, SIGNAL(clicked(bool)), this->timer, SLOT(start()) );
    connect( ui->startButton, SIGNAL(clicked(bool)), this, SLOT(newGame()));

    connect( this, SIGNAL(noItems()), ui->startButton, SLOT(show()) );
    connect( this->timer, SIGNAL(timeout()), this, SLOT(on_timeOut()) );

    qsrand (QDateTime::currentMSecsSinceEpoch());

}

void Dialog::newGame()
{
    etimer->start();
    for( int i(0); i < 15; ++i )
    {
        Item item;
        item.setRadius      ( 27 );
        item.setPosition    ( QPointF(item.getRadius() + qrand() % (this->rect().width() - item.getRadius()*2),
                                      item.getRadius() + qrand() % (this->rect().height() - item.getRadius()*2)));
        item.setVelocity    ( QPointF( -3 + qrand() % 7, -3 + qrand() % 7 ) );
        item.setColorFill   ( QColor( qrand() % 255, qrand() % 255, qrand() % 255, 255 ));
        item.setColorPen    ( QColor( qrand() % 255, qrand() % 255, qrand() % 255, 255 ));


            if(i < 5)
            {
                QPainterPath path;
                path.addRect    ( -25, -25, 50, 50 );
                item.setPath    ( path );
            }
            else if(i < 10)
            {
                QPolygon triangle;
                triangle            << QPoint( 0, 30 ) << QPoint( -25, -15 )
                                    << QPoint( 25, -15 ) << QPoint( 0, 30 );
                QPainterPath path;
                path.addPolygon     ( triangle );
                item.setPath        ( path );
            }
            else
            {
                QPainterPath path;
                path.addEllipse     ( -25, -25, 50, 50 );
                item.setPath        ( path );
            }

        items.push_back ( item );
    }
}

void Dialog::on_startButton_clicked()
{
    ui->startButton->hide();
    etimer->restart();
}

void Dialog::on_timeOut()
{
    for( Item & item:items )
        {
            item.setPosition( QPointF( item.getPosition().x() + item.getVelocity().x(), item.getPosition().y() + item.getVelocity().y() ) );

            if( item.getPosition().x() < item.getRadius() )
                item.setVelocity( QPointF( fabs(item.getVelocity().x()) , item.getVelocity().y() ) );

            if( item.getPosition().y() < item.getRadius() )
                item.setVelocity( QPointF( item.getVelocity().x(),  fabs(item.getVelocity().y())) );

            if( item.getPosition().x() >= this->width() - item.getRadius() )
                item.setVelocity( QPointF( -fabs(item.getVelocity().x()) , item.getVelocity().y() ) );

            if( item.getPosition().y() >= this->height() - item.getRadius()  )
                item.setVelocity( QPointF( item.getVelocity().x(),  -fabs(item.getVelocity().y() )) );

        }

    update();
}

void Dialog::mousePressEvent(QMouseEvent *event)
{
    bool hit = false; //этот флаг хранит состояние попал\не попал
    for (auto item = begin(items); item != end(items); ++item)
    {
        if( item->getPath().contains(event->pos() - item->getPosition())&&event->button() == Qt::LeftButton )
        {
            qDebug() << event->pos() << "ну ты и ловкач!";
            item->setColorFill(Qt::black);
            items.erase(item);
            hit = true;
            update();
            break;
        }
    }

    if( !hit && !items.empty() )
    {
        qDebug() << event->pos() << "не попал";
        for( int i(0); i < 3; ++i )
        {
            Item item;
            item.setRadius      ( 27 );
            item.setPosition    ( QPointF(item.getRadius() + qrand() % (this->rect().width() - item.getRadius()*2),
                                          item.getRadius() + qrand() % (this->rect().height() - item.getRadius()*2)));
            item.setVelocity    ( QPointF( -3 + qrand() % 7, -3 + qrand() % 7 ) );
            item.setColorFill   ( QColor( qrand() % 255, qrand() % 255, qrand() % 255, 255 ));
            item.setColorPen    ( QColor( qrand() % 255, qrand() % 255, qrand() % 255, 255 ));

            if( i < 1 )
            {
                QPainterPath path;
                path.addRect    ( -25, -25, 50, 50 );
                item.setPath    ( path );
            }
            else if( i < 2 )
            {
                QPolygon triangle;
                triangle            << QPoint( 0, 30 ) << QPoint( -25, -15 )
                                    << QPoint( 25, -15 ) << QPoint( 0, 30 );
                QPainterPath path;
                path.addPolygon     ( triangle );
                item.setPath        ( path );
            }
            else
            {
                QPainterPath path;
                path.addEllipse     ( -25, -25, 50, 50 );
                item.setPath        ( path );
            }
            items.push_back(item);
        }

        qDebug() << items.size() << "итемов";
        update();
    }

    if( items.empty() )
    {
        this->noItems();
        qDebug() << timeElapsed();

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

QString Dialog::timeElapsed()
{
    qint64 res = etimer->elapsed();
    qint64 sec = res / 1000;
    qint64 min = sec / 60;
    qint64 hr = min / 60;
    sec %= 60;
    min %= 60;

    QString timeElapsed = QString("%1:%2:%3").arg(hr).arg(min).arg(sec);
       //QString timeElapsed; QTextStream(&timeElapsed) << hr << ":" << min << ":" << sec;
    return timeElapsed;

}

Dialog::~Dialog()
{
    delete ui;
}





