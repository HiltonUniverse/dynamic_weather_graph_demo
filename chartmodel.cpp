#include "chartmodel.h"
#include "weather.h"

#include <QDebug>
#include <QDate>
#include <sstream>
#include <algorithm>
#include <iterator>

//---------------------------------------------------------------------------------------------------------------------
ChartModel::ChartModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_weather_json_parser = std::make_unique<WeatherJsonParser>("leuven",this);
    connect(m_weather_json_parser.get(),&WeatherJsonParser::parseCompleted,this,&ChartModel::jsonWeatherReceived);
    appendData();
}

//---------------------------------------------------------------------------------------------------------------------
void ChartModel::jsonWeatherReceived(weather::Weather weather)
{
    int index = m_columns.size();
    auto fetch_date_temp = [this](const auto& values){
        m_columns.append(qMakePair<QDate, double>(values.m_date, values.m_max));
    };

    beginInsertRows(QModelIndex(),index,static_cast<int>(weather.m_temp_info.size()));
    std::for_each(std::begin(weather.m_temp_info),std::end(weather.m_temp_info),fetch_date_temp);
    endInsertRows();
}

void ChartModel::appendData()
{
    static int value = 0;
    if(value >5)
    {
        int index = m_columns.size();
        beginInsertRows(QModelIndex(),0,index);
            qDebug() << "REAL DATA";
        endInsertRows();
        return;
    }
    int index = m_columns.size();

    beginInsertRows(QModelIndex(),index,index+2);
    m_columns.append(qMakePair<QDate, double>(QDate(2019,01,25), 5));
    m_columns.append(qMakePair<QDate, double>(QDate(2019,05,25), 10));
    endInsertRows();

    value++;
}


//---------------------------------------------------------------------------------------------------------------------
int ChartModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);//prevent unused warning
    return m_columns.size();
}

//---------------------------------------------------------------------------------------------------------------------
int ChartModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

//---------------------------------------------------------------------------------------------------------------------
QVariant ChartModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    if (index.column() == 0){
        return m_columns.at(index.row()).first;
    }
    if (index.column() == 1){
        return m_columns.at(index.row()).second;
    }
    return QVariant();
}
