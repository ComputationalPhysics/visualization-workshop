import QtQuick 2.0
import QtQuick.Controls 1.2

Item {
    width: 300
    height: 300

    Column {
        anchors.fill: parent
        Text {
            text: "Red:"
        }
        Slider {
            width: parent.width
        }
        Text {
            text: "Green:"
        }
        Slider {
            width: parent.width
        }
        Text {
            text: "Blue:"
        }
        Slider {
            width: parent.width
        }
    }
}
