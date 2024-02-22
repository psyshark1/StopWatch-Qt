#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui{new Ui::MainWindow}
{
    ui->setupUi(this);
    stopW = new Stopwatch(quint16(100), this);
    QObject::connect(this, &MainWindow::sig_StartTimer, stopW, &Stopwatch::start);
    QObject::connect(this, &MainWindow::sig_StopTimer, stopW, &Stopwatch::stop);
    QObject::connect(stopW, &Stopwatch::sig_sendTime, this, &MainWindow::RecieveTime);
    QObject::connect(this, &MainWindow::sig_ClearTimer, stopW, &Stopwatch::clear);
}

void MainWindow::on_pb_StartStop_clicked()
{
    ((boolFlags >> 0) & 1) ? boolFlags = boolFlags & (~(1 << 0)) : boolFlags = boolFlags | (1 << 0);
    if ((boolFlags >> 0) & 1)
    {
        emit sig_StartTimer();
        ui->pb_StartStop->setText("Стоп");
        ui->pb_Round->setEnabled(true);
    }
    else
    {
        emit sig_StopTimer();
        ui->pb_StartStop->setText("Старт");
        ui->pb_Round->setEnabled(false);
    }
}

void MainWindow::RecieveTime(const quint32 &time)
{
    if(!(time % 36000))
    {
        mm = 0; ss = 0; ++hh;
    }
    else if(!(time % 600))
    {
        ss = 0; ++mm;
    }
    else if (!(time % 10))
    {
        ++ss;
    }

    ui->lb_decseconds->setText(QString::number(time % 10));

    SetTimeValues();

    if ((boolFlags >> 1) & 1)
    {
        GetRoundTime(time);
        boolFlags = boolFlags & (~(1 << 1));
    }
}

void MainWindow::GetRoundTime(const quint32 &time)
{
    ++rounds;
    roundText.append(msg_Round).append(QString::number(rounds)).append(msg_RoundTime).append(QString::number((time / 10) - roundTime)).append(msg_RoundSec);
    ui->textBrowser->append(roundText);
    roundTime = time / 10;
    roundText.clear();
}

void MainWindow::SetTimeValues() noexcept
{
    ui->lb_seconds->setText(QString::number(ss));
    ui->lb_minutes->setText(QString::number(mm));
    ui->lb_hours->setText(QString::number(hh));
}

void MainWindow::on_pb_Round_clicked()
{
    boolFlags = boolFlags | (1 << 1);
}

void MainWindow::on_pb_Clear_clicked()
{
    mm = 0; ss = 0; hh=0; rounds=0; roundTime=0;
    ui->lb_decseconds->setText("0");
    SetTimeValues();
    ui->textBrowser->clear();
    emit sig_ClearTimer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

