#pragma once

#include "stdafx.h"
#include <chrono>
#include <time.h>
#include <string>
namespace Radar
{
	static void gotoxy(const short& x, const short& y)
	{
		COORD pos{ x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}

	static void setColorblue() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000b); }
	static void setColorred() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000c); }
	static void setColorwhite() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000f); }
	static void setColordefault() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007); }


	enum TIME_UNIT
	{
		  UINT_nanoseconds = 0x00000001
		, UNIT_microseconds = 0x00000002
		, UINT_milliseconds = 0x00000004
		, UINT_seconds = 0x00000010
		, UINT_minutes = 0x00000020
		, UINT_hours = 0x00000040
	};


	static void ChornoTime(bool start = true, const std::string& msg = "time : ", const DWORD& TIME_UNIT = TIME_UNIT::UINT_nanoseconds)
	{
		//C++ 11? 14 최신 문법으로 함수내 선언한 static 변수가 전역으로 잡힘
		static std::chrono::high_resolution_clock::time_point gStart;

		if (start) gStart = std::chrono::high_resolution_clock::now();

		else
		{
			auto gTotal_time = std::chrono::high_resolution_clock::now() - gStart;

			std::cout << msg;
			setColorred();
			if (TIME_UNIT & TIME_UNIT::UINT_nanoseconds)
			{
				std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(gTotal_time).count();

				setColorwhite();
				std::cout << " nanoseconds ";
			}
			if (TIME_UNIT & TIME_UNIT::UNIT_microseconds)
			{
				std::cout << std::chrono::duration_cast<std::chrono::microseconds>(gTotal_time).count();
				setColorwhite();
				std::cout << " microseconds ";
			}
			if (TIME_UNIT & TIME_UNIT::UINT_milliseconds)
			{
				std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(gTotal_time).count();

				setColorwhite();
				std::cout << " milliseconds ";
			}
			if (TIME_UNIT & TIME_UNIT::UINT_seconds)
			{
				std::cout << std::chrono::duration_cast<std::chrono::seconds>(gTotal_time).count();
				setColorwhite();
				std::cout << " seconds ";
			}
			if (TIME_UNIT & TIME_UNIT::UINT_minutes)
			{
				std::cout << std::chrono::duration_cast<std::chrono::minutes>(gTotal_time).count();
				setColorwhite();
				std::cout << " minutes ";
			}
			if (TIME_UNIT & TIME_UNIT::UINT_hours)
			{
				std::cout << std::chrono::duration_cast<std::chrono::hours>(gTotal_time).count();
				setColorwhite();
				std::cout << " hours ";
			}
			setColordefault();
			std::cout << std::endl;


		}

	}

	static void TimeRecord(bool start = true, const std::string& msg = "time : ", const DWORD& time_unit = UINT_nanoseconds)
	{
		ChornoTime(start, msg, time_unit);
	}
}
