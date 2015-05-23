#include "cst_singleton.h"

template<class T>
T* Singleton::GetInstance()
{
	static T instance;
	return &instance;
}


Singleton::Singleton();
{

}
