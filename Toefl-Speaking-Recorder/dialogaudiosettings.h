#ifndef DIALOGAUDIOSETTINGS_H
#define DIALOGAUDIOSETTINGS_H

#include <QDialog>

namespace Ui {
class DialogAudioSettings;
}

class DialogAudioSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAudioSettings(QWidget *parent = 0);
    ~DialogAudioSettings();

private:
    Ui::DialogAudioSettings *ui;
};

#endif // DIALOGAUDIOSETTINGS_H
