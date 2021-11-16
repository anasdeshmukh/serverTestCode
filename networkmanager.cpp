
#include "networkmanager.h"
#include <QScriptValueIterator>

netWorkManager::netWorkManager()
    : mNetMan()
    , mDataBuffer()
    , iCurrentFileOperation(0)
    , qstrCurrentFileName()
{
    connect(&mNetMan, &QNetworkAccessManager::finished, this, &netWorkManager::onResult);
    connect (&mNetMan, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),
             this, SLOT(onAuthenticationRequestSlot(QNetworkReply*,QAuthenticator*)) );
}

void netWorkManager::resetFileNameAndOperation()
{
    iCurrentFileOperation = 0;
    qstrCurrentFileName.clear();
}

void netWorkManager::connectToInternet(int iFileOperation, QString qstrFileName, QString qstrFileContent)
{
    switch (iFileOperation) {
    case 1:
        connectToCreate(qstrFileName);
        break;
    case 2:
        connectToRead(qstrFileName);
        break;
    case 3:
        connectToWrite(qstrFileName , qstrFileContent);
    }
}

void netWorkManager::connectToCreate(QString qstrFileName)
{
    qDebug() << Q_FUNC_INFO;
    QUrl url("https://orbvpn.com/panel/system/rest_api/test_api.php?");
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray byteData("{\"action\":\"CreateFile\",\"filename\":\"");
    QString qstrByteData = qstrFileName + "\"}";
    byteData.append(qstrByteData.toLocal8Bit());
    qDebug() << "request to server" << byteData;
    mNetMan.post(request, byteData);
}

void netWorkManager::connectToRead(QString qstrFileName)
{
    qDebug() << Q_FUNC_INFO;
    QUrl url("https://orbvpn.com/panel/system/rest_api/test_api.php?");
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QByteArray byteData("{\"action\":\"Read\",\"filename\":\"");
    QString qstrByteData = qstrFileName + "\"}";
    byteData.append(qstrByteData.toLocal8Bit());
    qDebug() << "request to server" << byteData;
    mNetMan.post(request, byteData);
}
void netWorkManager::connectToWrite(QString qstrFileName, QString qstrFileContent)
{
    qDebug() << Q_FUNC_INFO;
    QUrl url("https://orbvpn.com/panel/system/rest_api/test_api.php?");
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QByteArray byteData("{\"action\":\"Write\",\"filename\":");
    QString qstrByteData = "\"" + qstrFileName + "\",\"text\":\""+ qstrFileContent + "\"}";
    byteData.append(qstrByteData.toLocal8Bit());
    qDebug() << "request to server" << byteData;
    mNetMan.post(request, byteData);
}

void netWorkManager::onResult(QNetworkReply* reply)
{
    qDebug() << Q_FUNC_INFO;
    bool xErrValue = false;
    QString qstrStatus = "NA";
    QString qstrFileContent = "NA";

    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "error in connection : " << reply->error();
        emit networkReply(false, "ERROR", "Network Error.");
        return;
    }
    else
    {
        qDebug() << "network connected.";
//        QString data = (QString) reply->readAll(); // network response.
//        below is expected data
        QString data = "{\"error\":false,\"data\":[\"this is content read from server file.\"],\"200\":\"OK\"}";
        qDebug() << "data " << data;

        const QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
        QJsonObject jsonObj = doc.object();
        QJsonValue errValue = jsonObj.value(QString("error"));
        xErrValue = errValue.toBool();
        if(xErrValue)
            qDebug() << "errValue :" << xErrValue;

        QJsonValue statusValue = jsonObj.value(QString("200"));
        qstrStatus = statusValue.toString();
        qDebug() << "statusValue : " << qstrStatus;

        QJsonValue dataValue = jsonObj.value(QString("data"));
        if(dataValue.isUndefined()) {}
        else if(dataValue.isArray())
        {
            qstrFileContent = dataValue.toArray().at(0).toString();;
            qDebug() << qstrFileContent;
        }

        emit networkReply(xErrValue, qstrStatus, qstrFileContent);
    }
}

void netWorkManager::OnDataReadyToRead()
{
    qDebug() << Q_FUNC_INFO;
}

void netWorkManager::onAuthenticationRequestSlot(QNetworkReply *aReply,
                                                 QAuthenticator *aAuthenticator)
{
    qDebug() << Q_FUNC_INFO;
    aAuthenticator->setUser("test");
    aAuthenticator->setPassword("test1");
}

void netWorkManager::emitSignal()
{
    qDebug() << "emiting signal";
    emit mySignal("this is signal string");
}

/*
 * TODO : JSON creates, empty char, API not working
    QJsonObject obj;
    obj["action"] = "Write";
    obj["filename"] = "jsontest03";
    obj["text"] = "this is jsontest03 test.";
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson();
    QByteArray data("{\"action\":\"Write\",\"filename\":\"jsontest03\",\"text\":\"this is jsontest03 test.\"}");
*/
