#include "recordswindow.h"
#include "ui_recordswindow.h"

RecordsWindow::RecordsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordsWindow)
{
    ui->setupUi(this);
}

RecordsWindow::~RecordsWindow()
{
    delete ui;
}
