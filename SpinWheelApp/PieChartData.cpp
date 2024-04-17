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

#include "PieChartData.h"
#include "piechartbase.h"
#include "SliceData.h"
// wxdoughnutandpiechartbase.cpp


PieChartData::PieChartData()
{
}

PieChartData::ptr PieChartData::make_shared()
{
    return ptr(new PieChartData());
}

const std::map<wxString, SliceData>& PieChartData::GetSlices() const
{
    return m_value;
}

void PieChartData::AppendSlice(const SliceData& slice)
{
    Add(slice);
    Notify();
}

void PieChartData::UpdateSlices(const wxVector<SliceData>& slices)
{
    m_value.clear();
    AddSlices(slices);
}

void PieChartData::AddSlices(const wxVector<SliceData>& slices)
{
    for (const auto& slice : slices)
        Add(slice);

    Notify();
}

void PieChartData::Add(const SliceData& slice)
{
    auto key = slice.GetLabel();
    auto it = m_value.find(key);
    if (it == m_value.end())
        m_value.insert(std::make_pair(key, slice));
    else
        it->second.SetValue(it->second.GetValue() + slice.GetValue());
}

PieChartBase::SliceArc::SliceArc(const SliceData& slice,
    wxDouble x,
    wxDouble y,
    wxDouble startAngle,
    wxDouble endAngle,
    wxDouble outerRadius,
    wxDouble innerRadius,
    unsigned int strokeWidth)
    : wxChartsArc(x, y, startAngle, endAngle, outerRadius, innerRadius,
        slice.GetTooltipText(), wxChartsArcOptions(strokeWidth, slice.GetColor())),
    m_value(slice.GetValue())
{
}

void PieChartBase::SliceArc::Resize(const wxSize& size,
    const PieChartOptionsBase& options)
{
    wxDouble x = (size.GetX() / 2) - 2;
    wxDouble y = (size.GetY() / 2) - 2;
    wxDouble outerRadius = ((x < y) ? x : y) - (GetOptions().GetOutlineWidth() / 2);
    wxDouble innerRadius = outerRadius * ((wxDouble)options.GetPercentageInnerCutout()) / 100;

    SetCenter(x, y);
    SetRadiuses(outerRadius, innerRadius);
}

wxDouble PieChartBase::SliceArc::GetValue() const
{
    return m_value;
}

PieChartBase::PieChartBase(PieChartData::ptr data)
    : m_data(data), m_total(0)
{
}

PieChartBase::PieChartBase(const PieChartData::ptr data,
    const wxSize& size)
    : m_data(data), m_size(size), m_total(0)
{
}

void PieChartBase::SetData(const std::map<wxString, SliceData>& data)
{
    m_slices.resize(data.size());
    m_total = 0;
    size_t i = 0;
    for (const auto& pair : data)
    {
        auto slice = pair.second;

        m_total += slice.GetValue();
        wxDouble x = (m_size.GetX() / 2) - 2;
        wxDouble y = (m_size.GetY() / 2) - 2;
        wxDouble outerRadius = ((x < y) ? x : y) - (GetOptions().GetSliceStrokeWidth() / 2);
        wxDouble innerRadius = outerRadius * ((wxDouble)GetOptions().GetPercentageInnerCutout()) / 100;

        SliceArc::ptr newSlice = SliceArc::ptr(new SliceArc(slice,
            x, y, 0, 0, outerRadius, innerRadius, GetOptions().GetSliceStrokeWidth()));
        m_slices[i++] = newSlice;
    }
}

void PieChartBase::DoSetSize(const wxSize& size)
{
    m_size = size;
}

void PieChartBase::DoFit()
{
    SetData(m_data->GetSlices());

    for (size_t i = 0; i < m_slices.size(); ++i)
    {
        m_slices[i]->Resize(m_size, GetOptions());
    }

    wxDouble startAngle = 0.0;
    for (size_t i = 0; i < m_slices.size(); ++i)
    {
        SliceArc& currentSlice = *m_slices[i];

        wxDouble endAngle = startAngle + CalculateCircumference(currentSlice.GetValue());
        currentSlice.SetAngles(startAngle, endAngle);
        startAngle = endAngle;
    }
}

void PieChartBase::DoDraw(wxGraphicsContext& gc)
{
    Fit();

    for (size_t i = 0; i < m_slices.size(); ++i)
    {
        m_slices[i]->Draw(gc);
    }

}
wxDouble PieChartBase::CalculateCircumference(wxDouble value)
{
    if (m_total > 0)
    {
        return (value * 2 * M_PI / m_total);
    }
    else
    {
        return 0;
    }
}
/*
wxSharedPtr<wxVector<const wxChartsElement*>> wxDoughnutAndPieChartBase::GetActiveElements(const wxPoint& point)
{
    wxSharedPtr<wxVector<const wxChartsElement*>> activeElements(new wxVector<const wxChartsElement*>());
    for (size_t i = 0; i < m_slices.size(); ++i)
    {
        if (m_slices[i]->HitTest(point))
        {
            activeElements->push_back(m_slices[i].get());
        }
    }
    return activeElements;
}
*/

