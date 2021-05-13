# Function handling

C++에서는 함수형 프로그래밍을 지원하기 위해 다양한 함수 처리 문법을 제공한다.

### Example

``` c++
int test(const int arg1, const int arg2)
{
	return 0;
}

int test2(const auto arg1, const auto arg2)
{
	return (int(arg1) + int(arg2));
}

// 위 test2 함수는 아래와 완전 동일하다.
template <typename $Type1, typename $Type2>
int test3(const $Type1 arg1, const $Type2 arg2)
{
	return (int(arg1) + int(arg2));
}

class TestClass
{
public:
	int testFunc_version1(int, int) {return 0;}
	int testFunc_version2(int, int) {return 1;}
};

int main()
{
	/*
		Function handling

		추가 과제: 함수형 프로그래밍에 대해 "심도 있는" 조사를 하여라.
		C++17 버전 이후 C++은 함수형 프로그래밍을 적극 지원하고 있다.
	*/

	/*
		전통적으로 C/C++ 에서 함수의 이름은 함수 자신의 주소를 나타낸다.
		함수 포인터를 받기 위한 변수는 다음과 같이 선언한다.

		ReturnType(*variableName)(ParamType1, ParamType2, ...)
	*/
	int(*funcVal1)(int, int) = test;

	/*
		파라미터 타입에 대한 정보를 명시적으로 알리기 위해
		다음과 같이 작성할 수도 있다.
	*/
	int(*funcVal2)(int arg1, int arg2) = test;

	/*
		함수 포인터 타입을 미리 정의하고자 하는 경우
		다음과 같은 방법으로 정의한다.

		ReturnType(*)(ParamType1, ParamType2, ...)
	*/
	using FuncPtrType = int(*)(int, int);
	FuncPtrType funcVal3 = test;

	/*
		그렇다면 함수 "포인터"가 아닌, 함수 자체를 의미하는
		자료형은 어떻게 선언할 수 있을까? 정답은 간단하다.
		중간의 (*)를 제외해주면 된다.
	*/
	using FuncType = int(int, int);

	/*
		이렇게 선언한 FuncType은 함수 자체를 의미하므로,
		함수 포인터를 받기 위해선 FuncType의 포인터로 선언해야 한다.
	*/
	FuncType *const funcVal4 = test;

	/*
		함수 자체를 의미하는 자료형은 기존의 C에는 존재하지 않는 것이다.
		이러한 자료형이 생겼다는 것은 함수도 하나의 "객체"로 존재함을 의미한다.
		함수를 객체로 처리하는 것은 함수형 프로그래밍의 기본 개념이라 할 수 있다.

		함수를 객체로 바라본다면, 그 인스턴스는 함수를 선언하는 순간 유일하게 1개씩 생긴다고
		생각할 수 있다. 이는 마치 변수를 선언하는 것과 유사하다.
		
		전통적으로 함수가 선언과 정의로 나뉘는 것을 생각해보면 선언부를 표현하는 코드는
		다음과 같이 작성할 수도 있다.
	*/
	FuncType test;

	/*
		당연한 이야기지만 함수 구현이 되어있지 않다면 아래 코드는 링킹 오류가 발생한다.
		상단의 test 함수 구현부를 주석처리하고 빌드하여 링킹에러가 발생하는 것을 확인하여라.
	*/
	test(1, 2);

	// 위 코드는 전통적 함수 선언방법인 다음 코드와 완전히 동일한 코드이다.
	int test(int, int);

	/*
		변수 선언 시 명시적 타입 대신 auto를 사용하면 템플릿 함수화 되어
		임의의 타입을 받을 수 있다. test2 함수는 test3과 완전 동일한 코드를 생성한다.
	*/
	const int resultVal1 = test2(1, 2);			// int, int
	const int resultVal2 = test2(3.f, 4.f);		// float, float
	const int resultVal3 = test2(5, 6.f);		// int, float
	const int resultVal4 = test2(7.f, 8);		// float, int

	/*
		C++에서는 함수 객체를 만들기 위해 람다식을 제공한다.
		람다식은 기존의 함수와 거의 동일하나, 임의의 위치에서 즉시 구현이 가능하며
		함수 스코프 외부의 데이터도 접근이 가능하다는 장점이 있다.

		기본적인 람다식 선언법은 다음과 같다.

		[변수 캡처 목록](파라미터 목록) -> 반환 타입
		{
			구현부
		};
	*/
	
	// 람다식은 함수와 자료형을 공유한다.
	FuncPtrType lambda1 = [](const int arg1, const int arg2) -> int
	{
		return 1;
	};

	// 람다식 구현부에 의해 반환 타입이 추론 가능한 경우 반환 타입을 auto로 대체할 수 있다.
	FuncPtrType lambda2 = [](const int arg1, const int arg2) -> auto
	{
		return 2;
	};

	// 더 나아가, 반환 타입이 추론 가능한 경우 이를 명시적으로 기재하지 않아도 된다.
	FuncPtrType lambda3 = [](const int arg1, const int arg2)
	{
		return 3;
	};

	/*
		변수 캡처 목록에 변수를 추가하는 경우 람다식 내부에서 외부의 변수를
		사용할 수 있다. 캡처 목록에 변수를 사용하는 경우 람다식은 기존의 함수와
		호환되지 않는 독자적인 타입을 가지게 된다.
	*/
	const int intVal1 = 0;

	/*
		FuncPtrType과 반환타입 및 파라미터 타입이 동일하지만,
		캡처 목록을 사용하였기 때문에 기존 함수와 호환이 불가능하다.

		캡처 목록에 값이 존재하는 람다식의 경우 독자적인 람다식 타입을
		가지므로 변수를 받을 때엔 타입을 auto로 선언하여야 한다.

		람다식 변수를 선언할 수 있는 독자적 타입은 없다. 캡처 목록을
		사용하는 경우에는 항상 auto만 사용이 가능하다.
	*/
	// FuncPtrType lambda4 = [intVal1](const int arg1, const int arg2)
	const auto lambda4 = [intVal1](const int arg1, const int arg2) -> int
	{
		// 람다식 외부 스코프의 변수 사용 가능
		return intVal1;
	};

	/*
		캡처되는 변수는 람다식에서 사용될 때 그 값이 복사되어 들어가게 된다.
		객체의 경우 복사 생성자 호출을 통해 객체를 복사한다.

		만약 캡처 변수를 복사하고 싶지 않다면 변수 앞에 참조 기호(&)를 붙여
		참조 방식으로 변수를 캡처함을 명시적으로 알린다.
	*/
	const auto lambda5 = [&intVal1](const int arg1, const int arg2) -> int
	{
		return intVal1;
	};

	const int intVal2 = 1;
	const int intVal3 = 2;
	const int intVal4 = 3;
	const int intVal5 = 4;

	/*
		캡처 목록에는 여러 개의 변수를 선언할 수 있다.
		각 변수 앞에 &를 붙이거나 붙이지 않음으로써 선택적으로 복사 캡처/참조 캡처를
		수행할 수 있다.
	*/
	const auto lambda6 = [intVal1, &intVal2, intVal3, &intVal4, intVal5](const int arg1, const int arg2)
	{
		/*
			intVal1, intVal3, intVal5는 외부의 변수로부터 그 값이 복사된
			새로운 변수이다.

			intVal2, intVal4는 외부의 변수 그 자체를 참조한다.
		*/
		return (intVal1 + intVal2 + intVal3 + intVal4 + intVal5);
	};

	/*
		외부의 모든 변수를 일괄적으로 복사 방식으로 캡처하고자 한다면
		다음과 같이 = 기호를 캡처 목록에 넣는다.
	*/
	const auto lambda7 = [=](const int arg1, const int arg2)
	{
		// 외부의 모든 변수를 복사 캡처 방식으로 사용할 수 있다.
		return (intVal1 + intVal2 + intVal3 + intVal4 + intVal5);
	};

	/*
		모든 변수를 기본적으로 복사 방식으로 캡처하지만,
		선택적으로 일부를 참조 방식으로 캡처하고자 한다면
		= 기호 뒤에 변수를 &기호와 함께 추가 선언한다.
	*/
	const auto lambda8 = [=, &intVal4, &intVal5](const int arg1, const int arg2)
	{
		// intVal1, intVal2, intVal3은 복사되었고, intVal4, intVal5는 참조되었다.
		return (intVal1 + intVal2 + intVal3 + intVal4 + intVal5);
	};

	/*
		외부의 모든 변수를 일괄적으로 참조 방식으로 캡처하고자 한다면
		다음과 같이 & 기호를 캡처 목록에 넣는다.
	*/
	const auto lambda9 = [&](const int arg1, const int arg2)
	{
		/*
			외부의 모든 변수를 참조 캡처 방식으로 사용할 수 있다.
			당연한 이야기지만 성능은 참조 방식이 더욱 좋다.
			하지만 만약 멀티 스레드 환경에서 람다식이 호출되는 타이밍에
			람다식이 캡처한 변수가 존재하지 않는다면 잘못된 메모리 참조로
			프로그램이 죽는 문제가 있을 수 있다. 이는 개발자가 판단하여
			상황에 따라 복사 캡처 / 참조 캡처를 적절히 사용하여야 한다.
		*/
		return (intVal1 + intVal3 +  intVal5 + arg1 + arg2);
	};

	// 기본 참조 캡처, 일부 복사 캡처
	const auto lambda10 = [&, intVal3, intVal5](const int arg1, const int arg2)
	{
		/*
			외부의 모든 변수를 참조 캡처 방식으로 사용할 수 있다.
			당연한 이야기지만 성능은 참조 방식이 더욱 좋다.
			하지만 만약 멀티 스레드 환경에서 람다식이 호출되는 타이밍에
			람다식이 캡처한 변수가 존재하지 않는다면 잘못된 메모리 참조로
			프로그램이 죽는 문제가 있을 수 있다. 이는 개발자가 판단하여
			상황에 따라 복사 캡처 / 참조 캡처를 적절히 사용하여야 한다.
		*/
		return (intVal1 + intVal3 + intVal5 + arg1 + arg2);
	};

	// 함수와 유사하게, auto 키워드를 사용하여 템플릿 함수화 할 수 있다.
	const auto lambda11 = [](const auto arg1, const auto arg2)
	{
		return (int(arg1) + int(arg2));
	};

	const int resultVal5 = lambda11(1, 2);
	const int resultVal6 = lambda11(3.f, 4);

	/*
		물론 다음과 같이 템플릿을 사용할 수도 있다.
		람다식에서 템플릿을 사용하고자 하는 경우 캡처 목록과 파라미터 선언부 사이에
		template 키워드를 제외하고 입력한다.
	*/
	const auto lambda12 = []<typename $Type1, typename $Type2>(const $Type1 arg1, const $Type2 arg2)
	{
		return (int(arg1) + int(arg2));
	};

	const int resultVal7 = lambda12(5.f, 6);
	const int resultVal8 = lambda12(7.f, 8.f);

	/*
		멤버 함수 포인터는 기존의 함수 포인터 선언법에서 *표 좌측에
		"클래스::" 를 붙여줌으로써 선언할 수 있다.
		멤버 함수 포인터는 해당 클래스 내에 구현되어 있고 리턴 타입 및
		파라미터 타입이 일치하는 멤버 함수의 포인터를 저장할 수 있는
		멤버 변수이다.

		기존 함수와 달리 &연산자를 붙여주어야 하고,
		멤버 함수 좌측에 "클래스::" 를 붙여주어야 한다.
	*/
	int(TestClass::*pMemberFunc)(int, int) = &TestClass::testFunc_version1;
	pMemberFunc = &TestClass::testFunc_version2;

	TestClass classInstance;
	TestClass *const pClassInstance = &classInstance;

	/*
		멤버 함수 포인터에 저장된 함수를 호출하려면 다음과 같이 작성한다.
		먼저 멤버 함수 포인터를 *연산자를 통해 함수의 참조를 얻어온 뒤
		해당 함수를 호출하게 할 인스턴스와 . 연산자를 통해 연결한다.
		다음 그 전체를 괄호로 감싸고, 우측편에 인자 목록을 나열하여
		멤버 함수를 호출한다.
	*/
	const int resultVal9 = (classInstance.*pMemberFunc)(1, 2);

	// 인스턴스가 포인터 타입인 경우 다음과 같이 사용한다.
	const int resultVal10 = (pClassInstance->*pMemberFunc)(1, 2);

	/*
		함수에 대한 고급 문법인 함수 템플릿, std::function()에 대한 내용은
		다음 시간에 이어 설명하도록 한다.
	*/

	return 0;
}
```
