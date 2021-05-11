# rvalue reference & forwarding reference

### Example

``` c++
#include <utility>
#include <string>

using namespace std;

class TestClass
{
public:
	TestClass()
	{
		__data = new int[] { 1, 2, 3, 4, 5 };
	}

	~TestClass()
	{
		if (__data)
			delete[] __data;
	}

	// 복사 생성자
	TestClass(const TestClass& source)
	{
		/*
			const lvalue reference는 source를 보존해줘야 한다.
			따라서 deep copy를 수행해야 한다.
		*/

		__data = new int[5];
		memcpy(__data, source.__data, sizeof(int) * 5ULL);
	}

	// 이동 생성자
	TestClass(TestClass &&source) noexcept
	{
		/*
			어짜피 소멸될 rvalue는 훼손되어도 상관 없다.
			따라서 데이터 복사를 하지 않고 포인터만 바꿔치기 한다.
		*/
		std::swap(__data, source.__data);
	}

	TestClass &operator=(const TestClass &source)
	{
		// deep copy
		memcpy(__data, source.__data, sizeof(int) * 5ULL);
		return *this;
	}

	TestClass &operator=(TestClass &&source) noexcept
	{
		/*
			__data의 메모리는 해제하지 않아도 된다.
			__data는 source로 넘어가게 되어 임시값인 source가 파괴될 때 알아서 release 해준다.
		*/
		std::swap(__data, source.__data);
		return *this;
	}

private:
	int *__data = nullptr;
};

string testFunc()
{
	string retVal;
	retVal = "test";

	/*
		함수 내부에서만 사용되고 반환 값으로 쓰일 retVal도
		임시 값이기 때문에 move로 내보내는 것이 바람직 할 것 같다.
		하지만 아니다. 함수의 반환형과 동일한 변수를 return value로 사용하는 경우
		C/C++ 표준에서 제정한 컴파일러 최적화 규칙에 의해 함수 외부에서 결과를
		받는 변수와 동일한 메모리 위치를 사용하게 된다.

		즉 (retVal == 함수 외부에서 결과를 받는 변수) 공식이 성립된다.
		이러한 경우 이동 생성자도 필요 없이 애초에 객체를 1회만 만들면 되므로
		move를 통한 이동 생성자 호출보다 더욱 효율적이라 할 수 있다.
	*/
	// return move(retVal);

	return retVal;
}

template <typename $Type>
remove_cvref_t<$Type> testFunc2($Type &&value)
{
	remove_cvref_t<$Type> retVal;
	retVal = std::forward<$Type>(value);

	return retVal;
}

template <typename $Type>
$Type testFunc3(const $Type &&value)
{
	$Type retVal;
	retVal = value;

	return retVal;
}

int main()
{
	/*
		1. Rvalue reference
		rvalue reference는 C++에서 임시값을 의미하는 rvalue의 reference를 받을 수 있는 기능이다.
	*/

	// 아래와 같은 rvalue도 잠시 메모리가 잡힌다. 그러나 곧 소멸한다.
	5, 2.0f, 'a';

	/*
		위와 같은 상황에서 전통적으로 C++은 rvalue가 소멸되지 않고 계속 참조될 수 있도록
		rvalue를 const reference로 받을 수 있도록 하였다.
	*/
	const int &val1 = 5;
	const float &val2 = 2.0f;
	const char &val3 = 'a';

	/*
		그러나 이러한 처리 방식은 크게 두 가지의 문제점이 있다.
		
		1.
		const reference에 묶여 해당 값은 두번 다시 수정이 불가능하다.
		
		2.
		없어질 인스턴스를 의미하는 rvalue를 const reference로 표현하면 외부에서는 이것이 rvalue인지,
		lvalue인지 모른다. 복사 생성자 혹은 복사 대입연산의 인자로 쓰이는 경우 rvalue 여부와 상관없이
		항상 deep copy를 해주어야 하므로 매우 비효율적이다.

		이러한 문제점을 해결하기 위해 rvalue reference가 도입되었다.
	*/

	// rvalue는 rvalue reference에 묶을 수 있다.
	int &&val4 = 5;

	// 하지만 const lvalue reference는 묶을 수 없다.
	int val5 = 10;
	// int &&val6 = val5; // 에러

	// rvalue reference는 const 한정자가 없으므로 값의 변경이 가능하다.
	val4 += 2;

	/*
		rvalue reference는 임시 값을 표현하기 위해 만들어진 문법이지만,
		rvalue reference가 임시 값을 참조하는 순간 그 임시 값은 사용처가 있으므로
		메모리가 해제되지 않는다.
		다시말해 위의 val4에 대입된 임시값 5의 메모리는 val4가 스코프를 벗어나기 전까지
		해제되지 않는다.

		이 때문에 rvalue reference 변수는 rvalue를 표현하고 있으나 외부에서 lvalue reference로 취급된다.
	*/
	// int&& val7 = val4; // 에러

	/*
		따라서 rvalue reference가 다른 함수의 인자로 들어가거나 대입 연산의 피연산자로 쓰이는 경우,
		rvalue reference 속성을 그대로 전달하고 싶다면 std::move() 함수를 사용하여야 한다.
		move() 함수는 별다른 기능을 하지 않으며, rvalue reference로 강제 캐스팅만 해준다.
	*/
	int&& val8 = move(val4);
	val8 += 2;

	/*
		rvalue reference는 객체를 다룰 때 강력한 힘을 발휘한다.
		만약 rvalue reference 개념이 없었다면 아래와 같은 상황에서도 깊은 복사가 발생했을 것이다.
		하지만 rvalue reference를 통해 임시 객체의 데이터를 새로운 객체 내부로 옮기는 "이동 생성자"를
		구현할 수 있게 되었다.

		이동 생성자는 기존의 복사 생성자와 유사하며, 인자를 TestClass(TestClass &&source) 와 같이
		rvalue reference 형태로 받으면 된다.
	*/
	TestClass testA { TestClass() };

	TestClass testB;

	// 복사 연산자 호출. testA는 훼손되지 않음
	testB = testA;

	/*
		이동 생성자 호출. testA는 rvalue화 되어 testB로 데이터가 이동된다.
		이렇듯 사용자가 lvalue를 명시적으로 rvalue화 한 경우, 해당 인스턴스는
		더이상 사용해선 안된다.
	*/
	testB = move(testA); // 이시점 이후로 testA는 더이상 사용하지 말것.

	/*
		상단의 testFunc() 설명 참고.
	*/
	string testStr { testFunc() };


	/*
		2. Forwarding reference
		
		rvalue와 동일한 표현 방식을 사용한다. (Type &&value 형태)
		하지만 전혀 다른 기능을 제공한다. forwarding reference는 대입받는 변수의 rvalue/lvalue 여부를
		그대로 보존하여 받는다. 즉 lvalue 변수를 대입하면 lvalue reference가 되고, rvalue reference를 대입하면
		rvalue reference가 된다.
	*/

	/*
		forwarding reference는 template을 사용하는 경우에만 제한적으로 활성화된다.
		자세히 얘기하자면 template type parameter를 사용하는 경우, 그리고 그 type parameter를 &&로 받는 변수를
		선언하는 경우 그 변수는 forwarding reference가 된다.

		추가 과제:
		volatile 키워드, std::remove_reference, std::remove_const, std::remove_volatile에 대해 조사할 것.
		그리고 이들의 type alias인 remove_reference_t, remove_cv, remove_cvref_t 등에 대해서도 조사할 것.
	*/

	// testFunc2의 $Type &&value는 TestClass &value가 된다. (함수에 마우스를 올려볼 것)
	TestClass testC;
	TestClass testD = testFunc2(testC);

	// testFunc2의 $Type &&value는 const TestClass &value가 된다.
	const TestClass testE;
	testD = testFunc2(testE);

	// testFunc2의 $Type &&value는 TestClass &&value가 된다.
	TestClass testG;
	testD = testFunc2(move(testG));

	/*
		testFunc3()과 같이 forwarding reference에 const 한정자를 앞에 붙이게 되면
		더이상 forwarding reference가 아니다. 이는 const rvalue reference가 되며
		이동 생성자도, 이동 연산자도 못쓰는, 수정 못하는 임시값 reference를 의미한다.
		가장 무의미한 타입이며, 아직 사용 사례도 본적이 없다.
	*/
	testFunc3(move(testD));

	return 0;
}
```
