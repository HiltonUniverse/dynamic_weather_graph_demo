import QtQuick 2.9
import QtQuick.Window 2.2
import QtCharts 2.3



/* information on passing signals from c++ to qml

https://code.i-harness.com/en/q/86cc63
https://stackoverflow.com/questions/24406333/qml-using-cpp-signal-in-qml-always-results-in-cannot-assign-to-non-existent-pr
*/

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

  Connections{
      target: weatherInformation
      onParseCompleted:{

        console.log("Data Must Come here")
//        console.log(weatherInformation.structValues.cityName)
      }
  }

    //TESTING A HARDCODED GRAPH
    ChartView {
        title: "Line"
        anchors.fill: parent
        antialiasing: true

        LineSeries {
              name: "LineSeries"
              XYPoint { x: 0; y: 0 }
              XYPoint { x: 1.1; y: 2.1 }
              XYPoint { x: 1.9; y: 3.3 }
              XYPoint { x: 2.1; y: 2.1 }
              XYPoint { x: 2.9; y: 4.9 }
              XYPoint { x: 3.4; y: 3.0 }
              XYPoint { x: 4.1; y: 3.3 }
          }
    }
}
