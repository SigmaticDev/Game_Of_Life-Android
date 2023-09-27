import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts 1.15

Dialog {
    property alias simHeight: resizeOptions.simHeight
    property alias simWidth: resizeOptions.simWidth
    property alias simLooping: resizeOptions.simLooping

    title: "More Options"

    modal: true
    closePolicy: Popup.CloseOnEscape

    standardButtons: Dialog.Ok | Dialog.Cancel

    signal transmitDimensions(height: int, width: int)
    signal transmitLooping(loop: bool)
    signal generateBlank()
    signal generateSoup(density: real)

    onAccepted: {
        if (bar.currentIndex === 0) {
            transmitDimensions(resizeOptions.simHeight,
                               resizeOptions.simWidth);
            transmitLooping(resizeOptions.simLooping);
        } else if (bar.currentIndex === 1) {
            if (fillOptions.fillWithDead) {
                generateBlank()
            } else if (fillOptions.fillWithSoup) {
                generateSoup(fillOptions.soupDensity)
            }
        }
    }

    function setSimHeight(height) {
        resizeOptions.setSimHeight(height);
    }
    function setSimWidth(width) {
        resizeOptions.setSimWidth(width);
    }
    function setSimLooping(loop) {
        resizeOptions.setSimLooping(loop);
    }

    header: TabBar {
        id: bar

        TabButton {
            id: resizeButton
            text: qsTr("Resize")
        }

        TabButton {
            id: fillButton
            text: qsTr("Fill")
        }
    }

    StackLayout {
        id: optionsLayout
        currentIndex: bar.currentIndex

        Item {
            Layout.preferredHeight: resizeOptions.implicitHeight
            Layout.preferredWidth: resizeOptions.implicitWidth

            ResizeForm {
                id: resizeOptions
            }
        }

        Item {
            Layout.preferredHeight: fillOptions.implicitHeight
            Layout.preferredWidth: fillOptions.implicitWidth

            FillForm {
                id: fillOptions
            }
        }
    }

    Component.onCompleted: {
        standardButton(Dialog.Ok).contentItem.color = "black"
        standardButton(Dialog.Cancel).contentItem.color = "black"
        resizeButton.contentItem.color = "black"
        fillButton.contentItem.color = "black"
    }
}
