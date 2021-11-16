import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

Rectangle {
    id: page2
    width: 640
    height: 480
    color: "steelblue"

    property int readFile: 3

    Connections {
        target: Manager
        onNetworkReply:{
            console.log("response from server : ", xIsError, qstrStatus, qstrDataRead)
            if("ERROR" == qstrStatus) {
                msgDialog.show(qstrDataRead)
                fileNameInput.text = ""
                textFileEdit.text = ""
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
        id: button
        x: 470
        y: 122
        text: qsTr("Create File")

        onClicked: {
            Manager.connectToInternet(page2.readFile, fileNameInput.text, textFileEdit.text)
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
            text: "Enter Filename here"
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

    Rectangle {
        id: rectangle1
        x: 125
        y: 168
        width: 334
        height: 200
        color: "#ffffff"
        border.width: 2

        TextEdit {
            id: textFileEdit
            x: 8
            y: 8
            width: 308
            height: 184
            text: qsTr("Enter data to be write.")
            font.pixelSize: 12

//            ScrollView {
//                id: scrollView
//                x: 304
//                y: 0
//                width: 30
//                height: 200
//            }
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
