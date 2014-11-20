#ifndef __YATL_TYPE_LIST_H__
#define __YATL_TYPE_LIST_H__

#include <iostream>

namespace yatl {

template<unsigned int Index> struct Int2Type {
	enum { Value = Index };
};

template<class T> struct Type2Type {
	typedef T Original;
};

template<class T, class U, bool b> struct SelectType;

template<class T, class U> struct SelectType<T, U, true> {
	typedef T Result;
};

template<class T, class U> struct SelectType<T, U, false> {
	typedef U Result;
};

struct NullType;

struct EmptyType {};

template<class T, class U> struct TypeList {
	typedef T Head;
	typedef U Tail;
};

template
	<
		class T0 = NullType, class T1 = NullType, class T2 = NullType, 
		class T3 = NullType, class T4 = NullType, class T5 = NullType, 
		class T6 = NullType, class T7 = NullType, class T8 = NullType, 
		class T9 = NullType, class T10 = NullType, class T11 = NullType, 
		class T12 = NullType, class T13 = NullType, class T14 = NullType, 
		class T15 = NullType, class T16 = NullType, class T17 = NullType, 
		class T18 = NullType, class T19 = NullType, class T20 = NullType, 
		class T21 = NullType, class T22 = NullType, class T23 = NullType, 
		class T24 = NullType, class T25 = NullType, class T26 = NullType, 
		class T27 = NullType, class T28 = NullType, class T29 = NullType, 
		class T30 = NullType, class T31 = NullType, class T32 = NullType, 
		class T33 = NullType, class T34 = NullType, class T35 = NullType, 
		class T36 = NullType, class T37 = NullType, class T38 = NullType, 
		class T39 = NullType, class T40 = NullType, class T41 = NullType, 
		class T42 = NullType, class T43 = NullType, class T44 = NullType, 
		class T45 = NullType, class T46 = NullType, class T47 = NullType, 
		class T48 = NullType, class T49 = NullType, class T50 = NullType, 
		class T51 = NullType, class T52 = NullType, class T53 = NullType, 
		class T54 = NullType, class T55 = NullType, class T56 = NullType, 
		class T57 = NullType, class T58 = NullType, class T59 = NullType
	>
struct MakeTypeList {
	typedef TypeList<T0, typename MakeTypeList<
		T1, T2, T3, T4, T5, T6, T7, T8, T9, 
		T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, 
		T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, 
		T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, 
		T40, T41, T42, T43, T44, T45, T46, T47, T48, T49, 
		T50, T51, T52, T53, T54, T55, T56, T57, T58, T59>::Result> Result;
};

template<>
struct MakeTypeList<> {
	typedef NullType Result;
};


//
// TypeListLength
//
template<class T> struct TypeListLength;
template<> struct TypeListLength<NullType> {
	enum { Value = 0 };
};

template<class T, class U>
struct TypeListLength<TypeList<T, U>> {
	enum { Value = 1 + TypeListLength<U>::Value };
};

//
// TypeAtTypeList
//
template<class T, unsigned int Index> struct TypeAtTypeList;
template<class T, class U> struct TypeAtTypeList<TypeList<T, U>, 0> {
	typedef T Result;
};

template<unsigned int Index> struct TypeAtTypeList<NullType, Index> {
	typedef NullType Result;
};

template<class T, class U, unsigned int Index> struct TypeAtTypeList<TypeList<T, U>, Index> {
	typedef typename TypeAtTypeList<U, Index - 1>::Result Result;
};

//
// IndexOfTypeList
//
template<class T, class U> struct IndexOfTypeList;
template<class T> struct IndexOfTypeList<NullType, T> {
	enum { Value = -1 };
};

template<class T, class U> struct IndexOfTypeList<TypeList<T, U>, T> {
	enum { Value = 0 };
};

template<class T, class U, class P> struct IndexOfTypeList<TypeList<T, U>, P> {
	enum { Value = IndexOfTypeList<U, P>::Value == -1 ? -1 : IndexOfTypeList<U, P>::Value + 1 };
};

//
// AppendTypeList
//
template<class T, class U> struct AppendTypeList;
template<class U> struct AppendTypeList<NullType, U> {
	typedef TypeList<U, NullType> Result;
};

template<class T, class U> struct AppendTypeList<NullType, TypeList<T, U>> {
	typedef TypeList<T, U> Result;
};

template<class T, class U, class P> struct AppendTypeList<TypeList<T, U>, P> {
	typedef TypeList<T, typename AppendTypeList<U, P>::Result> Result;
};

//
// EraseTypeList
//
template<class T, class U> struct EraseTypeList;
template<class U> struct EraseTypeList<NullType, U> {
	typedef NullType Result;
};

template<class T, class U> struct EraseTypeList<TypeList<T, U>, T> {
	typedef U Result;
};

template<class T, class U, class P> struct EraseTypeList<TypeList<T, U>, P> {
	typedef TypeList<T, typename EraseTypeList<U, P>::Result> Result;
};

//
// EraseAllTypeList
//
template<class T, class U> struct EraseAllTypeList;
template<class U> struct EraseAllTypeList<NullType, U> {
	typedef NullType Result;
};

template<class T, class U> struct EraseAllTypeList<TypeList<T, U>, T> {
	typedef typename EraseAllTypeList<U, T>::Result Result;
};

template<class T, class U, class P> struct EraseAllTypeList<TypeList<T, U>, P> {
	typedef TypeList<T, typename EraseAllTypeList<U, P>::Result> Result;
};

//
// UniqueTypeList
//
template<class T> struct UniqueTypeList;
template<> struct UniqueTypeList<NullType> {
	typedef NullType Result;
};

template<class T, class U> struct UniqueTypeList<TypeList<T, U>> {
	typedef TypeList<T, typename UniqueTypeList<typename EraseAllTypeList<U, T>::Result>::Result> Result;
};

//
// ReplaceTypeList
//
template<class T, class U, class P> struct ReplaceTypeList;
template<class U, class P> struct ReplaceTypeList<NullType, U, P> {
	typedef NullType Result;
};

template<class T, class U, class P> struct ReplaceTypeList<TypeList<T, U>, T, P> {
	typedef TypeList<P, U> Result;
};

template<class T, class U, class P, class Q> struct ReplaceTypeList<TypeList<T, U>, P, Q> {
	typedef TypeList<T, typename ReplaceTypeList<U, P, Q>::Result> Result;
};

//
// ReplaceAllTypeList
//
template<class T, class U, class P> struct ReplaceAllTypeList;
template<class U, class P> struct ReplaceAllTypeList<NullType, U, P> {
	typedef NullType Result;
};

template<class T, class U, class P> struct ReplaceAllTypeList<TypeList<T, U>, T, P> {
	typedef TypeList<P, typename ReplaceAllTypeList<U, T, P>::Result> Result;
};

template<class T, class U, class P, class Q> struct ReplaceAllTypeList<TypeList<T, U>, P, Q> {
	typedef TypeList<T, typename ReplaceAllTypeList<U, P, Q>::Result> Result;
};

//
// ReverseToTypeList
//
template<class T, class U> struct ReverseToTypeList;
template<class T> struct ReverseToTypeList<NullType, T> {
	typedef T Result;
};

template<class T, class U, class E> struct ReverseToTypeList<TypeList<T, U>, E> {
	typedef typename ReverseToTypeList<U, TypeList<T, E>>::Result Result;
};

//
// ReverseTypeList
//
template<class T> struct ReverseTypeList {
	typedef typename ReverseToTypeList<T, NullType>::Result Result;
};

//
// FindTypeList
//
template<class T, class U> struct FindTypeList;
template<class T> struct FindTypeList<NullType, T> {
	typedef NullType Result;
};

template<class T, class U> struct FindTypeList<TypeList<T, U>, T> {
	typedef TypeList<T, U> Result;
};

template<class T, class U, class E> struct FindTypeList<TypeList<T, U>, E> {
	typedef typename FindTypeList<U, E>::Result Result;
};

//
// HasTypeList
//
template<class T, class U> struct HasTypeList;
template<class T> struct HasTypeList<NullType, T> {
	enum { Value = 0 };
};

template<class T, class U> struct HasTypeList<TypeList<T, U>, T> {
	enum { Value = 1 };
};

template<class T, class U, class E> struct HasTypeList<TypeList<T, U>, E> {
	enum { Value = HasTypeList<U, E>::Value };
};

//
// IsAllUniqueTypeList
//
template<class T> struct IsAllUniqueTypeList;
template<> struct IsAllUniqueTypeList<NullType> {
	enum { Value = 1 };
};

template<class T, class U> struct IsAllUniqueTypeList<TypeList<T, U>> {
	enum { Value = (HasTypeList<U, T>::Value == 0 ? 1 : 0) && (IsAllUniqueTypeList<U>::Value) };
};


template<class T> struct Tuple;
template<class T> struct Tuple {
	T value_;
};

template<> struct Tuple<NullType> {
};

template<class T, class U> struct Tuple<TypeList<T, U>> : public Tuple<U>{
	Tuple() {}
	Tuple(const Tuple<TypeList<T, U>> &src) : Tuple<U>(src), value_(src.value_) {}
	Tuple& operator = (const Tuple<TypeList<T, U>> &src) {
		value_ = src.value_;
		const Tuple<U> &obj = src;
		Tuple<U> &tail = *this;
		tail.operator=(obj);

		return *this;
	}
	Tuple(Tuple<TypeList<T, U>> &&src) : Tuple<U>((Tuple<U>&&)src) {
		value_ = src.value_;
		src.value_ = T();
	}
	Tuple& operator = (Tuple<TypeList<T, U>> &&src) {
		value_ = src.value_;
		src.value_ = T();
		Tuple<U> &obj = src;
		Tuple<U> &tail = *this;
		tail.operator=((Tuple<U>&&)obj);

		return *this;
	}
	T value_;
};

template<class T>
typename T::Head& get_help(Tuple<T> &src, Int2Type<0>)
{
	Tuple<T> &obj = src;
	return obj.value_;
}

template<unsigned int i, class T>
typename TypeAtTypeList<T, i>::Result& get_help(Tuple<T> &src, Int2Type<i>)
{
	Tuple<T::Tail> &obj = src;
	return get_help(obj, Int2Type<i - 1>());
}

template<unsigned int i, class T>
typename TypeAtTypeList<T, i>::Result& get(Tuple<T> &src)
{
	return get_help(src, Int2Type<i>());
}

template<class T> struct TupleConstructorHelper;
template<class T> struct TupleConstructorHelper<TypeList<T, NullType>> {
	TupleConstructorHelper(Tuple<TypeList<T, NullType>> &src) : container_(src) {}
	void operator () (const T &t) {
		new (&container_.value_) T(t);
	}

	Tuple<TypeList<T, NullType>>& container_;
};

template<class T, class U> struct TupleConstructorHelper<TypeList<T, U>> {
	TupleConstructorHelper(Tuple<TypeList<T, U>> &src) : container_(src) {}
	TupleConstructorHelper<U> operator () (const T &t) {
		new (&container_.value_) T(t);
		Tuple<U> &obj = container_;
		return TupleConstructorHelper<U>(obj);
	}

	Tuple<TypeList<T, U>>& container_;
};

template<class T, template <class> class F> struct EnumTypeList;

template<template <class> class F> struct EnumTypeList<NullType, F> {
};

template<class T, class U, template <class> class F> struct EnumTypeList<TypeList<T, U>, F>
{
	EnumTypeList() {
		F<T>();
		EnumTypeList<U, F>();
	}
};

template<class T> struct PrintType
{
	PrintType() { std::cout << "[" << typeid(T).name() << "], "; }
};

#define PRINT_TYPELIST(x) \
{																\
	std::cout << typeid(x).name() << std::endl <<				\
	" -Length:" << TypeListLength<x>::Value<< "  ";				\
	EnumTypeList<x, PrintType>(); std::cout << std::endl << std::endl;	\
}


typedef char r1;
typedef struct {
	char foo[2];
} r2;

template<class T1, class T2>
struct Conversion {

