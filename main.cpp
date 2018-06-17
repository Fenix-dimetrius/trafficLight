#include "trafficlights.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TrafficLights w;
    w.show();

    return a.exec();
}
