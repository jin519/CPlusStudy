# volatile

volatile 키워드는 해당 변수에 대해 컴파일러가 최적화를 적용할 수 없도록 한다. 즉, 개발자가 의도한대로 기계어가 만들어지도록 보장한다. 

### Example

``` c++
int x = 0; 
```

### Syntax

std::remove_reference
std::remove_const
std::remove_volatile

remove_reference_t
remove_cv
remove_cvref_t
