#pragma once

#include <memory>

namespace World
{
    template <typename T>
	class CFacetContainer
	{
        public:

            typedef typename T::EFacet EFacet;
            typedef std::shared_ptr<void> SharedVoidPtr;

        public:

            CFacetContainer();
            ~CFacetContainer();

        public:

            template <class TFacet>
            std::shared_ptr<TFacet> GetFacet(EFacet _FacetType) const;

            void SetFacet(EFacet _FacetType, SharedVoidPtr _pFacet);
            bool HasFacet(EFacet _FacetType) const;

        public:

            void Clear();

        private:

            SharedVoidPtr m_pFacets[EFacet::NumberOfFacets];
	};
} // namespace World

namespace World
{
    template <typename T>
    CFacetContainer<T>::CFacetContainer()
    {
        Clear();
    }

    template <typename T>
    CFacetContainer<T>::~CFacetContainer()
    {
    }

    template <typename T>
    template <class TFacet>
    std::shared_ptr<TFacet> CFacetContainer<T>::GetFacet(EFacet _FacetType) const
    {
        return std::static_pointer_cast<TFacet>(m_pFacets[_FacetType]);
    }

    template <typename T>
    void CFacetContainer<T>::SetFacet(EFacet _FacetType, SharedVoidPtr _pFacet)
    {
        m_pFacets[_FacetType] = _pFacet;
    }

    template <typename T>
    bool CFacetContainer<T>::HasFacet(EFacet _FacetType) const
    {
        return m_pFacets[_FacetType] != nullptr;
    }

    template <typename T>
    void CFacetContainer<T>::Clear()
    {
        for (int IndexOfFacet = 0; IndexOfFacet < EFacet::NumberOfFacets; IndexOfFacet++)
        {
            m_pFacets[IndexOfFacet] = nullptr;
        }
    }
} // namespace World

