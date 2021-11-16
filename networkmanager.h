#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QAuthenticator>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include <QtScript/QScriptEngine>
#include <QtDebug>

class netWorkManager : public QObject
{
    Q_OBJECT
public:
    netWorkManager();
    Q_INVOKABLE void connectToInternet(int iFileOperation ,QString qstrFileName, QString qstrFileContent);
    Q_INVOKABLE void emitSignal();

signals:
    void networkReply(bool xIsError, QString qstrStatus, QString qstrDataRead);
    void mySignal(QString str);

private:

    void resetFileNameAndOperation();
    void connectToCreate(QString qstrFileName);
    void connectToRead(QString qstrFileName);
    void connectToWrite(QString qstrFileName, QString qstrFileContent);

    Q_SLOT void onResult(QNetworkReply* reply);
    Q_SLOT void onAuthenticationRequestSlot(QNetworkReply *aReply,
                                            QAuthenticator *aAuthenticator);
    Q_SLOT void OnDataReadyToRead();

    QNetworkAccessManager mNetMan;
    QByteArray mDataBuffer;
    int iCurrentFileOperation;
    QString qstrCurrentFileName;
};

#endif // NETWORKMANAGER_H
