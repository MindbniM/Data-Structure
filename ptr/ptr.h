#pragma once
template<class T>
class auto_ptr
{
public:
	auto_ptr(T* data=nullptr) :_ptr(data)
	{}
	auto_ptr(auto_ptr<T>& ptr)
	{
		_ptr = ptr._ptr;
		ptr._ptr = nullptr;
	}
	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
	auto_ptr<T>& operator=(auto_ptr<T>& ptr)
	{
		_ptr = ptr._ptr;
		ptr._ptr = nullptr;
		return *this;
	}
	~auto_ptr()
	{
		delete _ptr;
		_ptr = nullptr;
	}
private:
	T* _ptr=nullptr;
};

template<class T>
class unique_ptr
{
public:
	unique_ptr(T* data = nullptr) :_ptr(data)
	{}
	unique_ptr(const unique_ptr<T>& ptr) = delete;
	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
	unique_ptr<T>& operator=(const unique_ptr<T>& ptr) = delete;
	~unique_ptr()
	{
		delete _ptr;
		_ptr = nullptr;
	}
private:
	T* _ptr = nullptr;
};

template<class T>
class shared_ptr
{
public:
	shared_ptr(T* data) :_ptr(data),_count(new int(1)),_m(new std::mutex)
	{}
	template<class D>
	shared_ptr(T* data,D del):_ptr(data),_count(new int(1)),_del(del),_m(new std::mutex)
	{}
	shared_ptr(const shared_ptr<T>& ptr)
	{
		_ptr = ptr._ptr;
		_count = ptr._count;
		_m = ptr._m;
		std::lock_guard<std::mutex> lock(*_m);
		++(*_count);
	}
	~shared_ptr()
	{
		remove();
	}
	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
	shared_ptr<T>& operator=(const shared_ptr& ptr)
	{
		if (_ptr != ptr._ptr)
		{
			remove();
			_ptr = ptr._ptr;
			_count = ptr._count;
			_m = ptr._m;
			std::lock_guard<std::mutex> lock(*_m);
			++(*_count);
		}
		return *this;
	}
	int count()
	{
		return *_count;
	}
	T* get()
	{
		return _ptr;
	}
private:
	void remove()
	{
		_m->lock();
		bool flag = false;
		if (--(*_count) == 0&&_ptr)
		{
			std::cout << "delete ptr "<<std::endl;
			_del(_ptr);
			delete _count;
			_ptr = nullptr;
			_count = nullptr;
			flag = true;
		}
		_m->unlock();
		if (flag)
		{
			delete _m;
		}
	
	}
	T* _ptr;
	int* _count;
	std::mutex* _m;
	std::function<void(T*)> _del = [](T* ptr) {delete ptr; };
};
template<class T>
class weak_ptr
{
public:
	weak_ptr(){}
	weak_ptr(shared_ptr<T>& ptr)
	{
		_ptr = ptr.get();
	}
	weak_ptr(const weak_ptr<T>& ptr)
	{
		_ptr = ptr._ptr;
	}
	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
private:
	T* _ptr=nullptr;
};
