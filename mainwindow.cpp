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

void MainWindow::RecieveTime(const QString& hh,const QString& mm,const QString& ss,const QString& dss)
{
    SetTimeValues(hh, mm, ss, dss);

    if ((boolFlags >> 1) & 1)
    {
        GetRoundTime(ss);
        boolFlags = boolFlags & (~(1 << 1));
    }
}

void MainWindow::GetRoundTime(const QString& ss)
{
    ++rounds;
    roundText.append(msg_Round).append(QString::number(rounds)).append(msg_RoundTime).append(QString::number(ss.toUInt() - roundTime)).append(msg_RoundSec);
    ui->textBrowser->append(roundText);
    roundTime = ss.toUInt();
    roundText.clear();
}

void MainWindow::SetTimeValues(const QString& hh,const QString& mm,const QString& ss,const QString& dss) noexcept
{
    ui->lb_decseconds->setText(dss);
    ui->lb_seconds->setText(ss);
    ui->lb_minutes->setText(mm);
    ui->lb_hours->setText(hh);
}

void MainWindow::on_pb_Round_clicked()
{
    boolFlags = boolFlags | (1 << 1);
}

void MainWindow::on_pb_Clear_clicked()
{
    rounds=0; roundTime=0;
    SetTimeValues("0","0","0","0");
    ui->textBrowser->clear();
    emit sig_ClearTimer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

