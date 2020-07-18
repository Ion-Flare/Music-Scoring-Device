/*
 * Creator: Ian Hudis 2019-2020
 * <ian.hudis@ndsu.edu>
 * share.dump(musicTrans)
*/
#include "recordingprocess.h"
#include <QtCore>

recordingprocess::recordingprocess(QObject *parent) : QThread(parent)
{
    time=0;
    midifile.addTimbre(track,10,2,instr);


}

void recordingprocess::run(){


        const int flash1=21; const int flash2=22; const int flash3=23;
        const int flash4=24; const int flash5=25;

        const int in5=29; const int in4=6; const int in3=27;
        const int in2=28; const int in1=26;

        wiringPiSetup();

        pinMode(in1,INPUT);
        pinMode(in2,INPUT);
        pinMode(in3,INPUT);
        pinMode(in4,INPUT);
        pinMode(in5,INPUT);

        bool b1=false;
        bool b2=false;
        bool b3=false;
        bool b4=false;
        bool b5=false;

        pinMode(flash5,OUTPUT); pinMode(flash4,OUTPUT); pinMode(flash3,OUTPUT);
        pinMode(flash2,OUTPUT); pinMode(flash1,OUTPUT);


        bool pressed_toggle[88];
        for (int i=0;i<88;i++){
            pressed_toggle[i]=true;
        }

      Flare(flash1,flash2,flash3,flash4,flash5);
        while(record){

            time++;
            emit valueChanged(time);


            checknote(in1,b1,flash1,71,pressed_toggle,"B4");
            checknote(in2,b2,flash2,72,pressed_toggle,"C5");
            checknote(in3,b3,flash3,73,pressed_toggle,"C5#");
            checknote(in4,b4,flash4,74,pressed_toggle,"D5");
            checknote(in5,b5,flash5,75,pressed_toggle,"E5");

delay(9.9);

    }
}

        void recordingprocess::checknote(const int input, bool noteval,const int flash,int note,bool pressed[],QString label)
        {
            if(digitalRead(input)!=LOW){ noteval=true; }else{ noteval=false;}

            if (noteval){
                digitalWrite(flash,HIGH);
                if(pressed[note]){
                    midifile.addNoteOn(track,time,100,note,30);
                    emit shownote(label+" " +QString::number(time));
                    pressed[note]=false;
                }

            }else{
                digitalWrite(flash,LOW);
                if(!pressed[note]){
                   midifile.addNoteOff(track,time,100,note);
              }
                pressed[note]=true;
            }

        }


void recordingprocess::Flare(int flash1,int flash2,int flash3,int flash4,int flash5){
    digitalWrite(flash1,HIGH);
    digitalWrite(flash2,LOW);
    delay(150);
    digitalWrite(flash2,HIGH);
    digitalWrite(flash1,LOW);
     delay(150);
     digitalWrite(flash2,LOW);
     digitalWrite(flash3,HIGH);
     delay(150);
     digitalWrite(flash3,LOW);
     digitalWrite(flash4,HIGH);
     delay(150);
     digitalWrite(flash4,LOW);
     digitalWrite(flash5,HIGH);
     delay(150);
     digitalWrite(flash5,LOW);
     digitalWrite(flash4,HIGH);
     delay(150);
     digitalWrite(flash4,LOW);
     digitalWrite(flash3,HIGH);
      delay(150);
      digitalWrite(flash3,LOW);
      digitalWrite(flash2,HIGH);
      delay(150);
      digitalWrite(flash2,LOW);
   }
