// yatl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "typelist.h"
#include "smarthandle.h"
#include "singleton.h"
#include "factory.h"

using namespace yatl;

class A1 {
public:
	A1() {printf("A1\n");}
	enum {
		yatl_index = 1
	};
};

class A2 {
public:
	A2() {printf("A2\n");}
	enum {
		yatl_index = 2
	};
};

class A3 {
public:
	A3() {printf("A3\n");}
	enum {
		yatl_index = 3
	};
};

class A4 {
public:
	A4() {printf("A4\n");}
	enum {
		yatl_index = 4
	};
};

class A5 {
public:
	A5() {printf("A5\n");}
	enum {
		yatl_index = 5
	};
};

class A6 {
public:
	A6() {printf("A6\n");}
	enum {
		yatl_index = 6
	};
};

class A7 {
public:
	A7() {printf("A7\n");}
	enum {
		yatl_index = 7
	};
};

template<class T, int begin_pos, int end_pos, bool valid> struct DoDispatch;

template<class T, int begin_pos, int end_pos> struct DoDispatch<T, begin_pos, end_pos, false> {
	DoDispatch(T &t, int index) {}
};


template<class T, int begin_pos, int end_pos> struct DoDispatch<T, begin_pos, end_pos, true>
{
	DoDispatch(T &t, int index) {
		
		const int middle_pos = (begin_pos + end_pos) >> 1;
		if (TypeAtTypeList<T, middle_pos>::Result::yatl_index == index) {
			TypeAtTypeList<T, middle_pos>::Result();
		}
		else if (TypeAtTypeList<T, middle_pos>::Result::yatl_index < index) {
			const bool cmp = middle_pos + 1 <= end_pos;
			DoDispatch<T, middle_pos + 1, end_pos, cmp>(t, index);
		}
		else {
			const bool cmp = begin_pos <= middle_pos - 1;
			DoDispatch<T, begin_pos, middle_pos - 1, cmp>(t, index);
		}
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	typedef YATL_TYPELIST(A5, A2, A3, A4, A1, A7, A6) TestType;
	typedef SortTypeList<TestType>::Result ttt;
	// PRINT_TYPELIST(ttt);

	DoDispatch<ttt, 0, TypeListLength<ttt>::Value - 1, true>(ttt(), 5);

	return 0;
}

void FactoryTest()
{
	typedef YATL_TYPELIST(int, unsigned int, char) TestType;
	Tuple<TestType> obj;
	(TupleConstructorHelper<TestType>(obj))(1)(-1)(0x41);
	FactoryHolder<TestType, CloneCreaterPolicy> TestFactory(obj);

	char *p = TestFactory.Create<char>();
	delete p;

}

void TypeListMacroTest()
{
	typedef YATL_TYPELIST(int, long, unsigned int, char, HANDLE, HWND) TestType;
	std::cout << IndexOfTypeList<TestType, char>::Value << std::endl;
	TypeAtTypeList<TestType, 3>::Result d = 0x41;
	std::cout << d << std::endl;
}

void TypeListTest()
{
	typedef TypeList<int, TypeList<char, TypeList<unsigned long, NullType>>> TestType;
	PRINT_TYPELIST(TestType);
	PRINT_TYPELIST(ReverseTypeList<TestType>::Result);

	TypeAtTypeList<TestType, 1>::Result d = 0x41;
	std::cout << d << std::endl;

	std::cout << IndexOfTypeList<TestType, char>::Value << std::endl;

	typedef AppendTypeList<TestType, double>::Result TestType2;
	PRINT_TYPELIST(TestType2);

	typedef AppendTypeList<TestType2, TestType>::Result TestType3;
	PRINT_TYPELIST(TestType3);

	std::cout << IsAllUniqueTypeList<TestType>::Value << std::endl;
	std::cout << IsAllUniqueTypeList<TestType3>::Value << std::endl;

	typedef EraseTypeList<TestType3, unsigned long>::Result TestType4;
	PRINT_TYPELIST(TestType4);

	typedef EraseAllTypeList<TestType4, char>::Result TestType5;
	PRINT_TYPELIST(TestType5);

	typedef UniqueTypeList<TestType3>::Result TestType6;
	PRINT_TYPELIST(TestType6);

	typedef ReplaceTypeList<TestType, char, int>::Result TestType7;
	TypeAtTypeList<TestType7, 1>::Result w = 0x41;
	std::cout << w << std::endl;
	PRINT_TYPELIST(TestType7);

	typedef ReplaceAllTypeList<TestType3, char, int>::Result TestType8;
	typedef EraseAllTypeList<TestType8, int>::Result TestType9;
	PRINT_TYPELIST(TestType8);
	PRINT_TYPELIST(TestType9);

}

void TupleTest()
{
	typedef TypeList<int, TypeList<char, TypeList<unsigned long, NullType>>> TestType;
	Tuple<TestType> TestValue1;
	get<1>(TestValue1) = 100;
	std::cout << get<1>(TestValue1) << std::endl;

	YATL_MAKE_TUPLE(TupleTest, int, char, unsigned long)(11)(0x41)(-1);
	YATL_DEF_TUPLE(TupleTest1, int, char, unsigned long)(TupleTest);

	YATL_DEF_TUPLE(TupleTest2, int, char, unsigned long);
	TupleTest2 = TupleTest1;

	YATL_DEF_TUPLE(TupleTest3, int, char, unsigned long)(std::move(TupleTest2));
	YATL_DEF_TUPLE(TupleTest4, int, char, unsigned long);

	TupleTest4 = std::move(TupleTest3);
}

void SingletonTest()
{
	class PrintTest {
	public:
		void Print() { std::cout << "hehe" << std::endl; }

	private:
		PrintTest() {}
		~PrintTest() {}

		friend struct SingleNewCreatorPolicy<PrintTest>;
	};

	SingletonHolder<PrintTest, SingleNewCreatorPolicy>::Instance().Print();

	SingletonHolder<PrintTest, SingleNewCreatorPolicy>::DestoryInstance();
}