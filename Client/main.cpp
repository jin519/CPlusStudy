#include <iostream>

// Var 프로젝트의 Var.h 참조
#include "../Var/Var.h"

using namespace std;

struct TestStruct
{
	int a{};
	double b{};
	const char* const str{};

	constexpr TestStruct() noexcept = default;
	constexpr TestStruct(const int a, const double b, const char* const str) noexcept :
		a{ a }, b{ b }, str{ str }
	{}

	TestStruct(const TestStruct& source) :
		a{ source.a }, b{ source.b }, str{ source.str }
	{
		cout << "TestStruct(const TestStruct &source) 호출" << endl;
	}

	friend ostream& operator<<(ostream& o, const TestStruct& testStruct)
	{
		o << '[' << testStruct.a << ", " << testStruct.b << ", " << testStruct.str << ']';
		return o;
	}
};

int main()
{
	/*
		모든 변수를 담을 수 있는 Var 클래스를 구현하여라.
		아래의 코드가 정상적으로 동작할 수 있도록 Var를 구현하여라.

		클래스는 가상테이블 및 생성/소멸자 처리를 구현해야 하므로 처리하지 않는다.
		기본타입 자료구조 및 구조체에 대한 처리만 구현하여라.

		값의 이동, 즉 rvalue 데이터에 대한 처리는 다루지 않는다.
		모든 대입 or 초기화는 데이터 복사를 기반으로 수행하여라.

		본 문제 풀이시 memcpy, memmove와 같은 메모리 조작 함수를 사용하지 말 것.

		[키워드]
		typeid, type_info:
		runtime에 타입 체킹이 가능한 정보 (RTTI; RunTime Type Information)

		placement new:
		별도의 메모리 placeholder를 미리 확보 후 해당 영역에 메모리를 재생성.
	*/
	// 빈 var 변수 생성
	Var var1;

	// int 값을 대입
	var1 = 1;

	try
	{
		// var1에 설정한 타입인 int로 캐스팅하여 값을 얻어옴
		cout << var1.get<int>() << endl;

		// var1에 설정한 타입이 아닌 float로 캐스팅. exception이 발생되어야 한다.
		cout << var1.get<float>() << endl;
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	// float 값으로 재설정
	var1 = 10.234f;

	// 이제 exception이 발생하지 않음
	cout << var1.get<float>() << endl;

	const TestStruct testStruct{ 10, 200., "this is test" };

	// TestStruct 데이터를 Var 생성과 동시에 삽입
	const Var var{ testStruct };

	// TestStruct 출력
	cout << var.get<TestStruct>() << endl;

	// Var 객체 소멸 시 내부 메모리 릴리즈 필요.
}