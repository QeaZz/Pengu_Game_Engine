#pragma once

// GameObject represents objects which moves are drawn
#include <vector>
#include <set>
#include "Vector2D.h"
#include <string>

enum Message { NO_MSG, HIT };

class Component;

class GameObject
{
protected:
	std::vector<GameObject*> receivers;
	std::vector<Component*> components;

	std::string id;

public:

	Vector2D position;
	int dir = -1;
	bool enabled;

	virtual ~GameObject();

	virtual void Create();
	virtual void AddComponent(Component * component);

	virtual void Init();
	virtual void Update(float dt);
	virtual void Destroy();
	virtual void AddReceiver(GameObject *go);
	virtual void Receive(Message m) {}
	virtual void Pushed(int nr, int dir) {}
	void Push(int nr, int dir);
	void Send(Message m);

	template<typename T>
	T GetComponent() {
		for (Component * c : components) {
			T t = dynamic_cast<T>(c);  //ugly but it works...
			if (t != nullptr) {
				return t;
			}
		}

		return nullptr;
	}

	std::string getID() {
		return id;
	}
};