/*
 * Creator: Ian Hudis 2019-2020
 * <ian.hudis@ndsu.edu>
 * share.dump(musicTrans)
*/
#include "music.h"
#include "ui_music.h"


#include <midihead/MidiFile.h>

#include <QThread>
#include <QElapsedTimer>
#include <QCoreApplication>
#include <QDebug>


recordingprocess recording; //background thread for picking up notes



Music::Music(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Music)
{
    ui->setupUi(this);

    //generally color
    ui->statusBar->setStyleSheet("background-color:#90efff");
    ui->mainToolBar->setStyleSheet("background-color:#000000");
    ui->background->setStyleSheet("background-color:black;");
    ui->Record->setStyleSheet("background-color: #90efff;");
    ui->StopRecord->setStyleSheet("background-color: #90efff;");
    ui->ExportMidi->setStyleSheet("background-color: #80ffb0;");
    ui->status->setStyleSheet("color: #90efff;");
    ui->filelabel->setStyleSheet("color: #90efff;");
    ui->timer->setStyleSheet("color: #ffaf10;");
     Write("Command Log \n");

    ui->cmd->setPalette(Qt::black);
    ui->cmd->setStyleSheet("color: #00efff");
    ui->cmd->ensureCursorVisible();

//font size
    QFont font = ui->cmd->font();
    font.setPointSize(13);
    ui->cmd->setFont(font);

    QFont font1 = ui->Record->font();
    font1.setPointSize(16);
    ui->Record->setFont(font1);

    QFont font2 = ui->StopRecord->font();
    font2.setPointSize(15);
    ui->StopRecord->setFont(font2);

    QFont font3 = ui->Record->font();
    font3.setPointSize(15);
    ui->ExportMidi->setFont(font3);


    QFont font4 = ui->filelabel->font();
    font4.setPointSize(14);
    ui->filelabel->setFont(font4);

    QFont font5 = ui->filename->font();
    font5.setPointSize(14);
    ui->filename->setFont(font5);

    //signal stuff
  connect(&recording, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
  connect(&recording,SIGNAL(shownote(QString)),this,SLOT(printNote(QString)));

}

Music::~Music()
{
    delete ui;
}


void Music::on_Record_clicked(){
ui->status->setText("Recording...");
ui->timer->setText("0");

recording.time=0;
recording.start();
recording.record=true;
Write("Recording Started");

}

void Music::on_StopRecord_clicked(){
    ui->status->setText("Recording Stopped.");

    recording.record=false;
    Write("Recording Ended");
}

void Music::on_ExportMidi_clicked(){

    ui->status->setText("Midi exported.");

    //takes name from bottum and saves the file

    QString name=ui->filename->toPlainText();

    if(name.size()!=0){
QString nameandextension=name+".midi";
std::string utf8_text = nameandextension.toUtf8().constData();
    recording.midifile.sortTracks();
    recording.midifile.write(utf8_text);
    Write(nameandextension+" was exported.");
}else{
        Write("Please give the midi file a name.");
    }

}

void Music::setValue(int value)
{
    if (value != m_value) {
        m_value = value;
        ui->timer->setText(QString::number(m_value));
    }
}

void Music::printNote(QString note){
   Write("Played Note: " + note);
}

void Music::Write(QString n){
ui->cmd->insertPlainText(QString::fromLatin1("%1 \n").arg(n));
}
