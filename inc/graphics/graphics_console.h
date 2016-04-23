#pragma once

namespace Gfx
{
    class CConsole
    {
        public:

            static const int s_MaxNumberOfCharactersPerRow    = 80;
            static const int s_MaxNumberOfCharactersPerColumn = 40;
            static const int s_MaxNumberOfCharacters = s_MaxNumberOfCharactersPerRow * s_MaxNumberOfCharactersPerColumn;

        public:
            
            enum EColorBase
            {
                ForegroundBlue      = 1,
                ForegroundGreen     = 2,
                ForegroundRed       = 4,
                ForegroundIntensity = 8,
                ForegroundCyan      = ForegroundBlue   | ForegroundGreen,
                ForegroundPurple    = ForegroundRed    | ForegroundBlue,
                ForegroundYellow    = ForegroundRed    | ForegroundGreen,

                BackgroundBlue      = 16,
                BackgroundGreen     = 32,
                BackgroundRed       = 64,
                BackgroundIntensity = 128,
                BackgroundCyan      = BackgroundBlue   | BackgroundGreen,
                BackgroundPurple    = BackgroundRed    | BackgroundBlue,
                BackgroundYellow    = BackgroundRed    | BackgroundGreen,

                FullIntensity       = ForegroundIntensity | BackgroundIntensity
            };

            enum EAttribute
            {
                BlackOnBlack   = 0,

                BlueOnBlue     = ForegroundBlue   | BackgroundBlue   | FullIntensity,
                GreenOnGreen   = ForegroundGreen  | BackgroundGreen  | FullIntensity,
                RedOnRed       = ForegroundRed    | BackgroundRed    | FullIntensity,
                CyanOnCyan     = ForegroundCyan   | BackgroundCyan   | FullIntensity,
                PurpleOnPurple = ForegroundPurple | BackgroundPurple | FullIntensity,
                YellowOnYellow = ForegroundYellow | BackgroundYellow | FullIntensity,

                BlueOnBlack    = ForegroundBlue   | ForegroundIntensity,
                GreenOnBlack   = ForegroundGreen  | ForegroundIntensity,
                RedOnBlack     = ForegroundRed    | ForegroundIntensity,
                CyanOnBlack    = ForegroundCyan   | ForegroundIntensity,
                PurpleOnBlack  = ForegroundPurple | ForegroundIntensity,
                YellowOnBlack  = ForegroundYellow | ForegroundIntensity,
            };

        public:

            static CConsole& GetInstance();

        public:

            void Print(char _Symbol, unsigned int _X, unsigned int _Y);
            void Clear();

            void SwapBuffers();
            void ActivateBuffer();

        public:

            void SetClearSymbol(char _Symbol);
            void SetPrintAttribute(unsigned short _Attribute);

        private:

            CConsole();
            ~CConsole();

        private:

            char       m_ClearSymbol;
            EAttribute m_CurrentAttribute;

        private:

            void* m_pConsoleBuffer1;
            void* m_pConsoleBuffer2;
            void* m_pActiveBuffer;
    };
} // namespace Gfx