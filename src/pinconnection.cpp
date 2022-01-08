#include "pinconnection.h"
#include "wiringpi.h"
#include <wiringPi/wiringPi.h>

PinConnection::PinConnection(QObject* parent)
    : QObject(parent)
{
}

PinConnection::PinConnection(int pin, ConnectionType type, QString data, QObject* parent)
    : QObject(parent),
      pin(pin),
      type(type),
      data(data)
{
    WiringPi::instance()->listenToPin(pin, INT_EDGE_BOTH);
    connect(WiringPi::instance(), &WiringPi::pinValueChanged, this, [=](int pin) {
        if (pin == this->pin)
            emit valueChanged(WiringPi::instance()->readPin(pin));
    });
}

int PinConnection::value() const
{
    return WiringPi::readPin(pin);
}

void PinConnection::changeValue(int value)
{
    if (!this->bouncingProtection)
        emit valueChanged(value);
    else
    {
        if (!bouncingProtectionTimer.isActive())
        {
            bouncingProtectionTimer.setSingleShot(true);
            bouncingProtectionTimer.start(500);
            emit valueChanged(value);
        }
    }
}

int PinConnection::getPin() const
{
    return this->pin;
}

void PinConnection::setPin(int pin)
{
    this->pin = pin;
    WiringPi::instance()->listenToPin(pin, INT_EDGE_BOTH);
    disconnect(WiringPi::instance(), &WiringPi::pinValueChanged, this, nullptr);
    connect(WiringPi::instance(), &WiringPi::pinValueChanged, this, [=](int pin) {
        if (pin == this->pin)
            changeValue(WiringPi::instance()->readPin(pin));
    });
    emit pinChanged();
}

PinConnection::ConnectionType PinConnection::getType() const
{
    return this->type;
}

void PinConnection::setType(ConnectionType type)
{
    this->type = type;
    emit typeChanged();
}

QString PinConnection::getData() const
{
    return this->data;
}

void PinConnection::setData(QString data)
{
    this->data = data;
    emit dataChanged();
}

bool PinConnection::getBouncingProtection() const
{
    return this->bouncingProtection;
}

void PinConnection::setBouncingProtection(bool b)
{
    this->bouncingProtection = b;
    emit bouncingProtectionChanged();
}

PinConnection* PinConnection::fromVariantMap(QVariantMap const& map)
{
    PinConnection* pin = new PinConnection;
    pin->setPin(map["pin"].toInt());
    pin->setType(static_cast<ConnectionType>(map["type"].toInt()));
    pin->setData(map["data"].toString());
    pin->setBouncingProtection(map["bouncingProtection"].toBool());
    return pin;
}

QVariantMap PinConnection::toVariantMap() const
{
    QVariantMap map;
    map["pin"]                = pin;
    map["type"]               = static_cast<int>(type);
    map["data"]               = data;
    map["bouncingProtection"] = bouncingProtection;
    return map;
}
