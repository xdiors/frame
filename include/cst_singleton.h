#ifndef CST_SINGLETON_H
#define CST_SINGLETON_H


// used to make a class singleton

#define SET_SINGLETON(T) 		\
private:						\
	T() 						\
	{							\
								\
	}							\
	~T()						\
	{							\
								\
	}							\
								\
public:							\
	static T* GetInstance()		\
	{							\
		static T instance;		\
		return &instance;		\
	}	

#endif 
