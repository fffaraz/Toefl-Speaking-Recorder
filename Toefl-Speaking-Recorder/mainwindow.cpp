#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isStarted = false;
    ui->btnStart->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_btnStart_clicked()
{
    if(!isStarted)
    {
        isStarted = true;
        ui->btnSkip->setEnabled(true);
        ui->btnStart->setText("Stop");
    }
    else
    {
        isStarted = false;
        ui->btnSkip->setEnabled(false);
        ui->btnStart->setText("Start");
    }
}
