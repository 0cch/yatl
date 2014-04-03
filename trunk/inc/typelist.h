#ifndef __YATL_TYPE_LIST_H__
#define __YATL_TYPE_LIST_H__

#include <iostream>

namespace yatl {

struct NullType;

struct EmptyType {};

template<class T, class U> struct TypeList {
	typedef T Head;
	typedef U Tail;
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
	typedef EmptyType Result;
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
// ReverseTo
//
template<class T, class U> struct ReverseTo;
template<class T> struct ReverseTo<NullType, T> {
	typedef T Result;
};

template<class T, class U, class E> struct ReverseTo<TypeList<T, U>, E> {
	typedef typename ReverseTo<U, TypeList<T, E>>::Result Result;
};

//
// Reverse
//
template<class T> struct Reverse {
	typedef typename ReverseTo<T, NullType>::Result Result;
};

template<unsigned int Index> struct Int2Type {
	enum { Value = Index };
};

template<class T> struct tuple;
template<class T> struct tuple {
	T value_;
};

template<> struct tuple<NullType> {
};

template<class T, class U> struct tuple<TypeList<T, U>> : public tuple<U>{
	T value_;
};

template<class T>
typename T::Head& get_help(tuple<T> &src, Int2Type<0>)
{
	tuple<T> &obj = src;
	return obj.value_;
}

template<unsigned int i, class T>
typename TypeAtTypeList<T, i>::Result& get_help(tuple<T> &src, Int2Type<i>)
{
	tuple<T::Tail> &obj = src;
	return get_help(obj, Int2Type<i - 1>());
}

template<unsigned int i, class T>
typename TypeAtTypeList<T, i>::Result& get(tuple<T> &src)
{
	return get_help(src, Int2Type<i>());
}

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

}

#endif

