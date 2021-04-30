# initializer_list

템플릿 클래스로, const T 타입 배열의 각 요소에 접근하는데 사용된다.
컴파일 시점에 객체가 생성된다.

``` c++
auto list = { 10, 20, 30 }; // list type: std::initializer_list<int> 
```

사용을 위해서는 <initializer_list> 헤더가 포함되어야 한다.

initializer_list 객체가 생성될 때 const T 타입 배열이 할당된다.
initializer_list 객체는 배열의 각 요소를 복사하지 않고, 참조만 한다.
initializer_list 객체의 복사본 또한 위의 임시 배열을 참조만 한다.
임시 배열은 initializer_list 객체와 생명 주기를 같이 한다. 

initializer-list 생성자는 initializer-list 형식으로 객체를 초기화 했을 때, 다른 생성자보다 우선순위가 높다.

``` c++
class myclass 
{
  myclass (int,int);
  myclass (initializer_list<int>);
  /* definitions ... */
};

myclass foo {10,20};  // calls initializer_list ctor
myclass bar (10,20);  // calls first constructor 
```