	static T1 MakeT1();

	static r1 CheckType(T2);
	static r2 CheckType(...);

	enum {
		exists = sizeof(CheckType(MakeT1())) == sizeof(r1),
		exists2way = Conversion<T2, T1>::exists && exists,
		sametype = false
	};
};

template<class T>
struct Conversion<T, T> {
	enum {
		exists = true,
		exists2way = true,
		sametype = true
	};
};



template<class T> struct SortTypeList_GetFirst;

template<class T> struct SortTypeList_GetFirst<TypeList<T, NullType>> {
	typedef T Result;
};

template<class T, class U> struct SortTypeList_GetFirst<TypeList<T, U>> {
	typedef typename SortTypeList_GetFirst<U>::Result TailResult;
	enum {
		CmpResult = T::yatl_index < TailResult::yatl_index
	};
	typedef typename SelectType<T, TailResult, CmpResult>::Result Result;
};

template<class T> struct SortTypeList;

template<> struct SortTypeList<NullType> {
	typedef NullType Result;
};

template<class T, class U> struct SortTypeList<TypeList<T, U>> {
	typedef typename SortTypeList_GetFirst<TypeList<T, U>>::Result FirstResult;
	typedef typename ReplaceTypeList<U, FirstResult, T>::Result TailResult;
	typedef typename TypeList<FirstResult, typename SortTypeList<TailResult>::Result> Result;
};

template<class T,int yatl_index> struct TypeListGetTypeByYatlIndex;

template<int yatl_index> struct TypeListGetTypeByYatlIndex<NullType, yatl_index> {
	typedef NullType Result;
};

template<class T, class U, int yatl_index> struct TypeListGetTypeByYatlIndex<TypeList<T, U>, yatl_index> {
	enum {
		CmpResult = yatl_index == T::yatl_index
	};
	typedef typename SelectType<T, typename TypeListGetTypeByYatlIndex<U, yatl_index>::Result, CmpResult>::Result Result;
};


template<class T, int begin_pos, int end_pos, bool valid, int yatl_index> struct BinaryFindTypeList;

template<class T, int begin_pos, int end_pos, int yatl_index> struct BinaryFindTypeList<T, begin_pos, end_pos, false, yatl_index> {
	typedef NullType Result;
};

template<class T, class U, int begin_pos, int end_pos, int yatl_index> struct BinaryFindTypeList<TypeList<T, U>, begin_pos, end_pos, true, yatl_index> {
	enum {
		MiddlePos = (begin_pos + end_pos) >> 1
	};

	typedef typename TypeAtTypeList<TypeList<T, U>, MiddlePos>::Result MiddleType;

	enum {
		CmpResult1 = MiddleType::yatl_index == yatl_index,
		CmpResult2 = MiddleType::yatl_index < yatl_index,
	};

	typedef typename SelectType<MiddleType, 
		typename SelectType<
		typename BinaryFindTypeList<TypeList<T, U>, MiddlePos + 1, end_pos, MiddlePos + 1 <= end_pos, yatl_index>::Result, 
		typename BinaryFindTypeList<TypeList<T, U>, begin_pos, MiddlePos - 1, begin_pos <= MiddlePos - 1, yatl_index>::Result, CmpResult2>::Result, 
		CmpResult1>::Result Result;
};


template<class T, int begin_pos, int end_pos, bool valid, class R = void, class P = void> struct DispatchEngine;

template<class T, int begin_pos, int end_pos, class R, class P> struct DispatchEngine<T, begin_pos, end_pos, false, R, P> {
	static R Dispatch(int index, P* param) { return R(); }
};

template<class T, int begin_pos, int end_pos, class R, class P> struct DispatchEngine<T, begin_pos, end_pos, true, R, P>
{
	static R Dispatch(int index, P* param) {

		const int middle_pos = (begin_pos + end_pos) >> 1;
		if (TypeAtTypeList<T, middle_pos>::Result::yatl_index == index) {
			return TypeAtTypeList<T, middle_pos>::Result::Run(param);
		}
		else if (TypeAtTypeList<T, middle_pos>::Result::yatl_index < index) {
			const bool cmp = middle_pos + 1 <= end_pos;
			return DispatchEngine<T, middle_pos + 1, end_pos, cmp, R, P>::Dispatch(index, param);
		}
		else {
			const bool cmp = begin_pos <= middle_pos - 1;
			return DispatchEngine<T, begin_pos, middle_pos - 1, cmp, R, P>::Dispatch(index, param);
		}

		return R();
	}
};

template<class T> struct TypleListIsAscending {};

template<class T> struct TypleListIsAscending<TypeList<T, NullType>> {};

template<class T, class U> struct TypleListIsAscending<TypeList<T, U>> {
	TypleListIsAscending() {
		static_assert(T::yatl_index < U::Head::yatl_index, "yatl assert : is not a ascending type list");
	}
};

};

