#ifndef PHYSICSOBJECT
//starting to number the versions to keep track of stuff better.
#define PHYSICSOBJECT 1

#include <raylib.h>

#include <math.h>

Vector3 scaleVector(Vector3 vec, float scale)
{
	return (Vector3){vec.x * scale, vec.y * scale, vec.z * scale};
}

Vector2 rotatePointVector2(Vector2 center, float angle, float base_x, float base_y)
{
	Vector2 point = (Vector2){base_x, base_y};
	float s = sin(angle);
	float c = cos(angle);

	float temp_x = (point.x), temp_y = (point.y);

	// translate point back to origin:
	temp_x -= center.x;
	temp_y -= center.y;

	// rotate point
	float xnew = temp_x * c - temp_y * s;
	float ynew = temp_x * s + temp_y * c;

	// translate point back:
	(point.x) = xnew + center.x;
	(point.y) = ynew + center.y;
	return point;
}

Vector2 rotate2PointVector3(float center_x, float center_y, float angle, float base_x, float base_y)
{
	Vector2 point = (Vector2){base_x, base_y};
	float s = sin(angle);
	float c = cos(angle);

	float temp_x = (point.x), temp_y = (point.y);

	// translate point back to origin:
	temp_x -= center_x;
	temp_y -= center_y;

	// rotate point
	float xnew = temp_x * c - temp_y * s;
	float ynew = temp_x * s + temp_y * c;

	// translate point back:
	(point.x) = xnew + center_x;
	(point.y) = ynew + center_y;
	return point;
}

//roll pitch yaw
Vector3 rotate3DPoint(Vector3 center, Vector3 point, Vector3 rotation)
{
    float cosa = cos(rotation.y);
    float sina = sin(rotation.y);

    float cosb = cos(rotation.x);
    float sinb = sin(rotation.x);

    float cosc = cos(rotation.z);
    float sinc = sin(rotation.z);

    float Axx = cosa*cosb;
    float Axy = cosa*sinb*sinc - sina*cosc;
    float Axz = cosa*sinb*cosc + sina*sinc;

    float Ayx = sina*cosb;
    float Ayy = sina*sinb*sinc + cosa*cosc;
    float Ayz = sina*sinb*cosc - cosa*sinc;

    float Azx = -sinb;
    float Azy = cosb*sinc;
    float Azz = cosb*cosc;

	Vector3 ret;

    float px = point.x - center.x;
    float py = point.y - center.y;
    float pz = point.z - center.z;

        ret.x = Axx*px + Axy*py + Axz*pz;
        ret.y = Ayx*px + Ayy*py + Ayz*pz;
        ret.z = Azx*px + Azy*py + Azz*pz;
	return ret;
}

float clamp(float max, float min, float number)
{
	if(number < min)
	{
		return min;
	}
	if(number > max)
	{
		return max;
	}
	return number;
}

//roll pitch yaw
Vector3 rotate3DPointClamp(Vector3 center, Vector3 rotation, Vector3 point, float min, float max)
{
    float cosa = cos(rotation.y);
    float sina = sin(rotation.y);

    float cosb = cos(rotation.x);
    float sinb = sin(rotation.x);

    float cosc = cos(rotation.z);
    float sinc = sin(rotation.z);

    float Axx = cosa*cosb;
    float Axy = cosa*sinb*sinc - sina*cosc;
    float Axz = cosa*sinb*cosc + sina*sinc;

    float Ayx = sina*cosb;
    float Ayy = sina*sinb*sinc + cosa*cosc;
    float Ayz = sina*sinb*cosc - cosa*sinc;

    float Azx = -sinb;
    float Azy = cosb*sinc;
    float Azz = cosb*cosc;

	Vector3 ret;

    float px = point.x - center.x;
    float py = point.y - center.y;
    float pz = point.z - center.z;

        ret.x = Axx*px + Axy*py + Axz*pz;
        ret.y = Ayx*px + Ayy*py + Ayz*pz;
        ret.z = Azx*px + Azy*py + Azz*pz;
		ret.x = clamp(max, min, ret.x);
		ret.y = clamp(max, min, ret.y);
		ret.z = clamp(max, min, ret.z);
	return ret;
}
/*
This is the approximation of 1 degree
*/
#define APPROX_DEGREE_MULT (1.57 / 90)
//THE CURRENT APROXIMATE VALUE IS: [90 = 1.57f], 1.57 / 90 = ~0.0174
Vector3 rotatePointVector3Degrees(Vector3 center, Vector3 rotation, Vector3 points)
{
	Vector3 ret = rotate3DPoint(center, points, scaleVector(rotation, APPROX_DEGREE_MULT));
	// ret = scaleVector(ret, 0.0174);
	return ret;

}

Vector3 rotatePointVector3(Vector3 center, Vector3 rotation_in_degrees, Vector3 points)
{

	Vector3 ret = rotate3DPoint(center, points, rotation_in_degrees);
	return ret;

}

