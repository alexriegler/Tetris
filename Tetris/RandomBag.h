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

		bool Empty() const { return m_UseSwapBag ? m_SwapCount == 0 : m_Count == 0 }

		bool Full() const { return m_UseSwapBag ? m_SwapCount == S : m_Count == S; }

		void Place(const T& item) 
		{
			if (!Full())
			{
				if (m_UseSwapBag)
				{
					m_SwapBag[m_Count] = item;
					m_SwapCount++;
				}
				else
				{
					m_Bag[m_Count] = item;
					m_Count++;
				}
			}
			// TODO: else error
		}

		T& Grab()
		{
			if (Empty())
			{
				m_UseSwapBag = !m_UseSwapBag;
				Mix();
			}

			if (m_UseSwapBag)
			{
				m_SwapCount--;
				SwitchBag(m_SwapBag[m_NextIndex])
				return m_SwapBag[m_NextIndex++];
			}
			else
			{
				m_Count--;
				SwitchBag(m_Bag[m_NextIndex])
				return m_Bag[m_NextIndex++];
			}
		}

		void Mix()
		{
			// Obtain a time-based seed
			unsigned seed = chrono::system_clock::now().time_since_epoch().count();
			
			if (m_UseSwapBag)
			{
				shuffle(m_SwapBag.begin(), m_SwapBag.end(), default_random_engine(seed));
			}
			else
			{
				shuffle(m_Bag.begin(), m_Bag.end(), default_random_engine(seed));
			}
		}

		T* Data() { return m_Bag; }
		const T* Data() const { return m_Bag; }
	private:
		array<T, S> m_Bag;
		size_t m_Count;
		array<T, S> m_SwapBag;
		size_t m_SwapCount;
		bool m_UseSwapBag = false;
		size_t m_NextIndex = 0;

		void SwitchBag(const T& item)
		{
			if (m_UseSwapBag)
			{
				m_Bag[m_Count] = item;
				m_Count++;
			}
			else
			{
				m_SwapBag[m_Count] = item;
				m_SwapCount++;
			}
		}
	};
}