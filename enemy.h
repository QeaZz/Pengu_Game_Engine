#pragma once
#include <math.h>

class EnemyBehaviourComponent : public Component
{
	ObjectPool<GameObject>* ice_pool;
	std::vector<bool> AI = {false, false, false, false, false}; //False
	bool noVelocity = true;
	Vector2D tempPos;


public:
	virtual ~EnemyBehaviourComponent() {}

	virtual void Create(AvancezLib* engine, GameObject* go, std::set<GameObject*>* game_objects, ObjectPool<GameObject>* ice_pool)
	{
		Component::Create(engine, go, game_objects);
		this->ice_pool = ice_pool;
	}

	virtual void Init()
	{

		for (int i = 0; i < 91; i++) {
			go->AddReceiver(ice_pool->pool[i]);
		}
		AI[0] = true;
	}

	virtual void Update(double dt)
	{
		AvancezLib::KeyStatus keys;
		keys = { false, false, false, false, false};

		
		keys = AIUpdate(keys);
		
		
		//std::vector<int> prio = { 0,0,0,0 };
		//prio = engine->getKeyPrio();

		//MovePrioKeys(prio, keys, dt, 0);

		if (keys.right) {
			Move(dt * 160.0f, 0);
			
		}
		if (keys.left) {
			Move(-dt * 160.0f, 0);
			
		}
		if (keys.up) {
			Move(0, -dt * 160.0f);
			
		}
		if (keys.down) {
			Move(0, dt * 160.0f);

		}
	}

	void AINewDirY() { // Sets a random new action for the AI
		int rnd = (std::rand() % 4); //random int 0-3
		if (rnd == 0) {
			AI[0] = true;
			AI[1] = false;
			AI[2] = false;
			AI[3] = false;
		}
		else if (rnd == 1) {
			AI[1] = true;
			AI[0] = false;
			AI[2] = false;
			AI[3] = false;
		}

		else if (rnd == 2) {
			AI[2] = true;
			AI[0] = false;
			AI[1] = false;
			AI[3] = false;
		}
		else if (rnd == 3) {
			AI[3] = true;
			AI[0] = false;
			AI[1] = false;
			AI[2] = false;
		}
	}
	/*void AINewDirX() { // Sets a random new action for the AI
		int rnd = (std::rand() % 2); //random int 0-3

		if (rnd == 2) {
			AI[2] = true;
			AI[0] = false;
			AI[1] = false;
			AI[3] = false;
		}
		else if (rnd == 3) {
			AI[3] = true;
			AI[0] = false;
			AI[1] = false;
			AI[2] = false;
		}
	}*/

