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
#include <wx/colour.h>
#include <wx/graphics.h>


/// This class is used to draw one of the segments of a circular chart
/// \ingroup elementclasses
class ChartsArc 
{
public:
    ChartsArc(wxDouble x, wxDouble y, wxDouble startAngle,
        wxDouble endAngle, wxDouble outerRadius, wxDouble innerRadius,
        const wxString& tooltip, const ChartsArcOptions& options);

    virtual void Draw(wxGraphicsContext& gc) const;

    virtual bool HitTest(const wxPoint& point) const;


    /// Sets the center of the arc.
    /// @param x The X coordinate of the center.
    /// @param y The Y coordinate of the center.
    void SetCenter(wxDouble x, wxDouble y);
    /// Sets the start and end angles. The angles are measured
    /// in radians, they start from the 3 o'clock position
    /// and follow a clockwise direction.
    /// @param startAngle The start angle in radians. This must be a
    /// value between 0 and 2*PI.
    /// @param endAngle The end angle in radians. This must be greater
    /// than the start angle.
    void SetAngles(wxDouble startAngle, wxDouble endAngle);
    /// Sets the inner and outer radiuses.
    /// @param outerRadius The new outer radius.
    /// @param innerRadius The new inner radius.
    void SetRadiuses(wxDouble outerRadius, wxDouble innerRadius);

    /// Gets the arc options.
    /// @return The arc options.
    const ChartsArcOptions& GetOptions() const;

private:
    ChartsArcOptions m_options;
    wxDouble m_x;
    wxDouble m_y;
    wxDouble m_startAngle;
    wxDouble m_endAngle;
    wxDouble m_outerRadius;
    wxDouble m_innerRadius;
};


/// Options for the wxChartsArc class.

/// \ingroup elementclasses
class ChartsArcOptions
{
public:
    /// Constructs a wxChartsArcOptions instance.
    /// @param outlineWidth The width of the pen used to draw the outline
    /// of the arc.
    /// @param fillColor The color of the brush used to fill the arc.
    ChartsArcOptions(unsigned int outlineWidth, const wxColor& fillColor);

    /// Gets the width of the pen used to draw
    /// the outline of the arc.
    /// @return The width of the pen.
    unsigned int GetOutlineWidth() const;

    /// Gets the color of the brush used to fill the
    /// arc.
    /// @return The color of the brush used to fill the
    /// arc.
    const wxColor& GetFillColor() const;

private:
    unsigned int m_outlineWidth;
    wxColor m_fillColor;
};
