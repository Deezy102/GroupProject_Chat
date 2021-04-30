import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.12

Page {
    id: root
    signal backButtonClicked();
    property string inConversationWith : ""
    property string userLogin : "Pudge_bez_moma"

    background: Rectangle {
        anchors.fill: parent
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        visible: true
        color: "#242424"
    }
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
                anchors.left: toolBar.left
                anchors.top: toolBar.top
                implicitWidth: 30
                implicitHeight: 30


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
                onClicked: {
                    menu.open()
                    console.log("menu clicked")
                }
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
                anchors.right: toolBar.right
                anchors.top: toolBar.top
                implicitWidth: 30
                implicitHeight: 30

                Text {
                    width: 30
                    height: 30
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
    Drawer {
        id: menu
        height: parent.height
        width: parent.width * 0.3
        background: Rectangle {color: "#333333"}
        clip: true

        Rectangle {
            id: userLoginRect
            height: 80
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            color: "#1f1f1f"

            Text {
                text: userLogin
                anchors.fill: parent
                color: "#ff0040"
                font.pixelSize: 16
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }
        ListView {
            id: menuList
            anchors.top: userLoginRect.bottom
            width: menu.width
            height: parent.height - userLoginRect.height
            model: ["Create Chat", "Contacts", "Etc"]
            delegate: ItemDelegate {
                width: menu.width
                Text {
                    text: modelData
                    color: "#ffffff"
                    anchors.fill: parent
                    font.pixelSize: 14
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

                }
                focus: true


            }
        }
    }

    ScrollView {
        id: chatListScroll
        anchors.top: toolBar.top
        anchors.bottom: root.bottom
        anchors.left: root.left
        width: parent.width * 0.3
        height: root.height-toolBar.height
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.interactive: true
        ListView {
            id: chatListView
            anchors.left: parent.left
            anchors.top: parrent.top
            anchors.bottom: parent.bottom
            height: parent.height - toolBar.height
            model: ["Chat 1", "Chat 2", "Chat 3", "Chat 2", "Chat 3", "Chat 2", "Chat 3", "Chat 2", "Chat 3", "Chat 2", "Chat 3", "Chat 2", "Chat 3", "Chat 2", "Chat 3"] //скорее всего надо подгружать модель с сервера при каждом логине или добавлении чата

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
    }
    ScrollView {
        id: chatScroll
        anchors.top: parent.top
        anchors.bottom: msgField.top
        anchors.right: parent.right
        width: parent.width * 0.7
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.interactive: true


        ListView {
            id: chatView
            anchors.top: toolBar.bottom
            anchors.bottom: msgField.top
            anchors.right: root.right
            width: root.width * 0.7
            model: ["Message 1", "Message 2", "Message 3", "Message 3", "Message 3", "Message 3", "Message 3", "Message 3", "Message 3", "Message 3", "Message 3", "Message 3", "Message 3"] //надо подгружать с сервера
            delegate: ItemDelegate {
                Text {
                    text: modelData
                    width: chatView.width
                    color: "#ffffff"
                }
            }
        }
    }
    TextField {
        id: msgField
        anchors.bottom: parent.bottom
        anchors.right: sendButton.left

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
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
