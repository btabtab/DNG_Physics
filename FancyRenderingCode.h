#ifndef FANCYRENDERING
#define FANCYRENDERING

#include <raylib.h>

#define SA (10*i)+120
#define SB (31*i)
#define SC (25*i)

void renderWireFrame(Vector3* points, int amount)
{
	for(int i = 0; i != amount-1; i++)
	{
		DrawLine3D(points[i], points[i+1], (Color){SA, 255 - SA, SA, 255});
	}
	int i = amount;
	DrawLine3D(points[0], points[amount-1], (Color){SA, 255 - SA, SA, 255});
}

void renderWireFrameRotated(Vector3* points, int amount, Vector3 center, Vector3 rotation)
{
	for(int i = 0; i != amount; i++)
	{
		DrawLine3D(
					rotatePointVector3(center, rotation, points[i]),
					rotatePointVector3(center, rotation, points[i+1]),
					(Color){SA, 255 - SA, SA, 255});
	}
	int i = amount;
	DrawLine3D(points[0], points[amount-1], WHITE);
}

void renderWireFrameRotatedDegrees(Vector3* points, int amount, Vector3 center, Vector3 rotation_degrees)
{
	for(int i = 0; i != amount-1; i++)
	{
		DrawLine3D(
					rotatePointVector3Degrees(center, rotation_degrees, points[i]),
					rotatePointVector3Degrees(center, rotation_degrees, points[i+1]),
					(Color){SA, 255 - SA, SA, 255});
	}
	int i = amount;
	DrawLine3D(
				rotatePointVector3Degrees(center, rotation_degrees, points[0]),
				rotatePointVector3Degrees(center, rotation_degrees, points[amount-1]),
				(Color){SA, 255 - SA, SA, 255});
}

void renderPolygonRotatedDegrees(Vector3* points, int amount, Vector3 center, Vector3 rotation_degrees)
{
	Vector3 poly_points[amount];
	for(int i = 0; i != amount-1; i++)
	{
		poly_points[i] = points[amount - i];
	}
	DrawTriangleStrip3D(poly_points, amount, RED);
}

void renderPointsAsCube(Vector3 position, Vector3 rotation, float dimensions)
{
	float a = 90;

	Vector3 top_points[] =
	{
		(Vector3){+dimensions, +dimensions, +dimensions},//1
		(Vector3){+dimensions, +dimensions, -dimensions},//2
		(Vector3){-dimensions, +dimensions, -dimensions},//3
		(Vector3){-dimensions, +dimensions, +dimensions},//4
		(Vector3){+dimensions, +dimensions, +dimensions},//1
	};
	Vector3 bot_points[] =
	{
		(Vector3){+dimensions, -dimensions, +dimensions},//1
		(Vector3){+dimensions, -dimensions, -dimensions},//2
		(Vector3){-dimensions, -dimensions, -dimensions},//3
		(Vector3){-dimensions, -dimensions, +dimensions},//4
		(Vector3){+dimensions, -dimensions, +dimensions},//1
	};

	for(int i = 0; i != 4; i++)
	{
		DrawLine3D(rotatePointVector3Degrees((Vector3){0, 0, 0}, rotation, top_points[i]), rotatePointVector3Degrees((Vector3){0, 0, 0}, rotation, bot_points[i]), RED);
	}
	renderWireFrameRotatedDegrees(top_points, 4, (Vector3){0, 0, 0}, rotation);
	renderWireFrameRotatedDegrees(bot_points, 4, (Vector3){0, 0, 0}, rotation);
}
#endif