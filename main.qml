import QtQuick 2.9
import QtQuick.Window 2.2
import QtCharts 2.3
import QtQml 2.0

//import MainLib 1.0


Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

//    property ChartModel chartModel : ChartModel{}

    ChartView {
            id : chart
            anchors.fill: parent
            antialiasing: true

            LineSeries {
                id : serie1

                axisX : DateTimeAxis {
                    id: xAxis
//                    min: chartModel.xMin
//                    max: chartModel.xMax
                    min: new Date("2019,02,08")
                    max: new Date("2019,02,20")
                    format: "yy MM dd"
                }

                axisY : ValueAxis {
                    id: yAxis
//                    min: chartModel.yMin
//                    max: chartModel.yMax
                    min: 200
                    max: 300
                }

                VXYModelMapper {
                    id: mapper
                    xColumn: 0
                    yColumn: 1
                    model: cpp_chart_model
                }
            }

//            MouseArea{
//                anchors.fill : parent
//                onClicked: {
//                    chartModel.appendData()
//                }
//            }
        }

}
