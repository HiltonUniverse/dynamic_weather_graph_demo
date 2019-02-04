#ifndef JSONOBJECTFACTOR_H
#define JSONOBJECTFACTOR_H

#include <QString>
#include <QObject>
#include <QJsonObject>
#include "weather.h"

class JsonFetch;

class WeatherJsonParser: public QObject
{
    Q_OBJECT
    Q_PROPERTY(weather::Weather structValues READ getParsedData NOTIFY parseCompleted)

signals:
    void parseCompleted();

public slots:
    void fetchWeatheJson(QJsonObject weatherObject);

public:
    WeatherJsonParser(const QString & cityName,QObject* parent=nullptr);
    weather::Weather getParsedData() const;

private:
    JsonFetch* m_json_fetch;
    weather::Weather m_weather;

};

#endif // JSONOBJECTFACTOR_H
