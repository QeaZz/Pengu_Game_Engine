#define _CRT_SECURE_NO_WARNINGS

#include "avancezlib.h"


const double BALL_SPEED = 150;
float game_speed = 1.f;		// speed of the game; it is increased each time all the aliens are hit
							// it is also the score multiplier


#include "component.h"
#include "game_object.h"

#include "player.h"
#include "wall.h"
#include "Ice.h"
#include "enemy.h"

#include "game.h"


int main(int argc, char** argv)
{

	AvancezLib engine;

	engine.init(224, 256);

	Game game;
	game.Create(&engine);
	game.Init();

	float lastTime = engine.getElapsedTime();
	while (true)
	{
		float newTime = engine.getElapsedTime();
		float dt = newTime - lastTime;
		dt = dt * game_speed;
		lastTime = newTime;

		engine.processInput();
		game.Update(dt);
		game.Draw();
	}

	// clean up
	game.Destroy();
	engine.destroy();

	return 0;
}




