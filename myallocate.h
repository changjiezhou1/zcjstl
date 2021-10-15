//
#ifndef MYTINYSTL_ALLOCATOR_H_
#define MYTINSTL_ALLOCATOR_H_

//
#include"construct.h"
#include "util.h"

namesapce mystl{
	//���������Լ��������ռ�

	//�����Լ���ģ����
template <class T>
class allocator {
public:
	//�������������ض���
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;//ָ������ָ��
	typedef T& reference;
	typedef const T& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;//������ʾ����������֮��Ĳ��
	
public:
	static T* allocate();//��Ĭ�Ϸ��亯��
	static T* allocate(size_type n);//���ݴ�С���з���

	static void deallocate(T* ptr);
	static void deallocate(pointer ptr, size_type n);

	static void construct(T* ptr);
	static void construct(T* ptr, const_reference value);
	static void construcr(T* ptr, T&& value);//�ƶ�����
	//ʹ�þ�̬��Ա��������ʹ��ֱ��ͨ������ȥ���ʣ�Ȼ����ǲ��޸������ı���

	template<class...Args>
	static void construct(T* ptr, Args&&... args);//������������ֵ�ƶ�
	static void destroy(T* ptr);
	static void destory(T* first, T* last);
	
};

template<class T>
T* allocator<T>::allocate() {
	return static_cast<T*>(::operator new(sizeof(T)));//��������ʹ����new���пռ�����룬���ҽ���static_cast<>������ת��
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
	mystl::construct(ptr);//ʹ��ǰ���ṩ�ĺ���
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

