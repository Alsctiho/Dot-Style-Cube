//make a cube from scratch
//objective:
//implement interpolation
//convert between Normalized Device Coordinates and 2D array coordinates
//point-in-polygon
//make a triangle and square
//EBO (optional)
//can read file (optional)
//implement matrix and vector
//convert 3D model data to 4 units vector
//matrices multiplication 4X4 * 4X4 and 4X4 * 4X1
//translate, rotate
//rotate and strech a square
//convert transformed matrices to screen view, perspective projection matrix
//Field of view
//
//a cube
//implement shadow

#include <iostream>
#include <cmath> //sin(radians) = sin(degree * 180 / pi)
#include <limits>
#include "matrix.h"

#define CHARS_MAP ".,-~:;=!*#$@"

void cleanScreen(char (&screen)[constants::screenHeight][constants::screenWidth])
{
	for (int iii = 0; iii < constants::screenHeight; iii++)
	{
		for (int jjj = 0; jjj < constants::screenWidth; jjj++)
		{
			screen[iii][jjj] = ' ';
		}
	}
}

void printScreen(const char (&screen)[constants::screenHeight][constants::screenWidth])
{
	for (int iii = 0; iii < constants::screenHeight; iii++)
	{
		for (int jjj = 0; jjj < constants::screenWidth; jjj++)
		{
			putchar(screen[iii][jjj]);
		}
		putchar('\n');
	}
}

bool pointInTriangle(const gem::viewTriangle &triangle, const gem::vec2 &test)
{
	//using coordinates of triangle OAB and a testing point P to find wheather P is inside triangle
	gem::vec2 OA{triangle.point[1].x - triangle.point[0].x, triangle.point[1].y - triangle.point[0].y};
	gem::vec2 OB{triangle.point[2].x - triangle.point[0].x, triangle.point[2].y - triangle.point[0].y};
	gem::vec2 OP{test.x - triangle.point[0].x, test.y - triangle.point[0].y};
	using gem::determinant;
	//w1 and w2 are the scalars of the vector OB and OA
	//OP = w1 * OB + w2 * OA
	float w1 = determinant(OP, OB) / determinant(OA, OB);
	float w2 = determinant(OP, OA) / determinant(OB, OA);
	if (w1 > 1 || w1 < 0 || w2 > 1 || w2 < 0)
	{
		return false;
	}
	else if (w1 + w2 > 1)
	{
		return false;
	}
	else
	{
		//onlly if w1 + w2 < 1 AND 0 < w1 < 1 AND 0 < w2 < 1, testing point is inside triangle
		return true;
	}
}

gem::vec2 convertArrayToNDC(int inputCol, int inputRow)
{
	float convertedX = (inputCol - constants::screenColumns / 2.0f) / (constants::screenColumns / 2.0f);
	float convertedY = (-inputRow + constants::screenRows / 2.0f) / (constants::screenRows / 2.0f);

	return {convertedX, convertedY};
}

void interpolation(const gem::viewTriangle &triangle, char (&screen)[constants::screenHeight][constants::screenWidth])
{
	//using 3 given view points to detect array unit wheather inside the triangle, if so, input '1' in array
	for (int iii = 0; iii < constants::screenHeight; iii++)
	{
		for (int jjj = 0; jjj < constants::screenWidth; jjj++)
		{
			if (screen[iii][jjj] == '.')
				continue;
			if (pointInTriangle(triangle, convertArrayToNDC(jjj, iii)))
				screen[iii][jjj] = '.'; //can be used for lighting extension
		}
	}
}

gem::viewTriangle projection(const gem::modelTriangle &modelTriangle, const gem::mat4 &transform)
{
	gem::viewTriangle viewTriangle;

	//need a conversion, model triangle points --> vec4
	gem::vec4 point[3];
	for (int iii = 0; iii < 3; iii++)
	{
		point[iii] = {
			modelTriangle.point[iii].x,
			modelTriangle.point[iii].y,
			modelTriangle.point[iii].z,
			modelTriangle.point[iii].w};
	}

	//vector(point) transformation
	point[0] = gem::cross(transform, point[0]);
	//gem::printVec4(point[0]);
	point[1] = gem::cross(transform, point[1]);
	//gem::printVec4(point[1]);
	point[2] = gem::cross(transform, point[2]);
	//gem::printVec4(point[2]);

	viewTriangle.point[0] = {point[0].x / point[0].w, point[0].y / point[0].w};
	viewTriangle.point[1] = {point[1].x / point[1].w, point[1].y / point[1].w};
	viewTriangle.point[2] = {point[2].x / point[2].w, point[2].y / point[2].w};
	return viewTriangle;
}

