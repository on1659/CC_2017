#pragma once
#include "stdafx.h"
#include <functional>
#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <tuple>
#include <stdexcept>

namespace type_invoke
{
	// apply

	// auto�� ���� �����ϴ�   Ÿ���� �߷н����ִ� Ű������,
	// decaltype�� �����κ��� Ÿ���� ������ �� �� �ִ� Ű������ �����ϸ� �ȴ�.

	struct Foo 
	{
		Foo(int num) : num_(num) {}
		void print_add(int i) const 
		{ 
			std::cout << num_ + i << '\n'; 
		}
		int num_;
	};

	template<class Callable>
	class Proxy
	{
		Callable c;
	public:
		Proxy(Callable c) : c(c){}
		template<class... Args>
		auto operator()(Args&&... args)
		{
			return std::invoke(c, std::forward<Args>(args)...);
		}
	};

	template<class Callable>
	class MyApply
	{
		Callable call;

	public:
		MyApply(Callable call) : call(call)
		{
		}

		template<class Fir, class Sec>
		auto operator()(Fir fir, Sec sec)
		{
			return std::apply(call, std::make_tuple(fir, sec));
		}
	};

	template<typename T>
	void print_add(T i)
	{
		cout << i << '\n';
	}
	template<typename ...Args>
	int sum(Args&&... args)
	{
		return (args + ... + 0);
	}
	void start()
	{
		// Basic
		std::invoke(&sum<int,int,int>, 1,2,3);

		// Step 1..
		auto add = [](int x, int y) {return x + y; };
		Proxy<decltype(add)> p{ add };
		cout << p(1, 2) << endl;

		// Step 2..
		auto five_add = [](int a, int b, int c, int d, int e) {return (a+b+c+d+e); };
		Proxy<decltype(five_add)> p2{ five_add };
		cout << p2(1, 2, 3, 4, 5) << endl;


		// Basic
		auto applySum = [](int a, int b){ return a + b; };

		// Step 1..
		cout << std::apply(applySum, std::make_tuple<int, int>(10, 10)) << endl;

		//Step 2..
		 MyApply<decltype(applySum)> myApply{ applySum };
		 cout << myApply(20, 30) << endl;

	}
}