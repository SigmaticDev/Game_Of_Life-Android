import QtQuick 2.15

TableView {
    // Property Declarations
    property real cellScale: 10

    // Signal Declarations
    // Signal Handler Attributes
    // JavaScript Functions
    // Object Properties
    implicitHeight: 400
    implicitWidth: 400


    delegate: Rectangle {
        implicitHeight: cellScale
        implicitWidth: cellScale

        border.width: 1
        border.color: "black"
        color: model.living ? "#424242" : "#cacaca"

        MouseArea {
            anchors.fill: parent

            onClicked: model.living = !model.living
        }
    }

    // Child Objects
    // States
    // Transitions
}
