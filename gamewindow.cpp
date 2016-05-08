#include "gamewindow.h"
#include "item.h"
#include "ui_gamewindow.h"
#include <QPainter>


GameWindow::GameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle("Figures");
    qsrand (QDateTime::currentMSecsSinceEpoch());
    ui->in_Game_frame->hide();
    ui->end_Game_frame->hide();
    ui->record_frame->show();
    ui->add_record_frame->hide();
    etimer = new QElapsedTimer();
    etimer->start();
    timer = new QTimer(this);
    timer->setInterval( 15 );
    record_table = new QTableWidget();
    connect( this->timer, SIGNAL(timeout()), this, SLOT(on_timeOut()) );

    this->record_table->setColumnCount(4);
    this->record_table->setColumnWidth(0,10);
    this->record_table->setColumnWidth(1,100);
    this->record_table->setColumnWidth(2,50);
    this->record_table->setColumnWidth(3,50);
    this->record_table->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("ID")));
    this->record_table->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Имя")));
    this->record_table->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Время")));
    this->record_table->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("Клики")));
    this->record_table->setShowGrid(true);
    this->record_table->setSelectionMode(QAbstractItemView::SingleSelection);
    this->record_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->record_table->setColumnHidden(0, true);

}

void GameWindow::randomizeItem( Item & item,int min_x, int min_y, int max_x, int max_y, int minVelocity, int maxVelocity )
{
    int velocity;
    if (rand() % 2)
        velocity = -random(abs(minVelocity), abs(maxVelocity));
    else
        velocity = random(abs(minVelocity), abs(maxVelocity));

    item.position = QPointF( random( min_x, max_x), random( min_y, max_y) );
    item.velocity = QPointF( velocity, velocity );
    item.colorFill = QColor( random( 0, 255), random( 0, 255), random( 0, 255) );
    item.colorPen = QColor( random( 0, 255), random( 0, 255), random( 0, 255) );
}

void GameWindow::newGame()
{
    ui->startButton->hide();

    ui->in_Game_frame->show();
    ui->end_Game_frame->hide();
    ui->record_frame->hide();
    ui->add_record_frame->hide();

    timer->start();
    etimer->restart();

    this->clickCount = 0;

    for( int i(0); i < 15; ++i )
    {
        Item item;
        item.radius = 27;
        randomizeItem   ( item, 0, 0, this->width(), this->height(), 1, 4 );

        if(i < 5)
        {
            item.path.addRect    ( -25, -25, 50, 50 );
        }
        else if(i < 10)
        {
            QPolygon triangle;
            triangle            << QPoint( 0, 30 ) << QPoint( -25, -15 )
                                << QPoint( 25, -15 ) << QPoint( 0, 30 );
            item.path.addPolygon     ( triangle );
        }
        else
        {
            item.path.addEllipse     ( -25, -25, 50, 50 );
        }

        items.push_back     ( item );
    }
}

void GameWindow::winGame()
{
    ui->startButton->show();

    ui->in_Game_frame->hide();
    ui->end_Game_frame->show();
    ui->record_frame->show();
    ui->add_record_frame->show();
    this->setRecordTime(this->timeElapsed());
    ui->verdict_label->setText("Красава!");
    ui->label_Elapsed_end->setText( timeElapsed() );
    ui->label_mousepress_end->setText( QString::number( clickCount ) );
    ui->startButton->setText("Хочу еще!");
    timer->stop();
}

void GameWindow::lossGame()
{
    ui->startButton->show();
    ui->in_Game_frame->hide();
    ui->end_Game_frame->show();
    ui->verdict_label->setText("Фу, лох!");
    ui->label_Elapsed_end->setText( timeElapsed() );
    ui->label_mousepress_end->setText( QString::number( clickCount ) );
    ui->startButton->setText("Отомстить");
    timer->stop();
}

void GameWindow::on_startButton_clicked()
{
    this->newGame();
}

void GameWindow::on_recordsButton_clicked()
{
    this->record_table->show();

}

