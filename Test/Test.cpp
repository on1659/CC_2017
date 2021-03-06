// abstractF.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include <iostream>

class 재료
{
public:
	virtual void show() const = 0;
};

class 방 : public 재료
{
public:
	void show()const { std::cout << "방" << std::endl; };
};

class 다리 : public 재료
{
	int 다리크기;
public:
	다리(int i = 1) :다리크기(i) {};
	void show()const {
		std::cout << "다리 : " << 다리크기
			<< std::endl;
	};
};

class 추상팩토리 {
public:
	방 * make방() {
		return new 방;
	}
	다리 * make다리(int n) {
		return new 다리(1);
	}
};

class 마법팩토리 :public 추상팩토리 {
public:
	방 * make방() {
		return new 방;
	}
	다리 * make다리(int n) {
		return new 다리(n);	// 선택 2
	}
};

class 칼팩토리 :public 추상팩토리 {
public:
	방 * make방() {
		return new 방;
	}
	다리 * make다리(int n) {
		return new 다리(n);	// 선택 2
	}
};

class 미로 {
	방* 방arr_[2];
	다리* 다리_;
public:

	void Make(추상팩토리* 팩토리)
	{
		//다리_ = 팩토리->make다리();
		//방arr_[0] = 팩토리->make방();
		//방arr_[1] = 팩토리->make방();

	}
};

template <class Type>
class AbstractClass
{
public:
	Type * make()
	{
		return createor();
	}

protected:
	Type * createor() = 0;
};

template<class T1, class T2>
class CreateFactory : public AbstractClass<T1>
{
	T1* creator() override { return new T2; }
};

class A 
{
public:
	void s()
	{
		std::cout << "a" << std::endl;
	}
};
class B : public A
{
public:
	void s()
	{
		std::cout << "b" << std::endl;
	}
};

class C : public B
{
public:
	void s()
	{
		std::cout << "c" << std::endl;
	}
};

