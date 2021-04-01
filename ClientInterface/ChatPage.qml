import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.12

Page {
    id: root
    signal backButtonClicked();

    Rectangle {
        id: backgroundRect
        anchors.fill: parent
        visible: true
        color: "#242424"

        RoundButton {
            id: backButton
            x: 592
            y: 20
            width: 40
            height: 40
            implicitWidth: Math.max(
                               backButtonBackground ? backButtonBackground.implicitWidth : 0,
                               textItem.implicitWidth + leftPadding + rightPadding)
            implicitHeight: Math.max(
                                backButtonBackground ? backButtonBackground.implicitHeight : 0,
                                textItem.implicitHeight + topPadding + bottomPadding)

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
        }
    }
}
/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
