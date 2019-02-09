#ifndef WEATHER_H
#define WEATHER_H


#include <QDebug>
#include <QString>
#include <QDate>
#include <memory>
#include <iostream>
#include <algorithm>
#include <iterator>


namespace weather
{
    struct MinMaxInfo
    {
        QDate m_date;
        double m_min;
        double m_max;
        QString m_description;
    };

    struct Weather
    {
    public:
        QString m_city_name;
        QString m_country_name;
        std::vector<weather::MinMaxInfo> m_temp_info;

        static void printDebugInfo(const Weather& weather)
        {
            qDebug() << "The weather information for " << weather.m_city_name
               << " of country " << weather.m_country_name;

            auto min_max_info = [](MinMaxInfo info){
                qDebug() << "The minimum temperature is: " << info.m_min
                         << "\nThe minimum temperature is: " << info.m_max
                         << "\nAnd the description is: "<< info.m_description
                         << " in date " << info.m_date
                         << "\n\n";
            };

            std::for_each(std::begin(weather.m_temp_info), std::end(weather.m_temp_info),min_max_info);

        }

    };

}

#endif // WEATHER_H
