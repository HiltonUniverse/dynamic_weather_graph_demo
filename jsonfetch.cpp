#include "jsonfetch.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <iostream>
#include <QString>
#include <QTextCodec>
#include <QJsonParseError>
#include <QJsonDocument>


//---------------------------------------------------------------------------------------------------------------------
JsonFetch::JsonFetch(QObject *parent)
    : QObject(parent)
    , m_network_manager(*(new QNetworkAccessManager(parent)))
{

}

//---------------------------------------------------------------------------------------------------------------------
void JsonFetch::fetchJsonData(const QString& URL)
{
    //Making HTTP request and fetching the weather API data

    QUrl url(URL);
    QNetworkRequest request;
    request.setUrl(url);

    m_reply = m_network_manager.get(request);  // GET

    connect(m_reply, &QNetworkReply::finished,this,&JsonFetch::afterResponse);
}


//---------------------------------------------------------------------------------------------------------------------
void JsonFetch::afterResponse()
{
    if(m_reply->error() == QNetworkReply::NoError)
    {

        QByteArray response = m_reply->readAll();
        QJsonParseError parse_error;
        QJsonDocument json_document = QJsonDocument::fromJson(response,&parse_error);

        QJsonObject json_object = json_document.object();

        emit jsonObjectReady(json_object);
    }
}

