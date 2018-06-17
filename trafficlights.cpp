#include "trafficlights.h"
#include "ui_trafficlights.h"

TrafficLights::TrafficLights(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrafficLights)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(407, 385)); //фиксируем размер окна

    // Задаем начальные параметры
    timer_tick = 1;
    t_Red = 8000;
    t_Yellow = 2000;
    t_RedYellow = 2000;
    t_Green = 8000;
    t_GreenStrob = 2000;
    t_GreenOnStob = 500;
    time_BufStrob = 0;
    time_Buf = 0;
    Light = 'g';

    // показываем начальные пораметры на форме
    ui->Red_lineEdit->setText(QString::number(t_Red));
    ui->RedYel_lineEdit->setText(QString::number(t_RedYellow));
    ui->Yel_lineEdit->setText(QString::number(t_Yellow));
    ui->Green_lineEdit->setText(QString::number(t_Green));
    ui->GreStob_lineEdit->setText(QString::number(t_GreenStrob));
    ui->Timer_lineEdit->setText(QString::number(t_GreenOnStob));

    // запускаем таймер
    tmr = new QTimer();
    tmr->setInterval(timer_tick);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    tmr->start();

    // настройки COM
    // считываем доступные порты
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
                ui->comboBox->addItem(info.portName());
}

TrafficLights::~TrafficLights()
{
    delete ui;
}


void TrafficLights::on_pushButton_clicked()
{

    t_GreenStrob = ui->GreStob_lineEdit->text().toInt();
    t_GreenOnStob = ui->Timer_lineEdit->text().toInt();
    tmr->stop();
    tmr->setInterval(timer_tick);
    tmr->start();
    t_Red =  ui->Red_lineEdit->text().toInt();
    t_Yellow = ui->Yel_lineEdit->text().toInt();
    t_RedYellow = ui->RedYel_lineEdit->text().toInt();
    t_Green = ui->Green_lineEdit->text().toInt();
    time_Buf = 0;
    Light = 'g';
}

void TrafficLights::red()
{
    ui->Red_Label->hide();
    ui->Yellow_label->show();
    ui->Green_label->show();
}

void TrafficLights::yellow()
{
    ui->Red_Label->show();
    ui->Yellow_label->hide();
    ui->Green_label->show();
}

void TrafficLights::green()
{
    ui->Red_Label->show();
    ui->Yellow_label->show();
    ui->Green_label->hide();
    isGreenOn = true;
}

void TrafficLights::redyel()
{
    ui->Red_Label->hide();
    ui->Yellow_label->hide();
    ui->Green_label->show();
}

void TrafficLights::greenStrob()
{
    ui->Red_Label->show();
    ui->Yellow_label->show();
    ui->Green_label->show();
}

void TrafficLights::updateTime()
{

ui->lcdNumber->display(time_Buf);
    switch (Light) {
    case 'w':
    {
        redyel();
        if (time_Buf>=t_RedYellow)
        {
           Light = 'g';
           if(serial.isOpen())
           {
             serial.putChar('g');

           }
           green();
           time_Buf = -1;
        }
        break;
    }
    case 'r':
    {
        red();
        if (time_Buf>=t_Red)
        {
           Light = 'w';
           if(serial.isOpen())
           {
             serial.putChar('w');

           }
           redyel();
           time_Buf = -1;
        }
        break;

    }

    case 'y':
    {
        yellow();;
        if (time_Buf>=t_Yellow)
        {
            Light = 'r';
           if(serial.isOpen())
           {
             serial.putChar('r');

           }

           red();
           time_Buf = -1;
        }


        break;
    }

    case 's':
    {

        if (time_BufStrob>=t_GreenOnStob)
        {
            time_BufStrob = 0;
            if (!isGreenOn)
               {
                green();

                if(serial.isOpen())
                {
                    serial.putChar('g');

                }
            }
            else
            {
              greenStrob();
              isGreenOn = false;
              if(serial.isOpen())
              {
                serial.putChar('k');

              }
            }

        }
        time_BufStrob++;
        if (time_Buf>=t_GreenStrob)
        {

           Light = 'y';
           if(serial.isOpen())
           {
             serial.putChar('y');

           }

           //yellow();
           time_Buf = -1;

        }
        break;
    }

    case 'g':
    {
        green();
        if (time_Buf>=t_Green)
        {

           Light = 's';
           if(serial.isOpen())
           {
             serial.putChar('k');

           }
           greenStrob();
           isGreenOn = false;

           //yellow();
           time_Buf = -1;

        }
        break;
    }


    default:
        break;
    }
    time_Buf++;


   // serial.getChar(s1);
    //ui->label_8->setText(QString(s1));

}

void TrafficLights::on_pushButton_2_clicked()
{
    if (serial.portName() != ui->comboBox->currentText())
        {
              serial.close();
              serial.setPortName(ui->comboBox->currentText());
        }

        //setup COM port
        serial.setBaudRate(QSerialPort::Baud9600);
        serial.setDataBits(QSerialPort::Data8);
        serial.setParity(QSerialPort::NoParity);
        serial.setStopBits(QSerialPort::OneStop);
        serial.setFlowControl(QSerialPort::NoFlowControl);
        serial.open(QSerialPort::WriteOnly);
}

void TrafficLights::on_pushButton_3_clicked()
{
//        if(serial.isOpen())
//        {
//           serial.putChar('y');
//        }
}

void TrafficLights::on_pushButton_4_clicked()
{
//    if(serial.isOpen())
//    {
//       serial.putChar('r');
//    }
}
