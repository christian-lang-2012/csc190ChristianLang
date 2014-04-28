#include<iostream>
using std::cout;

struct Vector2
{
	float X;
	float Y;
	Vector2(float x = 0, float y = 0): X(x), Y(y)
	{
		X = x;
		Y = y;
	}
};

Vector2 operator+(const Vector2& left, const Vector2& right)
{
	float resX = left.X + right.X;
	float resY = left.Y + right.Y;
	Vector2 result(resX, resY);
	return result;
}

Vector2 operator-(const Vector2& left, const Vector2& right)
{
	float resX = left.X + (-1 * right.X);
	float resY = left.Y + (-1 * right.Y);
	Vector2 result(resX, resY);
	return result;
}

std::ostream& operator<<(std::ostream& stream, const Vector2& right)
{
	cout << "{x:" << right.X << ", y:" << right.Y << "}";
	return stream;
}

Vector2 operator*(const float scalar, const Vector2& right)
{
	float resX = (scalar * right.X);
	float resY = (scalar * right.Y);
	Vector2 result(resX, resY);
	return result;
}

Vector2 operator*(const Vector2& left, const float scalar)
{
	float resX = (scalar * left.X);
	float resY = (scalar * left.Y);
	Vector2 result(resX, resY);
	return result;
}

Vector2 operator/(const float scalar, const Vector2& right)
{
	float resX = (scalar / right.X);
	float resY = (scalar / right.Y);
	Vector2 result(resX, resY);
	return result;
}

Vector2 operatorLERP(const Vector2& left, const Vector2& right, const int beta)
{

}