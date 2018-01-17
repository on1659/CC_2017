#pragma once

#include "stdafx.h"

class Vector2
{
public:
	float x, y;
	Vector2() :x(0.0f), y(0.0f) { }
	Vector2(const float& x, const float& y) : x(x), y(y) {}
	~Vector2() {}

	void set(const float& x, const float& y)
	{
		Vector2::x = x;	Vector2::y = y;
	}

	Vector2 operator+(const Vector2& other)
	{
		return Vector2(x + other.x, y + other.y);   //Vector2라는 객체를 생성해서 리턴함

	}
	void operator+=(const Vector2& other)
	{
		x += other.x; y += other.y;
	}

	Vector2 operator-(const Vector2& other)
	{
		return Vector2(x - other.x, y - other.y);
	}
	void operator-=(const Vector2& other)
	{
		x = x - other.x;
		y = y - other.y;
	}

	Vector2 operator*(const Vector2& other) const
	{
		return Vector2(x * other.x, y * other.y);

	}
	void operator*=(const Vector2& other)
	{
		x *= other.x; y *= other.y;
	}

	Vector2 operator*(const float& a) const
	{
		return Vector2(x * a, y * a);
	}
	void operator*=(const float& a)
	{
		x *= a; y *= a;
	}

	Vector2 operator/(const Vector2& other) const
	{
		return Vector2(x / other.x, y / other.y);
	}
	void operator/=(const Vector2& other)
	{
		x /= other.x; y /= other.y;
	}

	Vector2 operator/(const float& a) const
	{
		return Vector2(x / a, y / a);
	}
	void operator/=(const float& a)
	{
		x = x / a;
		y = y / a;
	}

	//내적 값이 변하지 말라고 const를 써줌
	float dot(Vector2 other) const
	{
		return (x * other.x) + (y * other.y);
	}

	//벡터의 크기
	float scale() const
	{
		return sqrt((x * x) + (y * y));
	}

	//단휘벡터 만들기 
	Vector2 normalize() const
	{
		float s = scale();
		return Vector2(x / s, y / s);
	}

	//두 벡터간의 거리.. (현재 이 벡터와 다른 벡터간의 거리
	float length(const Vector2& other) const
	{
		return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
	}

};
