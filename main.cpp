/*
 * Creator: Ian Hudis 2019-2020
 * <ian.hudis@ndsu.edu>
 * share.dump(musicTrans)
*/
#include "music.h"
#include "recordingprocess.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Music w;
    w.show();

    return a.exec();
}
