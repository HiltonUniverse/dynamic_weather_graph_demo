#ifndef JSONOBJECTFACTOR_H
#define JSONOBJECTFACTOR_H

#include <QString>
#include <QObject>
#include <QJsonObject>

class JsonFetch;

class WeatherJsonParser: public QObject
{
    Q_OBJECT
public slots:
    void fetchWeatheJson(QJsonObject weatherObject);

public:
    WeatherJsonParser(const QString & cityName,QObject* parent=nullptr);

private:
    JsonFetch* m_json_fetch;
};

#endif // JSONOBJECTFACTOR_H
