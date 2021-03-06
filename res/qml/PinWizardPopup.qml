import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Karunit 1.0
import KarunitPlugins 1.0

Popup {
    id: popup

    closePolicy: Popup.CloseOnEscape
    clip: true

    KUPWiringPiPinConnection {
        id: pin
    }

    contentItem: Item {
        anchors.fill: parent
        anchors.margins: 5

        SwipeView {
            id: view
            currentIndex: 0
            clip: true

            anchors.top: parent.top
            anchors.bottom: row.top
            anchors.left: parent.left
            anchors.right: parent.right

            Page {
                function updateData() {
                    pin.pin = pinCombobox.currentIndex
                }

                header: Label {
                    width: parent.width
                    horizontalAlignment: Qt.AlignHCenter
                    text: qsTr("Select pin")
                }

                ComboBox {
                    anchors.centerIn: parent
                    width: 300
                    id: pinCombobox
                    model: 64
                    displayText: "PIN " + currentText
                    delegate: ItemDelegate {
                        text: "PIN " + modelData
                    }
                }
            }
            Page {
                function updateData() {
                    pin.type = pinType.currentIndex
                }

                header: Label {
                    width: parent.width
                    horizontalAlignment: Qt.AlignHCenter
                    text: qsTr("Select connection type")
                }

                ComboBox {
                    anchors.centerIn: parent
                    width: 300
                    id: pinType
                    model: KUPWiringPiPinConnection.SIZE
                    displayText: KUPWiringPiPluginConnector.connectionSlotString(
                                     currentText)
                    delegate: ItemDelegate {
                        text: KUPWiringPiPluginConnector.connectionSlotString(
                                  modelData)
                    }
                }
            }
            Page {
                function updateData() {
                    pin.data = pinData.currentValue
                }

                header: Label {
                    width: parent.width
                    horizontalAlignment: Qt.AlignHCenter
                    text: qsTr("Select connection data")
                }

                ComboBox {
                    anchors.centerIn: parent
                    width: 300
                    id: pinData
                    model: pin.type == KUPWiringPiPinConnection.PLUGIN_SHOW ? KUInstance.widgetPlugins : KUInstance.availableSlots
                    delegate: ItemDelegate {
                        text: modelData
                    }
                }
            }
            Page {
                function updateData() {
                    pin.bouncingProtection = pinBouncingProtection.checked
                }

                header: Label {
                    width: parent.width
                    horizontalAlignment: Qt.AlignHCenter
                    text: qsTr("Add bouncing protection")
                }

                Switch {
                    anchors.centerIn: parent
                    width: 300
                    id: pinBouncingProtection
                    checked: pin.bouncingProtection
                }
            }
        }

        Row {
            id: row
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            spacing: 5

            Button {
                text: view.currentIndex == 0 ? qsTr("Close") : qsTr("Back")
                onClicked: {
                    if (view.currentIndex == 0) {
                        popup.close()
                    } else {
                        view.decrementCurrentIndex()
                    }
                }
            }

            Button {
                text: view.currentIndex == view.count - 1 ? qsTr("Finish") : qsTr(
                                                                "Next")
                onClicked: {
                    view.currentItem.updateData()
                    if (view.currentIndex == view.count - 1) {
                        KUPWiringPiPluginConnector.add(pin)
                        popup.close()
                    } else {
                        view.incrementCurrentIndex()
                    }
                }
            }
        }
    }
}
