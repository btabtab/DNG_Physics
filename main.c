#include "PhysicsObject.h"
#include "FancyRenderingCode.h"

void spinningDots();
void rotateableRoom();
void simpleFighterDemo();

void pointIntersectionDemo();

int main()
{
	// pointIntersectionDemo();
	// rotateableRoom();
	// spinningDots();
	// AirframeDemo();
	// PhysicsDemo();
	simpleFighterDemo();
}

void drawLinesInterConntected(Vector2* points, int amount)
{
	Color cols[2] = {PURPLE, GREEN};
	for(int i = 0; i != (amount - 1); i++)
	{
		DrawLine(points[i].x, points[i].x, points[i+1].x, points[i+1].y, cols[0]);
	}
	DrawLine(points[0].x, points[0].x, points[amount-1].x, points[amount-1].y, cols[1]);
}

void pointIntersectionDemo()
{
	InitWindow(1000, 1000, "PointIntersection");

	Vector2 points[4] =
	{
		{-14, +49},
		{+52, -32},
		{+15, +36},
		{-14, -18},
	};
	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		{
			ClearBackground(WHITE);
			{
				drawLinesInterConntected(points, 4);
			}
		}
		EndDrawing();
	}
	
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
			DrawFPS(10, 10);

		EndDrawing();
	}
	CloseWindow();
	// return 0;

}

void renderSimpleFighterLandingGear(Vector3 position, Vector3 local_rotation, Vector3 global_rotation, float landing_gear)
{
	Vector3 landing_gear_bases[] =
	{
		(Vector3){+0,+0,+5},
		(Vector3){+2,+0,+2},
		(Vector3){-2,+0,+2}
	};

	Vector3 landing_gear_rotations[] =
	{
		(Vector3){0,0,0},
		(Vector3){0,0,0},
		(Vector3){0,0,0},
	};

	Vector3 center = (Vector3){+0, +0, +0};
	
	Vector3 landing_gear_wheel_points[sizeof(landing_gear_bases) / sizeof(*landing_gear_bases)];

	Vector3 landing_gear_bases_rotated[sizeof(landing_gear_bases) / sizeof(*landing_gear_bases)];
	Vector3 landing_gear_wheel_points_rotated[sizeof(landing_gear_bases) / sizeof(*landing_gear_bases)];

	for(int i = 0; i != sizeof(landing_gear_bases) / sizeof(*landing_gear_bases); i++)
	{
		landing_gear_wheel_points[i] = addVectors(landing_gear_bases[i], (Vector3){0, +1.5, 0});

		landing_gear_bases_rotated[i] = rotatePointVector3Degrees(landing_gear_bases[i], local_rotation, center);
		landing_gear_wheel_points_rotated[i] = rotatePointVector3Degrees(landing_gear_wheel_points[i], local_rotation, center);
	}

	for(int i = 0; i != sizeof(landing_gear_bases) / sizeof(*landing_gear_bases); i++)
	{
		// DrawSphere(rotatePointVector3Degrees(landing_gear_wheel_points_rotated[i]), .25f, WHITE);
	}

	// Vector3 left_gear[] =
	// {
	// 	landing_gear_bases_rotated[0],
	// 	rotatePointVector3Degrees(landing_gear_wheel_points_rotated[0], (Vector3){0, 0, 0}, landing_gear_bases_rotated[0])
	// };

	// Vector3 right_gear[] =
	// {
	// 	landing_gear_bases_rotated[1],
	// 	rotatePointVector3Degrees(landing_gear_wheel_points_rotated[1], (Vector3){0, 0, 0}, landing_gear_bases_rotated[1])
	// };
	static float a = 0;
	a += 1;
	Vector3 front_gear[] =
	{
		landing_gear_bases_rotated[0],
		landing_gear_wheel_points_rotated[0]
	};

	Vector3 left_gear[] =
	{
		landing_gear_bases_rotated[1],
		landing_gear_wheel_points_rotated[1]
	};

	Vector3 right_gear[] =
	{
		landing_gear_bases_rotated[2],
		landing_gear_wheel_points_rotated[2]
	};

	renderWireFrameRotatedDegrees(left_gear, sizeof(left_gear) / sizeof(*left_gear), position, global_rotation);
	renderWireFrameRotatedDegrees(right_gear, sizeof(right_gear) / sizeof(*right_gear), position, global_rotation);

	renderWireFrameRotatedDegrees(front_gear, sizeof(front_gear) / sizeof(*front_gear), position, global_rotation);

}

