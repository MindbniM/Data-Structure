#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<assert.h>
using std::cout;
using std::cin;
using std::endl;
namespace M
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str+_size;
		}
		const_iterator begin()const
		{
			return _str;
		}
		const_iterator end()const
		{
			return _str + _size;
		}
		string(const char* str = "")
		{
			_capacity = strlen(str);
			_str = new char[_capacity + 1];
			_size = _capacity;
			strcpy(_str, str);
		}
		~string()
		{
			delete[] _str;
			_str == nullptr;
			_size = 0;
			_capacity = 0;
		}
		size_t size()
		{
			return _size;
		}
		void reserve(size_t capacity)
		{
			if (capacity < _capacity)
				return;
			char* new_str = new char[capacity+1];
			strcpy(new_str, _str);
			delete[] _str;
			_str = new_str;
			_capacity = capacity;
		}
		void resize(size_t size)
		{
			if (size < _size)
			{
				size_t len = strlen(_str);
				_size = len + 1;
			}
			else 
			{
				if (size > _capacity)
				{
					reserve(size);
				}
				for (int i = _size; i <= size; i++)
				{
					_str[i] = '\0';
				}
				_size = size;
			}
		}
		size_t capacity()
		{
			return _capacity;
		}
		char* c_str()
		{
			return _str;
		}
		const char* c_str() const
		{
			return _str;
		}
		char& operator[](size_t pos)
		{
			assert(pos <= _size);
			return _str[pos];
		}
		const char& operator[](size_t pos) const
		{
			assert(pos <= _size);
			return _str[pos];
		}
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
}