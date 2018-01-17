#pragma once

#include "stdafx.h"
#include <iostream>
#include <optional>

namespace type_optional
{

	// ������ ���� �ִ� ����
	std::optional<int> custom_sqrt(const int x)
	{
		if (x < 0) return {}; // return false�̶��� �ٸ��ϴ�.
		return sqrt(x);
	}

	bool ori_sqrt(int& x)
	{
		if (x < 0) return false;
		x = (int)sqrt(x);	// �� �κ�
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
		cout << " ������ ��� - 1\n";
		for (int i = s; i <= e; ++i)
		{
			int x = i;
			if (ori_sqrt(x))
				std::cout << x << ",";
			else
				cout << "invalid, ";
		}

		cout << "\n\n ������ ��� - 2\n";
		for (int i = s; i <= e; ++i)
		{
			auto result = pair_sqrt(i);
			if (result.first)
				std::cout << result.second << ",";
			else
				cout << "invalid, ";
		}

		cout << "\n\n optional ���\n";
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