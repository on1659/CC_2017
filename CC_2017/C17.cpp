#include "stdafx.h"

#pragma once

#include "C17.h"

#include <cassert>	// [[ noreturn ]]


namespace C17
{
	void Template::start()
	{
		std::cout << "-------C17------"<< std::endl;
		//print("hi", "hellow", "+", 123, 456);
		std::cout << sum(1, 2, 3, 4, 5) << std::endl;
	}

	void Auto_Deduction::start()
	 {
	 	auto a{ 1 };		// int
	 	auto b = { 1 };		// std::initalizer_list<int>
	 	auto c = { 1, 2 };	// std::initalizer_list<int>
	 	// auto d{ 1, 2 };		// error
	 }

	namespace Constexpr_lambdas
	{
	 int lambda(const int&a, const int& b)
	{
		auto add = [](const int& a, const int& b) constexpr 
		{
			return a + b; 
		};
		return add(a, b);
	}

	 void factorial(const int& k)
	{
		// partial ?
		/*
		auto getFactorializer = [] {
			unsigned int optimization[6] = {};
			auto for_each = [](auto* b, auto* e, auto pred) 
			{
				auto* it = b;
				while (it != e) 
					pred(it++ - b);
			};

			for_each(optimization, optimization + 6, [&](int n) 
			{
				if (!n)
					optimization[n] = 1;
				else
					optimization[n] = n * optimization[n - 1];
			});

			auto FacImpl = [=](auto fac, unsigned int n) 
			{
				if (n <= 5)
					return optimization[n];
				return
					n * fac(fac, n - 1);
			};
			auto Fact = [=](int n) {
				return FacImpl(FacImpl, n);
			};

			return Fact;
		};
		constexpr auto Factorial = getFactorializer();
		static_assert(Factorial(5) == 120, "");
		static_assert(Factorial(10) == 362800, "");
		*/
	}

	 auto MyObj::getValueCopy()
	 {
		 return[*this]{ return value; };
	 }

	 auto MyObj::getValueRef()
	 {
		 return [this] {return value; };
	 }

	 void start()
	 {
		 int n;
		 std::cout << "plz input n : "; 	std::cin >> n;

		 factorial(n);

		 std::cout << "square run time : " << square(n) << '\n';	// run-time
		 std::cout << "square compile : " << square(10) << '\n'; // compile-time

																 // &&
		 std::cout << "lambda : " << lambda(10, 20) << std::endl;
	 }

	 void start_capture()
	 {
		 MyObj mo;
		 auto valueCopy = mo.getValueCopy();
		 auto valueRef = mo.getValueRef();

		 mo.value = 321;
		 auto vc = valueCopy();
		 auto vr = valueRef();
		 std::cout << "copy : " << vc << std::endl;
		 std::cout << "ref : " << vr << std::endl;
	 }
	}

	namespace Attribute
	{
		// noreturn
		void func()
		{
			throw "error";
		}
		void noFunc(int i)
		{
			if (i > 0)
			{
				throw "positiv";
			}
		}

		// nodiscard
		Object factory_create(int n)
		{
			Object ob;
			ob.id_ = n;
			return ob;
		}
		void start_nodiscard()
		{
			for (int i = 0; i < 3; ++i)
				factory_create(3);

			std::cout << factory_create(99).id_ << std::endl;
		}

		// maybe_unused
		static void no_use([[maybe_unused]]  int a, int b)
		{
			std::cout << "a,b" << std::endl;
		}	
		static void no_use(int a)
		{
			std::cout << "a" << std::endl;
		}

	}

	namespace Memo_init
	{
		Monster::Monster()
		{
			state = rand() % 3;
		}

		const int Monster::getState() const
		{
			return state;
		}

		void Monster::addState()
		{
			state++;
			if (getState() > 3)
				state = 0;
		}

		void Monster::update()
		{
			switch (getState())
			{
				case 0:
				case 1:
				case 2:
					addState();
					break;
			}
		}
	}

	namespace initalize
	{
		void initalize::start()
		{
			QuestManager manager;
			manager.show();
		}
	}

	namespace type_any
	{
		void AnyManager::push(std::any in)
		{
			v.push_back(in);
		}

		void start()
		{
			AnyManager anyManager;
			anyManager.push(10);		// 0
			anyManager.push('c');		// 1
			anyManager.push(Name());	// 2
			anyManager.push(100);		// 3
			anyManager.push(Monster());	// 4
			anyManager.push(Name());	// 5
			anyManager.push(Monster());	// 6
			
			anyManager.valid();

		}
	}

	namespace type_optional
	{

	}
	void start_maybe_nouse()
	{

	}
}
