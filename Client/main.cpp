#include <iostream>

using namespace std;

static int varMain();
static int staticCalculatorMain(); 
static int arrayListMain(); 

int main() 
{
	int (*fp[])() = 
	{ 
		varMain, 
		staticCalculatorMain, 
		arrayListMain
	};

	return fp[2](); 
}

// --------------------------- Var

#include "../Var/Var.h"

struct TestStruct
{
	int a{};
	double b{};
	const char* const str{};

	constexpr TestStruct() noexcept = default;
	constexpr TestStruct(const int a, const double b, const char* const str) noexcept :
		a{ a }, b{ b }, str{ str }
	{}

	TestStruct(const TestStruct& source) :
		a{ source.a }, b{ source.b }, str{ source.str }
	{
		cout << "TestStruct(const TestStruct &source) ȣ��" << endl;
	}

	friend ostream& operator<<(ostream& o, const TestStruct& testStruct)
	{
		o << '[' << testStruct.a << ", " << testStruct.b << ", " << testStruct.str << ']';
		return o;
	}
};

int varMain()
{
	/*
		��� ������ ���� �� �ִ� Var Ŭ������ �����Ͽ���.
		�Ʒ��� �ڵ尡 ���������� ������ �� �ֵ��� Var�� �����Ͽ���.

		Ŭ������ �������̺� �� ����/�Ҹ��� ó���� �����ؾ� �ϹǷ� ó������ �ʴ´�.
		�⺻Ÿ�� �ڷᱸ�� �� ����ü�� ���� ó���� �����Ͽ���.

		���� �̵�, �� rvalue �����Ϳ� ���� ó���� �ٷ��� �ʴ´�.
		��� ���� or �ʱ�ȭ�� ������ ���縦 ������� �����Ͽ���.

		�� ���� Ǯ�̽� memcpy, memmove�� ���� �޸� ���� �Լ��� ������� �� ��.

		[Ű����]
		typeid, type_info:
		runtime�� Ÿ�� üŷ�� ������ ���� (RTTI; RunTime Type Information)

		placement new:
		������ �޸� placeholder�� �̸� Ȯ�� �� �ش� ������ �޸𸮸� �����.
	*/
	// �� var ���� ����
	Var var1;

	// int ���� ����
	var1 = 1;

	try
	{
		// var1�� ������ Ÿ���� int�� ĳ�����Ͽ� ���� ����
		cout << var1.get<int>() << endl;

		// var1�� ������ Ÿ���� �ƴ� float�� ĳ����. exception�� �߻��Ǿ�� �Ѵ�.
		cout << var1.get<float>() << endl;
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	// float ������ �缳��
	var1 = 10.234f;

	// ���� exception�� �߻����� ����
	cout << var1.get<float>() << endl;

	const TestStruct testStruct{ 10, 200., "this is test" };

	// TestStruct �����͸� Var ������ ���ÿ� ����
	const Var var{ testStruct };

	// TestStruct ���
	cout << var.get<TestStruct>() << endl;

	// Var ��ü �Ҹ� �� ���� �޸� ������ �ʿ�.

	return 0; 
}

// --------------------------- StaticCalculator

#include "../StaticCalculator/Number.h"
#include "../StaticCalculator/StaticCalculator.h"

template <typename T>
static constexpr T getNumberValue(const Number<T>& src)
{
	return src.getValue();
}

int staticCalculatorMain() 
{
	/*
		������ Ÿ�ӿ� ������ ��� �����Ǵ� static calculator�� �����Ͽ���.
		�Ʒ��� �ڵ尡 ���� �����ϵ��� ������ �����Ͽ���.
	*/

	/*
		���ø� �Ķ���ͷ� ���� Ÿ�Ը� �Է¹��� �� �ִ�
		Number Ŭ������ �����Ͽ���. �����ڷδ� value�� �ϳ� �Է¹��� �� �ִ�.
		�����ڴ� constexpr �����ڷ� �������ÿ�.

		����: static_assert�� Ŭ���� ����ο� ���� �Է� �� ������ Ÿ�ӿ�
		Ÿ�� �Ķ���͸� üũ�� �� �ִ�.
		��)
		class Test
		{
			static_assert(false, "false!");
		};

		static_assert�� ���� �����ϰ� ���� �����Ͽ���.
	*/
	constexpr Number<float> number1{ 5.f };

	/*
		Number Ÿ���� �Է¹޾� ������ value�� ��ȯ�ϴ� getNumberValue()
		�Լ��� �����Ͽ���. getNumberValue() �Լ��� constexpr �Լ��� �����Ѵ�.
		Number Ŭ�������� ���� �����ϱ� ���� getValue() ��� �Լ��� �����Ѵ�.
	*/
	constexpr float val1 = getNumberValue<float>(number1);

	constexpr Number<float> number2{ 10.f };
	constexpr float val2 = getNumberValue(number2);

	/*
		������ Ÿ�ӿ� �� ���ڸ� �Է¹޾� ������ �����ϴ� StaticCalculator Ŭ������
		�����Ͽ���. �� Ŭ������ �ν��Ͻ��� ������ �� ����� �ϸ�, calc static �Լ���
		���� ��� ��� ���� ��ȯ�Ѵ�.

		���ø� �Ķ���ʹ� ���ʷ� <number Ÿ��, lhs, rhs, ���� Ÿ��> �̴�.
		���� Ÿ���� PLUS, MINUS, PRODUCT, DIVIDE �� ������ �����Ͽ��� �Ѵ�.
		���� Ÿ���� constexpr �б⹮�� ���� �����Ͻÿ�.

		calcResult1 ���� ���콺�� �÷� 15.0f��� ���� �̸������ ��µǴ��� Ȯ���Ͽ���.
	*/
	constexpr float calcResult1 =
		StaticCalculator<float, val1, val2, OperationType::PLUS>::calc();

	// 15 ���
	cout << "calcResult1:" << calcResult1 << endl;

	constexpr Number<int> number3{ 70 };
	constexpr Number<int> number4{ 10 };

	constexpr int calcResult2 =
		StaticCalculator<int, number3.getValue(), number4.getValue(), OperationType::DIVIDE>::calc();

	// 7 ���
	cout << "calcResult2:" << calcResult2 << endl;

	// ũ�� 7�� �迭 ����
	int arr[calcResult2]{};

	return 0;
}

// --------------------------- ArrayList

#include "../ArrayList/ArrayList.h"

int arrayListMain()
{
	/*
		�Ʒ��� �ڵ带 ��� ���������� ������ �� �ִ� ArrayList�� �����Ͽ���.
		ArrayList�� std::vector�� ������ ������ �����Ѵ�.

		������ �Ʒ��� ���� ��� �����Ͻÿ�.

		1.
		ArrayList�� ���Ҵ� ���Ƿ� ���� �����ϴ�. (���ø�ȭ �� ��)

		2.
		ArrayList�� �޸𸮴� �׻� ���� ������� �����Ǿ� �ִ�. �� �迭�� ����,
		�޸𸮰� �ɰ������� �ʰ� �� �̾��� �ִ�.

		3.
		����Ʈ �����͸� ������� �ʰ�, new/delete���� �̿��Ͽ� �޸𸮸� �����Ͽ���.
	*/

	/*
		�ʱ� ũ�� 3�� ����Ʈ ����.
		�� �� ������ ���� Ÿ�� �Ķ������ �⺻ ������ ����.
		int�� �ƴ� �ٸ� ��(float, double, ������ string����) ��� �⺻ ������ �ʱ�ȭ �Ǿ�� �Ѵ�.

		�Ұ�ȣ() �� �ƴ� �߰�ȣ{} �� �����ڸ� ȣ���ϴ� uniform initializer�� ���� �����Ͽ� ���� �����Ͽ���.
	*/
	ArrayList<int> list1{ 3 };

	// operator[] �� �����Ͽ� index�� ���� �ش� ���Ҹ� ������ �� �ֵ��� �Ͽ���.
	int& first = list1[0];
	first = 10;

	// TEST 1
	list1.show("list1");

	// initializer list�� Ȱ���Ͽ� ���� 3���� �����ϸ� �ʱ�ȭ
	// initializer list�� ���� �����Ͽ� ���� �����Ͽ���.
	ArrayList<string> list2{ "elem1", "elem2", "elem3" };

	// TEST 2
	list2.show("list2");

	// list�� ���ʿ� elem4, elem5�� �߰�
	list2.add("elem4");
	list2.add("elem5");

	// size_t Ÿ���� element size�� ��ȯ. (5�� ��µǾ�� ��)
	cout << list2.getSize() << endl;

	// 1��° ���� (elem2)�� �����Ѵ�.
	const size_t removeIndex = 1ULL;
	list2.remove(removeIndex);

	// 4 ���
	cout << list2.getSize() << endl;

	// elem3 ���
	cout << list2.get(1ULL) << endl;

	// 1��° ��ġ�� "elem5" ����
	const size_t insertIndex = 1ULL;
	list2.insert(insertIndex, "elem5");

	// "elem5" ���
	cout << list2[1] << endl;

	// "elem3" ���
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
	ArrayList<string> list5{ 6 };

	return 0;
}