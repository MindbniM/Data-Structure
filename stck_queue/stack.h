#pragma once
namespace M
{
	template<class T, class container = std::deque<T>>
	class stack
	{
	public:
		void push(const T& val)
		{
			_con.push_back(val);
		}
		void pop()
		{
			_con.pop_back();
		}
		const T& top()
		{
			return _con.back();
		}
		size_t size()
		{
			return _con.size();
		}
		bool empty()
		{
			return _con.size() == 0;
		}
		void swap(stack<T>& st)
		{
			std::swap(_con, st);
		}
	private:
		container _con;
	};
}