Vector3 clampVector(Vector3 vector, float max, float min)
{
	return (Vector3){clamp(max, min, vector.x), clamp(max, min, vector.y), clamp(max, min, vector.z)};
}

typedef struct PhysicsObject
{
	Vector3 position;
	Vector3 direction;
	int ID;
	float weight;
	Vector3 last_position;
}
PhysicsObject;

Color getPhysObjIDColour(PhysicsObject* physobj)
{
	return (Color){255 - physobj->ID * 3, 255 - physobj->ID * 2, 255 - physobj->ID * 4, 255};
}

Vector3 addVectors(Vector3 a, Vector3 b)
{
	return (Vector3){a.x + b.x, a.y + b.y, a.z + b.z};
}

Vector3 multiplyVectors(Vector3 a, Vector3 b)
{
	return (Vector3){a.x * b.x, a.y * b.y, a.z * b.z};
}

Vector3 invertVector(Vector3 a)
{
	return (Vector3){-a.x, -a.y, -a.z};
}

Vector3 findMidPoint(Vector3 a, Vector3 b)
{
	return (Vector3){(a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2};
}

void renderPhysObjPosition(PhysicsObject* physobj)
{
	DrawSphere(physobj->position, .5, getPhysObjIDColour(physobj));
}

void renderPhysObjLineFromZZZ(PhysicsObject* physobj)
{
	DrawLine3D(physobj->position, (Vector3){0, 0, 0}, getPhysObjIDColour(physobj));
}

void drawLineToPhysObjGroundMarker(PhysicsObject* physobj)
{
	DrawLine3D(physobj->position, (Vector3){physobj->position.x, 0, physobj->position.z}, getPhysObjIDColour(physobj));
}

void renderPhysObjGroundAlignedMarker(PhysicsObject* physobj)
{
	DrawPlane((Vector3){physobj->position.x, 0, physobj->position.z}, (Vector2){1.f, 1.f}, getPhysObjIDColour(physobj));
}

void renderPhysObjGroundAlignedMarkerToZZZ(PhysicsObject* physobj)
{
	DrawLine3D((Vector3){0, 0, 0}, (Vector3){physobj->position.x, 0, physobj->position.z}, getPhysObjIDColour(physobj));
}

void renderPhysObjDirection(PhysicsObject* physobj)
{
	DrawLine3D(physobj->position, addVectors(physobj->position, physobj->direction), getPhysObjIDColour(physobj));
}

void renderPhysObjDebug(PhysicsObject* physobj)
{
	renderPhysObjPosition(physobj);
	renderPhysObjLineFromZZZ(physobj);
	renderPhysObjGroundAlignedMarker(physobj);
	drawLineToPhysObjGroundMarker(physobj);
	renderPhysObjGroundAlignedMarkerToZZZ(physobj);
	renderPhysObjDirection(physobj);
}

PhysicsObject newPhysicsObject(Vector3 pos, Vector3 direction, float weight)
{
	static int new_physobj_id = -1;
	new_physobj_id++;
	return (PhysicsObject){pos, direction, new_physobj_id, weight, (Vector3){0, 0, 0}};
}

// PhysicsObject allocateNewPhysicsObject(Vector3 pos, Vector3 direction)
// {
// }

float subtractPercentageFromNumber(float number, float percent)
{
	return (100 - percent) / 100;
}
void updatePhysicsObjectWeight(PhysicsObject* physobj)
{
	physobj->direction.y -= (physobj->weight) / 10;
}
void updatePhysicsObjectDrag(PhysicsObject* physobj, float percent_lost)
{
	physobj->direction.x *= subtractPercentageFromNumber(physobj->direction.x, percent_lost);
	physobj->direction.y *= subtractPercentageFromNumber(physobj->direction.y, percent_lost);
	physobj->direction.z *= subtractPercentageFromNumber(physobj->direction.z, percent_lost);
}

void updatePhysicsObjectPosition(PhysicsObject* physobj)
{
	physobj->position = addVectors(physobj->position, physobj->direction);
}

void bouncePhysicsObject(PhysicsObject* physobj, Vector3 direction)
{
	physobj->direction = multiplyVectors(physobj->direction, direction);
}

//decay here is the amount that that the object's "bounce energy" will diminish.
void bouncePhysicsObjectWithDecay(PhysicsObject* physobj, Vector3 direction, float decay_amount)
{
	physobj->direction = multiplyVectors(physobj->direction, direction);
}

void renderRoom(int dimensions)
{
	// Vector3 points[8] =
	// {
	// };
	/*
	++ | +-
	+- | --
	-- | -+
	-+ | ++
	*/
	DrawPlane((Vector3){0, -0.25, 0}, (Vector2){dimensions * 2, dimensions * 2}, (Color){25, 75, 25, 125});
	{
		DrawLine3D((Vector3){+dimensions, 0, +dimensions}, (Vector3){+dimensions, dimensions, +dimensions}, WHITE);
		DrawLine3D((Vector3){-dimensions, 0, +dimensions}, (Vector3){-dimensions, dimensions, +dimensions}, WHITE);
		DrawLine3D((Vector3){+dimensions, 0, -dimensions}, (Vector3){+dimensions, dimensions, -dimensions}, WHITE);
		DrawLine3D((Vector3){-dimensions, 0, -dimensions}, (Vector3){-dimensions, dimensions, -dimensions}, WHITE);
	}

		DrawLine3D((Vector3){-dimensions, 0, -dimensions}, (Vector3){+dimensions, dimensions, -dimensions}, BLUE);
		DrawLine3D((Vector3){+dimensions, 0, -dimensions}, (Vector3){-dimensions, dimensions, -dimensions}, BLUE);

		DrawLine3D((Vector3){-dimensions, 0, +dimensions}, (Vector3){-dimensions, dimensions, -dimensions}, GREEN);
		DrawLine3D((Vector3){-dimensions, 0, -dimensions}, (Vector3){-dimensions, dimensions, +dimensions}, GREEN);

		DrawLine3D((Vector3){+dimensions, 0, +dimensions}, (Vector3){+dimensions, dimensions, -dimensions}, RED);
		DrawLine3D((Vector3){+dimensions, 0, -dimensions}, (Vector3){+dimensions, dimensions, +dimensions}, RED);

		DrawLine3D((Vector3){-dimensions, 0, +dimensions}, (Vector3){+dimensions, dimensions, +dimensions}, ORANGE);
		DrawLine3D((Vector3){+dimensions, 0, +dimensions}, (Vector3){-dimensions, dimensions, +dimensions}, ORANGE);

}

float getPhysicsObjectSpeed(PhysicsObject* physobj)
{
	float avg = 0.f;
	avg += (physobj->position.x + physobj->last_position.x) / 2;
	avg += (physobj->position.y + physobj->last_position.y) / 2;
	avg += (physobj->position.z + physobj->last_position.z) / 2;
	return (avg / 3);
}

#include <stdint.h>

#include <stdlib.h>

#include <string.h>

int PhysicsDemo()
{
	const int screenWidth = 600;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "PhysicsDemo");

	Camera camera = { 0 };
	camera.position = (Vector3){ 10.0f, 10.0f, 8.0f };
	camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
	camera.fovy = 90.0f;
	camera.projection = CAMERA_PERSPECTIVE;
	
	SetCameraMode(camera, CAMERA_ORBITAL);

	SetTargetFPS(60);

	PhysicsObject test_obj = newPhysicsObject((Vector3){0, 0, 0}, (Vector3){3, 4, 5}, .5);

	float bounce_boundary = 500.f;
	// float bounce_boundary_change = 10.f;

	while (!WindowShouldClose())
	{
		BeginDrawing();

			ClearBackground(BLACK);

			BeginMode3D(camera);
			{

				// if(bounce_boundary < 10 || bounce_boundary > 1000)
				// {
				// 	bounce_boundary_change = (-bounce_boundary_change);
				// }
				// bounce_boundary += bounce_boundary_change;

				renderRoom(bounce_boundary);

				renderPhysObjPosition(&test_obj);
				renderPhysObjLineFromZZZ(&test_obj);
				renderPhysObjGroundAlignedMarker(&test_obj);
				drawLineToPhysObjGroundMarker(&test_obj);
				renderPhysObjGroundAlignedMarkerToZZZ(&test_obj);
				renderPhysObjDirection(&test_obj);

				updatePhysicsObjectPosition(&test_obj);
				updatePhysicsObjectWeight(&test_obj);
				if(test_obj.position.y < 0.f)
				{
					// ChirpSegment test_chirp = (ChirpSegment){600, 10};
					// playChirp(&test_chirp);
					bouncePhysicsObject(&test_obj, (Vector3){1, -1, 1});
				}
				if(test_obj.position.x < -bounce_boundary || test_obj.position.x > bounce_boundary)
				{
					bouncePhysicsObject(&test_obj, (Vector3){-1, 1, 1});
				}
				if(test_obj.position.z < -bounce_boundary || test_obj.position.z > bounce_boundary)
				{
					bouncePhysicsObject(&test_obj, (Vector3){1, 1, -1});
				}
				// DrawGrid(1000, 1);
				camera.target = test_obj.position;
				if(IsKeyDown(KEY_LEFT_SHIFT))
				{
					UpdateCamera(&camera);
					camera.position = addVectors(test_obj.position, (Vector3){25, 25, 25});
				}
				else
				{
					camera.position = (Vector3){500, 500, 500};
				}
			}
			EndMode3D();

			DrawFPS(10, 10);

		EndDrawing();
	}
	CloseWindow();
	return 0;
}
#endif