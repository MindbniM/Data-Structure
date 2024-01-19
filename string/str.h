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
			_str = new char[_capacity + 1] {0};
			_size = _capacity;
			strcpy(_str, str);
		}
		string(const string& str)
		{
			_str = new char[str.size() + 1];
			strcpy(_str, str.c_str());
			_capacity = str.size();
			_size = _capacity;
		}
		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = 0;
			_capacity = 0;
		}
		size_t size()const
		{
			return _size;
		}
		void reserve(size_t capacity)
		{
			if (capacity < _capacity)
				return;
			char* new_str = new char[capacity + 1]{0};
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
				_size = size;
			}
		}
		size_t capacity()const
		{
			return _capacity;
		}
		void push_back(char c)
		{
			if (_size == _capacity)
			{
				size_t new_capacity = _capacity == 0 ? 4 : 2 * _capacity;
				reserve(new_capacity);
			}
			_str[_size] = c;
			_size++;
		}
		char* c_str()
		{
			return _str;
		}
		const char* c_str() const
		{
			return _str;
		}
		string& append(const string str)
		{
			(*this)+= str;
			return *this;
		}
		string& insert(size_t pos, const string& str)
		{
			if (_size + str.size() > _capacity)
			{
				reserve(_size + str.size());
			}
			size_t end = pos + str.size()+_size;
			while (end >= _size)
			{
				_str[end] = _str[end - _size];
				--end;
			}
			strncpy(_str + pos, str.c_str(),str.size());
			_size += str.size();
			return *this;
		}
		string& erase(size_t pos, size_t n = npos)
		{
			if (n == npos || n + pos >= _size)
			{
				_str[pos] = '\0';
			}
			else
			{
				strcpy(_str + pos, _str + pos + n);
			}
			return *this;
		}
		string& repalce(size_t pos, size_t n, const string& str)
		{
			assert(pos <= _size);
			for (int i = pos; i < n+pos; i++)
			{
				_str[i] = str.c_str()[i];
			}
			return *this;
		}
		size_t find(const string& str, size_t pos=0)
		{
			assert(pos <= _size);
			char*s=strstr(_str + pos, str.c_str());
			if (s != nullptr)
			{
				return s - _str;
			}
			return npos;
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
		string& operator+= (const string& str)
		{
			if (_size + str.size() > _capacity)
			{
				reserve(_size + str.size());
			}
			strcpy(_str + _size, str.c_str());
			_size += str.size();
			return *this;
		}
		string& operator+= (char c)
		{
			push_back(c);
			return *this;
		}
		string operator+(const string& str) const
		{
			string s(*this);
			s += str;
			return s;
		}
		string& operator= (const string& str)
		{
			if (this == &str)
				return *this;
			strcpy(_str, str.c_str());
			return *this;
		}
		void swap(string& str)
		{
			if (this == &str)
				return ;

			_str = str.c_str();
		}
		static size_t npos;
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
	size_t string::npos = -1;
}