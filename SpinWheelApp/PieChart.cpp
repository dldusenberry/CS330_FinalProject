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

#include "PieChart.h"
#include <wx/pen.h>
#include <wx/brush.h>

// wxchartcircle.cpp

PieChart::PieChart(wxDouble x, 
    wxDouble y,
    wxDouble radius,
    const wxChartsCircleOptions& options)
    : wxChartsElement(tooltipProvider), m_options(options),
    m_x(x), m_y(y), m_radius(radius)
{
}

void PieChart::Draw(wxGraphicsContext& gc) const
{
    wxGraphicsPath path = gc.CreatePath();

    path.AddCircle(m_x, m_y, m_radius);

    wxBrush brush(m_options.GetFillColor());
    gc.SetBrush(brush);
    gc.FillPath(path);

    wxPen pen(m_options.GetOutlineColor(), m_options.GetOutlineWidth());
    gc.SetPen(pen);
    gc.StrokePath(path);
}

bool PieChart::HitTest(const wxPoint& point) const
{
    wxDouble distanceFromXCenter = point.x - m_x;
    wxDouble distanceFromYCenter = point.y - m_y;
    wxDouble radialDistanceFromCenter = sqrt((distanceFromXCenter * distanceFromXCenter) + (distanceFromYCenter * distanceFromYCenter));

    return (radialDistanceFromCenter <= m_radius);
}


void PieChart::SetCenter(wxDouble x, wxDouble y)
{
    m_x = x;
    m_y = y;
}

void PieChart::SetCenter(wxPoint2DDouble center)
{
    m_x = center.m_x;
    m_y = center.m_y;
}

void PieChart::SetRadius(wxDouble radius)
{
    m_radius = radius;
}


//piechart.cpp

PieChart::PieChart(wxPieChartData::ptr data,
    const wxSize& size)
    : PieChartBase(data, size),
    m_options(wxChartsDefaultTheme->GetPieChartOptions())
{
}

wxPieChart::wxPieChart(const PieChartData::ptr data,
    wxSharedPtr<wxPieChartOptions>& options,
    const wxSize& size)
    : PieChartBase(data, size), m_options(options)
{
}

const wxChartCommonOptions& PieChart::GetCommonOptions() const
{
    return m_options->GetCommonOptions();
}

const PieChartOptionsBase& PieChart::GetOptions() const
{
    return *m_options;
}



//  wxdoughnutandpiechartoptionsbase.cpp

#include "wxdoughnutandpiechartoptionsbase.h"

PieChartOptionsBase::PieChartOptionsBase(unsigned int percentageInnerCutout)
    : m_sliceStrokeWidth(2), m_percentageInnerCutout(percentageInnerCutout)
{
}

unsigned int PieChartOptionsBase::GetSliceStrokeWidth() const
{
    return m_sliceStrokeWidth;
}

unsigned int PieChartOptionsBase::GetPercentageInnerCutout() const
{
    return m_percentageInnerCutout;
}

void PieChartOptionsBase::SetSliceStrokeWidth(unsigned int strokeWidth)
{
    m_sliceStrokeWidth = strokeWidth;
}

void PieChartOptionsBase::SetPercentageInnerCutout(unsigned int cutout)
{
    m_percentageInnerCutout = cutout;
}

//wxpiechartoptions.cpp

#include "wxpiechartoptions.h"

PieChartOptions::PieChartOptions()
    : PieChartOptionsBase(0)
{
}

void PieChartOptions::SetSliceStrokeWidth(unsigned int strokeWidth)
{
    PieChartOptionsBase::SetSliceStrokeWidth(strokeWidth);
}