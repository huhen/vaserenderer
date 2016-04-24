#ifdef VASE_RENDERER_EXPER

#include "includes/circular_array.h"

namespace VASEr
{
	namespace VASErin
	{	//VASEr internal namespace
		template <typename T>
		circular_array<T>::circular_array(int size_) : size(size_)
		{
			array = new T[size];
			cur = 0;
		}

		template <typename T>
		circular_array<T>::~circular_array()
		{
			delete[] array;
		}

		template <typename T>
		void circular_array<T>::push(T obj)
		{
			array[cur] = obj;
			move(1);
		}

		template <typename T>
		int circular_array<T>::get_size() const
		{
			return size;
		}

		template <typename T>
		int circular_array<T>::get_i(int i) const //get valid index relative to current
		{
			int des = cur + i % size;
			if (des > size - 1)
			{
				des -= size;
			}
			if (des < 0)
			{
				des = size + i;
			}
			return des;
		}

		template <typename T>
		void circular_array<T>::move(int i) //move current relatively
		{
			cur = get_i(i);
		}

		template <typename T>
		T& circular_array<T>::operator[](int i) //get element at relative position
		{
			return array[get_i(i)];
		}
	}
}

#endif
