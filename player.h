#pragma once
#include <math.h>

class PlayerBehaviourComponent : public Component
{
	ObjectPool<GameObject>* ice_pool;

public:
	virtual ~PlayerBehaviourComponent() {}

	virtual void Create(AvancezLib* engine, GameObject* go, std::set<GameObject*>* game_objects, ObjectPool<GameObject>* ice_pool)
	{
		Component::Create(engine, go, game_objects);
		this->ice_pool = ice_pool;
	}

	virtual void Init()
	{
		go->position.x = 8 + 16;
		go->position.y = 8 + 16;

		for (int i = 0; i < 91; i++) {
			go->AddReceiver(ice_pool->pool[i]);
		}
	}

	virtual void Update(double dt)
	{
		AvancezLib::KeyStatus keys;
		std::vector<int> prio = { 0,0,0,0 };
		engine->getKeyStatus(keys);
		prio = engine->getKeyPrio();

		//MovePrioKeys(prio, keys, dt, 0);

		if (keys.right) {
			Move(dt * 160.0f, 0);
			if (keys.fire) { // if the button is pressed, check which ice block to move
				int nbr = 0;
				int dist = 1000;
				for (int i = 0; i < 91; i++) {
					if (go->position.y + 8 < ice_pool->pool[i]->position.y + 16 && go->position.y + 8 >= ice_pool->pool[i]->position.y) {
						if (dist > ice_pool->pool[i]->position.x - go->position.x && 0 < ice_pool->pool[i]->position.x - go->position.x) {
							dist = ice_pool->pool[i]->position.x - go->position.x;
							nbr = i;
						}
 						if(dist == 16)
							go->Push(nbr , 0);
 					}
				}
			}
		}
		if (keys.left) {
			Move(-dt * 160.0f, 0);

			if (keys.fire) { // if the button is pressed, check which ice block to move
				int nbr = 0;
				int dist = -1000;
				for (int i = 0; i < 91; i++) {
					if (go->position.y + 8 < ice_pool->pool[i]->position.y + 16 && go->position.y + 8 >= ice_pool->pool[i]->position.y) {
						if (dist < ice_pool->pool[i]->position.x - go->position.x && 0 > ice_pool->pool[i]->position.x - go->position.x) {
							dist = ice_pool->pool[i]->position.x - go->position.x;
							nbr = i;
						}
						if (dist == -16)
							go->Push(nbr, 1);
					}
				}
			}
		}
		if (keys.up) {
			Move(0, -dt * 160.0f);
			if (keys.fire) { // if the button is pressed, check which ice block to move
				int nbr = 0;
				int dist = -1000;
				for (int i = 0; i < 91; i++) {
					if (go->position.x + 8 < ice_pool->pool[i]->position.x + 16 && go->position.x + 8 >= ice_pool->pool[i]->position.x) {
						if (dist < ice_pool->pool[i]->position.y - go->position.y && 0 > ice_pool->pool[i]->position.y - go->position.y) {
							dist = ice_pool->pool[i]->position.y - go->position.y;
							nbr = i;
						}
						if (dist == -16)
							go->Push(nbr, 2																										);
					}
				}
			}
		}
		if (keys.down) {
			Move(0, dt * 160.0f);
			if (keys.fire) { // if the button is pressed, check which ice block to move
				int nbr = 0;
				int dist = 1000;
				for (int i = 0; i < 91; i++) {
					if (go->position.x + 8 < ice_pool->pool[i]->position.x + 16 && go->position.x + 8 >= ice_pool->pool[i]->position.x) {
						if (dist > ice_pool->pool[i]->position.y - go->position.y && 0 < ice_pool->pool[i]->position.y - go->position.y) {
							dist = ice_pool->pool[i]->position.y - go->position.y;
							nbr = i;
						}
						if (dist == 16)
							go->Push(nbr, 3);
					}
				}
			}
		}
	}

	//For desired movement (recursive) (broken after updated collsion detection was added)
	void MovePrioKeys(std::vector<int>& prio, AvancezLib::KeyStatus keys, double dt, int iter) {
		if (iter == 4) { // 4 priorites
			return;
		}
		else if (prio[0] == 1) {
			if (keys.right) {
				Move(dt * 160.0f, 0);
				return;
			}
			CutFirst(prio);
			iter++;
			MovePrioKeys(prio, keys, dt, iter);
		}
		else if (prio[0] == 2) {
			if (keys.left) {
				Move(-dt * 160.0f, 0);
				return;
			}
			CutFirst(prio);
			iter++;
			MovePrioKeys(prio, keys, dt, iter);
		}
		else if (prio[0] == 3) {
			if (keys.up) {
			Move(0, -dt * 160.0f);
			return;
			}
			CutFirst(prio);
			iter++;
			MovePrioKeys(prio, keys, dt, iter);
		}
		else if (prio[0] == 4) {
			if (keys.down){
				Move(0, dt * 160.0f);
				return;
			}
			CutFirst(prio);
			iter++;
			MovePrioKeys(prio, keys, dt, iter);
		}
	}

