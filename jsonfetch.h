#ifndef JSONFETCH_H
#define JSONFETCH_H

#include <QObject>
#include <QJsonObject>

class QNetworkRequest; //forward decleration only for pointer and reference.
class QNetworkReply;
class QNetworkAccessManager;

class JsonFetch : public QObject
{
    Q_OBJECT
public:
    explicit JsonFetch(QObject *parent = nullptr);
    void fetchJsonData(const QString& URL);

signals:
    void jsonObjectReady(QJsonObject jsonObject);

public slots:
    void afterResponse();

private:
    QNetworkAccessManager &m_network_manager;
    QNetworkReply* m_reply;
    QJsonObject* m_json_obj;
};

#endif // JSONFETCH_H
