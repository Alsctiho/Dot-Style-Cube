#pragma once
#include <iostream>
#include "math.h"

namespace constants
{
	constexpr float FOV{ 45.0f };	//Field of View in degrees
	constexpr float nearPlane{ 0.1f };
	constexpr float farPlane{ 100.0f };
	constexpr float pi{ 3.14159f };

	constexpr int screenWidth{ 120 };
	constexpr int screenColumns{ screenWidth - 1 };
	constexpr int screenHeight{ 60 };
	constexpr int screenRows{ screenHeight - 1 };
}

namespace gem
{
	struct modelPoint
	{
		union
		{
			struct
			{
				float attribute[4];
			};

			struct
			{
				float x, y, z, w;
			};
		};
	};

	struct ViewPoint 
	{
		union
		{
			struct
			{
				float attribute[2];
			};

			struct
			{
				float x, y;
			};
		};
	};


	struct modelTriangle
	{
		modelPoint point[3];
	};

	struct viewTriangle
	{
		ViewPoint point[3];
	};

	void printVec4(const gem::vec4&);
	void printMat4(const gem::mat4&);

	mat4 scale(const mat4&, const vec3&);
	mat4 rotate(const mat4&, float, const vec3&);
	mat4 translate(const mat4&, const vec3&);
	
	mat4 perspective(float, float, float, float);
}
