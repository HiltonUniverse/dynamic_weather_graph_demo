#include "weatherJasonParser.h"
#include "jsonfetch.h"
#include "jsonfetch.h"
#include "jsonhelper.h"
#include "weather.h"
#include <QDebug>
#include <QJsonArray>
#include <algorithm>
#include <iterator>
#include <memory>
#include <QDateTime>


namespace
{
//---------------------------------------------------------------------------------------------------------------------
    const QString getValidUrlWithCityName(const QString& cityName)
    {
        return "http://api.openweathermap.org/data/2.5/forecast/daily?q="+cityName+",0032&cnt=10&appid=fe37c3d28a6ebb417f52c05d92b28383";
    }
}

//---------------------------------------------------------------------------------------------------------------------
WeatherJsonParser::WeatherJsonParser(const QString& cityName, QObject *parent):QObject(parent)
{
//    weather = weather::Weather(); //type -> weather::Weather
    m_json_fetch = new JsonFetch(parent);
    m_json_fetch->fetchJsonData(getValidUrlWithCityName(cityName));
    connect(m_json_fetch,&JsonFetch::jsonObjectReady,this,&WeatherJsonParser::fetchWeatheJson);
}

//---------------------------------------------------------------------------------------------------------------------
weather::Weather WeatherJsonParser::getParsedData() const
{
    return m_weather;
}

//---------------------------------------------------------------------------------------------------------------------
void WeatherJsonParser::fetchWeatheJson(QJsonObject weatherObject)
{
    QJsonObject name = weatherObject[weather::CITY].toObject();
    this->m_weather.m_city_name = name[weather::CITY_NAME].toString(); //city name
    this->m_weather.m_country_name = name[weather::COUNTRY_NAME].toString(); //country name

    QJsonArray list_of_temperatures = weatherObject[weather::LIST_NAME].toArray();
    std::for_each(std::begin(list_of_temperatures),std::end(list_of_temperatures),[this](auto temperature){
       QJsonObject weather_info = temperature.toObject();
       QJsonObject temp = weather_info[weather::ARRAY_TEMP].toObject();
       QJsonArray weather_array = weather_info[weather::ARRAY_WEATHER].toArray();
       auto date_time = QDateTime::fromTime_t(static_cast<unsigned int>(weather_info[weather::DATE].toInt())).toString("dd/MM/yyyy hh:mm:ss");
       m_weather.m_temp_info.push_back({date_time,
                                      temp[weather::MIN_TEMP].toDouble(),
                                      temp[weather::MAX_TEMP].toDouble(),
                                      weather_array[0].toObject()[weather::WEATHER_DESCRIPTION].toString()});
    });

    qDebug()<< "Parse Completed";

    emit parseCompleted();
}

