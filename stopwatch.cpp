#include "stopwatch.h"

Stopwatch::Stopwatch(const quint16&& interval, QObject *parent) noexcept: QObject{parent}, qtimer{new QTimer(this)}
{
    qtimer->setInterval(interval);
    QObject::connect(qtimer, &QTimer::timeout, this, &Stopwatch::GetTime);

}

void Stopwatch::GetTime()
{
    ++tm;
    emit sig_sendTime(tm);
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
}

Stopwatch::~Stopwatch()
{

}
