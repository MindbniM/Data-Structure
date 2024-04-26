
namespace M
{
	template<class iterator, class refer, class ptr>
	class Reverse_iterator
	{
		typedef Reverse_iterator<iterator, refer, ptr> self;
	public:
		Reverse_iterator(iterator it)
			:_it(it)
		{
		}
		self& operator++()
		{
			--_it;
			return *this;
		}
		self& operator--()
		{
			++_it;
			return *this;
		}
		refer operator*()
		{
			iterator temp(_it);
			return *(--temp);
		}
		ptr operator->()const
		{
			iterator temp(_it);
			--temp;
			return temp.operator->();
		}
		bool operator==(const self& it)const
		{
			return _it == it._it;
		}
		bool operator!=(const self& it)const
		{
			return _it != it._it;
		}
	private:
		iterator _it;
	};
}
