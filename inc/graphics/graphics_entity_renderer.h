#pragma once

namespace Gfx
{
    class CEntityRenderer
    {
        public:

            static CEntityRenderer& GetInstance();

        public:

            void Render();

        private:

            CEntityRenderer();
            ~CEntityRenderer();
    };
} // namespace Gfx