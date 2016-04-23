#pragma once

#include "world/world_entity.h"

namespace Logic
{
    class CCommand
    {
        public:

            enum EType
            {
                MoveEntity,
                StandardAction,
                NumberOfTypes,
                Undefined = -1
            };

            enum EDirection
            {
                Stop,
                Up,
                Down,
                Left,
                Right
            };

        public:

            CCommand();

        public:

            EType GetType() const;
            void  SetType(EType _Type);

            void SetEntity(World::CEntity::SharedPtr _pEntity);
            World::CEntity::SharedPtr GetEntity() const;

            void SetMovingDirection(EDirection _Direction);
            EDirection GetMovingDirection() const;

        private:

            EType                     m_Type;
            World::CEntity::SharedPtr m_pEntity;
            EDirection                m_MovingDirection;
    };
} // namespace Logic