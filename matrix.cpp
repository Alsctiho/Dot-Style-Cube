#include <iostream>
#include <cmath>
#include "matrix.h"
#include <iomanip>

void gem::printVec4(const gem::vec4& vector) {
	std::cout << std::setprecision(4);
	for (int row = 0; row < 4; row++) {
		std::cout << vector.attribute[row] << '\t';
	}
	std::cout << std::endl;
}


void gem::printMat4(const gem::mat4& matrix) {
	std::cout << std::setprecision(4);
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			std::cout << matrix.vector[row].attribute[col] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

gem::mat4 gem::scale(const gem::mat4& matrix, const gem::vec3& scale) {
	gem::mat4 scaleMat = gem::empty::Mat4;

	scaleMat.vector[0].x = scale.x;
	scaleMat.vector[1].y = scale.y;
	scaleMat.vector[2].z = scale.z;
	scaleMat.vector[3].w = 1.0f;

	return gem::cross(scaleMat, matrix);
}

gem::mat4 gem::rotate(const gem::mat4& matrix, float radians, const gem::vec3& axis) {
	//rotate with an arbitrary axis
	//we pass in a matrix, then this matrix will rotate with the axis, finally return the matrix after rotation
	gem::mat4 rotationMat = gem::identity::Mat4;
	float cosine = cos(radians);
	float sine = sin(radians);
	rotationMat.vector[0].x = cosine + axis.x * axis.x * (1 - cosine);
	rotationMat.vector[0].y = axis.x * axis.y * (1 - cosine) - axis.z * sine;
	rotationMat.vector[0].z = axis.x * axis.z * (1 - cosine) + axis.y * sine;
	
	rotationMat.vector[1].x = axis.y * axis.x * (1 - cosine) + axis.z * sine;
	rotationMat.vector[1].y = cosine + axis.y * axis.y * (1 - cosine);
	rotationMat.vector[1].z = axis.y * axis.z * (1 - cosine) - axis.x * sine;

	rotationMat.vector[2].x = axis.z * axis.x * (1 - cosine) - axis.y * sine;
	rotationMat.vector[2].y = axis.z * axis.y * (1 - cosine) + axis.x * sine;
	rotationMat.vector[2].z = cosine + axis.z * axis.z * (1 - cosine);

	//update rotation to trans
	//Am I in the right order? Both are not I expected
	return gem::cross(rotationMat, matrix);
}

gem::mat4 gem::translate(const gem::mat4& matrix, const gem::vec3& translate) {
	//the matrix should be a identity matrix, this function just simulates glm::translate
	gem::mat4 translationMat = gem::identity::Mat4;
	translationMat.vector[0].w = translate.x;
	translationMat.vector[1].w = translate.y;
	translationMat.vector[2].w = translate.z;

	return gem::cross(translationMat, matrix);
}

gem::mat4 gem::perspective(float fovy, float aspect, float zNear, float zFar) {
	gem::mat4 projection = gem::empty::Mat4;
	//fovy is in radians
	const float tanHalfFovy = tan(fovy / 2);

	projection.vector[0].x = 1 / (aspect * tanHalfFovy);
	projection.vector[1].y = 1 / tanHalfFovy;
	projection.vector[2].z = zNear / (zNear - zFar);
	projection.vector[2].w = (zNear * zFar) / (zNear - zFar);
	projection.vector[3].z = -1.0f;

	return projection;
}