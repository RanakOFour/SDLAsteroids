#pragma once
#define H_VECTOR2

class Vector2
{
private:
	float m_X;
	float m_Y;
	float m_Magnitude;

public:
	Vector2();
	Vector2(float x, float y);
	~Vector2();
	float GetX();
	float GetY();
	float GetMagnitude();
	Vector2 GetDirection();
	void SetX(float x);
	void SetY(float y);
	void IncrementX(float increment);
	void IncrementY(float increment);
	Vector2 Normalized();
	Vector2 operator+ (Vector2 other);
	Vector2 operator- (Vector2 other);
	void operator+= (Vector2 other);
	void operator-= (Vector2 other);
	void operator*= (float x);
};