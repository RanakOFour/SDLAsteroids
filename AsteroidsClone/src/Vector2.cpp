#include "Vector2.h"
#include <math.h>

Vector2::Vector2()
{
	m_X = 0.0f;
	m_Y = 0.0f;
	m_Magnitude = 0.0f;
}

Vector2::Vector2(float x, float y)
{
	m_X = x;
	m_Y = y;
	m_Magnitude = sqrtf((x * x) + (y * y));
}

Vector2::~Vector2()
{
}

float Vector2::GetX()
{
	return m_X;
}

float Vector2::GetY()
{
	return m_Y;
}

void Vector2::SetX(float x)
{
	m_X = x;
	m_Magnitude = sqrtf((m_X * m_X) + (m_Y * m_Y));
}

void Vector2::SetY(float y)
{
	m_Y = y;
	m_Magnitude = sqrtf((m_X * m_X) + (m_Y * m_Y));
}

float Vector2::GetMagnitude()
{
	return m_Magnitude;
}

void Vector2::IncrementX(float increment)
{
	m_X += increment;
}

void Vector2::IncrementY(float increment)
{
	m_Y += increment;
}

Vector2 Vector2::GetDirection()
{
	if (m_X >= 0 && m_Y >= 0)
	{
		return Vector2(1, 1);
	}

	if (m_X >= 0)
	{
		return Vector2(1, -1);
	}

	if (m_Y >= 0)
	{
		return Vector2(-1, 1);
	}

	return Vector2(-1, -1);
}

Vector2 Vector2::Normalized()
{

	return Vector2((m_X / m_Magnitude), (m_Y / m_Magnitude));
}

Vector2 Vector2::operator+ (Vector2 other)
{
	return Vector2(m_X + other.m_X, m_Y + other.m_Y);
}

Vector2 Vector2::operator- (Vector2 other)
{
	return Vector2(m_X - other.m_X, m_Y - other.m_Y);
}

Vector2 Vector2::operator* (float x)
{
	return Vector2(m_X * x, m_Y * x);
}

void Vector2::operator+= (Vector2 other)
{
	m_X += other.m_X;
	m_Y += other.m_Y;
	m_Magnitude = sqrtf((m_X * m_X) + (m_Y * m_Y));
}

void Vector2::operator-= (Vector2 other)
{
	m_X -= other.m_X;
	m_Y -= other.m_Y;
	m_Magnitude = sqrtf((m_X * m_X) + (m_Y * m_Y));
}

Vector2 Vector2::operator*= (float x)
{
	m_X *= x;
	m_Y *= x;
	m_Magnitude = sqrtf((m_X * m_X) + (m_Y * m_Y));
	return *this;
}

bool Vector2::operator== (Vector2 other)
{
	if (this->m_X == other.m_X)
	{
		if (this->m_Y == other.m_Y)
		{
			return true;
		}
	}

	return false;
}