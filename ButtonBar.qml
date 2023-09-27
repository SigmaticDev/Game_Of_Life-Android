import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

Frame {
    RowLayout {
        IconButton {
            id: pauseButton
            iconSource: "assets/icons/pauseButton.png"
            toolTipText: "Stop the Simulation"
            onClicked: pauseSim()
        }
        IconButton {
            id: oneStepButton
            iconSource: "assets/icons/advanceOneStepButton.png"
            toolTipText: "Advance the Simulation One Step"
            onClicked: stepSim()
        }
        IconButton {
            id: playButton
            iconSource: "assets/icons/playButton.png"
            toolTipText: "Play at 1x Speed"
            onClicked: playSim()
        }
        IconButton {
            id: fastForwardButton
            iconSource: "assets/icons/fastForwardButton.png"
            toolTipText: "Play at 2x Speed"
            onClicked: fastForwardSim()
        }

        IconButton {
            id: saveButton
            iconSource: "assets/icons/saveButton.png"
            toolTipText: "Save to File"
            onClicked: saveSim()
        }

        IconButton {
            id: loadButton
            iconSource: "assets/icons/loadButton.png"
            toolTipText: "Load from File"
            onClicked: loadSim()
        }

        IconButton {
            id: optionsButton
            iconSource: "assets/icons/optionsButton.png"
            toolTipText: "More Options"
            onClicked: openSimOptions()
        }
    }

    signal pauseSim()
    signal stepSim()
    signal playSim()
    signal fastForwardSim()
    signal saveSim()
    signal loadSim()
    signal openSimOptions()
}
