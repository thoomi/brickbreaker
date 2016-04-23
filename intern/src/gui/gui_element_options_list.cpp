#include "gui/gui_element_options_list.h"

namespace Gui
{
    COptionsList::COptionsList(int _ID)
        : CElement          (_ID)
        , m_Items           ()
        , m_CurrentItemIndex(0)
        , m_MaxItemWidth    (0)
    {
    }

    COptionsList::~COptionsList()
    {
    }

    void COptionsList::AddItem(const std::string& _rItem)
    {
        m_Items.push_back(_rItem);

        if (_rItem.length() > m_MaxItemWidth)
        {
            m_MaxItemWidth = _rItem.length() + 5;
        }

        UpdateLayout();
    }

    int COptionsList::GetCurrentItem()
    {
        return m_CurrentItemIndex;
    }

    void COptionsList::IndexDown()
    {
        m_CurrentItemIndex++;

        if (m_CurrentItemIndex == m_Items.size())
        {
            m_CurrentItemIndex = 0;
        }
    }

    void COptionsList::IndexUp()
    {
        if (m_CurrentItemIndex == 0)
        {
            m_CurrentItemIndex = m_Items.size() - 1;
        }
        else
        {
            m_CurrentItemIndex--;
        }
    }

    void COptionsList::OnEvent(const Core::CUserEvent& _rEvent)
    {
        if (_rEvent.GetType() == Core::CUserEvent::Input)
        {
            if (_rEvent.GetAction() == Core::CUserEvent::KeyPressed)
            {
                switch (_rEvent.GetKey())
                {
                    case Core::CUserEvent::KeyDown:
                        IndexDown();
                        UpdateLayout();
                        break;

                    case Core::CUserEvent::KeyUp:
                        IndexUp();
                        UpdateLayout();
                        break;

                    default:
                        break;
                }
            }
        }
    }

    void COptionsList::UpdateLayout()
    {
        std::string Indicator = "[ ]  ";
        std::string Layout;

        unsigned int Index = 0;

        for (auto& Item : m_Items)
        {
            // -----------------------------------------------------------------------------
            // Mark the current activated item in the list.
            // -----------------------------------------------------------------------------
            if (Index == m_CurrentItemIndex)
            {
                Indicator.at(1) = '#';
            }
            else
            { 
                Indicator.at(1) = ' ';
            }

            // -----------------------------------------------------------------------------
            // Add the indicator and the items label to the layout.
            // -----------------------------------------------------------------------------
            Layout += Indicator + Item;


            // -----------------------------------------------------------------------------
            // Fill missing characters with empty spaces.
            // -----------------------------------------------------------------------------
            int Difference = m_MaxItemWidth - (Item.length() + 5);

            for (int IndexOfChar = 0; IndexOfChar < Difference; IndexOfChar++)
            {
                Layout += ' ';
            }

            Index++;

            // -----------------------------------------------------------------------------
            // Insert an empty space line between two items.
            // -----------------------------------------------------------------------------
            for (unsigned int IndexOfChar = 0; IndexOfChar < m_MaxItemWidth; IndexOfChar++)
            {
                Layout += ' ';
            }
        }

        SetLayout(Layout);

        SetWidth(m_MaxItemWidth);
        SetHeight(GetLayout().length() / m_MaxItemWidth);
    }
} // namespace Gui