#ifndef PINCONNECTION_H
#define PINCONNECTION_H

#include <QObject>
#include <QVariant>

class PinConnection : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int value READ value NOTIFY valueChanged)
    Q_PROPERTY(int pin READ getPin WRITE setPin NOTIFY pinChanged)
    Q_PROPERTY(ConnectionType type READ getType WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString data READ getData WRITE setData NOTIFY dataChanged)

public:
    enum ConnectionType
    {
        PLUGIN_SLOT,
        PLUGIN_SHOW,
        PLUGIN_SLOT_DATA,
        SIZE
    };
    Q_ENUM(ConnectionType);

    PinConnection(QObject* parent = nullptr);
    PinConnection(int pin, ConnectionType type, QString data, QObject* parent = nullptr);
    int value() const;

    int  getPin() const;
    void setPin(int pin);

    ConnectionType getType() const;
    void           setType(ConnectionType type);

    QString getData() const;
    void    setData(QString data);

    static PinConnection* fromVariantMap(QVariantMap const& map);
    QVariantMap           toVariantMap() const;

signals:
    void valueChanged(int value);
    void pinChanged();
    void typeChanged();
    void dataChanged();

private:
    int            pin  = -1;
    ConnectionType type = PLUGIN_SLOT;
    QString        data; // slot or plugin id
};

#endif // PINCONNECTION_H