int main()
{

	char screen[constants::screenHeight][constants::screenWidth]{};

	//local space
	//Element Buffer Objects
	gem::modelPoint pointEBO[8];
	pointEBO[0] = {-0.25f, -0.25f, 0.25f, 1.0f};
	pointEBO[1] = {0.25f, -0.25f, 0.25f, 1.0f};
	pointEBO[2] = {0.25f, 0.25f, 0.25f, 1.0f};
	pointEBO[3] = {-0.25f, 0.25f, 0.25f, 1.0f};
	pointEBO[4] = {-0.25f, -0.25f, -0.25f, 1.0f};
	pointEBO[5] = {0.25f, -0.25f, -0.25f, 1.0f};
	pointEBO[6] = {0.25f, 0.25f, -0.25f, 1.0f};
	pointEBO[7] = {-0.25f, 0.25f, -0.25f, 1.0f};

	gem::modelTriangle modelTriangle[12];
	//first triangle from +z
	modelTriangle[0].point[2] = pointEBO[0];
	modelTriangle[0].point[0] = pointEBO[1];
	modelTriangle[0].point[1] = pointEBO[2];

	//second triangle from +z
	modelTriangle[1].point[2] = pointEBO[0];
	modelTriangle[1].point[0] = pointEBO[3];
	modelTriangle[1].point[1] = pointEBO[2];

	//first triangle from +x
	modelTriangle[2].point[2] = pointEBO[1];
	modelTriangle[2].point[0] = pointEBO[2];
	modelTriangle[2].point[1] = pointEBO[6];

	//second triangle from +x
	modelTriangle[3].point[2] = pointEBO[1];
	modelTriangle[3].point[0] = pointEBO[6];
	modelTriangle[3].point[1] = pointEBO[5];

	//first triangle from +y
	modelTriangle[4].point[2] = pointEBO[7];
	modelTriangle[4].point[0] = pointEBO[3];
	modelTriangle[4].point[1] = pointEBO[2];

	//second triangle from +y
	modelTriangle[5].point[2] = pointEBO[7];
	modelTriangle[5].point[0] = pointEBO[6];
	modelTriangle[5].point[1] = pointEBO[2];

	//first triangle from -z
	modelTriangle[6].point[2] = pointEBO[4];
	modelTriangle[6].point[0] = pointEBO[5];
	modelTriangle[6].point[1] = pointEBO[7];

	//second triangle from -z
	modelTriangle[7].point[2] = pointEBO[5];
	modelTriangle[7].point[0] = pointEBO[6];
	modelTriangle[7].point[1] = pointEBO[7];

	//first triangle from -x
	modelTriangle[8].point[2] = pointEBO[0];
	modelTriangle[8].point[0] = pointEBO[3];
	modelTriangle[8].point[1] = pointEBO[7];

	//second triangle from -x
	modelTriangle[9].point[2] = pointEBO[0];
	modelTriangle[9].point[0] = pointEBO[4];
	modelTriangle[9].point[1] = pointEBO[7];

	//first triangle from -y
	modelTriangle[10].point[2] = pointEBO[0];
	modelTriangle[10].point[0] = pointEBO[1];
	modelTriangle[10].point[1] = pointEBO[4];

	//second triangle from -y
	modelTriangle[11].point[2] = pointEBO[1];
	modelTriangle[11].point[0] = pointEBO[4];
	modelTriangle[11].point[1] = pointEBO[5];

	//projection matrix is rarely changes, it is often best practice to set it outside the main loop only once.
	gem::mat4 proj = gem::perspective(gem::radians(constants::FOV), 1.0f, 0.1f, 100.0f);

	//std::cout << "This is perspective projection matrix" << std::endl;
	//gem::printMat4(proj);

	while (true)
	{
		cleanScreen(screen);

		static float degrees{0.0f};

		//transformation
		gem::mat4 trans{gem::identity::Mat4};
		trans = gem::rotate(trans, gem::radians(degrees), gem::normalize({2.0f, 1.0f, 1.0f}));
		trans = gem::translate(trans, gem::vec3{0.0f, -0.2f, -2.5f});
		//gem::printMat4(trans);

		//projection, this should be done by GPU
		trans = gem::cross(proj, trans);
		//gem::printMat4(trans);

		//first triangle from view perspective
		for (int i = 0; i < 12; i++)
		{
			gem::viewTriangle viewTriangle;
			viewTriangle = projection(modelTriangle[i], trans);
			interpolation(viewTriangle, screen);
		}
		std::cout << "Press Enter to continue.";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		printScreen(screen);

		degrees += 10;
	}

	return 0;
}