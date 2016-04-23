#pragma once

#include "world/world_player.h"

namespace World
{
	class CPlayerManager
	{
        public:

            enum EPlayerID
            {
                Player1,
                Player2,
                MaxNumberOfPlayers
            };

            
        public:

            static CPlayerManager& GetInstance();

        public:

            CPlayer::SharedPtr CreatePlayer(EPlayerID _ID);
            void DeletePlayer(EPlayerID _ID);
            CPlayer::SharedPtr GetPlayer(EPlayerID _ID);

        private:

            CPlayerManager();
            CPlayerManager(const CPlayerManager& _rPlayerManager);
            CPlayerManager& operator = (const CPlayerManager& _rPlayerManager);

        private:

            CPlayer::SharedPtr m_Players[MaxNumberOfPlayers];
	};
} // namespace World