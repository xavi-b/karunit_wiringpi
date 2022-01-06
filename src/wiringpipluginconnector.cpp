#include "wiringpipluginconnector.h"

KU_WiringPi_PluginConnector::KU_WiringPi_PluginConnector(QObject* parent)
    : KU::PLUGIN::PluginConnector(parent)
{
}

void KU_WiringPi_PluginConnector::setup()
{
}

void KU_WiringPi_PluginConnector::add(PinConnection* pin)
{
    this->pins.push_back(QVariant::fromValue(qobject_cast<QObject*>(pin)));
    emit pinsChanged();
}

void KU_WiringPi_PluginConnector::remove(int index)
{
    this->pins.removeAt(index);
    emit pinsChanged();
}

QString KU_WiringPi_PluginConnector::connectionSlotString(PinConnection::ConnectionType c) const
{
    return QVariant::fromValue(c).toString();
}
