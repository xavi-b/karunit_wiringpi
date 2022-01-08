import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Karunit 1.0
import KarunitPlugins 1.0

Item {
    anchors.fill: parent

    PinWizardPopup {
        id: popup
        parent: Overlay.overlay
        anchors.centerIn: parent
        width: parent.width - 50
        height: parent.height - 50

        modal: true
        focus: true
    }

    ListView {
        anchors.fill: parent
        id: listview
        model: KUPWiringPiPluginConnector.pins
        spacing: 5

        delegate: SwipeDelegate {
            id: swipeDelegate
            width: listview.width

            spacing: 5

            contentItem: RowLayout {
                Label {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: "PIN " + modelData.pin
                }
                Label {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: KUPWiringPiPluginConnector.connectionSlotString(
                              modelData.type)
                }
                Label {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: modelData.data
                }
                Label {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: "" + modelData.bouncingProtection
                }
            }

            ListView.onRemove: SequentialAnimation {
                PropertyAction {
                    target: swipeDelegate
                    property: "ListView.delayRemove"
                    value: true
                }
                NumberAnimation {
                    target: swipeDelegate
                    property: "height"
                    to: 0
                    easing.type: Easing.InOutQuad
                }
                PropertyAction {
                    target: swipeDelegate
                    property: "ListView.delayRemove"
                    value: false
                }
            }

            swipe.right: Label {
                id: deleteLabel
                text: qsTr("Delete")
                color: "white"
                verticalAlignment: Label.AlignVCenter
                padding: 12
                height: parent.height
                anchors.right: parent.right

                SwipeDelegate.onClicked: {
                    KUPWiringPiPluginConnector.remove(index)
                }

                background: Rectangle {
                    color: deleteLabel.SwipeDelegate.pressed ? Qt.darker(
                                                                   "tomato",
                                                                   1.1) : "tomato"
                }
            }
        }

        RoundButton {
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 5
            icon.name: "list-add"
            icon.color: "transparent"
            onClicked: {
                popup.open()
            }
        }
    }
}
