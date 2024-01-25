#pragma once
#ifndef M_VECTOR
#define M_VECTOR
namespace M
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		vector();
	private:
		iterator _start;
		iterator _finish;
		iterator _end_of_;
	};

	template<class T>
	vector<T>::vector()
		:_start(nullptr)
		,_finish(nullptr)
		,_end_of_(nullptr)
	{
	}
}

#endif // !M_VECTOR

