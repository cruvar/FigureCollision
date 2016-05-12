#include "gamewindow.h"
#include "item.h"
#include "ui_gamewindow.h"
#include <QPainter>
#include <algorithm>
#include <QSound>


GameWindow::GameWindow( QWidget *parent ) :
    QDialog( parent ),
    ui( new Ui::Dialog )
{
    ui->setupUi( this );
    this->loadRecords();
    setWindowTitle("Figures v0.1");
    qsrand( QDateTime::currentMSecsSinceEpoch() );
    ui->in_Game_frame->hide();
    ui->end_Game_frame->hide();
    ui->record_frame->show();
    ui->add_record_frame->hide();
    etimer = new QElapsedTimer();
    etimer->start();
    timer = new QTimer( this );
    timer->setInterval( 15 );
    record_table = new QTableWidget();

    connect( this->timer, SIGNAL( timeout() ), this, SLOT( on_timeOut() ) );

    ui->add_name_lineEdit->setValidator(new QRegExpValidator( QRegExp( "[A-Za-z0-9]{1,9}" ) ) );

    QFont font;
    font.setPointSize(14);
    this->record_table->setFont(font);

    this->record_table->setMinimumHeight(400);
    this->record_table->setMinimumWidth(300);
    this->record_table->setWindowTitle("Летопись Героев");
    this->record_table->setColumnCount( 3 ); 
    this->record_table->setHorizontalHeaderItem( 0, new QTableWidgetItem( tr("Имя") ) );
    this->record_table->setHorizontalHeaderItem( 1, new QTableWidgetItem( tr("Время") ) );
    this->record_table->setHorizontalHeaderItem( 2, new QTableWidgetItem( tr("Клики") ) );
    this->record_table->setShowGrid( false );
    this->record_table->setSelectionMode( QAbstractItemView::SingleSelection );
    this->record_table->setSelectionBehavior( QAbstractItemView::SelectRows );
    this->record_table->setEditTriggers( QAbstractItemView::NoEditTriggers );

}

void GameWindow::randomizeItem( Item & item, int min_x, int min_y, int max_x, int max_y, int minVelocity, int maxVelocity )
{
    int velocityX;
    int velocityY;
    if ( rand() % 2 )
    {
        velocityX = -random( abs( minVelocity ), abs( maxVelocity ) );
        velocityY = -random( abs( minVelocity ), abs( maxVelocity ) );
    }
    else
    {
        velocityX = random( abs( minVelocity ), abs( maxVelocity ) );
        velocityY = random( abs( minVelocity ), abs( maxVelocity ) );
    }

    item.position = QPointF( random( min_x, max_x), random( min_y, max_y) );
    item.velocity = QPointF( velocityX, velocityY );
    item.colorFill = QColor( random( 0, 255 ), random( 0, 255 ), random( 0, 255 ) );
    item.colorPen = QColor( random( 0, 255 ), random( 0, 255 ), random( 0, 255 ) );
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
    QSound::play(":/recources/sounds/win.wav");
    ui->startButton->show();  
    ui->in_Game_frame->hide();
    ui->end_Game_frame->show();
    ui->record_frame->show();
    ui->add_record_frame->show();
    this->recordTime = etimer->elapsed();
    ui->verdict_label->setText("Красава!");
    ui->label_Elapsed_end->setText( timeElapsed() );
    ui->label_mousepress_end->setText( QString::number( clickCount ) );
    ui->startButton->setText("Хочу еще!");
    timer->stop();
}

void GameWindow::lossGame()
{
    QSound::play(":/recources/sounds/lose.wav");
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
    QSound::play(":/recources/sounds/new_game.wav");
    this->newGame();
}

void GameWindow::on_recordsButton_clicked()
{
    this->showRecords();
}

void GameWindow::on_add_name_Button_clicked()
{
    Record record;
    record.name = ui->add_name_lineEdit->text();
    record.time = this->recordTime;
    record.clicks = this->clickCount;
    records.push_back( record );

    this->saveRecords();
    this->showRecords();
}

