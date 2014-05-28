#include "dialogabout.h"
#include "ui_dialogabout.h"

DialogAbout::DialogAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAbout)
{
    ui->setupUi(this);
    ui->lblInfo->setOpenExternalLinks(true);
    ui->lblDeveloper->setOpenExternalLinks(true);
}

DialogAbout::~DialogAbout()
{
    delete ui;
}

void DialogAbout::on_pushButton_clicked()
{
    this->done(0);
}
