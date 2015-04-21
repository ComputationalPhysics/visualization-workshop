import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Particles 2.0

Window {
    title: qsTr("Hello World")
    width: 640
    height: 480
    visible: true

    Rectangle {
        anchors.fill: parent
        color: "blue"
    }

    ParticleSystem {
        id: particles
        anchors.fill: parent

        ImageParticle {
            source: "anders.jpg"
            alpha: 0.5
            colorVariation: 0.6
        }

        Emitter {
            id: burstEmitter
            x: rect.x
            y: rect.y
            emitRate: 10
            lifeSpan: 2000
            enabled: true
            velocity: AngleDirection {
                magnitudeVariation: 100
                magnitude: 64
                angleVariation: 360
            }
            size: 64
            sizeVariation: 32
        }
    }

    Rectangle {
        id: rect
        x: 209
        y: 172
        color: "red"
        width: 50
        height: 50

        MouseArea {
            anchors.fill: parent
            drag.target: parent
        }
    }
}
