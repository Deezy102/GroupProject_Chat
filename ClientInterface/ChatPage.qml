import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.12

Page {
    id: root
    signal backButtonClicked();
    property string inConversationWith : ""



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
                background: Rectangle {color: "#333333"}
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
                ToolButton {
                    id: chatInfoButton
                    implicitHeight: 30
                    implicitWidth: parent.width
                    anchors.fill: parent
                    background: Rectangle {color: "transparent"}
                    enabled: false
                    onClicked: {
                        console.log("chat info clicked")
                        chatInfoPopup.open()
                    }

                }


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
//                Button { //chatCreateButton
//                    width: menu.width
//                    height: 40
//                    background: Rectangle {color: "#333333"}
//                    onClicked: {
//                        menu.close()
//                        chatCreationForm.open()
//                    }
//                }

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
    Popup {
        id: chatCreationForm
        height: 200
        width: 320
        anchors.centerIn: parent
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        contentItem: Rectangle {
            color: "#333333"
            anchors.fill: parent
            TextField {
                id: chatname
                width: 320
                height: 40
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter

                placeholderText: qsTr("Write Chat Name...")
                placeholderTextColor: "#ccc7c5c5"

                color: "#ffffff"
                font.pixelSize: 12

                background: Rectangle {
                    anchors.fill: parent
                    visible: true
                    color: "#1f1f1f"
                    border.color: "#ff0040"

                }
            }
            TextField {
                id: contact
                width: 320
                height: 40
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter

                placeholderText: qsTr("Write User Name...")
                placeholderTextColor: "#ccc7c5c5"

                color: "#ffffff"
                font.pixelSize: 12

                background: Rectangle {
                    anchors.fill: parent
                    visible: true
                    color: "#1f1f1f"
                    border.color: "#ff0040"

                }
            }


            Button {
                id: createChatButton

                anchors.bottom: parent.bottom
                anchors.right: parent.right

                width: 80
                height: 40
                background: Rectangle {
                    anchors.fill: parent
                    visible: true
                    color: "#1f1f1f"
                    border.color: "#ff0040"
                }

                Text {
                    anchors.fill: parent
                    text: "Create"
                    color: "#ffffff"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.bold: false
                    elide: Text.ElideRight
                }

                onClicked: client.receiveChatCreation(chatname.text, contact.text)
            }
        }

    }
    Popup {
        id: chatInfoPopup
        anchors.centerIn: parent
        height: (root.height - toolBar.height) * 0.9
        width: 300
        modal: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        contentItem: Rectangle {
            color: "#333333"
            anchors.fill: parent

            Rectangle {
                id: chatnameRect
                color: "#1f1f1f"
                border.color: "#ff0040"
                anchors.top: parent.top
                width: parent.width
                height: 80

                Text {
                    text: inConversationWith
                    anchors.fill: parent
                    color: "#ff0040"
                    font.pixelSize: 16
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            TextField {
                id: newUserName
                width: parent.width
                height: 40
                anchors.top: chatnameRect.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter

                placeholderText: qsTr("Write New User...")
                placeholderTextColor: "#ccc7c5c5"

                color: "#ffffff"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.bold: false

                background: Rectangle {
                    anchors.fill: parent
                    visible: true
                    color: "#1f1f1f"
                    border.color: "#ff0040"

                }
            }

            Button {
                id: adduserButton
                height: 40
                width: 80
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                background: Rectangle {
                    anchors.fill: parent
                    visible: true
                    color: "#1f1f1f"
                    border.color: "#ff0040"
                }

                Text {
                    anchors.fill: parent
                    text: "Add user"
                    color: "#ffffff"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.bold: false
                    elide: Text.ElideRight
                }
                onClicked: {
                    client.receiveAddUserToChat(inConversationWith, newUserName.text)
                }

            }
        }
    }

    TextField {
        id: chatField
        anchors.top: toolBar.bottom

        width: parent.width * 0.3
        height: 40

        placeholderText: qsTr("Write chat...")
        placeholderTextColor: "#ccc7c5c5"

        color: "#ffffff"
        font.pixelSize: 12


        background: Rectangle {
            anchors.fill: parent
            visible: true
            color: "#1f1f1f"
            border.color: "#ff0040"

        }
        Keys.onPressed: { if (event.key == Qt.Key_Return) client.receiveCurrenChat(chatField.text);}

    }
    ScrollView {
        id: chatListScroll
        anchors.top: chatField.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width * 0.3
        height: root.height-toolBar.height - chatField
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.interactive: true
        Text {
            id: chatList
            anchors.left: parent.left
            anchors.top: chatField.bottom
            width: root.width * 0.3
            height: root.height-toolBar.height-chatField
            color: "#ffffff"
            text: client.chats
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 14
            font.bold: false
            elide: Text.ElideRight
        }
    }
    ScrollView {
        id: msgScroll
        anchors.top: parent.top
        anchors.bottom: msgField.top
        anchors.right: parent.right
        width: parent.width * 0.7
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.interactive: true

        Text {
            id: msgList
            width: root.width * 0.7
            height: root.height - toolBar.height - msgField
            color: "#ffffff"
            text: client.messages
            leftPadding: 20
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 14
            font.bold: false
            elide: Text.ElideRight
        }
    }
    TextField {
        id: msgField
        anchors.bottom: parent.bottom
        anchors.right: sendButton.left

        width: parent.width * 0.7- sendButton.width
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
    Connections {
        target: client

        onCorrectChat: {
            inConversationWith = chatField.text
            chatField.placeholderText = qsTr("Write chat...")
            chatField.text = ""
        }

        onIncorrectChat: {
            chatField.text = ""
            chatField.placeholderText = "Try again"
        }
        onChatsChanged: {
            chatList.text = client.chats
        }

        onMessageChanged: {
            msgList.text = client.messages
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
