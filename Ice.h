#pragma once


// the main wall
class Ice : public GameObject
{
	int nr;
	RigidBodyComponent* rigidBodyComponent = this->GetComponent<RigidBodyComponent*>();
public:

	virtual ~Ice() { SDL_Log("Ice::~Ice"); }

	virtual void Init(Vector2D position, int nr)
	{
		SDL_Log("Ice::Init");
		GameObject::Init();

		this->position = position;
		id = "Ice";
		this->nr = nr;
	}

	virtual void Receive(Message m)
	{

	}
	virtual void Pushed(int nr, int dir) {
		if (this->nr == nr) {
			this->dir = dir;
		}
	}

	
};


class IceBehaviourComponent : public Component
{
	CollideComponent* collider;
	ObjectPool<Ice>* ice_pool;
	int moving;

public:
	virtual ~IceBehaviourComponent() {}

	virtual void Create(AvancezLib* engine, GameObject* go, std::set<GameObject*>* game_objects, ObjectPool<Ice>* ice_pool)
	{
		Component::Create(engine, go, game_objects);
		this->ice_pool = ice_pool;
		moving = -1;
	}

	virtual void Update(double dt)
	{
		RigidBodyComponent* rigidBodyComponent = go->GetComponent<RigidBodyComponent*>();
		if (moving == 0) { //If moving right, check collision with AI

			for (int i = 0; i < 91; i++) { //Ice collision check
				if (!(ice_pool->pool[i]->position.x == go->position.x && ice_pool->pool[i]->position.y == go->position.y)) { // Dont compare with itself
					if(go->position.y + 8 >= ice_pool->pool[i]->position.y && go->position.y + 8 <= ice_pool->pool[i]->position.y + 16)
						if(go->position.x + 16 >= ice_pool->pool[i]->position.x && go->position.x < ice_pool->pool[i]->position.x + 16){
							go->position.x = ice_pool->pool[i]->position.x - 16;
							rigidBodyComponent->velocity.x = 0;
							moving = -1;
						}
				}
			}
		}
		if (moving == 1) { //If moving left, check collision with AI

			for (int i = 0; i < 91; i++) { //Ice collision check
				if (!(ice_pool->pool[i]->position.x == go->position.x && ice_pool->pool[i]->position.y == go->position.y)) { // Dont compare with itself
					if (go->position.y + 8 >= ice_pool->pool[i]->position.y && go->position.y + 8 <= ice_pool->pool[i]->position.y + 16)
						if (go->position.x + 16 > ice_pool->pool[i]->position.x && go->position.x <= ice_pool->pool[i]->position.x + 16) {
							go->position.x = ice_pool->pool[i]->position.x + 16;
							rigidBodyComponent->velocity.x = 0;
							moving = -1;
						}
				}
			}
		}
		if (moving == 2) { //If moving up, check collision with AI

			for (int i = 0; i < 91; i++) { //Ice collision check
				if (!(ice_pool->pool[i]->position.x == go->position.x && ice_pool->pool[i]->position.y == go->position.y)) { // Dont compare with itself
					if (go->position.x + 8 >= ice_pool->pool[i]->position.x && go->position.x + 8 <= ice_pool->pool[i]->position.x + 16)
						if (go->position.y + 16 > ice_pool->pool[i]->position.y && go->position.y <= ice_pool->pool[i]->position.y + 16) {
							go->position.y = ice_pool->pool[i]->position.y + 16;
							rigidBodyComponent->velocity.y = 0;
							moving = -1;
						}
				}
			}
		}
		if (moving == 3) { //If moving down, check collision with AI

			for (int i = 0; i < 91; i++) { //Ice collision check
				if (!(ice_pool->pool[i]->position.x == go->position.x && ice_pool->pool[i]->position.y == go->position.y)) { // Dont compare with itself
					if (go->position.x + 8 >= ice_pool->pool[i]->position.x && go->position.x + 8 <= ice_pool->pool[i]->position.x + 16)
						if (go->position.y + 16 > ice_pool->pool[i]->position.y && go->position.y <= ice_pool->pool[i]->position.y + 16) {
							go->position.y = ice_pool->pool[i]->position.y - 16;
							rigidBodyComponent->velocity.y = 0;
							moving = -1;
						}
				}
			}
		}

		if (go->dir == 0) {
			rigidBodyComponent->velocity.x = 100;
			go->dir = -1;
			moving = 0;
		}
		if (go->dir == 1) {
			rigidBodyComponent->velocity.x = -100;
			go->dir = -1;
			moving = 1;
		}
		if (go->dir == 2){
			rigidBodyComponent->velocity.y = -100;
			go->dir = -1;
			moving = 2;
		}
		if (go->dir == 3) {
			rigidBodyComponent->velocity.y = 100;
			go->dir = -1;
			moving = 3;
		}

		if (go->position.x > (224 - 24)) { //Wall collision check
			go->position.x = 224 - 24;
			rigidBodyComponent->velocity.x = 0;
			rigidBodyComponent->velocity.y = 0;
		}

		if (go->position.x < 8) {
			go->position.x = 8;
			rigidBodyComponent->velocity.x = 0;
			rigidBodyComponent->velocity.y = 0;
		}

		if (go->position.y > (256 - 24)) {
			go->position.y = 256 - 24;
			rigidBodyComponent->velocity.x = 0;
			rigidBodyComponent->velocity.y = 0;
		}

		if (go->position.y < 8) {
			go->position.y = 8;
			rigidBodyComponent->velocity.x = 0;
			rigidBodyComponent->velocity.y = 0;
		}
	}
};
