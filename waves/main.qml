import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import Workshop 1.0

ApplicationWindow {
    title: qsTr("Hello World")
    width: 640
    height: 480
    visible: true

    Waves {
        id: simulator
        anchors.fill: parent
        color: Qt.rgba(redSlider.value, greenSlider.value, blueSlider.value)
        courant: courantSlider.value
    }

    Column {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        width: parent.width * 0.3

        Slider {
            id: redSlider
            width: parent.width
            value: 1.0
        }

        Slider {
            id: greenSlider
            width: parent.width
            value: 1.0
        }

        Slider {
            id: blueSlider
            width: parent.width
            value: 1.0
        }

        Slider {
            id: courantSlider
            width: parent.width
            value: 0.25
            minimumValue: 0.01
            maximumValue: 0.5
        }

        Slider {
            id: intervalSlider
            minimumValue: 1
            maximumValue: 200
            value: 16
        }
    }

    Timer {
        interval: intervalSlider.value
        running: true
        repeat: true
        onTriggered: {
            simulator.step()
        }
    }
}
