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

#pragma once
#include "slicedata.h"
#include "piechartoptionsbase.h"
#include "wxchartsarc.h"
#include "wxchartobservers.h"
#include <wx/control.h>
#include <wx/sharedptr.h>
#include <map>
#include <wx/graphics.h>

/// Data for the wxPieChartCtrl control.
class PieChartData : public wxChartObservableValue<std::map<wxString, SliceData>>
{
public:
    /// Smart pointer typedef.
    typedef wxSharedPtr<PieChartData> ptr;

    PieChartData();
    static ptr make_shared();

    const std::map<wxString, SliceData>& GetSlices() const;
    void AppendSlice(const SliceData& slice);
    void UpdateSlices(const wxVector<SliceData>& slices);
    void AddSlices(const wxVector<SliceData>& slices);

private:
    void Add(const SliceData& slice);
};

/// Common base class for the wxPieChart chart.

class PieChartBase
{
public:
    /// Constructs a wxDoughnutAndPieChartBase
    /// instance.
    PieChartBase(PieChartData::ptr data);
    PieChartBase(PieChartData::ptr data, const wxSize& size);
    void SetData(const std::map<wxString, SliceData>& data);

private:
    virtual void DoSetSize(const wxSize& size);
    virtual void DoFit();
    virtual void DoDraw(wxGraphicsContext& gc, bool suppressTooltips);
    wxDouble CalculateCircumference(double value);

private:
    virtual const PieChartOptionsBase& GetOptions() const = 0;

private:
    class SliceArc : public ChartsArc
    {
    public:
        typedef wxSharedPtr<SliceArc> ptr;

        SliceArc(const SliceData& slice, wxDouble x, wxDouble y,
            wxDouble startAngle, wxDouble endAngle, wxDouble outerRadius,
            wxDouble innerRadius, unsigned int strokeWidth);

        void Resize(const wxSize& size, const PieChartOptionsBase& options);

        wxDouble GetValue() const;

    private:
        wxDouble m_value;
    };

private:
    PieChartData::ptr m_data;
    wxSize m_size;
    wxVector<SliceArc::ptr> m_slices;
    wxDouble m_total;
};

