#pragma once
#ifndef M_VECTOR
#define M_VECTOR
#include"Reverse_iterator.h"
namespace M
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		typedef Reverse_iterator<iterator, T&, T*> reverse_iterator;
		typedef Reverse_iterator<const_iterator, const T&,const T*> const_reverse_iterator;
		vector()
		{}
		vector(const vector<T>& v)
		{
			reserve(v.capacity());
			for (auto& e : v)
			{
				push_back(e);
			}
		}
		vector(std::initializer_list<T> li)
		{
			for (auto& i : li)
			{
				push_back(i);
			}
		}
		template<class ITERATOR>
		vector(ITERATOR begin, ITERATOR end)
		{
			while (begin != end)
			{
				push_back(*begin);
				begin++;
			}
		}
		~vector()
		{
			delete[] _start;
			_start = _finish = _end = nullptr;
		}
		void push_back(const T& val);
		void pop_back();
		void insert(iterator pos,const T& val);
		iterator erase(iterator pos)
		{
			assert(size());
			assert(_start <= pos);
			assert(_finish >= pos);
			iterator end = pos;
			int n = pos - _start;
			while (end < _finish)
			{
				*end = *(end + 1);
				end++;
			}
			--_finish;
			return _start + n;
		}
		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_end, v._end);
		}
		T& front()
		{
			assert(_start);
			return *_start;
		}
		const T& front() const
		{
			assert(_start);
			return *_start;
		}
		T& back() 
		{
			assert(_start);
			return *(_start+size()-1);
		}
		const T& back() const
		{
			assert(_start);
			return *(_start + size()-1);
		}
		size_t capacity() const
		{
			return _end - _start;
		}
		size_t size() const
		{
			return _finish - _start;
		}
		void reserve(const size_t n);
		void resize(const size_t n, T val = T());
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator begin() const
		{
			return _start;
		}
		const_iterator end() const
		{
			return _finish;
		}
		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}
		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}
		T& operator[](size_t pos);
		const T& operator[](size_t pos) const;
		vector<T>& operator=(vector<T> v);
		vector<T>& operator=(std::initializer_list<T> li);
	private:
		iterator _start=nullptr;
		iterator _finish=nullptr;
		iterator _end=nullptr;
	};
	template<class T>
	void vector<T>::push_back(const T& val)
	{
		if (_finish == _end)
		{
			size_t newcapacity = capacity() == 0 ? 4 : 2 * capacity();
			reserve(newcapacity);
		}
		*_finish = val;
		++_finish;
	}
	template<class T>
	void vector<T>::pop_back()
	{
		assert(size());
		--_finish;
	}
	template<class T>
	void vector<T>::insert(iterator pos,const T& val)
	{
		assert(_start <= pos);
		assert(_finish>= pos);
		if (_finish == _end)
		{
			size_t n = pos - _start;
			size_t newcapacity = capacity() == 0 ? 4 : 2 * capacity();
			reserve(newcapacity);
			pos = _start + n;
		}
		_finish++;
		iterator end = _finish-1;
		while (end != pos)
		{
			*end = *(end - 1);
			end--;
		}
		*pos = val;
	}
	template<class T>
	void vector<T>::reserve(const size_t n)
	{
		if (n > capacity())
		{
			size_t oldn = size();
			T* temp = new T[n];
			if(_start!=nullptr)
			{
				size_t end = size();
				while (end > 0)
				{
					temp[end-1] = _start[end-1];
					end--;
				}
				delete[] _start;
			}
			_start = temp;
			_finish = _start + oldn;
			_end = _start + n;
		}
	}
	template<class T>
	void vector<T>::resize(const size_t n, T val)
	{
		if (n > size())
		{
			reserve(n);
			for (size_t i = size(); i < n; i++)
			{
				_start[i] = val;
				_finish++;
			}
		}
		else
		{
			_finish = _start+ n;
		}
	}
	template<class T>
	T& vector<T>::operator[](size_t pos)
	{
		assert(pos < size());
		return *(_start + pos);
	}
	template<class T>
	const T& vector<T>::operator[](size_t pos)const
	{
		assert(pos < size());
		return *(_start + pos);
	}
	template<class T>
	vector<T>& vector<T>::operator=( vector<T> v)
	{
		swap(v);
		return *this;
	}
	template<class T>
	vector<T>& vector<T>::operator=(std::initializer_list<T> li)
	{
		vector<T> v(li);
		swap(v);
		return *this;
	}


}

#endif // !M_VECTOR

