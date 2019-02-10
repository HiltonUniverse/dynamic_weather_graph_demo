#ifndef CHARTMODEL_H
#define CHARTMODEL_H

#include "weatherJasonParser.h"

#include <QAbstractTableModel>
#include <QDate>
#include <QMainWindow>
#include <memory>
#include <QTimer>

class ChartModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ChartModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

public slots:
    void appendData(weather::Weather weather);
    // QAbstractItemModel interface

private:
    QVector<QPair<QDate,double>> vec_;
    std::unique_ptr<WeatherJsonParser> m_weather_json_parser;
    QTimer m_timer;
};

#endif // CHARTMODEL_H
