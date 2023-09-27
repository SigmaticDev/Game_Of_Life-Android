import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

Window {
    id: window
    width: Screen.width
    height: Screen.height
    visible: true
    title: qsTr("Game of Life Test")

    ColumnLayout {
        anchors.fill: parent

        Frame {
            implicitWidth: parent.width

            Layout.fillHeight: true

            SimulationView {
                id: gameOfLife

                height: parent.height < parent.width ? parent.height : parent.width
                width: parent.height < parent.width ? parent.height : parent.width

                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter

                model: cellModel
            }
        }
        ButtonBar {
            implicitWidth: parent.implicitWidth

            onPauseSim: {
                simTimer.running = false
                simTimer.repeat = false
            }

            onStepSim: {
                simTimer.running = false
                simTimer.repeat = false
                gameOfLife.model.nextStep()
            }

            onPlaySim: {
                simTimer.interval = 200
                simTimer.running = true
                simTimer.repeat = true
            }

            onFastForwardSim: {
                simTimer.interval = 100
                simTimer.running = true
                simTimer.repeat = true
            }

            onOpenSimOptions: {
                // Stop the simulation
                simTimer.running = false
                simTimer.repeat = false

                // Load model data into forms in optionsDialog
                optionsDialog.setSimHeight(gameOfLife.model.rowCount())
                optionsDialog.setSimWidth(gameOfLife.model.columnCount())
                optionsDialog.setSimLooping(gameOfLife.model.loopingBorders())

                optionsDialog.open()
            }
        }
    }

    OptionsDialog {
        id: optionsDialog

        x: parent.width/2 - width/2
        y: parent.height/2 - height/2

        onTransmitDimensions: {
            gameOfLife.model.resize(height, width);
        }
        onTransmitLooping: {
            gameOfLife.model.setLoopingBorders(loop);
        }
        onGenerateBlank: {
            gameOfLife.model.clearAll();
        }
        onGenerateSoup: {
            gameOfLife.model.fillWithSoup(density);
        }
    }

    Timer {
        id: simTimer

        interval: 200
        running: false
        repeat: true
        onTriggered: gameOfLife.model.nextStep()
    }
}