void GameWindow::on_timeOut()
{
    for( Item & item:items )
    {
        item.position += item.velocity;

        if( item.position.x() < item.radius )
            item.velocity.rx() = fabs( item.velocity.x() );

        if( item.position.y() < item.radius )
            item.velocity.ry() = fabs( item.velocity.y() );

        if( item.position.x() >= this->width() - item.radius )
            item.velocity.rx() = -fabs( item.velocity.x() );

        if( item.position.y() >= this->height() - item.radius  )
            item.velocity.ry() = -fabs( item.velocity.y() );
    }

    ui->label_Elapsed->setText( timeElapsed() );
    ui->label_Items->setText( QString::number(items.size() ) );
    QPalette palette = ui->label_Items->palette();

    if ( items.size() > this->percentItems( 75 ) )
    {

        palette.setColor( QPalette::WindowText, Qt::red );
        ui->label_Items->setPalette( palette );

    }
    else
    {
        palette.setColor( QPalette::WindowText, Qt::black );
        ui->label_Items->setPalette( palette );
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

void GameWindow::loadRecords()
{
    QFile file("records.txt");
    if( !file.open(QIODevice::ReadOnly) )
    {
        return;
    }
    QByteArray line;
    do
    {
        line = file.readLine().trimmed();
        if(line.isEmpty())
            break;
        QList<QByteArray> columns = line.split( ' ' );
        if(columns.size() != 3)
            break;
        Record record;
        record.name = columns[0];
        record.time = columns[1].toInt();
        record.clicks = columns[2].toInt();
        records.push_back(record);
    }
    while(true);
}

void GameWindow::saveRecords()
{
    QFile file("records.txt");
    if( !file.open(QIODevice::WriteOnly | QIODevice::Truncate) )
    {
        qWarning() << "Cant open records.txt!!!";
        return;
    }

    for( const Record & record : records )
    {
        QString line = record.name + " " + QString::number( record.time ) + " " + QString::number( record.clicks );
        file.write( line.toLocal8Bit() + "\n" );
    }

}

void GameWindow::showRecords()
{
    std::sort(begin(records), end(records));

    this->record_table->setRowCount(records.size());
    this->record_table->resizeColumnsToContents();
    for( uint row = 0; row < records.size(); ++row)
    {
        const Record & record = records[row];
        this->record_table->setItem( row, 0, new QTableWidgetItem( record.name ) );
        this->record_table->setItem( row, 1, new QTableWidgetItem( timeToString( record.time ) ) );
        this->record_table->setItem( row, 2, new QTableWidgetItem( QString::number(record.clicks ) ) );
        this->record_table->setRowHeight( row, 20 );
    }
    this->record_table->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    this->record_table->show();

}

void GameWindow::mousePressEvent( QMouseEvent *event )
{
    bool hit = false; //этот флаг хранит состояние попал\не попал
    for ( auto item = begin( items ); item != end( items ); ++item )
    {
        if( item->path.contains( event->pos() - item->position )&&event->button() == Qt::LeftButton )
        {
            QSound::play(":/recources/sounds/hit.wav");
            clickCount++;
            items.erase( item );
            hit = true;
            update();
            break;
        }
    }

    if( !hit && !items.empty() )
    {
        QSound::play(":/recources/sounds/miss.wav");
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
        //painter.rotate      ( QDateTime::currentMSecsSinceEpoch() % 360 );
        painter.setPen      ( { item.colorPen, 2 } );
        painter.fillPath    ( item.path, item.colorFill );
        painter.drawPath    ( item.path );
        painter.restore();  // вернули в прежнее состояние
    }

    Q_UNUSED( event );
}

QString GameWindow::timeElapsed()
{
    return timeToString( etimer->elapsed());
}

QString GameWindow::timeToString(qint64 time)
{
    qint64 sec = time / 1000;
    qint64 min = sec / 60;
    sec %= 60;
    min %= 60;
    QString timeElapsed = QString( "%1:%2" ).arg( min, 2, 10, QChar( '0' ) ).arg( sec, 2, 10, QChar( '0' ) );
    return timeElapsed;
}


GameWindow::~GameWindow()
{
    delete ui;
}




