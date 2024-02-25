#include "stopwatch.h"

Stopwatch::Stopwatch(const quint16&& interval, QObject *parent) noexcept: QObject{parent}, qtimer{new QTimer(this)}
{
    qtimer->setInterval(interval);
    QObject::connect(qtimer, &QTimer::timeout, this, &Stopwatch::GetTime);

}

void Stopwatch::GetTime()
{
    ++tm;

    if(!(tm % 36000))
    {
        mm = 0; ss = 0; ++hh;
    }
    else if(!(tm % 600))
    {
        ss = 0; ++mm;
    }
    else if (!(tm % 10))
    {
        ++ss;
    }

    emit sig_sendTime(QString::number(hh),QString::number(mm),QString::number(ss),QString::number(tm % 10));
}

void Stopwatch::start()
{
    qtimer->start();
}

void Stopwatch::stop()
{
    qtimer->stop();
}

void Stopwatch::clear()
{
    tm = 0;
    mm = 0; ss = 0; hh=0;
}

Stopwatch::~Stopwatch()
{

}
