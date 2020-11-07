#pragma once
#include <algorithm>
#include <array>
#include <random>
#include <chrono>
using namespace std;

namespace Tetris
{
	template<typename T, size_t S>
	class RandomBag
	{
	public:
		size_t Count() const { return m_UseSwapBag ? m_SwapCount : m_Count; }
		
		constexpr size_t Capacity() const { return S; }

		bool Empty() const { return m_UseSwapBag ? m_SwapCount == 0 : m_Count == 0; }

		bool Full() const { return m_UseSwapBag ? m_SwapCount == S : m_Count == S; }

		void Place(T* item)
		{
			if (!Full())
			{
				if (m_UseSwapBag)
				{
					m_SwapCount++;
					m_SwapBag[m_SwapCount - 1] = item;
				}
				else
				{
					m_Count++;
					m_Bag[m_Count - 1] = item;
				}
			}
			// TODO: else error
		}

		T Grab()
		{
			if (Empty())
			{
				m_UseSwapBag = !m_UseSwapBag;
				Mix();
			}

			return SwapAndGrab();
		}

		void Mix()
		{
			// Obtain a time-based seed
			unsigned int seed = (unsigned int) chrono::system_clock::now().time_since_epoch().count();
			
			if (m_UseSwapBag)
			{
				shuffle(m_SwapBag.begin(), m_SwapBag.end(), default_random_engine(seed));
			}
			else
			{
				shuffle(m_Bag.begin(), m_Bag.end(), default_random_engine(seed));
			}
		}
	private:
		array<T*, S> m_Bag{};
		size_t m_Count = 0;

		array<T*, S> m_SwapBag{};
		size_t m_SwapCount = 0;

		bool m_UseSwapBag = false;

		T SwapAndGrab()
		{
			if (m_UseSwapBag)
			{
				// Remove item from bag
				T* item = m_SwapBag[m_SwapCount - 1];
				m_SwapCount--;

				// Place item into swap bag
				m_Count++;
				m_Bag[m_Count - 1] = item;
				
				// Return item
				return *item;
			}
			else
			{
				// Remove item from bag
				T* item = m_Bag[m_Count - 1];
				m_Count--;

				// Place item into swap bag
				m_SwapCount++;
				m_SwapBag[m_SwapCount - 1] = item;

				// Return item
				return *item;
			}
		}
	};
}