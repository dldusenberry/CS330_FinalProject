#include "App.h"
#include "WheelApp.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    WheelApp* wheelApp = new WheelApp("Spin the Wheel");
    wheelApp->SetClientSize(1000, 600);
    wheelApp->Center();
    wheelApp->Show(true);
    return true;
 }
/*
wxIMPLEMENT_APP(wxPieChartApp);

bool wxPieChartApp::OnInit()
{
    PieChartFrame* frame = new PieChartFrame("wxCharts - PieChart Sample");
    frame->Show(true);
    return true;
}
*/




