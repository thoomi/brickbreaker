#pragma once

#include "world/world_entity.h"

#include <string>

namespace World
{
    class CPlayer
	{
        public:

            typedef std::shared_ptr<CPlayer> SharedPtr;
            typedef std::unique_ptr<CPlayer> UniquePtr;

        public:

            int GetID() const;

            void SetPlayerName(const std::string& _rName);
            const std::string& GetPlayerName() const;

            CEntity::SharedPtr GetEntity() const;
            void SetEntity(CEntity::SharedPtr _pEntity);

        public:

            int GetNumberOfDestroyedBricks();
            void CountDestroyedBrick();
            void ClearBrickCount();

        public:

            CPlayer(int _ID);

        private:

            CPlayer(const CPlayer& _rPlayer);
            CPlayer& operator = (const CPlayer& _rPlayer);

        private:

            int                m_ID;
            std::string        m_PlayerName;
            CEntity::SharedPtr m_pEntity;

        private:

            int m_NumberOfDestroyedBricks;
	};
} // namespace World