#include "PhysicsObject.h"

#define SA (10 * i) + 120
#define SB (31 * i)
#define SC (25 * i)

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

void spinningDots();
void rotateableRoom();
void simpleFighterDemo();
int main()
{
	// rotateableRoom();
	// spinningDots();
	// AirframeDemo();
	// PhysicsDemo();
}

//This exists purely to test rotation based operations.
void spinningDots()
{
	const int screenWidth = 600;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "spinningDots");

	Camera camera = { 0 };
	camera.position = (Vector3){ 10.0f, 10.0f, 8.0f };
	camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
	camera.fovy = 90.0f;
	camera.projection = CAMERA_PERSPECTIVE;
	
	SetCameraMode(camera, CAMERA_ORBITAL);

	SetTargetFPS(60);

	// PhysicsObject test_obj = newPhysicsObject((Vector3){0, 0, 0}, (Vector3){3, 4, 5}, 0.5);

	// float bounce_boundary = 500.f;
	// float bounce_boundary_change = 10.f;

	float dimensions = 5.f;

	Vector3 points[8] =
	{
		(Vector3){+dimensions, -dimensions, +dimensions},
		(Vector3){-dimensions, -dimensions, +dimensions},
		(Vector3){+dimensions, -dimensions, -dimensions},
		(Vector3){-dimensions, -dimensions, -dimensions},

		(Vector3){+dimensions, +dimensions, +dimensions},
		(Vector3){-dimensions, +dimensions, +dimensions},
		(Vector3){+dimensions, +dimensions, -dimensions},
		(Vector3){-dimensions, +dimensions, -dimensions},
	};

	float theta;
	while (!WindowShouldClose())
	{
		BeginDrawing();
			ClearBackground(BLACK);

			BeginMode3D(camera);
			{
				theta += .025;
				#define SA (10 * i) + 120
				#define SB (31 * i)
				#define SC (25 * i)
				for(int i = 0; i != 8; i++)
				{
					DrawSphere(rotatePointVector3((Vector3){0, 0, 0}, (Vector3){theta, 0, 0}, points[i]), .5, (Color){SB, SA, SA,	255});
					DrawSphere(rotatePointVector3((Vector3){0, 0, 0}, (Vector3){0, theta, 0}, points[i]), .5, (Color){SA, SB, SA,	255});
					DrawSphere(rotatePointVector3((Vector3){0, 0, 0}, (Vector3){0, 0, theta}, points[i]), .5, (Color){SA, SA, SB,	255});

					DrawSphere(rotatePointVector3((Vector3){0, 0, 0}, (Vector3){0, theta, theta}, points[i]), .5, (Color){SA, SB, SB,	255});
					DrawSphere(rotatePointVector3((Vector3){0, 0, 0}, (Vector3){theta, 0, theta}, points[i]), .5, (Color){SB, SA, SB,	255});
					DrawSphere(rotatePointVector3((Vector3){0, 0, 0}, (Vector3){theta, theta, 0}, points[i]), .5, (Color){SB, SB, SA,	255});

					DrawSphere(rotatePointVector3((Vector3){0, 0, 0}, (Vector3){theta, theta, theta}, points[i]), .5, (Color){SC, SC, SC,	255});

					DrawSphere(points[i], .5, (Color){31 * i, 31 * i, (10 * i) + 120, 255});
				}
			}
			EndMode3D();

			DrawFPS(10, 10);

		EndDrawing();
	}
	CloseWindow();
	// return 0;
}

