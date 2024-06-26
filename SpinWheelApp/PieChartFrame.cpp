/*
	Copyright (c) 2015-2019 Xavier Leclercq

	Permission is hereby granted, free of charge, to any person obtaining a
	copy of this software and associated documentation files (the "Software"),
	to deal in the Software without restriction, including without limitation
	the rights to use, copy, modify, merge, publish, distribute, sublicense,
	and/or sell copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
	IN THE SOFTWARE.
*/

#include "PieChartFrame.h"
#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include "PieChartData.h"
#include "PieChartCtrl.h"

PieChartFrame::PieChartFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title)
{
	// Create a top-level panel to hold all the contents of the frame
	wxPanel* panel = new wxPanel(this, wxID_ANY);

	// Create the data for the pie chart widget
	PieChartData::ptr chartData = PieChartData::make_shared();
	chartData->AppendSlice(SliceData(300, wxColor(0x4A46F7), "Red"));
	chartData->AppendSlice(SliceData(50, wxColor(0xBDBF46), "Green"));
	chartData->AppendSlice(SliceData(100, wxColor(0x5CB4FD), "Yellow"));
	chartData->AppendSlice(SliceData(40, wxColor(0xB19F94), "Grey"));
	chartData->AppendSlice(SliceData(120, wxColor(0x60534D), "Dark Grey"));

	// Create the pie chart widget
	PieChartCtrl* pieChartCtrl = new PieChartCtrl(panel, wxID_ANY, chartData,
		wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);

	// Create the legend widget
	wxChartsLegendData legendData(chartData->GetSlices());
	wxChartsLegendCtrl* legendCtrl = new wxChartsLegendCtrl(panel, wxID_ANY, legendData,
		wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);

	// Set up the sizer for the panel
	wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
	panelSizer->Add(pieChartCtrl, 1, wxEXPAND);
	panelSizer->Add(legendCtrl, 1, wxEXPAND);
	panel->SetSizer(panelSizer);
}