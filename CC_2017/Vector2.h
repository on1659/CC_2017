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
		return Vector2(x + other.x, y + other.y);   //Vector2��� ��ü�� �����ؼ� ������

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

	//���� ���� ������ ����� const�� ����
	float dot(Vector2 other) const
	{
		return (x * other.x) + (y * other.y);
	}

	//������ ũ��
	float scale() const
	{
		return sqrt((x * x) + (y * y));
	}

	//���ֺ��� ����� 
	Vector2 normalize() const
	{
		float s = scale();
		return Vector2(x / s, y / s);
	}

	//�� ���Ͱ��� �Ÿ�.. (���� �� ���Ϳ� �ٸ� ���Ͱ��� �Ÿ�
	float length(const Vector2& other) const
	{
		return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
	}

};
