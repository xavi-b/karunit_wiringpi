#include "wiringpi.h"
#include <wiringPi/wiringPi.h>
#include <QDebug>

WiringPi::WiringPi(QObject* parent)
    : QObject(parent)
{
    qDebug() << "wiringPiSetup";
    wiringPiSetup();
}

void WiringPi::callbackPinValueChanged(int pin)
{
    emit WiringPi::instance()->pinValueChanged(pin);
}

WiringPi* WiringPi::instance(QObject* parent)
{
    static WiringPi instance(parent);
    return &instance;
}

void WiringPi::listenToPin(int pin, int mode)
{
    pinMode(pin, INPUT);
    pullUpDnControl(pin, PUD_DOWN);
    wiringPiISR(pin, mode, &WiringPi::callbackPinValueChanged);
}

int WiringPi::readPin(int pin)
{
    return digitalRead(pin);
}
