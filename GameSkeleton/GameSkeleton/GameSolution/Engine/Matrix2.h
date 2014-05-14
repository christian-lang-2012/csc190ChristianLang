#ifndef MATRIX_H
#define MATRIX_H
#include "Vector2.h"

using Engine::Vector2;

class Matrix2
{
public:	
	float x1, x2, y1, y2;
	Matrix2()
	{
		x1 = 1;
		x2 = 0;
		y1 = 0;
		x1 = 1;
	}

	Matrix2(Vector2 vector1, Vector2 vector2)
	{
		x1 = vector1.X;
		y1 = vector1.Y;
		x2 = vector2.X;
		y2 = vector2.Y;
	}

			operator float*() 
		{
			return &x1;
		}

	friend inline Matrix2 operator*(Matrix2 m1, Matrix2 m2);
	friend inline Vector2 operator*(Matrix2 m1, Vector2 v1);

	inline Matrix2 Rotation(Matrix2 m1, float angle)
	{
		Vector2 first(cosf(angle), sinf(angle));
		Vector2 second(-sinf(angle), cosf(angle));
		Matrix2 rotation(first, second);
		return m1 * rotation;
	}

	inline Matrix2 Scale(Matrix2 m1, float scale)
	{
		Vector2 first(m1.x1 * scale, m1.y1);
		Vector2 second(m1.x2, m1.y2 * scale);

		return Matrix2(first, second);
	}

	inline Matrix2 ScaleX(Matrix2 m1, float scale)
	{
		Vector2 first(m1.x1 * scale, m1.y1);
		Vector2 second(m1.x2, m1.y2);

		return Matrix2 (first, second);
	}

	inline Matrix2 ScaleY(Matrix2 m1, float scale)
	{
		Vector2 first(m1.x1, m1.y1);
		Vector2 second(m1.x2, m1.y2 * scale);
		return Matrix2 (first, second);
	}
};


inline Matrix2 operator*(Matrix2 m1, Matrix2 m2)
{
	float newX1, newX2, newY1, newY2;
	newX1 = (m1.x1 * m2.x1) + (m1.x2 * m2.y1);
	newX2 = (m1.x1 * m2.x2) + (m1.x2 * m2.y2);
	newY1 = (m1.y1 * m2.x1) + (m1.y2 * m2.y1);
	newY2 = (m1.y1 * m2.x2) + (m1.y2 + m2.y2);

	Vector2 first(newX1, newY1);
	Vector2 second(newX2, newY2);
	return Matrix2(first, second);

}

inline Vector2 operator*(Matrix2 m1, Vector2 v1)
{
	float newX, newY;
	newX = (m1.x1 * v1.X) + (m1.x2 * v1.Y);
	newY = (m1.y1 * v1.X) + (m1.y2 * v1.Y);
	return Vector2 (newX, newY);
}

#endif