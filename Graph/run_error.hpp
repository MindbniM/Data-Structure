#pragma once
#include<iostream>
#include<exception>
class run_exception : public std::exception
{
public:
	run_exception(const std::string& str):_str(str)
	{}
	virtual const char* what()
	{
		return _str.c_str();
	}
private:
	std::string _str;
};