void rotateableRoom()
{
	const int screenWidth = 600;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "rotateableRoom");

	Camera camera = { 0 };
	camera.position = (Vector3){ 10.0f, 10.0f, 8.0f };
	camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
	camera.fovy = 90.0f;
	camera.projection = CAMERA_PERSPECTIVE;
	
	SetCameraMode(camera, CAMERA_ORBITAL);

	SetTargetFPS(60);

	// PhysicsObject test_obj = newPhysicsObject((Vector3){0, 0, 0}, (Vector3){3, 4, 5}, 0.5);

	// float bounce_boundary = 500.f;
	// float bounce_boundary_change = 10.f;

	float dimensions = 5.f;

	// Vector3 points[8] =
	// {
	// 	(Vector3){+dimensions, -dimensions, +dimensions},
	// 	(Vector3){-dimensions, -dimensions, +dimensions},
	// 	(Vector3){+dimensions, -dimensions, -dimensions},
	// 	(Vector3){-dimensions, -dimensions, -dimensions},

	// 	(Vector3){+dimensions, +dimensions, +dimensions},
	// 	(Vector3){-dimensions, +dimensions, +dimensions},
	// 	(Vector3){+dimensions, +dimensions, -dimensions},
	// 	(Vector3){-dimensions, +dimensions, -dimensions},
	// };
	Vector3 points[] =
	{
		(Vector3){+dimensions, -dimensions, +dimensions},//1
		(Vector3){+dimensions, -dimensions, -dimensions},//2
		(Vector3){-dimensions, -dimensions, -dimensions},//3
		(Vector3){-dimensions, -dimensions, +dimensions},//4
		(Vector3){+dimensions, -dimensions, +dimensions},//1

		(Vector3){+dimensions, +dimensions, +dimensions},//5
		(Vector3){-dimensions, +dimensions, +dimensions},//6
		(Vector3){-dimensions, +dimensions, -dimensions},//7
		(Vector3){+dimensions, +dimensions, -dimensions},//8
	};

	int point_amount = sizeof(points) / sizeof(*points);

	Vector3 theta = {0.f, 0.f, 0.f};

	while (!WindowShouldClose())
	{
		static float g = 0;
		BeginDrawing();
			ClearBackground(BLACK);

			BeginMode3D(camera);
			{
				if(IsKeyDown(KEY_R))
				{
					if(IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT))
					{
						theta.x = 0.f;
					}
					if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN))
					{
						theta.y = 0.f;
					}
					if(IsKeyPressed(KEY_K) || IsKeyPressed(KEY_L))
					{
						theta.z = 0.f;
					}
				}
				
				theta.x -= (((float)IsKeyPressed(KEY_LEFT	)) / 3) + ((((float)IsKeyDown(KEY_A)) * 3));
				theta.x += (((float)IsKeyPressed(KEY_RIGHT	)) / 3) + ((((float)IsKeyDown(KEY_D)) * 3));

				theta.y -= (((float)IsKeyPressed(KEY_UP		)) / 3) + ((((float)IsKeyDown(KEY_W)) * 3));
				theta.y += (((float)IsKeyPressed(KEY_DOWN	)) / 3) + ((((float)IsKeyDown(KEY_S)) * 3));

				theta.z -= (((float)IsKeyPressed(KEY_K		)) / 3) + ((((float)IsKeyDown(KEY_Q)) * 3));
				theta.z += (((float)IsKeyPressed(KEY_L		)) / 3) + ((((float)IsKeyDown(KEY_E)) * 3));


				#define SA (10 * i) + 120
				#define SB (31 * i)
				#define SC (25 * i)

				// renderWireFrame(points, 4);
				{
					renderPointsAsCube((Vector3){0, 0, 0}, theta, 5.f);
					// renderPointsAsCube((Vector3){0, 0, 0}, theta, 2.5f);
				}



				// renderWireFrameRotated(points, 4, (Vector3){0, 0, 0}, (Vector3){1, 1, 0});
				// renderWireFrameRotated(points, 4, (Vector3){0, 0, 0}, (Vector3){1, 1, 1});
				// renderWireFrame(points+4, 4);

				// for(int i = 0; i != 4; i++)
				// {
				// 	Vector3 cols[2] =
				// 	{
				// 		{(255 / point_amount) * i, (255 / point_amount) * i, (255 / point_amount) * i},
				// 		{(255 / point_amount) * i+1, (255 / point_amount) * i+1, (255 / point_amount) * i+1}
				// 	};
				// 	Color col[2] =
				// 	{
				// 		(Color){SA, 255 - SA, SA, 255},
				// 		(Color){cols[1].x, cols[1].y - 10, cols[1].z * sqrt(cols[0].y), 255}
				// 	};
				// 	Vector3 res_point = rotatePointVector3((Vector3){0, 0, 0}, (Vector3){theta.x, theta.z, theta.y}, points[i]);
				// 	Vector3 new_point = rotatePointVector3((Vector3){0, 0, 0}, (Vector3){theta.x, theta.z, theta.y}, points[i+1]);
				// 	// DrawSphere(res_point, .5, (Color){SB, SA, SA,	255});
				// 	DrawLine3D(res_point, new_point, col[0]);
				// }
			}
			EndMode3D();
			// #include <string.h>
			// #include <stdlib.h>
			// #include <stdio.h>
			char* buff[10];
			gcvt(g, 7, buff);
			DrawText(buff, 0, 40, 10, RED);
			DrawFPS(10, 10);

		EndDrawing();
	}
	CloseWindow();
	// return 0;

}

