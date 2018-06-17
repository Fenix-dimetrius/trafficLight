#ifndef TRAFFICLIGHTS_H
#define TRAFFICLIGHTS_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QTime>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class TrafficLights;
}

class TrafficLights : public QMainWindow
{
    Q_OBJECT

public:
    explicit TrafficLights(QWidget *parent = 0);
    ~TrafficLights();



private slots:
    void on_pushButton_clicked();
    void updateTime();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::TrafficLights *ui;
    QTimer *tmr;
    int t_Red,t_Yellow,t_Green, t_RedYellow, t_GreenStrob, t_GreenOnStob, time_Buf,time_BufStrob,timer_tick;
    char Light;
    char *s1;
    QSerialPort serial;

    // WARNING! STUPID CODE DETECTED!
    void red();
    void yellow();
    void green();
    void redyel();
    void greenStrob();
    bool isGreenOn;


};

#endif // TRAFFICLIGHTS_H
