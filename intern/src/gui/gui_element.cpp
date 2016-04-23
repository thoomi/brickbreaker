#include "gui/gui_element.h"

namespace Gui
{
    CElement::CElement(int _ID)
        : m_Width            (0)
        , m_Height           (0)
        , m_PositionX        (0)
        , m_PositionY        (0)
        , m_ID               (_ID)
        , m_Layout           ()
        , m_BaseTextAttribute(0)
        , m_TextAttributes   ()
    {
    }

    CElement::~CElement()
    {
    }

    int CElement::GetWidth() const
    {
        return m_Width;
    }

    int CElement::GetHeight() const
    {
        return m_Height;
    }

    int CElement::GetPositionX() const
    {
        return m_PositionX;
    }

    int CElement::GetPositionY() const
    {
        return m_PositionY;
    }

    void CElement::SetWidth(int _Value)
    {
        m_Width = _Value;
    }

    void CElement::SetHeight(int _Value)
    {
        m_Height = _Value;
    }

    void CElement::SetPositionX(int _Value)
    {
        m_PositionX = _Value;
    }

    void CElement::SetPositionY(int _Value)
    {
        m_PositionY = _Value;
    }

    const std::string& CElement::GetLayout() const
    {
        return m_Layout;
    }
    void CElement::SetLayout(const std::string& _rString)
    {
        m_Layout = _rString;
    }

    int CElement::GetID()
    {
        return m_ID;
    }

    void CElement::SetBaseTextAttribute(unsigned short _Attribute)
    {
        m_BaseTextAttribute = _Attribute;
    }

    void CElement::SetTextAttributes(unsigned short* _pAttributes)
    {
        m_TextAttributes = CAttributeContainer(_pAttributes, _pAttributes + m_Layout.length());
    }

    unsigned short CElement::GetTextAttributeAt(unsigned int _Index)
    {
        if (_Index < m_TextAttributes.size())
        {
            return m_TextAttributes.at(_Index);
        }
        else
        {
            return m_BaseTextAttribute;
        }
    }
} // namespace Gui