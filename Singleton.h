
#ifndef DESIGNPATTERN_SINGLETON_H
#define DESIGNPATTERN_SINGLETON_H

// 线程不太安全（每一个线程用的是一个instance）
class Singleton_NOTSECURE
{
private:
	Singleton_NOTSECURE() {}
	static Singleton_NOTSECURE* pInstance;
public:
	static Singleton_NOTSECURE* GetInstance()
	{
		if (pInstance == nullptr)
			pInstance = new Singleton_NOTSECURE();
		return pInstance;
	}
};

// 线程很安全（每一个线程用的是不同的instance）
class Singleton
{
private:
	Singleton() {}
	~Singleton() {}
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
public:
	static Singleton& GetInstance()
	{
		static Singleton instance;
		return instance;
	}
	void DoSomething();
};

#endif