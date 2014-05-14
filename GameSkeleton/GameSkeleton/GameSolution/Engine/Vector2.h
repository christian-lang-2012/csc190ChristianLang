#ifndef VECTOR2_H
#define VECTOR2_H


#include<iostream>
using std::cout;

namespace Engine{

	struct Vector2
	{
		float X;
		float Y;
		explicit Vector2(float x = 0.0f, float y = 0.0f): X(x), Y(y)
		{

		}

		operator float*() 
		{
			return &X;
		}

		

		inline float Length()
		{
			float xSquared = X * X;
			float ySquared = Y * Y;
			float underRadical = xSquared + ySquared;
			float result = sqrt(underRadical);
			return result;
		}

		inline float LengthSquared()
		{
			return sqrt(Length());
		}

		inline Vector2 Normalized()
		{

			float resX = X / Length();
			float resY = Y / Length();
			Vector2 result(resX, resY);
			return result;
		}

		inline Vector2 PerpCW()
		{
			Vector2 cwVector(Y, (-1 * X));
			return cwVector;
		}

		inline Vector2 PerpCCW()
		{
			Vector2 cwVector((-1 * Y), X);
			return cwVector;
		}
		
		inline Vector2 self_Lerp(Vector2 b, float beta)
		{
			float lerpX = ((1-beta) * X) + (beta * b.X);
			float lerpY = ((1-beta) * Y) + (beta * b.Y);
			Vector2 lerpVector(lerpX, lerpY);
			return lerpVector;
		}

		inline float self_Dot(const Vector2& right)
		{
			return (X * right.X) + (Y * right.Y);
		}

	};

	struct Vector3
	{
		float X, Y, Z;
		explicit Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f): X(x), Y(y), Z(z)
		{

		}
	};

	inline float Length(Vector2 a, Vector2 b)
	{
		float xSquared = a.X * b.X;
		float ySquared = a.Y * b.Y;
		float underRadical = xSquared + ySquared;
		float result = sqrt(underRadical);
		return result;
	}

	inline Vector2 Lerp(Vector2 a, Vector2 b, float beta)
	{
		float lerpX = ((1-beta) * a.X) + (beta * b.X);
		float lerpY = ((1-beta) * a.Y) + (beta * b.Y);
		Vector2 lerpVector(lerpX, lerpY);
		return lerpVector;
	}

	inline float Dot(const Vector2& left, const Vector2& right)
	{
		return (left.X * right.X) + (left.Y * right.Y);
	}

	inline Vector2 operator+(const Vector2& left, const Vector2& right)
	{
		float resX = left.X + right.X;
		float resY = left.Y + right.Y;
		Vector2 result(resX, resY);
		return result;
	}

	inline Vector2 operator-(const Vector2& left, const Vector2& right)
	{
		float resX = left.X + (-1 * right.X);
		float resY = left.Y + (-1 * right.Y);
		Vector2 result(resX, resY);
		return result;
	}

	inline std::ostream& operator<<(std::ostream& stream, const Vector2& right)
	{
		cout << "{x:" << right.X << ", y:" << right.Y << "}";
		return stream;
	}

	inline Vector2 operator*(const float scalar, const Vector2& right)
	{
		float resX = (scalar * right.X);
		float resY = (scalar * right.Y);
		Vector2 result(resX, resY);
		return result;
	}

	inline Vector2 operator*(const Vector2& left, const float scalar)
	{
		float resX = (scalar * left.X);
		float resY = (scalar * left.Y);
		Vector2 result(resX, resY);
		return result;
	}

	inline Vector2 operator/(const float scalar, const Vector2& right)
	{
		float resX = (scalar / right.X);
		float resY = (scalar / right.Y);
		Vector2 result(resX, resY);
		return result;
	}

	inline Vector2 operator/(const Vector2& right, const float scalar)
	{
		float resX = (right.X / scalar);
		float resY = (right.Y / scalar);
		Vector2 result(resX, resY);
		return result;
	}

}

#endif