#pragma once

#include "gui/gui_element.h"
#include "gui/gui_event_listener.h"

#include <memory>
#include <string>
#include <vector>

namespace Gui
{
    class COptionsList : public CElement, public CEventListener
    {
        public:
            
            typedef std::shared_ptr<COptionsList> SharedPtr;
            typedef std::unique_ptr<COptionsList> UniquePtr;

        public:

            COptionsList(int _ID);
            ~COptionsList(void);

        public:

            virtual void OnEvent(const Core::CUserEvent& _rEvent) override;

        public:

            void AddItem(const std::string& _rItem);
            int GetCurrentItem();

        private:

            void IndexUp();
            void IndexDown();

        private:

            void UpdateLayout();

        private:

            std::vector<std::string> m_Items;
            unsigned int             m_CurrentItemIndex;
            unsigned int             m_MaxItemWidth;
    };
} // namespace Gui