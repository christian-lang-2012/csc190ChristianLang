#ifndef MATRIX_3
#define MATRIX_3

#include "Vector2.h"

using Engine::Vector2;
using Engine::Vector3;

namespace Engine
{
	class Matrix3
	{
	public:
		float x1, x2, x3, y1, y2, y3, z1, z2, z3;
		Matrix3()
		{
			x1 = 1;
			x2 = 0;
			x3 = 0;
			y1 = 0;
			y2 = 1;
			y3 = 0;
			z1 = 0;
			z2 = 0;
			z3 = 1;
		}

		Matrix3(Vector2 first, Vector2 second)
		{
			x1 = first.X;
			x2 = second.X;
			x3 = 0;
			y1 = first.Y;
			y2 = second.Y;
			y3 = 0;
			z1 = 0;
			z2 = 0;
			z3 = 1;
		}

		operator float*() 
		{
			return &x1;
		}

		friend inline Matrix3 operator*(Matrix3 m1, Matrix3 m2);
		friend inline Vector3 operator*(Matrix3 m1, Vector3 v1);

		inline Matrix3 Rotation(float angle)
		{
			Vector2 first (cosf(angle), sinf(angle));
			Vector2 second (-sinf(angle), cosf(angle));
			Matrix3 rotation (first, second);
			return rotation;
		}

		inline Matrix3 Scale(float scale)
		{
			Matrix3 m2 = (*this);
			m2.x1 = m2.x1 * scale;
			m2.y2 = m2.y2 * scale;
			return m2;
		}

		inline Matrix3 ScaleX(float scale)
		{
			Matrix3 m2 = (*this);
			m2.x1 = m2.x1 * scale;
			m2.x2 = m2.x2 * scale;
			return m2;
		}

		inline Matrix3 ScaleY(float scale)
		{
			Matrix3 m2 = (*this);
			m2.y2 = m2.y2 * scale;
			m2.y1 = m2.y1 * scale;
			return m2;
		}

		inline Matrix3 Translation(float x, float y)
		{
			Matrix3 m2 = (*this);
			x3 += x;
			y3 += y;
			return m2;
		}

		inline Matrix3 Translation(const Vector2& t)
		{
			Matrix3 m2 = (*this);
			m2.x3 = t.X;
			m2.y3 = t.Y;
			return m2;
		}

	};


	inline Matrix3 operator*(Matrix3 m1, Matrix3 m2)
	{
		float newX1, newX2, newX3, newY1, newY2, newY3;
		newX1 = (m1.x1 * m2.x1) + (m1.x2 * m2.y1);
		newX2 = (m1.x1 * m2.x2) + (m1.x2 * m2.y2);
		newX3 = (m1.x1 * m2.x3) + (m1.x2 * m2.y3) + m1.x3;
		newY1 = (m1.y1 * m2.x1) + (m1.y2 * m2.y1);
		newY2 = (m1.y1 * m2.x2) + (m1.y2 * m2.y2);
		newY3 = (m1.y1 * m2.x3) + (m1.y2 * m2.y3) + m1.y3;
		Vector2 first(newX1, newY1);
		Vector2 second(newX2, newY2);
		Matrix3 m3 (first, second);
		m3.x3 = newX3;
		m3.y3 = newY3;
		return m3;

	}

	inline Vector2 operator*(Matrix3 m1, Vector2 v1)
	{
		float newX, newY;
		newX = (m1.x1 * v1.X) + (m1.x2 * v1.Y) + m1.x3;
		newY = (m1.y1 * v1.X) + (m1.y2 * v1.Y) + m1.y3;
		return Vector2(newX, newY);
	}

	inline Vector3 operator*(Matrix3 m1, Vector3 v1)
	{
		float newX, newY;
		newX = (m1.x1 * v1.X) + (m1.x2 * v1.Y) + m1.x3;
		newY = (m1.y1 * v1.X) + (m1.y2 * v1.Y) + m1.y3;
		return Vector3(newX, newY, 1.0f);
	}
}

#endif