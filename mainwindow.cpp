//install libasound2 and libasound2-dev

#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "arecordmidi.c"
#include <QDebug>
#include <QProcess>

#include <QDateTime>



#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <signal.h>
#include <getopt.h>
#include <sys/poll.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <signal.h>
#include <getopt.h>
#include <sys/poll.h>
#include <alsa/include/asoundlib.h>
//#include <alsa/include/aconfig.h>
#include <alsa/include/config.h.in>
#include <alsa/include/version.h>

//


#include <linux/soundcard.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int mrid;
int mrport;


QProcess process1;
QProcess process2;
QProcess process3;
QProcess process4;


static int queue;


QList<QString> nameAr;
QList<QString> clientAr;
QList<QString> portAr;






MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //

        //


#define perm_ok(pinfo,bits) ((snd_seq_port_info_get_capability(pinfo) & (bits)) == (bits))
snd_seq_t *seq;
snd_seq_open(&seq, "default", SND_SEQ_OPEN_DUPLEX, 0);
//

    mrid = snd_seq_client_id(seq);
    //qDebug() <<  mrid;

    mrport = snd_seq_set_client_name(seq, "MidiRecorder");
    //qDebug() <<  mrport;

    //
    snd_seq_client_info_t *cinfo;
    snd_seq_port_info_t *pinfo;
    //



        snd_seq_port_info_alloca(&pinfo);


        snd_seq_port_info_set_capability(pinfo,
                         SND_SEQ_PORT_CAP_WRITE |
                         SND_SEQ_PORT_CAP_SUBS_WRITE);
        snd_seq_port_info_set_type(pinfo,
                       SND_SEQ_PORT_TYPE_MIDI_GENERIC |
                       SND_SEQ_PORT_TYPE_APPLICATION);
        snd_seq_port_info_set_midi_channels(pinfo, 16);


        snd_seq_port_info_set_timestamping(pinfo, 1);
        snd_seq_port_info_set_timestamp_queue(pinfo, queue);




//



    snd_seq_client_info_alloca(&cinfo);
    snd_seq_port_info_alloca(&pinfo);
    snd_seq_client_info_set_client(cinfo, -1);
    while (snd_seq_query_next_client(seq, cinfo) >= 0)

    {
            snd_seq_port_info_set_client(pinfo, snd_seq_client_info_get_client(cinfo));
            snd_seq_port_info_set_port(pinfo, -1);

            int seldd;

            while (snd_seq_query_next_port(seq, pinfo) >= 0)
                if (    perm_ok
                        (pinfo, SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ))
                            {
                                QString pname = snd_seq_port_info_get_name(pinfo);
                               //qDebug() << pname;
                                nameAr.append(pname);
                                int icnum = snd_seq_client_info_get_client(cinfo);
                                QString scnum = QString::number(icnum);
                               //qDebug() << scnum;
                               clientAr.append(scnum);
                                int ipnum = snd_seq_port_info_get_port(pinfo);
                                QString spnum = QString::number(ipnum);
                               //qDebug() << spnum;
                                portAr.append(spnum);
                               seldd++;


                            }




     }


    ui->comboBoxClients->addItems(nameAr);
}






void MainWindow::slotrec()

{
//qDebug() << "Recording midi";


    //process1.start("gnome-terminal -x bash -c \"arecordmidi -l\"");
     //process3.start("gnome-terminal -x bash -c \"aconnect -o\"");
      //process2.start("gnome-terminal -x bash -c \"aconnect -i\"");


      int getmididev = ui->comboBoxClients->currentIndex();
      //qDebug() << getmididev;

      QString getclient =  clientAr[getmididev];
      int igetclient = getclient.toInt();
      //qDebug() << igetclient;

      QString getport =  portAr[getmididev];
      int igetport = getport.toInt();
      //qDebug() << igetport;


      QDateTime local(QDateTime::currentDateTime());

     QString dt = local.toString("yyyyMMddhhmmss");

       QString filename = "AlsaMidiRec" + dt + ".midi";

         //qDebug() << filename;



   // process1.start("gnome-terminal -x bash -c \"arecordmidi -p 20:0 m.midi\"");

       QString acommand = "gnome-terminal -x bash -c \"arecordmidi -p " + getclient + ":" + getport + " " + filename;

       //qDebug() << acommand;

       process1.start(acommand);





 //qDebug() <<  mrid;




 ui->statusBar->showMessage("Recording");



}





void MainWindow::slotstop()

{
 ui->statusBar->showMessage("");
    //process1.start("gnome-terminal -x bash -c \"arecordmidi -l\"");
     //process3.start("gnome-terminal -x bash -c \"aconnect -o\"");
      //process2.start("gnome-terminal -x bash -c \"aconnect -i\"");

 //qDebug() << nameAr;



    //signal(SIGINT, sighandler);
   // signal(SIGTERM, sighandler);

//int pidr = getpid();
//int pidr = fork();

 char buf[512];
 FILE *cmd_pipe = popen("pidof -s arecordmidi", "r");

 fgets(buf, 512, cmd_pipe);
 pid_t pid = strtoul(buf, NULL, 10);

 pclose( cmd_pipe );

QString pidrs = QString::number(pid);
 //qDebug() << pidrs  ;

 //QString comend = "gnome-terminal -x bash -c \"kill -INT " + pidrs + "\"";

 kill (pid, SIGINT);
  kill (pid, SIGTERM);

  //qDebug() << comend;
//process4.start(comend);




      //aconnect -i


//process1.terminate(SIGINT);
//process.close();
}






MainWindow::~MainWindow()
{
    delete ui;
}
