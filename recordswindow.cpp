#include "recordswindow.h"
#include "ui_recordswindow.h"

RecordsWindow::RecordsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordsWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount( 4 );

    ui->tableWidget->setColumnWidth( 0, 100 );
    ui->tableWidget->setColumnWidth( 1, 100 );
    ui->tableWidget->setColumnWidth( 2, 100 );
    ui->tableWidget->setColumnWidth( 4, 100 );

    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("ID")));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Name")));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Time")));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("Clicks")));

    ui->tableWidget->setShowGrid(true);

    ui->tableWidget->setColumnHidden(0, true);

}

void RecordsWindow::on_add_name_button_clicked()
{
    ui->tableWidget->insertRow(0);
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(ui->name_Edit->text()));
}

void RecordsWindow::on_ok_button_clicked()
{

}

void RecordsWindow::on_close_button_clicked()
{

}

RecordsWindow::~RecordsWindow()
{
    delete ui;
}

