#pragma once


#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <execution>
#include <algorithm>
#include <thread>
#include <mutex>

using namespace std::execution;

namespace parallel_excute
{
	#define MAX 10000

	#define IMAGE_WIDTH  50
	#define IMAGE_HEIGHT 50

	std::vector<int> v;

	void no_mutex()
	{
		std::string str;
		int sum = 0;
		
		str.clear();
		Radar::ChornoTime();
		std::for_each(std::execution::par, v.begin(), v.end(), [&](const int a) { sum += a; });
		str += " sum:";  str += to_string(sum); str += " par:";
		Radar::ChornoTime(false, str, Radar::UNIT_microseconds);
		cout << endl;

		sequenced_policy sp;
		sum = 0;
		str.clear();
		Radar::ChornoTime();
		std::for_each(sp, v.begin(), v.end(), [&](const int a) { sum += a; });
		str += " sum:";  str += to_string(sum); str += " sequenced_policy:";
		Radar::ChornoTime(false, str, Radar::UNIT_microseconds);
		cout << endl;

		parallel_policy pp;
		sum = 0;
		str.clear();
		Radar::ChornoTime();
		std::for_each(pp, v.begin(), v.end(), [&](const int a) { sum += a; });
		str += " sum:";  str += to_string(sum); str += " parallel_policy:";
		Radar::ChornoTime(false, str, Radar::UNIT_microseconds);
		cout << endl;

		parallel_unsequenced_policy pup;
		sum = 0;
		str.clear();
		Radar::ChornoTime();
		std::for_each(pup, v.begin(), v.end(), [&](const int a) { sum += a; });
		str += " sum:";  str += to_string(sum); str += " parallel_unsequenced_policy:";
		Radar::ChornoTime(false, str, Radar::UNIT_microseconds);
		cout << endl;
	}

	void mutex_ver()
	{
		std::mutex m;

		std::string str;
		int sum = 0;

		str.clear();
		Radar::ChornoTime();
		std::for_each(std::execution::par, v.begin(), v.end(), [&](const int a) { std::lock_guard<std::mutex> guard(m); sum += a; });
		str += " sum:";  str += to_string(sum); str += " par:";
		Radar::ChornoTime(false, str, Radar::UNIT_microseconds);
		cout << endl;

		sequenced_policy sp;
		sum = 0;
		str.clear();
		Radar::ChornoTime();
		std::for_each(sp, v.begin(), v.end(), [&](const int a) { std::lock_guard<std::mutex> guard(m); sum += a; });
		str += " sum:";  str += to_string(sum); str += " sequenced_policy:";
		Radar::ChornoTime(false, str, Radar::UNIT_microseconds);
		cout << endl;

		parallel_policy pp;
		sum = 0;
		str.clear();
		Radar::ChornoTime();
		std::for_each(pp, v.begin(), v.end(), [&](const int a) { std::lock_guard<std::mutex> guard(m); sum += a; });
		str += " sum:";  str += to_string(sum); str += " parallel_policy:";
		Radar::ChornoTime(false, str, Radar::UNIT_microseconds);
		cout << endl;

		parallel_unsequenced_policy pup;
		sum = 0;
		str.clear();
		Radar::ChornoTime();
		std::for_each(pup, v.begin(), v.end(), [&](const int a) { std::lock_guard<std::mutex> guard(m); sum += a; });
		str += " sum:";  str += to_string(sum); str += " parallel_unsequenced_policy:";
		Radar::ChornoTime(false, str, Radar::UNIT_microseconds);
		cout << endl;

	}


	int gSum = 0;
	void thread_sum(int n)
	{
		int counting = MAX / n;
		for (int i = 0; i < counting; ++i)
			gSum++;
	}

	struct ScreenShotImage
	{
		struct RGBA
		{
			union
			{
				struct
				{
					int r, g, b, a;
				};
				int rgba[4];
			};
			RGBA() :r(0), g(0), b(0), a(0)
			{
			}
			RGBA(int r, int g, int b, int a) 
			{
				rgba[0] = r;
				rgba[1] = g;
				rgba[2] = b;
				rgba[3] = a;
			}
			RGBA& operator+=(RGBA& other)
			{
				r += other.r; g += other.g;
				b += other.b; a += other.a;
				return *this;
			}
		};

		RGBA image[IMAGE_WIDTH][IMAGE_HEIGHT];

		ScreenShotImage()
		{
			for (int y = 0; y < IMAGE_HEIGHT; ++y)
			{
				for (int x = 0; x < IMAGE_WIDTH; ++x)
				{
					RGBA color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
					image[y][x] = color;
				}
			}
		}
		RGBA* begin()
		{
			return &image[0][0];
		}
		RGBA* end()
		{
			return &image[IMAGE_WIDTH - 1][IMAGE_HEIGHT -1];
		}
	};

	int getThreadPixel(ScreenShotImage image)
	{
		ScreenShotImage::RGBA color;
		std::for_each(std::execution::par, image.begin(), image.end(), [&](ScreenShotImage::RGBA input)
		{
			color += input;
		});

		int aver = (color.r + color.g + color.b + color.a) /4;
		aver /= (IMAGE_WIDTH * IMAGE_HEIGHT); 
		return aver;
	}

	int getPixel(ScreenShotImage image)
	{
		ScreenShotImage::RGBA color;
		std::for_each(image.begin(), image.end(), [&](ScreenShotImage::RGBA input)
		{
			color += input;
		});

		int aver = (color.r + color.g + color.b + color.a) / 4;
		aver /= (IMAGE_WIDTH * IMAGE_HEIGHT);
		return aver;
	}

	void start()
	{
		for (int i = 0; i < MAX; ++i) v.push_back(1);

		cout << "no mutex" << endl;
		no_mutex();

		cout << "mutex" << endl;
		mutex_ver();

		vector<std::thread> v;
		for(int i =0; i < 4; ++i)
			v.push_back(std::thread{ thread_sum, 4 });
		
		for (auto& d : v)
			d.join();

		std::cout << "\n thread : " << gSum << endl << endl << endl;


		static ScreenShotImage image;
		Radar::ChornoTime();
		int pixel = getPixel(image);
		Radar::ChornoTime(false, "pixcel : ", Radar::UNIT_microseconds);
		cout << pixel << "\n";

		Radar::ChornoTime();
		pixel = getThreadPixel(image);
		Radar::ChornoTime(false, "thread pixcel : ", Radar::UNIT_microseconds);
		cout << pixel << "\n";
	}
}