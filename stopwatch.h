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

public slots:
    void GetTime();
    void start();
    void stop();
    void clear();
signals:
    void sig_sendTime(const quint32& tm);
};

#endif // STOPWATCH_H