#define YATL_TYPELIST(...) yatl::MakeTypeList<__VA_ARGS__>::Result
#define YATL_TUPLE(...) yatl::Tuple<YATL_TYPELIST(__VA_ARGS__)>
#define YATL_DEF_TUPLE(obj, ...) YATL_TUPLE(__VA_ARGS__) obj
#define YATL_TUPLE_CONSTRUCTOR(type, obj) (yatl::TupleConstructorHelper<type>(obj))
#define YATL_MAKE_TUPLE(obj, ...) \
	YATL_DEF_TUPLE(obj, __VA_ARGS__);\
	YATL_TUPLE_CONSTRUCTOR(YATL_TYPELIST(__VA_ARGS__), obj)


#define DefineHasType(t, m) namespace yatl {	\
	template<typename T> r1 has_type_##t##_##m(typename const T::m *);	\
	template<typename T> r2 has_type_##t##_##m(...);	\
	bool t##HasType##m() {return sizeof(has_type_##t##_##m<t>(0)) == sizeof(r1);} \
}

#define IsAscendingTypeList(type)	TypleListIsAscending<type>()

#define DeclareHasType(t, m) bool yatl::t##HasType##m()

#define DISPATCH_ITEM_DECL(index, return_type, param_type)	\
	public:	\
	enum {	yatl_index = index	};	\
	static return_type Run(param_type * param);

#define DISPATCH_ITEM_DEF(index, return_type, param_type)	\
	public:	\
	enum {	yatl_index = index	};	\
	static return_type Run(param_type * param)

#define DISPATCH_ITEM_DEF_IMPL(base, return_type, param_type)	\
	static return_type base::Run(param_type * param)

#endif

