import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("User Latitude")

    ColumnLayout {
        anchors.fill: parent

        
        RowLayout {
            Rectangle {
                width: 200
                height: 40
                color: "gray"
                Text {
                    text: "Name"
                    color: "white"
                    anchors.centerIn: parent
                }
            }
            Rectangle {
                width: 100
                height: 40
                color: "gray"
                Text {
                    text: "Latitude"
                    color: "white"
                    anchors.centerIn: parent
                }
            }
        }

        
        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 10
            clip: true

            model: ListModel {
                id: userModel
            }

            delegate: RowLayout {
                Rectangle {
                    width: 200
                    height: 40
                    color: "lightgray"
                    Text {
                        text: model.name
                        anchors.centerIn: parent
                    }
                }
                Rectangle {
                    width: 100
                    height: 40
                    color: model.lat < 0 ? "red" : "green"
                    Text {
                        text: model.lat
                        anchors.centerIn: parent
                    }
                }
            }
        }
    }

    Connections {
        target: networkManager
        function onDataReady(data) {
            userModel.clear()
            for (var i = 0; i < data.length; ++i) {
                var user = data[i]
                userModel.append({
                    "name": user.name,
                    "lat": parseFloat(user.address.geo.lat)
                })
            }
        }
        function onErrorOccurred(error) {
            console.log("Error: " + error)
        }
    }
}