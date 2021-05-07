#include <iostream>

using namespace std;

int varMain();
int staticCalculatorMain(); 

int main() 
{
	int (*fp[2])() = { varMain, staticCalculatorMain };

	return fp[1](); 
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