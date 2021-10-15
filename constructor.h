#infndef MYTINYSTL_CONSTRUCT_H_
#define MYTINYSTL_CONSTRUCT_H_
//consturct负责对象的构造
//destroy:负责对象的析构

#include<new>
#include "type_traits.h"
#include"iterator.h"

#include _MSC_VER
#progma warning(push)//保存当前的编译器警告状态
#progma warning(disable:4100)//unused parameter 不使用4100进行
#endif //_MSC_VER

namespace mystl {
	template<class Ty>
	void construct(Ty* ptr) {
		::new ((void*)ptr) Ty();
	}
	template <class Ty1,class Ty2>
	void construct(Ty1* ptr, const Ty2& value) {
		::new ((void*)ptr)Ty1(value);
	}
	template<class Ty,class... Args>
	void construct(Ty* ptr, Args&&...args) {
		::new ((void*)ptr) Ty(mystl::forward<Args>(args)...);

	}
	template <class Ty>
	void destroy_one(Ty*, std::true_type) {//没有指明析构函数的应该是使用默认的析构函数
		
	}

	template <class Ty>
	void destroy_one(Ty* pointer, std::false_type) {
		if (pointer != nullptr) {//有自己实现的析构函数，就可以使用
			pointer->~Ty();
		}
	}

	template <class ForwardIter>
	void destroy_cat(ForwardIter,ForwardIter,std::true_type){}

	template <class ForwardIter>
	void destroy_cat(ForwardIter first, ForwardIter last, std::false_type) {
		//通过迭代器进行销毁
		for (; first != last; ++first) {
			destroy(&*first);//首先调用destory,然后调用destory_one进行析构、
		}

	}
	template<class Ty>
	void destroy(Ty* pointer) {
		destroy_one(pointer, std::is_trivially_destructible<Ty>{});//is_trivially_destructible使用微不足道的可毁灭的
	} 

	template<class ForwardIter>

	void destroy(ForwardIter first, ForwardIter last) {
		destory_cat(first, last, std::is_trivially_destructible<typename iterator_traits<ForwardIter>::value_type>{});
	}


	}
	
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
		