#include "graphics/graphics_console.h"

#include "Windows.h"

namespace Gfx
{
    CConsole& CConsole::GetInstance()
    {
        static CConsole s_Instance;

        return s_Instance;
    }

    CConsole::CConsole()
        : m_ClearSymbol      (' ')
        , m_CurrentAttribute (EAttribute::BlackOnBlack)
        , m_pConsoleBuffer1  (nullptr)
        , m_pConsoleBuffer2  (nullptr)
        , m_pActiveBuffer    (nullptr)
    {
        COORD               ScreenBufferCoord;
        SMALL_RECT          WindowSize;
        CONSOLE_CURSOR_INFO CursorInfo;

        ScreenBufferCoord.X = static_cast<SHORT>(s_MaxNumberOfCharactersPerRow);
        ScreenBufferCoord.Y = static_cast<SHORT>(s_MaxNumberOfCharactersPerColumn);

        WindowSize.Top    = 0;
        WindowSize.Left   = 0;
        WindowSize.Bottom = ScreenBufferCoord.Y - 1;
        WindowSize.Right  = ScreenBufferCoord.X - 1;

        CursorInfo.dwSize = 1;
        CursorInfo.bVisible = false;

        m_pConsoleBuffer1 = CreateConsoleScreenBuffer(GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);
        m_pConsoleBuffer2 = CreateConsoleScreenBuffer(GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);

        SetConsoleScreenBufferSize(m_pConsoleBuffer1, ScreenBufferCoord);
        SetConsoleWindowInfo(m_pConsoleBuffer1, true, &WindowSize);

        SetConsoleScreenBufferSize(m_pConsoleBuffer2, ScreenBufferCoord);
        SetConsoleWindowInfo(m_pConsoleBuffer2, true, &WindowSize);

        SetConsoleCursorInfo(m_pConsoleBuffer1, &CursorInfo);
        SetConsoleCursorInfo(m_pConsoleBuffer2, &CursorInfo);

        m_pActiveBuffer = m_pConsoleBuffer1;
    }

    CConsole::~CConsole()
    {
        CloseHandle(m_pConsoleBuffer1);
        CloseHandle(m_pConsoleBuffer2);
    }

    void CConsole::Print(char _Symbol, unsigned int _X, unsigned int _Y)
    {
        COORD Position = { static_cast<SHORT>(_X), static_cast<SHORT>(_Y) };
        DWORD NumberOfWrittenChars;
        
        SetConsoleCursorPosition(m_pActiveBuffer, Position);
        SetConsoleTextAttribute(m_pActiveBuffer, static_cast<WORD>(m_CurrentAttribute));
        
        WriteConsole(m_pActiveBuffer, &_Symbol, 1, &NumberOfWrittenChars, nullptr);
    }

    void CConsole::Clear()
    {
        DWORD                      NumberOfWrittenChars;

        // -----------------------------------------------------------------------------
        // Disabled the FillConsoleOutput because it caused some weired rendering issue
        // in release mode.
        // -----------------------------------------------------------------------------
        
        CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;
        COORD                      OriginCoord = { 0, 0 };


        GetConsoleScreenBufferInfo(m_pActiveBuffer, &ScreenBufferInfo);

        DWORD MaxNumberOfChars = ScreenBufferInfo.dwSize.X * ScreenBufferInfo.dwSize.Y;
        ScreenBufferInfo.wAttributes = EAttribute::BlackOnBlack;

        FillConsoleOutputCharacter(m_pActiveBuffer, static_cast<TCHAR>(m_ClearSymbol), MaxNumberOfChars, OriginCoord, &NumberOfWrittenChars);
        FillConsoleOutputAttribute(m_pActiveBuffer, ScreenBufferInfo.wAttributes, MaxNumberOfChars, OriginCoord, &NumberOfWrittenChars);
        

        /*SetConsoleTextAttribute(m_pActiveBuffer, EAttribute::BlackOnBlack);

        for (unsigned int IndexOfChar = 0; IndexOfChar < s_MaxNumberOfCharacters; IndexOfChar++)
        {
            WriteConsole(m_pActiveBuffer, &m_ClearSymbol, 1, &NumberOfWrittenChars, nullptr);
        }*/
    }

    void CConsole::SwapBuffers()
    {
        m_pActiveBuffer = m_pActiveBuffer == m_pConsoleBuffer1 ? m_pConsoleBuffer2 : m_pConsoleBuffer1;
    }

    void CConsole::ActivateBuffer()
    {
        SetConsoleActiveScreenBuffer(m_pActiveBuffer);
    }

    void CConsole::SetClearSymbol(char _Symbol)
    {
        m_ClearSymbol = _Symbol;
    }

    void CConsole::SetPrintAttribute(unsigned short _Attribute)
    {
        m_CurrentAttribute = static_cast<EAttribute>(_Attribute);
    }
} // namespace Gfx

