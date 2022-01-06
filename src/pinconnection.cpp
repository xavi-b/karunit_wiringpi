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
            emit valueChanged();
    });
}

int PinConnection::value() const
{
    return WiringPi::readPin(pin);
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
            emit valueChanged();
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
