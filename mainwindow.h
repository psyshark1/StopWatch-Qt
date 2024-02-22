#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stopwatch.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_StartStop_clicked();
    void RecieveTime(const quint32& time);
    void on_pb_Round_clicked();
    void on_pb_Clear_clicked();

signals:
    void sig_StartTimer();
    void sig_StopTimer();
    void sig_ClearTimer();

private:
    Ui::MainWindow *ui;
    Stopwatch* stopW{nullptr};
    char boolFlags{0b00000000};
    //boolFlags pb_StartStop_STATE 0 bit
    //boolFlags pb_Round_STATE     1 bit
    static constexpr char msg_Round[10]{"Круг "};
    static constexpr char msg_RoundTime[15]{", время: "};
    static constexpr char msg_RoundSec[8]{" сек"};
    quint16 hh{0};
    quint16 mm{0};
    quint16 ss{0};
    quint8 rounds{0};
    quint32 roundTime{0};
    QString roundText{""};
    void GetRoundTime(const quint32 &time);
    void SetTimeValues() noexcept;
};
#endif // MAINWINDOW_H
