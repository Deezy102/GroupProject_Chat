import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

Page {
    id: root
    signal sucAuth();
    signal sendLogin(string login);

    background: Rectangle {
        anchors.fill: parent
        visible: true
        color: "#242424"
    }

    Connections {
        target: client

        onServerSucReg: {
            popup.open()
        }

        onServerFailReg: {
            incorrect.text = "Choose another login"
            incorrect.visible = true
        }

        onClientFailVerifpass: {
            incorrect.text = "Incorrect login or password\nOr password and verified password are not equal"
            incorrect.visible = true

        }

        onServerSucAuth: {
            root.sucAuth()
            incorrect.visible = false
        }

        onServerFailAuth: {
            incorrect.text = "Sign In failed"
            incorrect.visible = true
        }
    }

    Popup {
        id: popup
        anchors.centerIn: Overlay.overlay
        width: 200
        height: 150
        modal: true
        focus: true



        Button {
            id: okButton
            anchors.centerIn: parent
            text: "Ok"

            onClicked: popup.close()
        }

        contentItem: Text {
            anchors.centerIn: parent
            font.pixelSize: 18
            text: "Successful registration"
        }
    }


    Text {
        id: incorrect
        height: 40
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: verifyPasswordField.bottom
        anchors.topMargin: 10
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        visible: false
        color: "#FF0040"
        font.pixelSize: 12
    }

    Text {
        id: textWellcome
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 69
        color: "#ffffff"
        text: "Wellcome!"
        font.pixelSize: 24
        font.bold: true
    }



    Button {
        id: signin_button
        anchors.top: verifyPasswordField.bottom
        anchors.topMargin: 40
        anchors.horizontalCenter: parent.horizontalCenter
        width: 100
        height: 40

        background: signInButtonBackground
        contentItem: signInTextItem

        onClicked: {
            client.receiveLogData(usernameField.text, passwordField.text)
            userLogin = usernameField.text
            //root.sucAuth() //DELETE THIS!!!
        }

        Text {
            id: signInTextItem
            text: "Sign In"
            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: false
            elide: Text.ElideRight
        }

        Rectangle {
            id: signInButtonBackground
            implicitWidth: 100
            implicitHeight: 40
            color: "#242424"
            border.color: "#FF0040"
            border.width: 1
            anchors.fill: parent
            radius: 20
        }
    }


    Button {
        id: signup_button
        anchors.top: signin_button.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        width: 100
        height: 40
        visible: false

        background: signUpButtonBackground

        contentItem: signUpTextItem


        onClicked: {
            client.receiveRegData(usernameField.text, passwordField.text, verifyPasswordField.text)
        }

        Text {
            id: signUpTextItem
            text: "Sign Up"

            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: false
            elide: Text.ElideRight
        }

        Rectangle {
            id: signUpButtonBackground
            implicitWidth: 100
            implicitHeight: 40
            opacity: enabled ? 1 : 0.3
            color: "#242424"
            border.color: "#FF0040"
            border.width: 1
            anchors.fill: parent
            radius: 20
        }

    }

    Button {
        id: signUpSwitchButton
        anchors.top: signin_button.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        width: 100
        height: 40

        background: signUpSwitchButtonBackground

        contentItem: signUpSwitchTextItem

        Text {
            id: signUpSwitchTextItem
            text: "Sign Up"

            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: false
            elide: Text.ElideRight
        }

        Rectangle {
            id: signUpSwitchButtonBackground
            implicitWidth: 100
            implicitHeight: 40

            color: "#242424"
            border.color: "#FF0040"
            border.width: 1
            anchors.fill: parent
            radius: 20
        }

        Connections {
            target: signUpSwitchButton
            onClicked: root.state = "signupState"
        }
    }

    Button {
        id: reconnectButton
        width: 124
        height: 78
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10

        Image {
            id: ghoul_eye
            anchors.fill: parent
            width: 124
            source: "ghoul_eye.png"
            fillMode: Image.PreserveAspectFit
        }

        onClicked: client.reconnect()
    }
    RoundButton {
        id: backButton
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        width: 40
        height: 40
        visible: false

        font.pointSize: 12

        background: backButtonBackground

        contentItem: backTextItem

        Text {
            id: backTextItem
            text: "<"
            opacity: enabled ? 1.0 : 0.3
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


        Connections {
            target: backButton
            onClicked: root.state = "signinState"
        }
    }

    TextField {
        id: usernameField
        width: 200
        height: 40
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: textWellcome.bottom
        anchors.topMargin: 40

        placeholderTextColor: "#ccc7c5c5"
        placeholderText: qsTr("Username")

        color: "#ffffff"
        background: usernameFieldBackground

        Rectangle {
            id: usernameFieldBackground
            width: 200
            height: 40
            color: "#00000000"
            border.color: "#ff0040"
            anchors.fill: parent
        }
    }

    TextField {
        id: passwordField
        width: 200
        height: 40
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: usernameField.bottom
        anchors.topMargin: 10

        placeholderTextColor: "#ccc7c5c5"
        placeholderText: qsTr("Password")
        echoMode: TextInput.Password

        color: "#ffffff"
        background: passwordFieldBackground

        Rectangle {
            id: passwordFieldBackground
            width: 200
            height: 40
            color: "#00000000"
            border.color: "#ff0040"
            anchors.fill: parent
        }

    }

    TextField {
        id: verifyPasswordField
        width: 200
        height: 40
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: passwordField.bottom
        anchors.topMargin: 10
        echoMode: TextInput.Password

        placeholderTextColor: "#ccc7c5c5"
        placeholderText: qsTr("Verify password")

        color: "#ffffff"
        background: verifyPasswordFieldBackground

        Rectangle {
            id: verifyPasswordFieldBackground
            width: 200
            height: 40
            color: "#00000000"
            border.color: "#ff0040"
            anchors.fill: parent
        }
    }
    states: [
        State {
            name: "signinState"

            PropertyChanges {
                target: incorrect
                visible: false
            }

            PropertyChanges {
                target: backButton
                visible: false
            }

            PropertyChanges {
                target: verifyPasswordField
                visible: false
            }
        },
        State {
            name: "signupState"

            PropertyChanges {
                target: incorrect
                visible: false
            }

            PropertyChanges {
                target: backButton
                visible: true
            }


            PropertyChanges {
                target: usernameField
                font.pointSize: 8
                placeholderTextColor: "#ccc7c5c5"
            }

            PropertyChanges {
                target: verifyPasswordField
                visible: true
                placeholderTextColor: "#ccc7c5c5"
            }

            PropertyChanges {
                target: passwordField
                placeholderTextColor: "#ccc7c5c5"
            }

            PropertyChanges {
                target: signup_button
                visible: true
            }

            PropertyChanges {
                target: signUpSwitchButton
                visible: false
            }

            PropertyChanges {
                target: signin_button
                visible: false
            }
        }

    ]
    transitions: [
        Transition {
            id: transition
            ParallelAnimation {
                SequentialAnimation {
                    PauseAnimation {
                        duration: 50
                    }

                    PropertyAnimation {
                        property: "x"
                        duration: 150
                    }
                }

                SequentialAnimation {
                    PauseAnimation {
                        duration: 50
                    }

                    PropertyAnimation {
                        property: "y"
                        duration: 150
                    }
                }
            }
            to: "*"
            from: "*"
        }
    ]

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
