﻿#include <iostream>

using namespace std;

int varMain();
int staticCalculatorMain(); 
int functionHandlingMain(); 

int main() 
{
	int (*fp[])() = 
	{ 
		varMain, 
		staticCalculatorMain, 
		functionHandlingMain
	};

	return fp[2](); 
}

// --------------------------- Var

#include "../Var/Var.h"

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

int varMain()
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

	return 0; 
}

// --------------------------- StaticCalculator

#include "../StaticCalculator/Number.h"
#include "../StaticCalculator/StaticCalculator.h"

template <typename T>
static constexpr T getNumberValue(const Number<T>& src)
{
	return src.getValue();
}

int staticCalculatorMain() 
{
	/*
		컴파일 타임에 동작이 모두 결정되는 static calculator를 구현하여라.
		아래의 코드가 정상 동작하도록 로직을 구현하여라.
	*/

	/*
		템플릿 파라미터로 숫자 타입만 입력받을 수 있는
		Number 클래스를 구현하여라. 생성자로는 value를 하나 입력받을 수 있다.
		생성자는 constexpr 생성자로 만들으시오.

		참고: static_assert를 클래스 선언부에 직접 입력 시 컴파일 타임에
		타입 파라미터를 체크할 수 있다.
		예)
		class Test
		{
			static_assert(false, "false!");
		};

		static_assert에 대해 조사하고 글을 정리하여라.
	*/
	constexpr Number<float> number1{ 5.f };

	/*
		Number 타입을 입력받아 내부의 value를 반환하는 getNumberValue()
		함수를 구현하여라. getNumberValue() 함수는 constexpr 함수로 구현한다.
		Number 클래스에서 값을 제공하기 위해 getValue() 멤버 함수를 구현한다.
	*/
	constexpr float val1 = getNumberValue<float>(number1);

	constexpr Number<float> number2{ 10.f };
	constexpr float val2 = getNumberValue(number2);

	/*
		컴파일 타임에 두 숫자를 입력받아 연산을 수행하는 StaticCalculator 클래스를
		구현하여라. 이 클래스는 인스턴스를 생성할 수 없어야 하며, calc static 함수를
		통해 계산 결과 값을 반환한다.

		템플릿 파라미터는 차례로 <number 타입, lhs, rhs, 연산 타입> 이다.
		연산 타입은 PLUS, MINUS, PRODUCT, DIVIDE 네 가지를 제공하여야 한다.
		연산 타입은 constexpr 분기문을 통해 조사하시오.

		calcResult1 위에 마우스를 올려 15.0f라는 값이 미리보기로 출력되는지 확인하여라.
	*/
	constexpr float calcResult1 =
		StaticCalculator<float, val1, val2, OperationType::PLUS>::calc();

	// 15 출력
	cout << "calcResult1:" << calcResult1 << endl;

	constexpr Number<int> number3{ 70 };
	constexpr Number<int> number4{ 10 };

	constexpr int calcResult2 =
		StaticCalculator<int, number3.getValue(), number4.getValue(), OperationType::DIVIDE>::calc();

	// 7 출력
	cout << "calcResult2:" << calcResult2 << endl;

	// 크기 7인 배열 생성
	int arr[calcResult2]{};

	return 0;
}

// --------------------------- FunctionHandling

#include "../FunctionHandling/Lurker.h"
#include "../FunctionHandling/Tank.h"

int functionHandlingMain()
{
	Lurker lurker{ 225 };
	Tank tank{ 175 };

	static constexpr auto attackEachOther = [](Unit& lurker, Unit& tank)
	{
		lurker.attack(tank); 
		tank.attack(lurker); 
	};

	attackEachOther(lurker, tank);
	cout << "공격 1회" << endl;
	cout << "Lurker: " << lurker << endl;
	cout << "Tank: " << tank << endl << endl;

	attackEachOther(lurker, tank);
	cout << "공격 2회" << endl;
	cout << "Lurker: " << lurker << endl;
	cout << "Tank: " << tank << endl << endl;

	lurker.burrow(true);
	tank.attack(lurker);
	cout << "공격 3회" << endl;
	cout << "Lurker: " << lurker << endl;
	cout << "Tank: " << tank << endl << endl;

	attackEachOther(lurker, tank);
	cout << "공격 4회" << endl;
	cout << "Lurker: " << lurker << endl;
	cout << "Tank: " << tank << endl << endl;

	lurker.attack(tank);
	tank.setSeigeMode(true);
	cout << "공격 5회" << endl;
	cout << "Lurker: " << lurker << endl;
	cout << "Tank: " << tank << endl << endl;

	attackEachOther(lurker, tank);
	cout << "공격 6회" << endl;
	cout << "Lurker: " << lurker << endl;
	cout << "Tank: " << tank << endl << endl;

	attackEachOther(lurker, tank);
	cout << "공격 7회" << endl;
	cout << "Lurker: " << lurker << endl;
	cout << "Tank: " << tank << endl << endl;

	if (lurker.isAlive() && !tank.isAlive())
		cout << "Lurker 승" << endl;

	else if (!lurker.isAlive() && tank.isAlive())
		cout << "Tank 승" << endl;

	else
		cout << "무승부" << endl;

	return 0;
}
