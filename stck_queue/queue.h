#pragma once
namespace M
{
	template<class T, class Container = std::deque<T>>
	class queue
	{
	public:
		void push(const T& val)
		{
			_con.push_back(val);
		}
		void pop()
		{
			_con.pop_front();
		}
		const T& front()
		{
			return _con.front();
		}
		const T& back()
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
	private:
		Container _con;
	};
	template<class T,class Container=std::vector<T>,class Compare=less<T>>
	class priority_queue
	{
	public:
		size_t size()
		{
			return _con.size();
		}
		void push(const T& val)
		{
			_con.push_back(val);
			atjustup(size() - 1);
		}
		void pop()
		{
			std::swap(_con[0], _con[size() - 1]);
			_con.pop_back();
			atjustdown(0);
		}
		bool empty()
		{
			return size() == 0;
		}
		const T& top()
		{
			return _con[0];
		}
	private:
		void atjustup(size_t n)
		{
			int prant = (n - 1) / 2;
			while (prant >= 0)
			{
				if(Compare()(_con[n], _con[prant]))
				{
					std::swap(_con[n],_con[prant]);
					n=prant;
					prant=(n-1)/2;
				}
				else
					break;
			}
		}
		void atjustdown(size_t n)
		{
			int child = n * 2 + 1;
			while (child < size())
			{
				if (child + 1 < size() && Compare()(_con[child + 1], _con[child]))
					child++;
				if (Compare()(_con[child], _con[n]))
				{
					std::swap(_con[child], _con[n]);
					n = child;
					child = n * 2 + 1;
				}
				else
					break;
			}
		}
		Container _con;
	};
}
