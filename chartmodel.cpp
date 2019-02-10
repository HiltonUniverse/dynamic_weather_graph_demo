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
    connect(m_weather_json_parser.get(),&WeatherJsonParser::parseCompleted,this,&ChartModel::appendData);
}















//---------------------------------------------------------------------------------------------------------------------
void ChartModel::appendData(weather::Weather weather)
{
    vec_.clear();
    weather::Weather::printDebugInfo(weather);
    int index = vec_.size();
    auto fetch_date_temp = [this](const auto& values){
        this->vec_.append(qMakePair<QDate, double>(values.m_date, values.m_max));
    };

    beginInsertRows(QModelIndex(),index,static_cast<int>(weather.m_temp_info.size()));
    std::for_each(std::begin(weather.m_temp_info),std::end(weather.m_temp_info),fetch_date_temp);
    endInsertRows();
}


int ChartModel::rowCount(const QModelIndex & /* parent */) const
{
    return vec_.size();
}

int ChartModel::columnCount(const QModelIndex & /* parent */) const
{
    return 2;
}

//---------------------------------------------------------------------------------------------------------------------
QVariant ChartModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    if (index.column() == 0){
        return vec_.at(index.row()).first;
    }
    if (index.column() == 1){
        return vec_.at(index.row()).second;
    }
    return QVariant();
}
