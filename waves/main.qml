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

    Diffusion {
        id: simulator
        anchors.fill: parent

    }

    Timer {
        interval: 16
        running: true
        repeat: true
        onTriggered: {
            simulator.step()
        }
    }
}
