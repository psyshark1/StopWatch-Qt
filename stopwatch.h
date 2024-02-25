#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>

class Stopwatch : public QObject
{
    Q_OBJECT
public:
    explicit Stopwatch(const quint16&& interval, QObject *parent = nullptr) noexcept;
    QTimer* qtimer{nullptr};
    ~Stopwatch();
private:
    quint32 tm{0};
    quint16 hh{0};
    quint16 mm{0};
    quint16 ss{0};

public slots:
    void GetTime();
    void start();
    void stop();
    void clear();
signals:
    void sig_sendTime(const QString& hh,const QString& mm,const QString& ss,const QString& dss);
};

#endif // STOPWATCH_H
