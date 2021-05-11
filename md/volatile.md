# volatile

volatile 키워드는 해당 변수에 대해 컴파일러가 최적화를 적용할 수 없도록 한다.<br> 
즉, 개발자가 의도한대로 기계어가 만들어지도록 보장한다. 

### Example

``` c++
int x = 0; 

while (x < 10)
  ++x;
```
compiler 최적화 시 다음과 같이 변경된다.

``` c++
int x = 10; 
```

int 앞에 volatile을 붙이면 위의 상황이 발생하지 않는다.

# std::remove_reference

reference를 제거한다.

``` c++
template <class T>
struct remove_reference;

template <class T>
using remove_reference_t = typename remove_reference<T>::type;
```

### Example

``` c++
#include <type_traits>

std::is_same<int, int>();                                 // true
std::is_same<int, int &>();                               // false 
std::is_same<int, int &&>();                              // false
 
std::is_same<int, std::remove_reference<int>::type>();    // true
std::is_same<int, std::remove_reference<int &>::type>();  // true
std::is_same<int, std::remove_reference<int &&>::type>(); // true

std::is_same<int, std::remove_reference_t<int &&>>();     // true
```

# std::remove_const

const를 제거한다.

``` c++
template <class T>
struct remove_const;

template <class T>
using remove_const_t = typename remove_const<T>::type;
```

# std::remove_volatile

volatile을 제거한다.

``` c++
template <class T>
struct remove_volatile;

template <class T>
using remove_volatile_t = typename remove_volatile<T>::type;
```

# std::remove_cv

const, volatile을 제거한다.

``` c++
template <class T>
struct remove_cv;

template <class T>
using remove_cv_t = typename remove_cv<T>::type;
```
# std::remove_cvref

const, volatile, reference를 제거한다.

``` c++
template <class T>
struct remove_cvref;

template <class T>
using remove_cvref_t = typename remove_cvref<T>::type;
```
