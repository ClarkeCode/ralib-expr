/*******************************************************************************************
*
*   raylib [models] example - Show the difference between perspective and orthographic projection
*
*   Example originally created with raylib 2.0, last time updated with raylib 3.7
*
*   Example contributed by Max Danielsson (@autious) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2018-2024 Max Danielsson (@autious) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#define NICER_RAYLIB_VECTORS_IMPLEMENTATION
#include "nicerRayVectors.hpp"

#define FOVY_PERSPECTIVE    45.0f
#define WIDTH_ORTHOGRAPHIC  10.0f

//Ken Perlin's SmootherStep, see https://en.wikipedia.org/wiki/Smoothstep
// 0 <= X <= 1
float SmootherStep(float x) {
	if (x <= 0) return 0;
	if (x >= 1) return 1;
	return x * x * x * (x * (6.0f * x - 15.0f) + 10.0f);
}

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

struct ZoomInfo {
	float maxZoomFactor;
	bool isActive;
	float currentZoomFactor;
	float targetZoomFactor;
};
ZoomInfo zoomer = {
	.maxZoomFactor = 3,
	.isActive = false,
	.currentZoomFactor = 1,
	.targetZoomFactor = 1,
};
void ToggleZoom(ZoomInfo& zoom) {
	zoomer.isActive = !zoomer.isActive;
	zoomer.targetZoomFactor = (zoomer.isActive ? zoomer.maxZoomFactor : 1.0f);
}
void ApplyZoom(Camera& camera, ZoomInfo& zoom) {
	if (zoom.currentZoomFactor < zoom.targetZoomFactor) zoom.currentZoomFactor += 0.1f;
	if (zoom.currentZoomFactor > zoom.targetZoomFactor) zoom.currentZoomFactor -= 0.1f;
	camera.fovy = FOVY_PERSPECTIVE / zoom.currentZoomFactor;
}

void BulkWriteText(const char** arr, size_t arr_sz, Vector2 point, float font_sz, Color color) {
	for (size_t x = 0; x < arr_sz; x++) {
		DrawText(arr[x], point.x, point.y + font_sz * (float)x, font_sz, color);
	}
}

int main(void) {
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [models] example - geometric shapes");

	// Define the camera to look into our 3d world
	Vector3 one = Vec(0, 10, 0);
	Vector3 two = { 0.0f, 0.0f, 12.0f };

	Camera camera = { (one + two), Vec(0, 0, 0), Vec(0, 1, 0), FOVY_PERSPECTIVE, CAMERA_PERSPECTIVE };

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	DisableCursor();
	// Main game loop
	while (!WindowShouldClose()) { // Detect window close button or ESC key
		// Update
		//----------------------------------------------------------------------------------
		if (IsKeyPressed(KEY_SPACE)) {
			if (camera.projection == CAMERA_PERSPECTIVE) {
				camera.fovy = WIDTH_ORTHOGRAPHIC;
				camera.projection = CAMERA_ORTHOGRAPHIC;
			}
			else {
				camera.fovy = FOVY_PERSPECTIVE;
				camera.projection = CAMERA_PERSPECTIVE;
			}
		}



		if (IsMouseButtonPressed(MOUSE_BUTTON_SIDE)) ToggleZoom(zoomer);
		ApplyZoom(camera, zoomer);

		UpdateCameraPro(&camera,
			(Vector3){
				(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))*0.1f -      // Move forward-backward
				(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))*0.1f,
				(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))*0.1f -   // Move right-left
				(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))*0.1f,
				0.0f                                                // Move up-down
			},
			(Vector3){
				GetMouseDelta().x*5.4f * GetFrameTime() / zoomer.currentZoomFactor,    // Rotation: yaw
				GetMouseDelta().y*5.4f * GetFrameTime() / zoomer.currentZoomFactor,    // Rotation: pitch
				0.0f                                                                   // Rotation: roll
			},
			0.0f// GetMouseWheelMove()*2.0f // Move to target (zoom)
		);


		//----------------------------------------------------------------------------------
		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();
			ClearBackground(RAYWHITE);
			BeginMode3D(camera);

				DrawCube((Vector3){-4.0f, 0.0f, 2.0f}, 2.0f, 5.0f, 2.0f, RED);
				DrawCubeWires((Vector3){-4.0f, 0.0f, 2.0f}, 2.0f, 5.0f, 2.0f, GOLD);
				DrawCubeWires((Vector3){-4.0f, 0.0f, -2.0f}, 3.0f, 6.0f, 2.0f, MAROON);

				DrawSphere((Vector3){-1.0f, 0.0f, -2.0f}, 1.0f, GREEN);
				DrawSphereWires((Vector3){1.0f, 0.0f, 2.0f}, 2.0f, 16, 16, LIME);

				DrawCylinder((Vector3){4.0f, 0.0f, -2.0f}, 1.0f, 2.0f, 3.0f, 4, SKYBLUE);
				DrawCylinderWires((Vector3){4.0f, 0.0f, -2.0f}, 1.0f, 2.0f, 3.0f, 4, DARKBLUE);
				DrawCylinderWires((Vector3){4.5f, -1.0f, 2.0f}, 1.0f, 1.0f, 2.0f, 6, BROWN);

				DrawCylinder((Vector3){1.0f, 0.0f, -4.0f}, 0.0f, 1.5f, 3.0f, 8, GOLD);
				DrawCylinderWires((Vector3){1.0f, 0.0f, -4.0f}, 0.0f, 1.5f, 3.0f, 8, PINK);

				DrawGrid(10, 1.0f);        // Draw a grid

			EndMode3D();

			//Telescope visual effect
			if (zoomer.isActive) {
				float screenW = GetScreenWidth();
				float viewfinderInnerRadius = screenW / 2.0f * 0.7f;
				DrawCircleGradient(GetScreenWidth()/2, GetScreenHeight()/2, viewfinderInnerRadius*1.01f, Fade(BLACK, 0.0f), Fade(BLACK, 0.6f));
				DrawRing(Vec(GetScreenWidth()/2, GetScreenHeight()/2), viewfinderInnerRadius, screenW, 0, 360, 0, Fade(BLACK, 0.95f));
				DrawCircleV(Vec(GetScreenWidth()/2, GetScreenHeight()/2), 2.0f, Fade(BLACK, 0.8f));
			}

			// DrawText("Press Spacebar to switch camera type", 10, GetScreenHeight() - 30, 20, DARKGRAY);
			if (camera.projection == CAMERA_ORTHOGRAPHIC) DrawText("ORTHOGRAPHIC", 10, 40, 20, BLACK);
			else if (camera.projection == CAMERA_PERSPECTIVE) DrawText("PERSPECTIVE", 10, 40, 20, BLACK);

			int TEXTSIZE = 10;
			const char* aaa[] = {
				TextFormat("Position %.3f %.3f %.3f", SpreadV3(camera.position)),
				TextFormat("Target %.3f %.3f %.3f len %.3f", SpreadV3(camera.target), Vector3Length(camera.target)),
				TextFormat("Up Vec %.3f %.3f %.3f", SpreadV3(camera.up)),
				TextFormat("Zoomer: %d C: %.3f T: %.3f", zoomer.isActive, zoomer.currentZoomFactor, zoomer.targetZoomFactor),
				// "lorem", "info", "battery"
			};
			DrawRectangleV(Vec(0, GetScreenHeight() - TEXTSIZE * ARRAY_SIZE(aaa)), Vec(200, TEXTSIZE * ARRAY_SIZE(aaa)), Fade(LIGHTGRAY, 0.8f));
			BulkWriteText(aaa, ARRAY_SIZE(aaa), Vec(10, GetScreenHeight() - TEXTSIZE * ARRAY_SIZE(aaa)), TEXTSIZE, BLACK);



			DrawFPS(10, 10);
		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
