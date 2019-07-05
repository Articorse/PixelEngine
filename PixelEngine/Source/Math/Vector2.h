#pragma once

class Vector2
{
public:
	Vector2();
	Vector2(const Vector2& other);
	Vector2(int _x, int _y);

	int x;
	int y;

	Vector2& operator=(const Vector2& other);
	Vector2 operator+(const Vector2& other);
	Vector2 operator-(const Vector2& other);
	Vector2 operator*(const Vector2& other);
	Vector2 operator*(int _x);

	Vector2 operator+=(const Vector2& other);
	Vector2 operator-=(const Vector2& other);
	Vector2 operator*=(const Vector2& other);
	Vector2 operator*=(int _x);

	bool operator==(const Vector2& other);
	bool operator!=(const Vector2& other);
};