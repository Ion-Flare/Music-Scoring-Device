/*
 * Creator: Ian Hudis 2019-2020
 * <ian.hudis@ndsu.edu>
 * share.dump(musicTrans)
*/
#ifndef RECORDINGPROCESS_H
#define RECORDINGPROCESS_H

#include <QDebug>
#include <QtCore>
#include<QThread>
#include <QObject>

#include <wiringPi.h>
#include "midihead/MidiFile.h"
#include "midihead/Binasc.h"
#include "midihead/MidiEvent.h"
#include "midihead/MidiEventList.h"
#include "midihead/MidiMessage.h"


using namespace smf;
using namespace std;

class recordingprocess : public QThread
{
    Q_OBJECT
public:

    explicit recordingprocess(QObject *parent = 0);
    MidiFile midifile;
      //QString name;
       bool record=false;
    int time;
       void run();

       //tick2-tick1 = length of note
        int track =0;
        int instr= 1;  // 1=piano

signals:

   void valueChanged(int);
   void shownote(QString);

public slots:

    void checknote(const int input, bool noteval,const int flash,int note,bool pressed[],QString label);
    void Flare(int flash1,int flash2,int flash3,int flash4,int flash5);

};

#endif // RECORDINGPROCESS_H
