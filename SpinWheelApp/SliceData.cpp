#include "SliceData.h"
#include <sstream>
#include <wx/defs.h>

SliceData::SliceData(wxDouble value,
    const wxColor& color,
    const wxString& label)
    : m_value(value), m_color(color),
    m_label(label)
{
}

wxDouble SliceData::GetValue() const
{
    return m_value;
}

void SliceData::SetValue(wxDouble value)
{
    m_value = value;
}

const wxColor& SliceData::GetColor() const
{
    return m_color;
}

const wxString& SliceData::GetLabel() const
{
    return m_label;
}

wxString SliceData::GetTooltipText() const
{
    std::stringstream result;
    result << m_label << ": " << m_value;
    return result.str();
}