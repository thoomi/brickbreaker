#pragma once

#include <memory>
#include <string>
#include <vector>

namespace Gui
{
    class CElement
    {
        public:
            
            typedef std::shared_ptr<CElement> SharedPtr;
            typedef std::unique_ptr<CElement> UniquePtr;

            typedef std::vector<unsigned short> CAttributeContainer;

        public:

            CElement(int _ID);
            virtual ~CElement(void);

        public:

            int GetWidth() const;
            int GetHeight() const;

            int GetPositionX() const;
            int GetPositionY() const;

        public:

            void SetWidth(int _Value);
            void SetHeight(int _Value);

            void SetPositionX(int _Value);
            void SetPositionY(int _Value);

        public:

            const std::string& GetLayout() const;
            void SetLayout(const std::string& _rString);

            void SetBaseTextAttribute(unsigned short _Attribute);

            void SetTextAttributes(unsigned short* _pAttributes);
            unsigned short GetTextAttributeAt(unsigned int _Index);

        public:

            int GetID();

        private:

            int m_Width;
            int m_Height;

            int m_PositionX;
            int m_PositionY;

        private:

            int                 m_ID;
            std::string         m_Layout;
            unsigned short      m_BaseTextAttribute;
            CAttributeContainer m_TextAttributes;
    };
} // namespace Gui