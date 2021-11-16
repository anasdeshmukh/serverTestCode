import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

Rectangle {
    id: page1
    width: 640
    height: 480
    color: "steelblue"

    property int readFile: 1

    Connections {
        target: Manager
        onMySignal:{
            msgDialog.show(str)
        }
    }

    Connections {
        target: Manager
        onNetworkReply:{
            console.log("response from server : ", xIsError, qstrStatus, qstrDataRead)
            if("ERROR" == qstrStatus) {
                msgDialog.show(qstrDataRead)
                fileNameInput.text = ""
            }
            else {
                msgDialog.show(qstrStatus)
            }
        }
    }

    Label {
        width: 552
        height: 41
        text: qsTr("Add Filename in textbox to create file on server, then press button to create file")
        anchors.verticalCenterOffset: -154
        anchors.horizontalCenterOffset: 0
        anchors.centerIn: parent
    }

    Button {
        text: "CreateFile"
        x: 470
        y: 122
        onClicked: {
            Manager.connectToInternet(page1.readFile, fileNameInput.text, "NA")
        }
    }

    Label {
        id: label
        x: 24
        y: 122
        width: 95
        height: 40
        text: qsTr("Filename :")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
        font.pointSize: 14
    }

    Rectangle {
        id: rectangle
        x: 125
        y: 122
        width: 334
        height: 40
        color: "#ffffff"
        border.width: 2
        border.color: "black"

        TextInput {
            id: fileNameInput
            x: 8
            y: 0
            width: 326
            height: 40
            text: "Text Input"
            selectByMouse: true
            activeFocusOnPress: true
            renderType: Text.QtRendering
            focus: true
            overwriteMode: true
            cursorVisible: true
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 14
        }
    }

    MessageDialog {
        id : msgDialog
        title: "Message Box"
        text: "file created. Ok."

        function show(caption) {
            msgDialog.text = caption
            msgDialog.open()
        }
    }
}
