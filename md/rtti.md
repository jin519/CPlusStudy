# Run-time Type Information

RTTI는 run-time에 결정되는 객체의 type에 대한 정보를 제공하는 기능이다.
일관되게 사용한다면 리소스 관리에 강력한 도구가 될 수 있다.

### dynamic_cast

``` c++
SpecificClass* pSpecific = dynamic_cast<SpecificClass*>(pInterface); 
SpecificClass& specific = dynamic_cast<SpecificClass&>(interface); 
```

dynamic_cast는 기본 클래스의 포인터를 파생 클래스의 포인터로 캐스팅한다.
캐스팅 대상 타입이 잘못되었을 경우 nullptr가 리턴된다.
reference 캐스팅도 가능하며, 이때는 타입이 잘못되었을 경우 std::bad_cast exception이 발생한다.

### typeid

``` c++
const std::type_info& type = typeid(object); 
```

typeid 연산자는 객체를 설명하는 const std::type_info 객체의 reference를 리턴한다.
객체가 역참조된 nullptr일 경우, std::bad_typeid exception이 발생한다. 
단순히 객체 정보만 필요하다면, dynamic_cast 보다 상수 시간이 소요되는 typeid가 유리하다.
std::type_info::name() 은 컴파일러에 따라 구현이 달라질 수 있기 때문에 유의해야 한다.

### type_index

std::type_info 객체의 래퍼 클래스.
type_info 객체와의 관계가 포인터를 통해 유지되므로 복사 생성, 복사 대입이 가능하다.

``` c++
#include <typeinfo>
#include <typeindex>

std::unordered_map<std::type_index, std::string> type_names;

type_names[std::type_index(typeid(int))] = "int";
type_names[std::type_index(typeid(double))] = "double";

int i;
double d;
 
std::cout << "i is " << type_names[std::type_index(typeid(i))] << '\n';
std::cout << "d is " << type_names[std::type_index(typeid(d))] << '\n'; 
```

### 한계

- 다형성(클래스 내 하나 이상의 가상 함수가 존재함) 타입에만 사용할 수 있다. 
- 타입을 저장하는데 필요한 부가 정보들 때문에, 일부 컴파일러는 RTTI를 활성화하려면 설정을 변경해야 한다.
- 포인터의 reference 는 RTTI가 동작하지 않는다.

``` c++
void example( int*& refptrTest )
{
    // report int*
    std::cout << "What type is *&refptrTest : " << typeid( refptrTest ).name() << std::endl;
}
```
