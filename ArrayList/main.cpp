#include "ArrayList.h"

using namespace std;

int main()
{
	/*
		아래의 코드를 모두 정상적으로 실행할 수 있는 ArrayList를 구현하여라.
		ArrayList는 std::vector와 동일한 동작을 수행한다.

		구현시 아래의 명세를 모두 만족하시오.

		1.
		ArrayList의 원소는 임의로 설정 가능하다. (템플릿화 할 것)

		2.
		ArrayList의 메모리는 항상 단일 블록으로 구성되어 있다. 즉 배열과 같이,
		메모리가 쪼개져있지 않고 쭉 이어져 있다.

		3.
		스마트 포인터를 사용하지 않고, new/delete만을 이용하여 메모리를 관리하여라.
	*/

	/*
		초기 크기 3의 리스트 생성.
		이 때 원소의 값은 타입 파라미터의 기본 값으로 설정.
		int가 아닌 다른 값(float, double, 심지어 string까지) 모두 기본 값으로 초기화 되어야 한다.

		소괄호() 가 아닌 중괄호{} 로 생성자를 호출하는 uniform initializer에 대해 조사하여 글을 정리하여라.
	*/
	ArrayList<int> list1{ 3ULL };

	// operator[] 를 구현하여 index에 따라 해당 원소를 접근할 수 있도록 하여라.
	int& first = list1[0];
	first = 10;
	list1[1] = 20;
	list1[2] = 30;

	// TEST 1
	list1.show("list1"); 

	// initializer list를 활용하여 원소 3개를 삽입하며 초기화
	// initializer list에 대해 조사하여 글을 정리하여라.
	ArrayList<string> list2{ "elem1", "elem2", "elem3" };

	// TEST 2
	list2.show("list2"); 

	// list의 뒤쪽에 elem4, elem5를 추가
	list2.add("elem4");
	list2.add("elem5");

	// size_t 타입의 element size를 반환. (5가 출력되어야 함)
	cout << list2.getSize() << endl;

	// 1번째 원소 (elem2)를 삭제한다.
	const size_t removeIndex = 1ULL;
	list2.remove(removeIndex);

	// 4 출력
	cout << list2.getSize() << endl;

	// elem3 출력
	cout << list2.get(1ULL) << endl;

	// 1번째 위치에 "elem5" 삽입
	const size_t insertIndex = 1ULL;
	list2.insert(insertIndex, "elem5");

	// "elem5" 출력
	cout << list2[1] << endl;

	// "elem3" 출력
	cout << list2[2] << endl << endl;

	// TEST 3
	const int list1Size = int(list1.getSize());
	ArrayList<int> list3{ list1Size };
	{
		memcpy(list3.getRaw(), list1.getRaw(), sizeof(int) * list1Size);
		list3.show("list3");
	}

	// TEST 4
	ArrayList<int> list4; 
	{
		list4.insert(0ULL, 5);
		list4.show("list4"); 
	}

	// TEST 5
	ArrayList<string> list5(6); 

	return 0;
}