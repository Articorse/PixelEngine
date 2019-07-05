#include "Vector2.h"

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(const Vector2& other)
{
	x = other.x;
	y = other.y;
}

Vector2::Vector2(int _x, int _y)
{
	x = _x;
	y = _y;
}

Vector2& Vector2::operator=(const Vector2& other)
{
	x = other.x;
	y = other.y;

	return *this;
}

Vector2 Vector2::operator+(const Vector2& other)
{
	Vector2 ret;

	ret.x = x + other.x;
	ret.y = y + other.y;

	return ret;
}

Vector2 Vector2::operator-(const Vector2& other)
{
	Vector2 ret;

	ret.x = x - other.x;
	ret.y = y - other.y;

	return ret;
}

Vector2 Vector2::operator*(const Vector2& other)
{
	Vector2 ret;

	ret.x = x * other.x;
	ret.y = y * other.y;

	return ret;
}

Vector2 Vector2::operator*(int _x)
{
	Vector2 ret;

	ret.x = x * _x;
	ret.y = y * _x;

	return ret;
}

Vector2 Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;

	return *this;
}

Vector2 Vector2::operator-=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;

	return *this;
}

Vector2 Vector2::operator*=(const Vector2& other)
{
	x *= other.x;
	y *= other.y;

	return *this;
}

Vector2 Vector2::operator*=(int _x)
{
	x *= _x;
	y *= _x;

	return *this;
}

bool Vector2::operator==(const Vector2& other)
{
	return (x == other.x && y == other.y);
}

bool Vector2::operator!=(const Vector2& other)
{
	return !operator==(other);
}

//string Vector2::ToString()
//{
//	stringstream ss;
//	ss << "X: " << x << ", Y: " << y;
//	return ss.str();
//}