// yatl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "typelist.h"
#include "smarthandle.h"
#include "singleton.h"

using namespace yatl;

int _tmain(int argc, _TCHAR* argv[])
{
	
	return 0;
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
	PRINT_TYPELIST(Reverse<TestType>::Result);

	TypeAtTypeList<TestType, 1>::Result d = 0x41;
	std::cout << d << std::endl;

	std::cout << IndexOfTypeList<TestType, char>::Value << std::endl;

	typedef AppendTypeList<TestType, double>::Result TestType2;
	PRINT_TYPELIST(TestType2);

	typedef AppendTypeList<TestType2, TestType>::Result TestType3;
	PRINT_TYPELIST(TestType3);

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