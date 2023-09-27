import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

Frame {
    property alias simHeight: heightInput.value
    property alias simWidth: widthInput.value
    property alias simLooping: loopingInput.checked

    function setSimHeight(height) {
        heightInput.value = height;
    }
    function setSimWidth(width) {
        widthInput.value = width;
    }
    function setSimLooping(loop) {
        loopingInput.checked = loop;
    }

    ColumnLayout {
        RowLayout {
            Label {
                id: heightLabel

                text: "Simulation Height:"
            }

            SpinBox {
                id: heightInput

                editable: true

                from: 1
                stepSize: 1
                to: 1000
            }
        }

        RowLayout {
            Label {
                id: widthLabel

                text: "Simulation Width:"
            }

            SpinBox {
                id: widthInput

                editable: true

                from: 1
                stepSize: 1
                to: 1000
            }
        }

        RowLayout {
            CheckBox {
                id: loopingInput
            }

            Label {
                id: loopingLabel

                text: "Looping Borders?"

                MouseArea {
                    anchors.fill: parent

                    onClicked: loopingInput.toggle()
                }
            }
        }
    }
}
