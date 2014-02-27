#include "dialogaudiosettings.h"
#include "ui_dialogaudiosettings.h"

DialogAudioSettings::DialogAudioSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAudioSettings)
{
    ui->setupUi(this);
}

DialogAudioSettings::~DialogAudioSettings()
{
    delete ui;
}
