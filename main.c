#include <raylib.h>

typedef struct PhysicsObject
{
	Vector3 position;
	Vector3 direction;
	int ID;
	float weight;
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

void renderPhysObjPosition(PhysicsObject* physobj)
{
	DrawSphere(physobj->position, 1, getPhysObjIDColour(physobj));
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

PhysicsObject newPhysicsObject(Vector3 pos, Vector3 direction)
{
	static int new_physobj_id = -1;
	new_physobj_id++;
	return (PhysicsObject){pos, direction, new_physobj_id, 0.5};
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

#include <stdint.h>

#include <stdlib.h>

#include <string.h>

typedef struct ChirpSegment
{
	uint16_t frequency;
	uint16_t length;
}
ChirpSegment;

AudioStream* getAudioStream()
{
	static AudioStream audio_stream;
	return &audio_stream;
}

void initAudioSystem()
{
	InitAudioDevice();
	(*getAudioStream()) = InitAudioStream(44100, 16, 1);
}
#define MAX_SAMPLES 512
#define MAX_SAMPLES_PER_UPDATE 4096
void playChirp(ChirpSegment* chirp)
{
	_beep(chirp->frequency, chirp->length);
}

int main()
{
	const int screenWidth = 600;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "raylib");

	Camera camera = { 0 };
	camera.position = (Vector3){ 10.0f, 10.0f, 8.0f };
	camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
	camera.fovy = 90.0f;
	camera.projection = CAMERA_PERSPECTIVE;
	
	SetCameraMode(camera, CAMERA_ORBITAL);

	SetTargetFPS(60);

	PhysicsObject test_obj = newPhysicsObject((Vector3){0, 0, 0}, (Vector3){3, 4, 5});

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
					ChirpSegment test_chirp = (ChirpSegment){600, 10};
					playChirp(&test_chirp);
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