void renderSimpleFighter(Vector3 position, Vector3 local_rotation, Vector3 global_rotation, float landing_gear)
{
	Vector3 center = (Vector3){+0, +0, +0};
	Vector3 base[] =
	{
		(Vector3){+0, +0, +9},//nose
		(Vector3){-3, +0, +1},//right wing tip
		(Vector3){+3, +0, +1},//left wing yip
	};
	Vector3 fuselage_1[] =
	{
		base[0],
		(Vector3){0, -2, 3},//fuselage top
		(Vector3){0, -4, 1},//fin tip
		(Vector3){0, 0, 1}
	};

	Vector3 base_rotated[] =
	{
		rotatePointVector3Degrees(base[0], local_rotation, center),
		rotatePointVector3Degrees(base[1], local_rotation, center),
		rotatePointVector3Degrees(base[2], local_rotation, center),
	};
	Vector3 fuselage_1_rotated[] =
	{
		rotatePointVector3Degrees(fuselage_1[0], local_rotation, center),
		rotatePointVector3Degrees(fuselage_1[1], local_rotation, center),
		rotatePointVector3Degrees(fuselage_1[2], local_rotation, center),
		rotatePointVector3Degrees(fuselage_1[3], local_rotation, center),
	};
	
	renderWireFrameRotatedDegrees(base_rotated, sizeof(base) / sizeof(*base), position, global_rotation);
	renderWireFrameRotatedDegrees(fuselage_1_rotated, sizeof(fuselage_1) / sizeof(*fuselage_1), position, global_rotation);

	renderSimpleFighterLandingGear(position, local_rotation, global_rotation, landing_gear);
}

void renderPolygonalSimpleFighter(Vector3 position, Vector3 local_rotation, Vector3 global_rotation, float landing_gear)
{
	Vector3 center = (Vector3){+0, +0, +0};
	Vector3 base[] =
	{
		(Vector3){+0, +0, +9},//nose
		(Vector3){-3, +0, +1},//right wing tip
		(Vector3){+3, +0, +1},//left wing yip
	};
	Vector3 fuselage_1[] =
	{
		base[0],
		(Vector3){0, -2, 3},//fuselage top
		(Vector3){0, -4, 1},//fin tip
		(Vector3){0, 0, 1}
	};

	Vector3 base_rotated[] =
	{
		rotatePointVector3Degrees(base[0], local_rotation, center),
		rotatePointVector3Degrees(base[1], local_rotation, center),
		rotatePointVector3Degrees(base[2], local_rotation, center),
	};
	Vector3 fuselage_1_rotated[] =
	{
		rotatePointVector3Degrees(fuselage_1[0], local_rotation, center),
		rotatePointVector3Degrees(fuselage_1[1], local_rotation, center),
		rotatePointVector3Degrees(fuselage_1[2], local_rotation, center),
		rotatePointVector3Degrees(fuselage_1[3], local_rotation, center),
	};

	renderPolygonRotatedDegrees(base_rotated, sizeof(base) / sizeof(*base), position, global_rotation);
	renderPolygonRotatedDegrees(fuselage_1_rotated, sizeof(fuselage_1) / sizeof(*fuselage_1), position, global_rotation);

	renderSimpleFighterLandingGear(position, local_rotation, global_rotation, landing_gear);

}

void simpleFighterDemo()
{
	const int screenWidth = 720;
	const int screenHeight = 1600;

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

	Vector3 aircraft_rotation;
	Vector3 aircraft_position = (Vector3){+10, 0, +10};

	float theta = 0.0f;
	float local_theta = 0.0f;
	float landing_gear = 0.0f;
	while (!WindowShouldClose())
	{
		float alt_amount = 1;

		if(IsKeyDown(KEY_TAB))
		{
			aircraft_position.z -= alt_amount / 2;
		}
		if(IsKeyDown(KEY_LEFT_SHIFT))
		{
			aircraft_position.z += alt_amount / 2;
		}

		if(IsKeyDown(KEY_W))
		{
			aircraft_rotation.z -= alt_amount;
		}

		if(IsKeyDown(KEY_A))
		{
			aircraft_rotation.y += alt_amount;
		}

		if(IsKeyDown(KEY_E))
		{
			aircraft_rotation.x -= alt_amount;
		}

		if(IsKeyDown(KEY_S))
		{
			aircraft_rotation.z += alt_amount;
		}

		if(IsKeyDown(KEY_D))
		{
			aircraft_rotation.y -= alt_amount;
		}

		if(IsKeyDown(KEY_Q))
		{
			aircraft_rotation.x += alt_amount;
		}


		theta += 1;
		local_theta += 2;
		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode3D(camera);
		{
			// renderPolygonalSimpleFighter((Vector3){-0, 0, -0}, aircraft_rotation, (Vector3){theta * ((float)IsKeyDown(KEY_R)), 0, 0}, landing_gear);
			renderSimpleFighter((Vector3){+5, 10, 10}, (Vector3){0, 25, 25}, (Vector3){0, 0, 0}, landing_gear);
			renderSimpleFighter(aircraft_position, (Vector3){aircraft_rotation.x, aircraft_rotation.y, aircraft_rotation.z}, (Vector3){0, 0, 0}, landing_gear);
			renderSimpleFighter((Vector3){-10, 0, 0}, (Vector3){0, 0, 0}, (Vector3){0, 0, 0}, landing_gear);
		}
		EndMode3D();

		DrawFPS(10, 10);

		EndDrawing();
		if(IsKeyDown(KEY_U) && IsKeyDown(KEY_U))
		{}
	}
	CloseWindow();
}