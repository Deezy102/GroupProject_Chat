import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Page {
    id: root
    signal signInButtonClicked();

    Rectangle {
        id: backgroundRect
        anchors.fill: parent
        visible: true
        color: "#242424"


        Text {
            id: text1
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 69
            color: "#ffffff"
            text: qsTr("Wellcome!")
            font.pixelSize: 24
            anchors.horizontalCenterOffset: 0
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
                root.signInButtonClicked()
            }

            Text {
                id: signInTextItem
                text: "Sign In"

                opacity: enabled ? 1.0 : 0.3
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
                opacity: enabled ? 1 : 0.3
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

                opacity: enabled ? 1.0 : 0.3
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

                opacity: enabled ? 1.0 : 0.3
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
                opacity: enabled ? 1 : 0.3
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

        Image {
            id: ghoul_eye
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 20
            width: 124
            source: "ghoul_eye.png"
            fillMode: Image.PreserveAspectFit
        }

        RoundButton {
            id: backButton
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            width: 40
            height: 40
            visible: false
            implicitWidth: Math.max(
                               backButtonBackground ? backButtonBackground.implicitWidth : 0,
                               textItem.implicitWidth + leftPadding + rightPadding)
            implicitHeight: Math.max(
                                backButtonBackground ? backButtonBackground.implicitHeight : 0,
                                textItem.implicitHeight + topPadding + bottomPadding)

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
                function onClicked() {
                    page.state = "signinState"
                }
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
            anchors.top: text1.bottom
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
    }
    states: [
        State {
            name: "signinState"

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