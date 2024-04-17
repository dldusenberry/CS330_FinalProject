#pragma once
#include <wx/string.h>
#include <wx/colour.h>

/// The data associated with a slice in some charts like the pie and doughnut charts.

/// \ingroup dataclasses
class SliceData
{
public:
    /// Constructs a wxChartSliceData instance.
    /// @param value The value of the slice.
    /// @param color The slice will be filled with this color.
    /// @param label The label of the slice. By default this will
    /// be used in the legend and the tooltips.
    SliceData(wxDouble value, const wxColor& color,
        const wxString& label);

    wxDouble GetValue() const;
    void SetValue(wxDouble value);
    const wxColor& GetColor() const;
    const wxString& GetLabel() const;

    wxString GetTooltipText() const;

private:
    wxDouble m_value;
    wxColor m_color;
    wxString m_label;
};

