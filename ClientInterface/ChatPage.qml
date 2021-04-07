import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.12
import "."

Page {
    id: root
    signal backButtonClicked();

    Rectangle {
        id: backgroundRect
        anchors.fill: parent
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        visible: true
        color: "#242424"



        ScrollView {
            id: chatSroll
            anchors.left: listView.right
            anchors.bottom: msgField.top
            anchors.top: backButton.bottom
            anchors.topMargin: 10

            width: parent.width - listView.width

            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ScrollBar.vertical.interactive: true


            ListView {
                id: chatView
                model: 20
                anchors.fill: parent

                delegate: ItemDelegate {
                    Text {
                        text: "Item " + index
                        color: "#ccc7c5c5"

                    }

                }
                highlightFollowsCurrentItem: false
            }

            focus: true

        }


        RoundButton {
            id: backButton

            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10

            width: 40
            height: 40
            visible: true
            font.pointSize: 12

            background: backButtonBackground

            contentItem: backTextItem

            onClicked: {
                root.backButtonClicked();

            }
            Text {
                id: backTextItem
                text: "<"
                color: "#ffffff"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.bold: false
                elide: Text.ElideRight

            }

            Rectangle {
                id: backButtonBackground
                width: 40
                height: 40
                visible: true
                color: "#00000000"
                border.color: "#ff0040"
                radius: 20
            }
        }

        TextField {
            id: msgField
            anchors.bottom: parent.bottom
            anchors.left: listView.right

            width: parent.width - listView.width - sendButton.width
            height: 40

            placeholderText: qsTr("Write message...")
            placeholderTextColor: "#ccc7c5c5"

            color: "#ffffff"
            font.pixelSize: 12


            background: msgFieldBackground

            Rectangle {
                id: msgFieldBackground
                anchors.fill: parent
                visible: true
                color: "#1f1f1f"
                border.color: "#ff0040"

            }


        }

        Button {
            id: sendButton
            anchors.bottom: parent.bottom
            anchors.right: parent.right

            width: 40
            height: 40
            background: sendButtonBackground
            contentItem: sendButtonItem

            onClicked: {
                client.receiveMessage(msgField.text)
                msgField.text = ""

            }

            Rectangle {
                id: sendButtonBackground

                anchors.fill: parent
                visible: true
                color: "#1f1f1f"
                border.color: "#ff0040"
            }

            Text {
                id:sendButtonItem
                anchors.fill: parent
                text: "^"
                color: "#ffffff"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.bold: false
                elide: Text.ElideRight
            }


        }



    ListView {
        id: listView
        anchors.left: parent.left
        anchors.top: parent.top
        width: parent.width * 0.3
        height: parent.height
        spacing: 20

        model: ["Chat 1", "Chat 2", "Chat 3"]

        delegate: ItemDelegate {
            text: modelData
            width: listView.width

        }
    }

    }
}
/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
