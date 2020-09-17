#pragma once
#include <Math.h>
#define PI 3.14159265
#define DEG_TO_RAD PI/180.0f

struct Vector2
{
	float x;
	float y;

	Vector2(float _x=0.0f, float _y=0.0f) :x(_x),y(_y){}

	float MagnitudeSqr() { return x * x + y * y; }
	float Magnitude() { return sqrt(x * x + y * y); }

	Vector2 Normalized() {
		float mag = Magnitude();
		return Vector2(x / mag, y / mag);
	}

};
inline Vector2 operator +(const Vector2& left, const Vector2& right) {
	return Vector2(left.x + right.x, left.y + right.y);
}
inline Vector2 operator -(const Vector2& left, const Vector2& right) {
	return Vector2(left.x - right.x, left.y - right.y);
}

inline Vector2 RotateVector(Vector2& vec, float angle) {
	float radAngle = (float)(angle * DEG_TO_RAD);
	return Vector2((float)(vec.x * cos(radAngle) - vec.y * sin(radAngle)), (float)(vec.x * sin(radAngle) + vec.y * cos(radAngle)));

}