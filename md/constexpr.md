# constexpr specifier

constexpr은 컴파일 타임에 동작을 결정짓는 모던 c++ 패러다임에서 중요한 역할을 하는 키워드이다. <br>
constexpr 키워드가 붙는 변수, 함수, 로직 등은 모두 `컴파일 타임에 값이 결정`되어 성능 향상에 큰 기여를 한다.

### Example

``` c++
template <int $val>
class TestClass
{
public:
	// 일반적으로 static 멤버 변수는 cpp 파일에서 초기화가 이루어지며, 이때 instance가 만들어진다.
	// 선언과 동시에 초기화하기 위해서는 다음을 참고한다. static inline int VALUE = $val; 
	// constexpr은 암묵적으로 inline 의미를 포함한다.
	static constexpr int VALUE = $val;
};

constexpr int constexprFunc(const int val)
{
	int retVal = 0;

	for (int i = 0; i < val; i++)
		retVal++;

	return retVal;
}

int nonConstexprFunc(const int val)
{
	int retVal = 0;

	for (int i = 0; i < val; i++)
		retVal++;

	return retVal;
}

constexpr int testFunc(const int testVal)
{
	if (testVal >= 0)
		return constexprFunc(testVal);
	else
		return nonConstexprFunc(testVal);
}

constexpr const int& testFunc2(const int& ref)
{
	return ref;
}

int main()
{
	/*
		1. constexpr 변수
		constexpr 변수는 직관적으로 "변수화된 리터럴" 이라고 생각하면 된다.
		전통적인 C/C++ 환경에서는 컴파일 타임에 결정되는 변수를 구현하기 위해 #define 구문으로 상수를 선언하곤
		하였다. 그러나 이는 심볼->리터럴로의 단순 대입 기능만 제공하기 때문에 타입 안정성을 제공하지 않는다.

		기본적으로 constexpr 변수를 선언하는 방법은 다음과 같다.
	*/
	constexpr int val1 = 5;

	/*
		위 constexpr 변수는 컴파일 타임에 값이 결정되는 리터럴과 동일하게 취급된다.
		visual studio 환경에서 마우스를 변수 위에 올려보면 val1 = 5 라는 값이 확정되어 출력되는 것을 볼 수 있다.
		
		constexpr 변수는 호환 가능한 constexpr 변수 or 리터럴과 연산이 가능하게 된다.
	*/
	constexpr int val2 = 2;

	// 아래의 product에 마우스를 올려보면 10이라는 값이 미리 계산되어 있는 것을 알 수 있다.
	constexpr int product = (val1 * val2);
	
	// constexpr 변수를 이용하면 컴파일 타임에 크기를 결정하여야 하는 배열도 초기화 할 수 있다.
	int intArr1[product] {};

	/*
		템플릿 파라미터의 인자로도 제공할 수 있다.
		아래의 변수 또한 10이라는 값이 컴파일 타임에 결정되는 것을 알 수 있다.
	*/
	constexpr int templateVal1 = TestClass<product>::VALUE;

	/*
		2. constexpr 함수
		constexpr 함수는 컴파일 타임에 동작이 결정되는 함수이다.
		함수 호출에 의한 스택 프레임이 별도로 생기지 않으며 inline 함수와 유사하게 컴파일 시
		함수 구현부가 함수 호출 위치에 직접 대입된다. 그러나 inline 함수는 구현부의 단순 대치인 것에 반해
		constexpr 함수는 동작 자체를 모두 계산하여 그 결과를 반환한다. void 함수라면 동작 결정 과정만 수행한다.

		당연한 듯 하지만 constexpr 함수에 의해 반환되는 값은 constexpr 변수에 대입이 가능하다.
	*/
	constexpr int val3 = constexprFunc(4);

	// 유사하게 배열, 템플릿 파라미터 등에도 직접 대입이 가능하다.
	int intArr2[constexprFunc(4)] {};
	constexpr int templateVal2 = TestClass<constexprFunc(4)>::VALUE;

	/*
		constexpr 함수 내부의 구현은 기본적으로 비 constexpr 함수만 호출하지 않으면 된다.
		for, while, if 등의 반복 및 분기문도 사용이 가능하다. 컴파일 타임에 그 결과를 계산할 수 있는 로직이면 되기 때문이다.
		constexprFunc() 함수의 구현부 또한 for 문을 사용하였다.
	*/

	/*
		그러나 상단의 testFunc() 함수를 보면 constexpr 함수로 선언되어 있음에도 불구하고 비 constexpr 함수인
		nonConstexprFunc() 함수를 호출하는 것을 확인할 수 있다.
		이것은 if 구문에 의해 if (true)인 구문만 활성화되고 else 구문은 컴파일 타임에 제거되기 때문이다.
		만약 testunc() 함수의 인자로 0보다 작은 값을 입력하면 testFunc() 함수의 constexpr 특성은 암묵적으로 사라지게 된다.

		아래 testFunc() 함수의 인자를 양수/음수로 변경해보고, 음수 값 입력시에만 컴파일 에러가 발생하는 것을 확인하여라.
	*/
	constexpr int val4 = testFunc(-1);

	/*
		물론 컴파일 타임에 동작이 결정되어야 하므로 인자 또한 constexpr 특성을 가진 (값의 특정이 가능한)
		인자를 넣어주어야 한다. constexpr 이 아닌 변수를 입력 시 위의 경우와 같이
		함수에서 암묵적으로 constexpr 특성이 제거된다.
	*/
	int val5 = 0;
	constexpr int val6 = testFunc(val5);

	/*
		value가 아닌 pointer나 reference를 넘겨주는 구문은 컴파일 타임에 결정이 가능하므로,
		val5와 같이 비 constexpr 변수도 컴파일 타임에 reference는 사용이 가능하다.
	*/
	const int &val5Ref = testFunc2(val5);

	/*
		3. constexpr 멤버 함수
		constexpr 함수는 클래스의 생성자 및 멤버 함수에서도 동일하게 적용 가능하다.
		참고로 생성자 또한 함수이다.
	*/
	class TestClass2
	{
	public:
		/*
			constexpr 함수와 동일한 특성을 지니고 있다.
			컴파일 타임에 멤버 변수 __value를 입력 값으로 초기화 할 수 있다.
			TestClass2 인스턴스를 constexpr 변수로 만드려면 반드시 constexpr 생성자가 있어야 하며,
			인자 또한 constexpr 변수 혹은 리터럴이어야 한다.
		*/
		constexpr TestClass2(const int value) :
			__value { value }
		{}

		constexpr int getValue() const
		{
			return __value;
		}

	private:
		// class instance 자체는 constexpr에 대한 표현을 하지 않는다.
		// 멤버 변수에 대한 constexpr 특성을 부여하는 것은
		// 외부에서 현재 class 인스턴스를 constexpr로 선언하는 문장이다.
		int __value;
	};

	// TestClass2::__value는 constexpr화 되었다.
	constexpr TestClass2 testClassVal1 { val1 };
	constexpr int val7 = testClassVal1.getValue();

	// TestClass2::__value는 비 constexpr화 되었다.
	TestClass2 testClassVal2 { val1 };
	constexpr int val8 = testClassVal2.getValue();

	/*
		constexpr 생성자 및 멤버 함수가 있더라도 비 constexpr 인스턴스를 생성하면
		constexpr 특성을 잃어버리게 된다. 즉 컴파일 타임에 결정 가능한 값을 제공하지 못한다.
		하지만 constexpr 함수는 이러한 경우에도 충분히 유용하다.
		constexpr 함수는 컴파일 타임에 값을 결정하는 역할도 하지만, 내부 로직을 결정하는 작업도
		수행하기 때문에 inline 함수의 기능도 제공하기 때문이다.
		따라서 가능하다면 최대한 constexpr 함수를 많이 제공하는 것이 성능면에서 유리하다.
	*/

	/*
		4. constexpr 분기문
		만약 분기의 조건문이 컴파일 타임에 결정이 가능하다면, 분기를 컴파일 타임에 결정할 수 있다.
		true나 false인 값이 응용 시작 시 단 1회만 초기화 되고 다시 변하지 않는다면, 그리고 그 값이
		분기문에서 사용된다면 의미없는 분기가 반복되는 상황을 제거할 수 있어 성능에 유리하다.
	*/

	if constexpr (val7 > 0)
	{
		// 이곳의 분기는 항상 활성화 됨. 마치 분기가 없는 것처럼.
		int a = 0;
	}
	else
	{
		// 이곳의 분기는 코드조차 생성되지 않음.
		int a = 1;
	}

	return 0;
}
```
