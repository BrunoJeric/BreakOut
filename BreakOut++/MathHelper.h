#pragma once
#include <Math.h>
namespace EngineSDL {
#define PI 3.14159265
#define DEG_TO_RAD PI/180.0f

	struct Vector2
	{
		float x;
		float y;

		Vector2(float _x = 0.0f, float _y = 0.0f) :x(_x), y(_y) {}

		float MagnitudeSqr() { return x * x + y * y; }
		float Magnitude() { return sqrt(x * x + y * y); }

		Vector2 Normalized() {
			float mag = Magnitude();
			return Vector2(x / mag, y / mag);
		}

		Vector2& operator +=(const Vector2& right) {
			x += right.x;
			y += right.y;

			return *this;
		}
		Vector2& operator -=(const Vector2& right) {
			x -= right.x;
			y -= right.y;

			return *this;
		}

	};
	inline Vector2 operator +(const Vector2& left, const Vector2& right) {
		return Vector2(left.x + right.x, left.y + right.y);
	}
	inline Vector2 operator -(const Vector2& left, const Vector2& right) {
		return Vector2(left.x - right.x, left.y - right.y);
	}
	inline Vector2 operator *(const Vector2& left, const float& right) {
		return Vector2(left.x * right, left.y * right);
	}


	inline Vector2 RotateVector(const Vector2& vec, float angle) {
		float radAngle = (float)(angle * DEG_TO_RAD);

		return Vector2((float)(vec.x * cos(radAngle) - vec.y * sin(radAngle)), (float)(vec.x * sin(radAngle) + vec.y * cos(radAngle)));
	}

	inline Vector2 Lerp(Vector2& start, Vector2& end, float time) {
		if (time <= 0.0f)
			return start;

		if (time >= 1.0f)
			return end;

		Vector2 dir = (end - start).Normalized();
		float mag = (end - start).Magnitude();

		return start + dir * mag * time;
	}

	const Vector2 VEC_ZERO = { 0.0f, 0.0f };
	const Vector2 VEC_ONE = { 1.0f, 1.0f };
	const Vector2 VEC_UP = { 0.0f, 1.0f };
	const Vector2 VEC_RIGHT = { 1.0f, 0.0f };
}