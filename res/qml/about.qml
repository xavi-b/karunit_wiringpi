import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

ScrollView {
    contentWidth: width

    Column {
        width: parent.width

        Label {
            width: parent.width
            wrapMode: Text.WordWrap
            leftPadding: 10
            rightPadding: leftPadding
            text: "karunit_wiringpi"
        }

        Label {
            width: parent.width
            wrapMode: Text.WordWrap
            leftPadding: 10
            rightPadding: leftPadding
            text: "<p>xavi-b/karunit_wiringpi</p>" + "LGPL 3.0 License"
        }

        Label {
            width: parent.width
            wrapMode: Text.WordWrap
            leftPadding: 10
            rightPadding: leftPadding
            text: "WiringPi"
        }

        Label {
            width: parent.width
            wrapMode: Text.WordWrap
            leftPadding: 10
            rightPadding: leftPadding
            text: "<p>xavi-b/WiringPi</p>" + "<p>WiringPi/WiringPi</p>" + "LGPL 3.0 License"
        }
    }
}
