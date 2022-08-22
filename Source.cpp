#include "raylib.h"

class Ball
{
public:
	float x, y;
	float speedX, speedY;
	float radius;

	void Draw()
	{
		DrawCircle((int)x, (int)y, radius, WHITE);
	}
};



int main() {
	InitWindow(600, 600, "window");
	//leftpaddle
	Rectangle leftPaddle;
	leftPaddle.x = 20;
	leftPaddle.y = GetScreenHeight() / 2;
	leftPaddle.width = 10;
	leftPaddle.height = 150;
	//right paddle
	Rectangle rightPaddle;
	rightPaddle.x = GetScreenWidth() - 20;
	rightPaddle.y = GetScreenHeight() / 2;
	rightPaddle.width = 10;
	rightPaddle.height = 150;

	//ball
	Ball ball;
	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5;
	ball.speedX = 300;
	ball.speedY = 300;

	int paddlespeed = 500;
	int ballspeed = 300;
	const char* winnerText = nullptr;
	while (!WindowShouldClose()) {
		ClearBackground(BLACK);
		BeginDrawing();
		DrawRectangleRec(leftPaddle, WHITE);
		DrawRectangleRec(rightPaddle, WHITE);
		ball.x += ball.speedX * GetFrameTime();
		ball.y += ball.speedY * GetFrameTime();
		if (IsKeyDown(KEY_W) && leftPaddle.y>0 ) {
			leftPaddle.y -= paddlespeed * GetFrameTime();
		}
		if (IsKeyDown(KEY_S) && leftPaddle.y <GetScreenHeight() - leftPaddle.height) {
			leftPaddle.y += paddlespeed * GetFrameTime();
		}
		if (IsKeyDown(KEY_UP) && rightPaddle.y > 0 ) {
			rightPaddle.y -= paddlespeed * GetFrameTime();
		}
		if (IsKeyDown(KEY_DOWN) && rightPaddle.y<GetScreenHeight() - rightPaddle.height) {
			rightPaddle.y += paddlespeed * GetFrameTime();
		}


		//collisions
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, leftPaddle))
		{
			if (ball.speedX < 0)
			{
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedX;
			}
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, rightPaddle))
		{
			if (ball.speedX > 0)
			{
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * -ball.speedX;
			}
		}


		//out of bounds

		if (ball.y < 0)
		{
			ball.y = 0;
			ball.speedY *= -1;
		}
		if (ball.y > GetScreenHeight())
		{
			ball.y = GetScreenHeight();
			ball.speedY *= -1;
		}


		//winner
		if (ball.x < 0)
		{
			winnerText = "Right Player Wins!";
		}
		if (ball.x > GetScreenWidth())
		{
			winnerText = "Left Player Wins!";
		}
		if (winnerText && IsKeyPressed(KEY_SPACE))
		{
			ball.x = GetScreenWidth() / 2;
			ball.y = GetScreenHeight() / 2;
			ball.speedX = 300;
			ball.speedY = 300;
			leftPaddle.x = 20;
			leftPaddle.y = GetScreenHeight() / 2;
			rightPaddle.x = GetScreenWidth() - 20;
			rightPaddle.y = GetScreenHeight() / 2;
			paddlespeed = 500;
			winnerText = nullptr;
		}
		if (winnerText)
		{
			int textWidth = MeasureText(winnerText, 60);
			DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
			paddlespeed = 0;
		}

		ball.Draw();
		EndDrawing();
	}
	CloseWindow();

	return 0;
}