	AvancezLib::KeyStatus AIUpdate(AvancezLib::KeyStatus & keys) {
		keys.up = AI[0];
		keys.down = AI[1];
		keys.right = AI[2];
		keys.left = AI[3];
		keys.fire = AI[4];
		return keys;
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
			if (keys.down) {
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

	// move the enemy left or right
	// param move depends on the time, so the enemy moves always at the same speed on any computer
	void Move(double moveX, double moveY)
	{
		if (moveX != 0) {//Increase or disincrease the amount moved per click (enemy speed)
			if (moveX < 0) {
				moveX *= 0.3;
				go->position.x += moveX;
			}
			else {
				moveX *= 0.3;
				go->position.x += moveX;
			}
		}
		if (moveY != 0) {
			if (moveY < 0) {
				moveY *= 0.3;
				go->position.y += moveY;
			}
			else {
				moveY *= 0.3;
				go->position.y += moveY;
			}
		}

		for (int i = 0; i < 91; i++) { //Ice collision check
			if (ice_pool->pool[i] != NULL) {
				if (go->position.x >= ice_pool->pool[i]->position.x - 16 && go->position.x <= ice_pool->pool[i]->position.x) { //Check if enemy is in a Ice block  | LEFT 
					if (go->position.y < ice_pool->pool[i]->position.y + 16 && go->position.y > ice_pool->pool[i]->position.y) { // BOT
						RigidBodyComponent* rigidBodyComponent = ice_pool->pool[i]->GetComponent<RigidBodyComponent*>();
						if (rigidBodyComponent->velocity.x != 0 || rigidBodyComponent->velocity.y != 0) {
							go->Receive(HIT);
						}
						if ((go->position.x - (ice_pool->pool[i]->position.x - 16)) > (ice_pool->pool[i]->position.y + 16 - go->position.y)) {
							go->position.y = ice_pool->pool[i]->position.y + 16;
							AINewDirY();
						}
						else {
							go->position.x = ice_pool->pool[i]->position.x - 16;
							AINewDirY();
						}

					}
					else if (go->position.y >= ice_pool->pool[i]->position.y - 16 && go->position.y <= ice_pool->pool[i]->position.y) { //TOP
						RigidBodyComponent* rigidBodyComponent = ice_pool->pool[i]->GetComponent<RigidBodyComponent*>();
						if (rigidBodyComponent->velocity.x != 0 || rigidBodyComponent->velocity.y != 0) {
							go->Receive(HIT);
						}
						if ((go->position.x - ice_pool->pool[i]->position.x - 16) > (go->position.y - ice_pool->pool[i]->position.y - 16)) {
							go->position.y = ice_pool->pool[i]->position.y - 16;
							AINewDirY();
						}
						else {
							go->position.x = ice_pool->pool[i]->position.x - 16;
							AINewDirY();
						}
					}
				}
				else if (go->position.x <= ice_pool->pool[i]->position.x + 16 && go->position.x >= ice_pool->pool[i]->position.x) { // RIGHT
					if (go->position.y < ice_pool->pool[i]->position.y + 16 && go->position.y > ice_pool->pool[i]->position.y) { // BOT
						RigidBodyComponent* rigidBodyComponent = ice_pool->pool[i]->GetComponent<RigidBodyComponent*>();
						if (rigidBodyComponent->velocity.x != 0 || rigidBodyComponent->velocity.y != 0) {
							go->Receive(HIT);
						}
						if ((ice_pool->pool[i]->position.x + 16 - go->position.x) > (ice_pool->pool[i]->position.y + 16 - go->position.y)) {
							go->position.y = ice_pool->pool[i]->position.y + 16;
							AINewDirY();
						}
						else {
							go->position.x = ice_pool->pool[i]->position.x + 16;
							AINewDirY();
						}
					}
					else if (go->position.y >= ice_pool->pool[i]->position.y - 16 && go->position.y <= ice_pool->pool[i]->position.y) { //TOP
						RigidBodyComponent* rigidBodyComponent = ice_pool->pool[i]->GetComponent<RigidBodyComponent*>();
						if (rigidBodyComponent->velocity.x != 0 || rigidBodyComponent->velocity.y != 0) {
							go->Receive(HIT);
						}
						if ((ice_pool->pool[i]->position.x + 16 - go->position.x) > (go->position.y - (ice_pool->pool[i]->position.y - 16))) {
							go->position.y = ice_pool->pool[i]->position.y - 16;
							AINewDirY();
						}
						else {
							go->position.x = ice_pool->pool[i]->position.x + 16;
							AINewDirY();
						}
					}
				}
			}
		}


		if (go->position.x > (224 - 24
			)) { //Wall collision check
			go->position.x = 224 - 24;
			AINewDirY();
		}

		if (go->position.x < 8){
			go->position.x = 8;
			AINewDirY();
		}

		if (go->position.y > (256 - 24)){
			go->position.y = 256 - 24;
			AINewDirY();
		}

		if (go->position.y < 8){
			go->position.y = 8;
			AINewDirY();
		}
	}

};

// the main enemy
class Enemy : public GameObject
{
public:

	bool alive;	// it's game over when goes below zero 

	virtual ~Enemy() { SDL_Log("Enemy::~Enemy"); }

	virtual void Init(Vector2D pos)
	{
		SDL_Log("Enemy::Init");
		GameObject::Init();
		alive = true;
		this->position = pos;
	}

	virtual void Receive(Message m)
	{
		if (m == HIT && alive)
		{
			SDL_Log("Enemy::Hit!");
			RemoveLife();

			if (!alive) {
				this->Destroy();
			}
		}
	}

	void RemoveLife()
	{
		alive = false;
	}
};
