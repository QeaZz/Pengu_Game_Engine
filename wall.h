#pragma once


// the main wall
class Wall : public GameObject
{
public:

	virtual ~Wall() { SDL_Log("Wall::~Wall"); }

	virtual void Init(Vector2D position)
	{
		SDL_Log("Wall::Init");
		GameObject::Init();

		this->position = position;
		id = "Wall";
	}
};


class WallBehaviourComponent : public Component
{
	CollideComponent* collider;

public:
	virtual ~WallBehaviourComponent() {}

	virtual void Create(AvancezLib* engine, GameObject* go, std::set<GameObject*>* game_objects, CollideComponent* collider)
	{
		Component::Create(engine, go, game_objects);
		this->collider = collider;
	}

	virtual void Update(double dt)
	{

	}
};
