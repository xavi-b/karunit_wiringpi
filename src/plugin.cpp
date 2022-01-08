#include "plugin.h"
#include <QQmlEngine>

QString KU_WiringPi_Plugin::name() const
{
    return "WiringPi";
}

QString KU_WiringPi_Plugin::id() const
{
    return "karunit_wiringpi";
}

KU::PLUGIN::PluginVersion KU_WiringPi_Plugin::version() const
{
    return {1, 0, 0};
}

QString KU_WiringPi_Plugin::license() const
{
    return "LGPL";
}

QString KU_WiringPi_Plugin::icon() const
{
    return QString();
}

bool KU_WiringPi_Plugin::initialize()
{
    this->getPluginConnector()->setup();

    qmlRegisterSingletonInstance("KarunitPlugins", 1, 0, "KUPWiringPiPluginConnector", this->pluginConnector);
    qmlRegisterType<PinConnection>("KarunitPlugins", 1, 0, "KUPWiringPiPinConnection");

    return true;
}

bool KU_WiringPi_Plugin::stop()
{
    return true;
}

bool KU_WiringPi_Plugin::loadSettings()
{
    int size = KU::Settings::instance()->beginReadArray("logins");
    for (int i = 0; i < size; ++i)
    {
        KU::Settings::instance()->setArrayIndex(i);
        PinConnection* pin = PinConnection::fromVariantMap(KU::Settings::instance()->value("pin").toMap());
        this->getPluginConnector()->add(pin);
    }
    KU::Settings::instance()->endArray();
    return true;
}

bool KU_WiringPi_Plugin::saveSettings()
{
    auto list = this->getPluginConnector()->getPins();
    KU::Settings::instance()->beginWriteArray(id() + "/pins");
    for (int i = 0; i < list.size(); ++i)
    {
        KU::Settings::instance()->setArrayIndex(i);
        KU::Settings::instance()->setValue("pin", list[i].value<PinConnection*>()->toVariantMap());
    }
    KU::Settings::instance()->endArray();
    KU::Settings::instance()->sync();
    return KU::Settings::instance()->status() == QSettings::NoError;
}

KU_WiringPi_PluginConnector* KU_WiringPi_Plugin::getPluginConnector()
{
    if (this->pluginConnector == nullptr)
        this->pluginConnector = new KU_WiringPi_PluginConnector;
    return qobject_cast<KU_WiringPi_PluginConnector*>(this->pluginConnector);
}
