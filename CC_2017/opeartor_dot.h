#pragma once
#include "stdafx.h"
#include <functional>
#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <tuple>
#include <stdexcept>

namespace operator_dot // not 
{
	struct Info
	{
		Vector2 pos;
		Vector2 speed;
		int x, y;
		Vector2 getPos()
		{
			return pos;
		}
	};
	class Monster
	{
		Info info;
	public:
		Monster()
		{
		}

		void draw()
		{
		}
		void proc()
		{
		}
		Info* operator->()
		{
			return &info;
		}
		//Info& operator.()
		//{
		//	return info;
		//}
	};

	void start()
	{
		Monster mon;
		mon->getPos();
	}
}