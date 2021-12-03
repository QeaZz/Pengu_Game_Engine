#pragma once

#include <set>
#include "object_pool.h"
#include "game_object.h"

class GameObject;
class AvancezLib;
class Sprite;


class Component
{
protected:
	AvancezLib * engine;	// used to access the engine
	GameObject * go;		// the game object this component is part of
	std::set<GameObject*> * game_objects;	// the global container of game objects

public:
	virtual ~Component() {}

	virtual void Create(AvancezLib* engine, GameObject * go, std::set<GameObject*> * game_objects);

	virtual void Init() {}
	virtual void Update(double dt) = 0;
	virtual void Receive(int message) {}
	virtual void Destroy() {}
};


class RenderComponent : public Component
{
	Sprite* sprite;

public:

	virtual void Create(AvancezLib* engine, GameObject * go, std::set<GameObject*> * game_objects, const char * sprite_name);
	virtual void Update(double dt);
	virtual void Destroy();

	Sprite * GetSprite() { return sprite; }
};


class CollideComponent : public Component
{
protected:
	ObjectPool<GameObject> * coll_objects; // collision will be tested with these objects

public:
	virtual void Create(AvancezLib* engine, GameObject * go, std::set<GameObject*> * game_objects, ObjectPool<GameObject> * coll_objects);
	virtual void Update(double dt);
};


class IceCollideComponent : public Component
{
protected:
	ObjectPool<GameObject>* player;

public:
	virtual void Create(AvancezLib* engine, GameObject* go, std::set<GameObject*>* game_objects, ObjectPool<GameObject>* coll_objects);
	virtual void Update(double dt);
};



class RigidBodyComponent : public Component
{
public:
	Vector2D velocity, acceleration;

	virtual void Create(AvancezLib* engine, GameObject * go, std::set<GameObject*> * game_objects);
	virtual void Update(double dt);
};
