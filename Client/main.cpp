#include <iostream>

// Var ������Ʈ�� Var.h ����
#include "../Var/Var.h"

using namespace std;

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

int main()
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
}