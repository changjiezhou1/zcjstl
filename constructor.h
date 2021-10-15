#infndef MYTINYSTL_CONSTRUCT_H_
#define MYTINYSTL_CONSTRUCT_H_
//consturct�������Ĺ���
//destroy:������������

#include<new>
#include "type_traits.h"
#include"iterator.h"

#include _MSC_VER
#progma warning(push)//���浱ǰ�ı���������״̬
#progma warning(disable:4100)//unused parameter ��ʹ��4100����
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
	void destroy_one(Ty*, std::true_type) {//û��ָ������������Ӧ����ʹ��Ĭ�ϵ���������
		
	}

	template <class Ty>
	void destroy_one(Ty* pointer, std::false_type) {
		if (pointer != nullptr) {//���Լ�ʵ�ֵ������������Ϳ���ʹ��
			pointer->~Ty();
		}
	}

	template <class ForwardIter>
	void destroy_cat(ForwardIter,ForwardIter,std::true_type){}

	template <class ForwardIter>
	void destroy_cat(ForwardIter first, ForwardIter last, std::false_type) {
		//ͨ����������������
		for (; first != last; ++first) {
			destroy(&*first);//���ȵ���destory,Ȼ�����destory_one����������
		}

	}
	template<class Ty>
	void destroy(Ty* pointer) {
		destroy_one(pointer, std::is_trivially_destructible<Ty>{});//is_trivially_destructibleʹ��΢������Ŀɻ����
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
		