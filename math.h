#pragma once

namespace gem
{
    struct vec2
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

	struct vec3
	{
		union
		{
			struct
			{
				float attribute[3];
			};

			struct
			{
				float x, y, z;
			};
		};
	};

	struct vec4 
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

    struct mat2 
	{
		vec2 vector[2];
	};

	struct mat3 
	{
		vec3 vector[3];
	};

	struct mat4 
	{
		vec4 vector[4];
	};

    float radians(float);
	float degrees(float);

	vec2 normalize(gem::vec2);
	vec3 normalize(gem::vec3);

	float determinant(vec2&, vec2&);
	float determinant(vec3&, vec3&, vec3&);

	float dot(const vec2&, const vec2&);
	float dot(const vec3&, const vec3&);

	vec4 cross(const mat4&, const vec4&);
	mat4 cross(const mat4&, const mat4&);

    namespace empty
	{
		const vec2 Vec2{ 0.0f, 0.0f };
		const vec3 Vec3{ 0.0f, 0.0f, 0.0f };
		const vec4 Vec4{ 0.0f, 0.0f, 0.0f, 0.0f };

		const mat3 Mat3{
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
		};

		const mat4 Mat4{
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
		};
	}

	namespace identity
	{
		const mat3 Mat3{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
		};

		const mat4 Mat4{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
		};
	}
}