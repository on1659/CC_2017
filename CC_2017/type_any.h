
#pragma once

#include "stdafx.h"
#include <any>
#include <iostream>

namespace type_any
{
	/*
		boost.any 기반 라이브러리
		모든 종류의 정보를 저장 (단, 복사생성자를 지원해야 함)
		any_cast()를 통해 원하는 타입으로 변환된 결과를 얻을 수 있음
	*/
	class Monster
	{
	public:
		int k;

		Monster()
		{
			k = rand();
		}
		Monster(int k_)
		{
			k = k_;
		}

		Monster(const Monster& mon)
		{
			k = mon.k;
		}

		Monster& operator=(Monster& mon)
		{
			k = mon.k;
		}

		Monster& operator=(Monster&& mon)
		{
			k = mon.k;
		}
	};

	struct Name
	{
		std::string name;

		Name& operator=(Name mon)
		{
			name = mon.name;
		}
	};

	class AnyManager
	{
		std::vector<any> v;

		template<class T>
		bool isVaild(const int n)
		{
			if (v.size() < n)
				return false;

			try {
				std::any_cast<T>(v[n]);	// ★
				cout << "true" << endl;
				return true;
			}
			catch (const std::bad_any_cast& e) {
				std::cout << e.what() << endl;
				return false;
			}
		}

	public:
		void push(std::any in)
		{
			v.push_back(in);
		}

		void valid()
		{
			while (1)
			{
				int t, n;
				switch (cin >> t >> n; t)
				{
				case 0:
					isVaild<int>(n);
					break;

				case 1:
					isVaild<char>(n);
					break;

				case 2:
					isVaild<Name>(n);
					break;

				case 3:
					isVaild<Monster>(n);
					break;
				}
			}
		}
	};
	
	void start()
	{
		std::vector<std::any> vAny;
		vAny.push_back(10);
		vAny.push_back(Name());
		vAny.push_back(Monster());

		try {
			std::any_cast<int>(vAny[0]);	// ★
			cout << "true" << endl;
		}
		catch (const std::bad_any_cast& e) {
			std::cout << e.what() << endl;
		}
		
		auto result = std::any_cast<int>(vAny[1]);	// assert
		cout << result << endl;
	}

	void start2()
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