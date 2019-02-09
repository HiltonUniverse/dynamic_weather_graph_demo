#ifndef CHARTMODEL_H
#define CHARTMODEL_H

#include "weatherJasonParser.h"

#include <QAbstractTableModel>
#include <QDate>
#include <QMainWindow>
#include <memory>

class WeatherJsonParser;

namespace weather{
    struct Weather;
}

class ChartModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ChartModel(QObject *parent = nullptr);
    virtual ~ChartModel() = default;

public slots:
    void jsonWeatherReceived(weather::Weather weather);
    void appendData();
    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    QVector<QPair<QDate,double>> m_columns;
    std::unique_ptr<WeatherJsonParser> m_weather_json_parser;
};

#endif // CHARTMODEL_H
