import QtQuick 2.15
import QtQuick.Controls

Button {
    required property url iconSource
    required property string toolTipText

    implicitHeight: 40
    implicitWidth: 40

    hoverEnabled: true

    background: Rectangle {
        implicitHeight: parent.implicitHeight
        implicitWidth: parent.implicitWidth

        border.width: 2
        border.color: "black"

        color: parent.pressed ? "#8e8e8e" : "#d8d8d8"
    }

    contentItem: Image {
        source: iconSource
    }

    ToolTip.delay: 1000
    ToolTip.text: toolTipText
    ToolTip.timeout: 5000
    ToolTip.visible: hovered
}
