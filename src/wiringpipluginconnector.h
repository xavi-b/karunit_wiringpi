#ifndef WIRINGPIPLUGINCONNECTOR_H
#define WIRINGPIPLUGINCONNECTOR_H

#include <QQmlContext>
#include "plugininterface.h"
#include "pinconnection.h"
#include "settings.h"

class KU_WiringPi_PluginConnector : public KU::PLUGIN::PluginConnector
{
    Q_OBJECT
    Q_PROPERTY(QVariantList pins MEMBER pins NOTIFY pinsChanged)

public:
    KU_WiringPi_PluginConnector(QObject* parent = nullptr);
    void setup();

    Q_INVOKABLE void    add(PinConnection* pin);
    Q_INVOKABLE void    remove(int index);
    Q_INVOKABLE QString connectionSlotString(PinConnection::ConnectionType c) const;

signals:
    void pinsChanged();

private:
    QVariantList pins;
};

#endif // WIRINGPIPLUGINCONNECTOR_H
