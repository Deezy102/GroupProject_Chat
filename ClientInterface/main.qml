import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: window
    property string userLogin
    visible: true
    width: 640
    height: 480
    minimumWidth: 640
    minimumHeight: 480
    color: "#242424"
    title: "SSSchat"

    property int defMargin: 10



    StackView {
        id: stackview
        anchors.fill: parent
        initialItem: logPage
    }

    LoginPage {
        id: logPage
        onSucAuth: {
            stackview.push(chatPage);
        }

    }

    ChatPage {
        id: chatPage
        visible: false

        onBackButtonClicked: {
            stackview.pop(logPage);
        }
    }
}



