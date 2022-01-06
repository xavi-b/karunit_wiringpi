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

    return true;
}

bool KU_WiringPi_Plugin::stop()
{
    return true;
}

bool KU_WiringPi_Plugin::loadSettings()
{
    return true;
}

bool KU_WiringPi_Plugin::saveSettings() const
{
    return KU::Settings::instance()->status() == QSettings::NoError;
}

KU_WiringPi_PluginConnector* KU_WiringPi_Plugin::getPluginConnector()
{
    if (this->pluginConnector == nullptr)
        this->pluginConnector = new KU_WiringPi_PluginConnector;
    return qobject_cast<KU_WiringPi_PluginConnector*>(this->pluginConnector);
}
