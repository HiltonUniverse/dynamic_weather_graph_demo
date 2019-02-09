import QtQuick 2.9
import QtQuick.Window 2.2
import QtCharts 2.3
import MainLib 1.0


/* information on passing signals from c++ to qml

https://code.i-harness.com/en/q/86cc63
https://stackoverflow.com/questions/24406333/qml-using-cpp-signal-in-qml-always-results-in-cannot-assign-to-non-existent-pr
*/

Window
{
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    property ChartModel chart_model: ChartModel{}

    ChartView
    {
        title: "Line"
        anchors.fill: parent
        antialiasing: true

        legend
        {
            visible: false
            alignment: Qt.AlignBottom
        }

        DateTimeAxis
        {
            id: axisX
            format: "yyyy MMM dd"
        }

        ValueAxis
        {
            id: axisY
        }

        LineSeries
        {
            axisX: axisX
            axisY: axisY

            name: "LineSeries"

            VXYModelMapper
            {
                id: model_mapper_line_series
                model: chart_model
                xColumn: 0
                yColumn: 1
            }
        }

//        ScatterSeries
//        {
//            name: "ScatterSeries"

//            axisX: axisX
//            axisY: axisY

//            VXYModelMapper
//            {
//                id: model_mapper_scatter_series
//                model: cpp_chart_model
//                xColumn: 0
//                yColumn: 1
//            }
//        }

        MouseArea{
                    anchors.fill : parent
                    onClicked: {
                        chart_model.appendData()
                    }
                }
    }
}
