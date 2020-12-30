
#ifndef DESIGNPATTERN_SINGLETON_H
#define DESIGNPATTERN_SINGLETON_H

// �̲߳�̫��ȫ��ÿһ���߳��õ���һ��instance��
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

// �̺߳ܰ�ȫ��ÿһ���߳��õ��ǲ�ͬ��instance��
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