void simpleFighterDemo()
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

		// PhysicsObject test_obj = newPhysicsObject((Vector3){0, 0, 0}, (Vector3){3, 4, 5}, 0.5);

		// float bounce_boundary = 500.f;
		// float bounce_boundary_change = 10.f;

		float dimensions = 5.f;

		Vector3 points[8] =
		{
			(Vector3){+dimensions, -dimensions, +dimensions},
			(Vector3){-dimensions, -dimensions, +dimensions},
			(Vector3){+dimensions, -dimensions, -dimensions},
			(Vector3){-dimensions, -dimensions, -dimensions},

			(Vector3){+dimensions, +dimensions, +dimensions},
			(Vector3){-dimensions, +dimensions, +dimensions},
			(Vector3){+dimensions, +dimensions, -dimensions},
			(Vector3){-dimensions, +dimensions, -dimensions},
		};

		float theta;
		while (!WindowShouldClose())
		{
			BeginDrawing();
				ClearBackground(BLACK);

				BeginMode3D(camera);
				{
					theta += .025;
					#define SA (10 * i) + 120
					#define SB (31 * i)
					#define SC (25 * i)
					for(int i = 0; i != 8; i++)
					{
						DrawSphere(rotatePointVector3((Vector3){0, 0, 0}, (Vector3){theta, 0, 0}, points[i]), .5, (Color){SB, SA, SA,	255});
						DrawSphere(rotatePointVector3((Vector3){0, 0, 0}, (Vector3){0, theta, 0}, points[i]), .5, (Color){SA, SB, SA,	255});
						DrawSphere(rotatePointVector3((Vector3){0, 0, 0}, (Vector3){0, 0, theta}, points[i]), .5, (Color){SA, SA, SB,	255});

						DrawSphere(rotatePointVector3((Vector3){0, 0, 0}, (Vector3){0, theta, theta}, points[i]), .5, (Color){SA, SB, SB,	255});
						DrawSphere(rotatePointVector3((Vector3){0, 0, 0}, (Vector3){theta, 0, theta}, points[i]), .5, (Color){SB, SA, SB,	255});
						DrawSphere(rotatePointVector3((Vector3){0, 0, 0}, (Vector3){theta, theta, 0}, points[i]), .5, (Color){SB, SB, SA,	255});

						DrawSphere(rotatePointVector3((Vector3){0, 0, 0}, (Vector3){theta, theta, theta}, points[i]), .5, (Color){SC, SC, SC,	255});

						DrawSphere(points[i], .5, (Color){31 * i, 31 * i, (10 * i) + 120, 255});
					}
				}
				EndMode3D();

				DrawFPS(10, 10);

			EndDrawing();
		}
		CloseWindow();
}