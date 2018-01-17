#pragma once

#include "stdafx.h"
#include <iostream>
#include <optional>

namespace type_optional
{

	// 실패할 수도 있는 연산
	std::optional<int> custom_sqrt(const int x)
	{
		if (x < 0) return {}; // return false이랑은 다릅니다.
		return sqrt(x);
	}

	bool ori_sqrt(int& x)
	{
		if (x < 0) return false;
		x = (int)sqrt(x);	// 이 부분
		return true;
	}
	pair<bool, int> pair_sqrt(const int x)
	{
		if (x < 0) return pair<bool, int>(false, -1);
		return pair<bool, int>(true, sqrt(x));
	}

	void start()
	{
		int s = -2;
		int e = 2;
		cout << " 기존의 방식 - 1\n";
		for (int i = s; i <= e; ++i)
		{
			int x = i;
			if (ori_sqrt(x))
				std::cout << x << ",";
			else
				cout << "invalid, ";
		}

		cout << "\n\n 기존의 방식 - 2\n";
		for (int i = s; i <= e; ++i)
		{
			auto result = pair_sqrt(i);
			if (result.first)
				std::cout << result.second << ",";
			else
				cout << "invalid, ";
		}

		cout << "\n\n optional 방식\n";
		for (int i = s; i <= e; ++i)
		{
			std::optional<int> x = custom_sqrt(i);
			if (x)
				std::cout << *x << ",";
			else
				cout << "invalid, ";
		}
		cout << endl << endl;
	}
}