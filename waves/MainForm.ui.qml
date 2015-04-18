import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {
    id: item1
    width: 640
    height: 480

    TestBanana {
        id: testBanana1
        x: 270
        y: 79
        anchors.horizontalCenter: parent.horizontalCenter
        baseColor: "#0000ff"
    }

    TestBanana {
        id: testBanana2
        x: 190
        y: 146
        anchors.top: testBanana1.bottom
        anchors.topMargin: 6
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.horizontalCenter: testBanana1.horizontalCenter
        anchors.right: testBanana1.right
        anchors.left: testBanana1.left
        baseColor: "#ffbb00"
    }
}
