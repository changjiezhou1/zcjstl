#ifndef MYINTYSTL_TYPE_TRAITS_H_
#define MYINTYSTL_TYPE_TRAITS_H_
//本文件使用做为提取类型信息

#include<type_traits>
namespace mystl {
	//helper struct

	template <class T,T v>
	struct m_integral_constant
	{
		static constexpr T value = v;//静态常量类型

	};

	template<bool b>
	using m_bool_constant = m_integral_constant<bool, b>;

	typedef m_bool_constant<true> m_true_type;
	typedef m_bool_constant<false> m_false_type;

	template <class T1,class T2>
	struct pair;
	template <class T>
	struct is_pair : mystl::m_false_type{
		//??

	};
	template <class T1,class T2>
	struct 	is_pair<mystl::pair<T1,T2>> : mystl::m_true_type{};
}


#endif // !MYINTYSTL_TYPE_TRAITS_H_