	void CutFirst(std::vector<int>& prio) {
		prio[0] = prio[1];
		prio[1] = prio[2];
		prio[2] = prio[3];
		prio[3] = prio[0];
	}

	// move the player left or right
	// param move depends on the time, so the player moves always at the same speed on any computer
	void Move(double moveX, double moveY)
	{
		if (moveX != 0) {//Increase or disincrease the amount moved per click (player speed)
			if (moveX < 0) {
				moveX -= -0.05;
				go->position.x += moveX;
			}
			else {
				moveX += -0.05;
				go->position.x += moveX;
			}
		}
		if (moveY != 0){
			if (moveY < 0) {
				moveY -= -0.05;
				go->position.y += moveY;
			}
			else {
				moveY += -0.05;
				go->position.y += moveY;
			}
		}

		for (int i = 0; i < 91; i++) { //Ice collision check
			if (ice_pool->pool[i] != NULL) {
				if (go->position.x >= ice_pool->pool[i]->position.x - 16 && go->position.x <= ice_pool->pool[i]->position.x) { //Check if player is in a Ice block  | LEFT 
					if (go->position.y < ice_pool->pool[i]->position.y + 16 && go->position.y > ice_pool->pool[i]->position.y) { // BOT
						if ((go->position.x - (ice_pool->pool[i]->position.x - 16)) > (ice_pool->pool[i]->position.y + 16 - go->position.y))
							go->position.y = ice_pool->pool[i]->position.y + 16;
						else
							go->position.x = ice_pool->pool[i]->position.x - 16;

					}
					else if (go->position.y >= ice_pool->pool[i]->position.y - 16 && go->position.y <= ice_pool->pool[i]->position.y) { //TOP
						if((go->position.x - ice_pool->pool[i]->position.x - 16) > (go->position.y - ice_pool->pool[i]->position.y - 16))
							go->position.y = ice_pool->pool[i]->position.y - 16;
						else
							go->position.x = ice_pool->pool[i]->position.x - 16;
					}
				}
				else if (go->position.x <= ice_pool->pool[i]->position.x + 16 && go->position.x >= ice_pool->pool[i]->position.x) { // RIGHT
					if (go->position.y < ice_pool->pool[i]->position.y + 16 && go->position.y > ice_pool->pool[i]->position.y) { // BOT
						if ((ice_pool->pool[i]->position.x + 16 - go->position.x) > (ice_pool->pool[i]->position.y + 16 - go->position.y))
							go->position.y = ice_pool->pool[i]->position.y + 16;
						else
							go->position.x = ice_pool->pool[i]->position.x + 16;
					}
					else if (go->position.y >= ice_pool->pool[i]->position.y - 16 && go->position.y <= ice_pool->pool[i]->position.y) { //TOP
						if ((ice_pool->pool[i]->position.x + 16 - go->position.x) > (go->position.y - (ice_pool->pool[i]->position.y - 16)))
							go->position.y = ice_pool->pool[i]->position.y - 16;
						else
							go->position.x = ice_pool->pool[i]->position.x + 16;
					}
				}
			}
		}
		

		if (go->position.x > (224 - 24)) //Wall collision check
			go->position.x = 224 - 24;
			
		if (go->position.x < 8)
			go->position.x = 8;

		if (go->position.y > (256 - 24))
			go->position.y = 256- 24;

		if (go->position.y < 8)
			go->position.y = 8;
	}

};

// the main player
class Player : public GameObject
{
public:

	int lives;	// it's game over when goes below zero 

	virtual ~Player()	{		SDL_Log("Player::~Player");	}

	virtual void Init()
	{
		SDL_Log("Player::Init");
		GameObject::Init();
		lives = 5;
	}

	virtual void Receive(Message m) 
	{
		if (m == HIT)
		{ 
			SDL_Log("Player::Hit!");
			RemoveLife();

			if (lives < 0)
				lives = 5;
				//Send(GAME_OVER);
		}
	}

	void RemoveLife()
	{
		lives--;
		SDL_Log("remaining lives %d", lives);
	}
};
