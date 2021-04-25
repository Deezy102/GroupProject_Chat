import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.12

Page {
    id: root
    signal backButtonClicked();

    property string inConversationWith : "chatName"


    background: backgroundRect

    header: ToolBar {
        id: toolBar
        background: Rectangle {
            implicitHeight: 30
            color: "#333333"
        }

        RowLayout {
            anchors.fill: parent
            ToolButton {
                id: menuButton
                Layout.leftMargin: 5

                Text {
                    text: "⋮"
                    anchors.fill: menuButton
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    color: "#ffffff"
                    font.pixelSize: 16
                }
                background: Rectangle {
                    color: "#333333"
                }
                onClicked: menu.open()
            }

            Label {
                text: root.inConversationWith
                color: "#ffffff"
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
                font.pixelSize: 16
            }

            ToolButton {
                id: backButton
                Layout.rightMargin: 5
                Text {
                    text: "<"
                    anchors.fill: backButton
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    color: "#ffffff"
                    font.pixelSize: 16
                }
                background: Rectangle {
                    color: "#333333"
                }
                onClicked: backButtonClicked()
            }
        }
    }






    ScrollView {
        id: chatSroll
        anchors.left: chatListView.right
        anchors.bottom: msgField.top
        anchors.top: parent.top

        width: parent.width - chatListView.width

        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.interactive: true


        ListView {
            id: chatView
            anchors.fill: parent
            model: ["Message 1", "Message 2", "Message 3", "Message 3", "Message 3", "Message 3", "Message 3", "Message 3", "Message 3", "Message 3", "Message 3", "Message 3", "Message 3"] //надо подгружать с сервера


            delegate: ItemDelegate {
                Text {
                    text: modelData
                    width: chatView.width
                    color: "#ffffff"

                }

            }
        }

        focus: true

    }

    ListView {
        id: chatListView
        anchors.left: parent.left
//        anchors.top: backButton.bottom
        width: parent.width * 0.3
        height: availableHeight
        spacing: 20

        model: ["Chat 1", "Chat 2", "Chat 3"] //скорее всего надо подгружать модель с сервера при каждом логине или добавлении чата

        delegate: ItemDelegate {
            Text {
                text: modelData
                color: "#ffffff"
            }
            width: chatListView.width
            onClicked: {
                console.log("clicked:", modelData)
                root.inConversationWith = modelData
            }

        }
    }


    //        RoundButton {
    //            id: backButton

    //            anchors.top: parent.top
    //            anchors.topMargin: 10
    //            anchors.right: parent.right
    //            anchors.rightMargin: 10

    //            width: 40
    //            height: 40
    //            visible: true
    //            font.pointSize: 12

    //            background: backButtonBackground

    //            contentItem: backTextItem

    //            onClicked: {
    //                root.backButtonClicked();

    //            }
    //            Text {
    //                id: backTextItem
    //                text: "<"
    //                color: "#ffffff"
    //                horizontalAlignment: Text.AlignHCenter
    //                verticalAlignment: Text.AlignVCenter
    //                font.bold: false
    //                elide: Text.ElideRight

    //            }

    //            Rectangle {
    //                id: backButtonBackground
    //                width: 40
    //                height: 40
    //                visible: true
    //                color: "#00000000"
    //                border.color: "#ff0040"
    //                radius: 20
    //            }
    //        }

    TextField {
        id: msgField
        anchors.bottom: parent.bottom
        anchors.left: chatListView.right

        width: parent.width - chatListView.width - sendButton.width
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






}
/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:11}
}
##^##*/
