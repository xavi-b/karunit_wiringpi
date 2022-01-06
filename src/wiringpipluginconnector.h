#ifndef WIRINGPIPLUGINCONNECTOR_H
#define WIRINGPIPLUGINCONNECTOR_H

#include <QQmlContext>
#include <wiringPi/wiringPi.h>
#include "plugininterface.h"
#include "settings.h"

class KU_WiringPi_PluginConnector : public KU::PLUGIN::PluginConnector
{
    Q_OBJECT

public:
    KU_WiringPi_PluginConnector(QObject* parent = nullptr);
    void setup();

signals:

private:
};

#endif // WIRINGPIPLUGINCONNECTOR_H
