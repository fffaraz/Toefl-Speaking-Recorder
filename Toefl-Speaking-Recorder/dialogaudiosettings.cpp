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

/*
 QStringList codecs = capture->supportedAudioCodecs();
     for(int i = 0; i < codecs.count(); i++)
         codecsBox->addItem(codecs.at(i));
*/
