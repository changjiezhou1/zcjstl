//
#ifndef MYTINYSTL_ALLOCATOR_H_
#define MYTINSTL_ALLOCATOR_H_

//
#include"construct.h"
#include "util.h"

namesapce mystl{
	//定义属于自己的命名空间

	//建立自己的模板类
template <class T>
class allocator {
public:
	//进行类型命名重定义
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;//指向常量的指针
	typedef T& reference;
	typedef const T& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;//用来表示两个迭代器之间的差距
	
public:
	static T* allocate();//，默认分配函数
	static T* allocate(size_type n);//根据大小进行分配

	static void deallocate(T* ptr);
	static void deallocate(pointer ptr, size_type n);

	static void construct(T* ptr);
	static void construct(T* ptr, const_reference value);
	static void construcr(T* ptr, T&& value);//移动构造
	//使用静态成员函数可以使得直接通过对象去访问，然后就是不修改其他的变量

	template<class...Args>
	static void construct(T* ptr, Args&&... args);//不定参数的右值移动
	static void destroy(T* ptr);
	static void destory(T* first, T* last);
	
};

template<class T>
T* allocator<T>::allocate() {
	return static_cast<T*>(::operator new(sizeof(T)));//我们这里使用了new进行空间的申请，并且进行static_cast<>进行了转换
}
template<class T>
T* allocator<T>; :allocate(size_type n) {
	if (n == 0)
		return nullptr;
	return static_cast<T*>(::operator new(n*sizeof(T)));

}
template<class T>
void allocator<T>::deallocate(T* ptr)
{
	if (prt == nullptr)
		return;
	::operator delete(ptr);
}

template<class T>
void allocator<T>::construct(T* ptr) {
	mystl::construct(ptr);//使用前面提供的函数
}
 template<class T>
 void allocator<T>::construct(T* ptr, const T& value) {
	 mystl::construct(ptr, value);
 }
 template <class T>
 void allocator<T>::construct(T* ptr, T&& value) {
	 mystl::construct(ptr, mystl::move(value));
 }
 template<class T>
 template<class...Args>
 void allocator<T>::construct(T* ptr, Args&&... args) {
	 mystl::construct(ptr, mystl::forward<Args>(args)...);
 }
 template <class T>
 void allocator<T>::destroy(T* ptr) {
	 mystl::destroy(ptr);
 }
 template<class T>
 void allocator<T>::destroy(T* first, T* last) {
	 mystl::destroy(first, last);
 }
}//namespace mystl
#endif //!MYTINYSTL_ALLOCATOR_H

