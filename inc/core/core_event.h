#pragma once

namespace Core
{
    class CUserEvent
    {
        public:

            enum EType
            {
                Input
            };

            enum EAction
            {
                KeyPressed,
                KeyReleased
            };

            enum EKey
            {
                KeyLeft   = 0x25,  ///< Cursor left
                KeyRight  = 0x27,  ///< Cursor right
                KeyUp     = 0x26,  ///< Cursor up
                KeyDown   = 0x28,  ///< Cursor down
                KeySpace  = 0x20,  ///< Space bar
                KeyEscape = 0x1B,  ///< Escape
                KeyReturn = 0x0D,  ///< Return / Enter
                KeyA      = 0x41,  ///< A
                KeyD      = 0x44,  ///< D
                KeyS      = 0x53,  ///< S
                KeyW      = 0x57,  ///< W
            };

        public:

            CUserEvent(unsigned int _Type, unsigned int _Key);
            CUserEvent(unsigned int _Type, unsigned int _Action, unsigned int _Key);
            ~CUserEvent();

        public:

            EType   GetType()   const;
            EAction GetAction() const;
            EKey    GetKey()    const;

        private:

            struct SBits
            {
                unsigned int m_Action : 8;
                unsigned int m_Key    : 8;
                unsigned int m_Type   : 4;
            };

        private:

            SBits m_Bits;
    };
} // namespace Core