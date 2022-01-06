#ifndef WIRINGPI_H
#define WIRINGPI_H

#include <QObject>

class WiringPi : public QObject
{
    Q_OBJECT
private:
    WiringPi(QObject* parent = nullptr);
    static void callbackPinValueChanged(int pin);

public:
    static WiringPi* instance(QObject* parent = nullptr);
    static void      listenToPin(int pin, int mode);
    static int       readPin(int pin);

signals:
    void pinValueChanged(int);
};

#endif // WIRINGPI_H
