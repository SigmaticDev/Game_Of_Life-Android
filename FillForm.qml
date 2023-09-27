import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

Frame {
    property alias fillWithDead: fillWithDeadButton.checked
    property alias fillWithSoup: fillWithSoupButton.checked
    property alias soupDensity: soupDensityInput.value

    ColumnLayout {
        RadioButton {
            id: fillWithDeadButton

            text: "Fill With Dead Cells."
        }

        RadioButton {
            id: fillWithSoupButton

            text: "Fill With Soup."
        }

        Slider {
            id: soupDensityInput

            from: 0.0
            to: 1.0
            stepSize: 0.05
            value: 0.40
        }
    }
}
