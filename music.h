/*
 * Creator: Ian Hudis 2019-2020
 * <ian.hudis@ndsu.edu>
 * share.dump(musicTrans)
*/
#ifndef MUSIC_H
#define MUSIC_H

#include "recordingprocess.h"
//#include "wiringPi.h"
#include "midihead/Binasc.h"
#include "midihead/MidiEvent.h"
#include "midihead/MidiEventList.h"
#include "midihead/MidiFile.h"
#include "midihead/MidiMessage.h"
#include <QMainWindow>
#include <random>
#include <iostream>

class recordingprocess;

using namespace smf;
using namespace std;

namespace Ui {
class Music;
}

class Music : public QMainWindow
{
    Q_OBJECT

public:

    explicit Music(QWidget *parent = 0);
    ~Music();

       int value() const { return m_value; }


public slots:

     void setValue(int value);
     void printNote(QString);

private slots:

    void Write(QString n);

    void on_Record_clicked();
    void on_StopRecord_clicked();
    void on_ExportMidi_clicked();

private:

    Ui::Music *ui;
int m_value;
int n=0;

};

#endif // MUSIC_H
