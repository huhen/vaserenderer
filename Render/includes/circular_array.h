#ifndef VASER_CIRCULAR_ARRAY_H
#define VASER_CIRCULAR_ARRAY_H

#ifdef VASE_RENDERER_EXPER
namespace VASEr
{
	namespace VASErin
	{	//VASEr internal namespace
		template <typename T>
		class circular_array
		{
			const int size;
			int cur; //current
			T* array;
		public:
			circular_array(int size_);

			~circular_array();

			void push(T obj);

			int get_size() const;

			int get_i(int i) const; //get valid index relative to current

			void move(int i); //move current relatively

			T& operator[](int i); //get element at relative position
		};
	}
}

#endif //VASE_RENDERER_EXPER

#endif
