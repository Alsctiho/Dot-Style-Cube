#include <iostream>
#include <cmath>
#include "math.h"
#include <iomanip>

#define PI 3.1415926f

float gem::radians(float degrees)
{
	return degrees / 180 * PI;
}

float gem::degrees(float radians)
{
	return radians * 180 / PI;
}

gem::vec2 gem::normalize(gem::vec2 vector)
{
	gem::vec2 result = gem::empty::Vec2;
	float magnitude = sqrt(vector.x * vector.x + vector.y * vector.y);
	result.x = vector.x / magnitude;
	result.y = vector.y / magnitude;

	return result;
}

gem::vec3 gem::normalize(gem::vec3 vector)
{
	vec3 result = gem::empty::Vec3;
	float magnitude = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	result.x = vector.x / magnitude;
	result.y = vector.y / magnitude;
	result.z = vector.z / magnitude;

	return result;
}

float gem::determinant(gem::vec2 &vector1, gem::vec2 &vector2)
{
	//a1b2 - a2b1
	return (vector1.x * vector2.y) - (vector1.y * vector2.x);
}

float gem::determinant(gem::vec3 &vector1, gem::vec3 &vector2, gem::vec3 &vector3)
{
	float firstPart = vector1.x * (vector2.y * vector3.z - vector3.y * vector2.z);
	float secondPart = vector1.y * (vector2.x * vector3.z - vector3.x * vector2.z);
	float thirdPart = vector1.z * (vector2.x * vector3.y - vector3.x * vector2.y);

	return firstPart - secondPart + thirdPart;
}

float gem::dot(const gem::vec2 &vector1, const gem::vec2 &vector2)
{ //a1 * b1 + a2 * b2
	return vector1.x * vector2.x + vector1.y * vector2.y;
}

float gem::dot(const gem::vec3 &vector1, const gem::vec3 &vector2)
{ //a1 * b1 + a2 * b2 + a3 * b3
	return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}

gem::vec4 gem::cross(const gem::mat4 &matrix, const gem::vec4 &vector)
{ //4X4 * 4X1 = 4*1
	gem::vec4 result = gem::empty::Vec4;

	for (int iii = 0; iii < 4; iii++)
	{
		for (int jjj = 0; jjj < 4; jjj++)
		{
			result.attribute[iii] += matrix.vector[iii].attribute[jjj] * vector.attribute[jjj];
		}
	}

	return result;
}

gem::mat4 gem::cross(const gem::mat4 &matrix1, const gem::mat4 &matrix2)
{ //4X4 * 4X4 = 4X4
	gem::mat4 result;
	result = gem::empty::Mat4;
	for (int iii = 0; iii < 4; iii++)
	{
		for (int jjj = 0; jjj < 4; jjj++)
		{
			for (int kkk = 0; kkk < 4; kkk++)
			{
				result.vector[iii].attribute[jjj]
					// ---- dot ||||
					+= matrix1.vector[iii].attribute[kkk] * matrix2.vector[kkk].attribute[jjj];
			}
		}
	}
	return result;
}