#include "dialogaudiosettings.h"
#include "ui_dialogaudiosettings.h"

DialogAudioSettings::DialogAudioSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAudioSettings)
{
    ui->setupUi(this);

    QAudioRecorder audioRecorder;

    auto Codecs = audioRecorder.supportedAudioCodecs();
    for(int i = 0; i < Codecs.count(); i++)
        ui->cmbCodec->addItem(Codecs.at(i));

    auto SampleRates = audioRecorder.supportedAudioSampleRates();
    for(int i = 0; i < SampleRates.count(); i++)
        ui->cmbSampleRates->addItem(QString::number(SampleRates.at(i)));

    auto Containers = audioRecorder.supportedContainers();
    for(int i = 0; i < Containers.count(); i++)
        ui->cmbContainers->addItem(Containers.at(i));

    auto Inputs = audioRecorder.audioInputs();
    for(int i = 0; i < Inputs.count(); i++)
        ui->cmbInputs->addItem(Inputs.at(i));

}

DialogAudioSettings::~DialogAudioSettings()
{
    delete ui;
}