void GameWindow::on_add_name_Button_clicked()
{
    Record record;
    record.name = ui->add_name_lineEdit->text();
    record.time = this->recordTime;
    record.clicks = this->clickCount;
    records.push_back(record);

    this->record_table->insertRow(0);
    //this->record_table->setItem(0, 0, new QTableWidgetItem(query.value(0).toString()));
    this->record_table->setItem(0, 1, new QTableWidgetItem(record.name));
    this->record_table->setItem(0, 2, new QTableWidgetItem(record.time));
    this->record_table->setItem(0, 3, new QTableWidgetItem(QString::number(record.clicks)));
    this->record_table->setRowHeight(0, 20);
    qDebug() << record.name;
}

void GameWindow::on_timeOut()
{
    for( Item & item:items )
    {
        item.position += item.velocity;

        if( item.position.x() < item.radius )
            item.velocity.rx() = fabs(item.velocity.x());

        if( item.position.y() < item.radius )
            item.velocity.ry() = fabs(item.velocity.y());

        if( item.position.x() >= this->width() - item.radius )
            item.velocity.rx() = -fabs(item.velocity.x());

        if( item.position.y() >= this->height() - item.radius  )
            item.velocity.ry() = -fabs(item.velocity.y());
    }

    ui->label_Elapsed->setText(timeElapsed());
    ui->label_Items->setText(QString::number(items.size()));
    QPalette p = ui->label_Items->palette();

    if ( items.size() > this->percentItems( 75 ) )
    {
        p.setColor(QPalette::WindowText, Qt::red);
        ui->label_Items->setPalette(p);
    }
    else
    {
        p.setColor(QPalette::WindowText, Qt::black);
        ui->label_Items->setPalette(p);
    }

    if( items.empty() )
    {
        this->winGame();
    }

    if( items.size() > this->maxItems )
    {
        items.clear();
        this->lossGame();
    }
    update();
}

void GameWindow::mousePressEvent(QMouseEvent *event)
{
    bool hit = false; //этот флаг хранит состояние попал\не попал
    for (auto item = begin(items); item != end(items); ++item)
    {
        if( item->path.contains(event->pos() - item->position)&&event->button() == Qt::LeftButton )
        {
            clickCount++;
            items.erase(item);
            hit = true;
            update();
            break;
        }
    }

    if( !hit && !items.empty() )
    {
        clickCount++;
        for( int i(0); i < 3; ++i )
        {
            Item item;
            item.radius = 27;
            randomizeItem   ( item, 0, 0, this->width(), this->height(), 1, 4 );

            if( i < 1 )
            {
                item.path.addRect    ( -25, -25, 50, 50 );
            }
            else if( i < 2 )
            {
                QPolygon triangle;
                triangle            << QPoint( 0, 30 ) << QPoint( -25, -15 )
                                    << QPoint( 25, -15 ) << QPoint( 0, 30 );
                item.path.addPolygon     ( triangle );
            }
            else
            {
                item.path.addEllipse     ( -25, -25, 50, 50 );
            }
            items.push_back     ( item );
        }
        update();
    }
}

void GameWindow::paintEvent( QPaintEvent *event )
{
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing );


    foreach( const Item & item,items )
    {
        painter.save();     // сохранили состояние пеинтера
        painter.translate   ( item.position );
        painter.setPen      ( { item.colorPen, 2 } );
        painter.fillPath    ( item.path, item.colorFill );
        painter.drawPath    ( item.path );
        painter.restore();  // вернули в прежнее состояние
    }

    Q_UNUSED( event );
}

QString GameWindow::timeElapsed()
{
    qint64 res = etimer->elapsed();
    qint64 sec = res / 1000;
    qint64 min = sec / 60;
    sec %= 60;
    min %= 60;
    QString timeElapsed = QString("%1:%2").arg(min, 2, 10, QChar('0')).arg(sec, 2, 10, QChar('0'));
    return timeElapsed;
}


GameWindow::~GameWindow()
{
    delete ui;
}


