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
    connect(pin, &PinConnection::valueChanged, this, [=](int value) {
        emitLogSignal("Signal from pin: " + QString::number(pin->getPin()));
        if (pin->getType() == PinConnection::PLUGIN_SHOW)
        {
            emitLogSignal("PLUGIN_SHOW");
            emitShowPluginSignal(pin->getData());
        }
        else
        {
            if (pin->getType() == PinConnection::PLUGIN_SLOT)
            {
                emitLogSignal("PLUGIN_SLOT");
                emitPluginSignal(pin->getData());
            }

            if (pin->getType() == PinConnection::PLUGIN_SLOT_DATA)
            {
                emitLogSignal("PLUGIN_SLOT_DATA");
                QVariantMap data;
                data.insert("pinValue", value);
                emitPluginDataSignal(pin->getData(), data);
            }
        }
    });
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

QVariantList KU_WiringPi_PluginConnector::getPins()
{
    return this->pins;
}
