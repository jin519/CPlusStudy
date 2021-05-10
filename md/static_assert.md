# static_assert

compile-time에 assertion 체크를 수행한다.

### Syntax

``` c++
static_assert(bool_constexpr, message); // (since C++11)
static_assert(bool_constexpr);          // (since C++17)
```

### Explanation

static assert는 namespace, block 영역, 클래스 선언 시점에 사용할 수 있다.
bool_constexpr이 false를 리턴한다면 compile-time에 에러가 발생하며, message가 있다면 표시한다. 
message는 string literal 타입이기 때문에 동적으로 결정되는 정보나, string literal이 아닌 const 타입을 포함할 수 없다. 
특히 template type 인자의 이름을 포함할 수 없다.

### Example

``` c++
#include <type_traits>

template <typename T>
class Number 
{
  // 숫자 타입만 입력받을 수 있다. 
	static_assert(std::is_arithmetic_v<T>, "invalid type.");

public:
	constexpr Number(const T value); 

	constexpr T getValue() const;

private:
	T __value; 
};
```
