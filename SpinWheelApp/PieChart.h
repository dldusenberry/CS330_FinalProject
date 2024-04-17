#pragma once


#include "wxchartscircleoptions.h"
//#include <wx/sharedptr.h>
#include <wx/colour.h>
#include <wx/graphics.h>



//class CircleChart{};

/// This class is used to draw a circle on the chart.

/// \ingroup elementclasses
//class WXCHARTS_EXPORT PieChart : public wxChartsElement
class PieChart
{
public:
    PieChart(wxDouble x, wxDouble y, wxDouble radius,
        const CircleChartOptions& options);

    virtual void Draw(wxGraphicsContext& gc) const;

    virtual bool HitTest(const wxPoint& point) const;


    /// Sets the center of the circle.
    /// @param x The X coordinate of the center.
    /// @param y The Y coordinate of the center.
    void SetCenter(wxDouble x, wxDouble y);
    /// Sets the center of the circle.
    /// @param position The new center of the circle.
    void SetCenter(wxPoint2DDouble center);
    void SetRadius(wxDouble radius);

private:
    PieChartOptions m_options;
    wxDouble m_x;
    wxDouble m_y;
    wxDouble m_radius;
};


/// Options for the wxChartsCircle class.

/// \ingroup elementclasses
class CircleChartOptions
{
public:
    /// Constructs a CircleChartOptions instance.
    /// @param outlineWidth The width of the pen used to draw the outline
    /// of the circle.
    /// @param outlineColor The color of the outline.
    /// @param fillColor The color of the brush used to fill the circle.
    CircleChartOptions(unsigned int outlineWidth, const wxColor& outlineColor,
        const wxColor& fillColor);

    unsigned int GetOutlineWidth() const;
    const wxColor& GetOutlineColor() const;
    const wxColor& GetFillColor() const;

private:
    unsigned int m_outlineWidth;
    wxColor m_outlineColor;
    wxColor m_fillColor;
};

