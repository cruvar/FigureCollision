#include "dialog.h"
#include "item.h"
#include "ui_dialog.h"
#include <QPainter>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    timerPaint = new QTimer(this);
    timer      = new QTimer(this);
    timer->start(1000);
    timerPaint->setInterval( 15 );

    connect( ui->startButton, SIGNAL(clicked(bool)), this->timerPaint, SLOT(start()) );
    connect( ui->startButton, SIGNAL(clicked(bool)), this, SLOT(newGame()));
    connect( this, SIGNAL(noItems()), ui->startButton, SLOT(show()) );
    connect( this->timerPaint, SIGNAL(timeout()), this, SLOT(on_timeOut()) );



    qsrand (QDateTime::currentMSecsSinceEpoch());


}

void Dialog::newGame()
{
    //квадратики
    for( int i(0); i < 5; ++i )
    {
        Item item;
        item.drawItem ( QPointF(qrand() % this->rect().width(), qrand() % this->rect().height() ),
                        25,
                        QPointF( 1 + qrand() % 3, 1 + qrand() % 3 ),
                        QColor( qrand() % 255, qrand() % 255, qrand() % 255, 255 ),
                        QColor( qrand() % 255, qrand() % 255, qrand() % 255, 255 ) );
        QPainterPath path;
        path.addRect    ( -25, -25, 50, 50 );
        item.setPath    ( path );
        items.push_back ( item );
    }

    //треугольнички
    for( int i(0); i < 5; ++i )
    {
        Item item;
        item.drawItem ( QPointF(qrand() % this->rect().width(), qrand() % this->rect().height() ),
                        25,
                        QPointF( 1 + qrand() % 3, 1 + qrand() % 3 ),
                        QColor( qrand() % 255, qrand() % 255, qrand() % 255, 255 ),
                        QColor (qrand() % 255, qrand() % 255, qrand() % 255, 255 ) );

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
        item.drawItem ( QPointF(qrand() % this->rect().width(), qrand() % this->rect().height() ),
                        25,
                        QPointF( 1 + qrand() % 3, 1 + qrand() % 3 ),
                        QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255 ),
                        QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255 ) );

        QPainterPath path;
        path.addEllipse     ( -25, -25, 50, 50 );
        item.setPath        ( path );
        items.push_back     ( item );

    }
}

void Dialog::on_startButton_clicked()
{
    ui->startButton->hide();

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
            item.drawItem( QPointF(qrand() % this->rect().width(), qrand() % this->rect().height() ),
                           25,
                           QPointF(1 + qrand() % 3, 1 + qrand() % 3),
                           QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255 ),
                           QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255 )
                           );
            if(i < 1)
            {
                QPainterPath path;
                path.addRect    ( -25, -25, 50, 50 );
                item.setPath    ( path );
            }
            else if(i < 2)
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





