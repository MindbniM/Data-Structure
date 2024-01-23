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
			string s(str.c_str());
			swap(s);
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
			size_t end = str.size()+_size;
			while (end > pos)
			{
				_str[end] = _str[end - str.size()];
				--end;
			}
			strncpy(_str + pos, str.c_str(),str.size());
			_size += str.size();
			return *this;
		}
		string& insert(size_t pos, char c)
		{
			if (_size + 1 > _capacity)
			{
				reserve(_size + 1);
			}
			size_t end = 1 + _size;
			while (end > pos)
			{
				_str[end] = _str[end - 1];
				--end;
			}
			_str[pos] = c;
			_size ++;
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
		string substr(size_t pos, size_t len = string::npos)
		{
			assert(pos <= _size);
			string s;
			if (len == npos || pos+len >= _size)
			{
				s += (_str + pos);
				return s;
			}
			while (len>0)
			{
				s += _str[pos];
				pos++;
				len--;
			}
			return s;

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
		string& operator= (string str)
		{
			swap(str);
			return *this;
		}
		void swap(string& str)
		{
			if (this == &str)
				return ;
			std::swap(_str, str._str);
			std::swap(_size, str._size);
			std::swap(_capacity, str._capacity);
		}
		void clear()
		{
			memset(_str, 0, _size);
			_size = 0;
		}
		static size_t npos;
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
	size_t string::npos = -1;
	std::ostream& operator<<(std::ostream& out, M::string& str)
	{
		for (int i = 0; i < str.size(); i++)
		{
			out << str.c_str()[i];
		}
		return out;
	}
	std::istream& operator>>(std::istream& in, M::string& str)
	{
		char ch=in.get();
		char strbuff[128];
		int i = 0;
		while (ch != ' ' && ch != '\n')
		{
			strbuff[i++]=ch;
			if (i == 127)
			{
				strbuff[i] = '\0';
				str += strbuff;
				i = 0;
			}
			ch = in.get();
		}
		if (i != 0)
		{
			strbuff[i] = '\0';
			str += strbuff;
		}
		return in;
	}
}