# uniform_initialization

uniform initialization은 다양한 타입의 요소들을 일관된 방식으로 초기화 하기 위한 c++ 11 기능이다. <br>
{} 내부에 초기화 할 요소들을 ,로 나열한다.

``` c++
int i{}; // initialized built-in type, equals to int i{0};

int j{10}; // initialized built-in type

int a[]{1, 2, 3, 4} // Aggregate initialization

X x1{}; // default constructor

X x2{1}; // Parametrized constructor;

X x4{x3}; // copy-constructor
```
