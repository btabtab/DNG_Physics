
/*the Airframe component has failed completly.*/
#ifndef AIRFRAME
#define AIRFRAME

#include "PhysicsObject.h"

typedef struct AirFrame
{
	PhysicsObject physobj;

	float pitch_angle;
	float roll_angle;
	float bearing;

	float wing_surface_area;
	float stability;
	Vector3 nose_direction;
	Vector3 up_direction;
	float wingsweep;
	float max_speed;
}
AirFrame;
#include <stdlib.h>

void renderAirFrameWingSurfaceArea(AirFrame* airframe)
{
	// _beep(400, 1);
	DrawSphere(airframe->physobj.position, .5, GREEN);
}

void renderAirFrameNoseDirection(AirFrame* airframe)
{
	DrawLine3D(airframe->physobj.position, addVectors(airframe->physobj.position, airframe->nose_direction), BLUE);
}

void renderAirFrameUpDirection(AirFrame* airframe)
{
	DrawLine3D(airframe->physobj.position, addVectors(airframe->physobj.position, airframe->up_direction), RED);
}
void renderAirFrameWings(AirFrame* airframe)
{
	DrawLine3D(airframe->physobj.position, addVectors(airframe->physobj.position, (Vector3){+airframe->wing_surface_area, 0, 0}), ORANGE);
	DrawLine3D(airframe->physobj.position, addVectors(airframe->physobj.position, (Vector3){-airframe->wing_surface_area, 0, 0}), ORANGE);
}

AirFrame newAirFrame(PhysicsObject physobj, float wing_surface_area, float stability, Vector3 nose_dir, Vector3 up_dir, float sweep, float max_speed)
{
	return (AirFrame){physobj, 0, 0, 0, wing_surface_area, stability, nose_dir, up_dir, sweep, max_speed};
}

void renderAirFrameData(AirFrame* airframe)
{
	// renderPhysObjDebug(&airframe->physobj);
	// renderAirFrameWingSurfaceArea(airframe);
	renderAirFrameNoseDirection(airframe);
	renderAirFrameUpDirection(airframe);
	renderAirFrameWings(airframe);

	// renderAirFrameNoseDirectionWithRotation(airframe);
}

void updateAirFrame(AirFrame* airframe)
{
}

int AirframeDemo()
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
	AirFrame test_af;
	
	{
		PhysicsObject test_obj = newPhysicsObject((Vector3){0, 200, 0}, (Vector3){3, 0, 5}, 0.5);
		test_af = newAirFrame(test_obj, 1.f, 10.f, (Vector3){0, 0, 1}, (Vector3){0, 1, 0}, 1, 6);
	}

	float bounce_boundary = 500.f;
	// float bounce_boundary_change = 10.f;

	while (!WindowShouldClose())
	{
		if(IsKeyDown(KEY_L))
		{
			UpdateCamera(&camera);
		}
		BeginDrawing();

			ClearBackground(BLACK);

			BeginMode3D(camera);
			{
				// if(bounce_boundary < 10 || bounce_boundary > 1000)
				// {
				// 	bounce_boundary_change = (-bounce_boundary_change);
				// }
				// bounce_boundary += bounce_boundary_change;

				updateAirFrame(&test_af);
				renderAirFrameData(&test_af);
				renderRoom(bounce_boundary);
				renderPhysObjDebug(&test_af.physobj);

				#define PITCH_RATE 0.02
				{
					if(IsKeyPressed(KEY_W))
					{
						test_af.pitch_angle += 0.025;
					}
					if(IsKeyDown(KEY_S))
					{
						test_af.pitch_angle -= 0.025;
					}
					if(IsKeyDown(KEY_A))
					{
						//rotate nose direction down.
						test_af.roll_angle += 0.025;
					}
					if(IsKeyDown(KEY_D))
					{
						//rotate nose direction down.
						test_af.roll_angle -= 0.025;
					}

					// if(test_af.physobj.position.y < 0.f)
					// {
					// 	// ChirpSegment test_chirp = (ChirpSegment){600, 10};
					// 	// playChirp(&test_chirp);
					// 	bouncePhysicsObject(&test_af.physobj, (Vector3){1, -1, 1});
					// }
					// if(test_af.physobj.position.x < -bounce_boundary || test_af.physobj.position.x > bounce_boundary)
					// {
					// 	bouncePhysicsObject(&test_af.physobj, (Vector3){-1, 1, 1});
					// }
					// if(test_af.physobj.position.z < -bounce_boundary || test_af.physobj.position.z > bounce_boundary)
					// {
					// 	bouncePhysicsObject(&test_af.physobj, (Vector3){1, 1, -1});
					// }
					// DrawGrid(1000, 1);
					camera.target = test_af.physobj.position;

					if(IsKeyDown(KEY_LEFT_SHIFT))
					{
						camera.position = addVectors(test_af.physobj.position, (Vector3){5, 5, 5});
					}
					else
					{
						camera.position = (Vector3){500, 500, 500};
					}
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