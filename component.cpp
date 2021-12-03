#include "component.h"
#include "game_object.h"
#include "avancezlib.h"
#include <math.h> 

void Component::Create(AvancezLib * engine, GameObject * go, std::set<GameObject*>* game_objects)
{
	this->go = go;
	this->engine = engine;
	this->game_objects = game_objects;
}

void RenderComponent::Create(AvancezLib * engine, GameObject * go, std::set<GameObject*>* game_objects, const char * sprite_name)
{
	Component::Create(engine, go, game_objects);

	sprite = engine->createSprite(sprite_name);
}

void RenderComponent::Update(double dt)
{
	if (!go->enabled)
		return;

	if (sprite) 
		sprite->draw(int(go->position.x), int(go->position.y));
}

void RenderComponent::Destroy()
{
	if (sprite != NULL)
		sprite->destroy();
	sprite = NULL;
}


void CollideComponent::Create(AvancezLib* engine, GameObject * go, std::set<GameObject*> * game_objects, ObjectPool<GameObject> * coll_objects)
{
	Component::Create(engine, go, game_objects);
	this->coll_objects = coll_objects;
}


void IceCollideComponent::Create(AvancezLib* engine, GameObject* go, std::set<GameObject*>* game_objects, ObjectPool<GameObject>* coll_objects)
{
	Component::Create(engine, go, game_objects);
	this->player = coll_objects;

}

void IceCollideComponent::Update(double dt)
{
	
}


void RigidBodyComponent::Create(AvancezLib* engine, GameObject * go, std::set<GameObject*> * game_objects)
{
	Component::Create(engine, go, game_objects);
}

void RigidBodyComponent::Update(double dt)
{
	//Forward Euler method:
	go->position = go->position + velocity * dt;
}