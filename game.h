#pragma once

bool change_direction = false;

class Game : public GameObject
{
	std::set<GameObject*> game_objects;	// http://www.cplusplus.com/reference/set/set/
	
	AvancezLib* engine;

	int iceCounter = 0;

	ObjectPool<Ice> ice_pool;

	Ice* ice;
	Wall* wall;
	Player * player;
	Enemy* enemy;

public:

	virtual void Create(AvancezLib* engine)
	{
		SDL_Log("Game::Create");

		this->engine = engine;

		wall = new Wall();
		WallBehaviourComponent* wall_behaviour = new WallBehaviourComponent();
		RenderComponent* wall_render = new RenderComponent();
		wall_render->Create(engine, wall, &game_objects, "data/walls.bmp");
		wall->Create();
		wall->AddComponent(wall_behaviour);
		wall->AddComponent(wall_render);
		wall->AddReceiver(this);

		ice_pool.Create(91);
		for (auto ice = ice_pool.pool.begin(); ice != ice_pool.pool.end(); ice++)
		{
			IceBehaviourComponent* behaviour = new IceBehaviourComponent();
			behaviour->Create(engine, *ice, &game_objects, &ice_pool);
			RenderComponent* render = new RenderComponent();
			render->Create(engine, *ice, &game_objects, "data/Ice.bmp");
			IceCollideComponent* ice_ice_collision = new IceCollideComponent();
			ice_ice_collision->Create(engine, *ice, &game_objects, reinterpret_cast<ObjectPool<GameObject>*>(&ice_pool));
			RigidBodyComponent* rigidBodyComponent = new RigidBodyComponent();
			rigidBodyComponent->Create(engine, *ice, &game_objects);
			(*ice)->Create();
			(*ice)->AddComponent(behaviour);
			(*ice)->AddComponent(render);
			(*ice)->AddComponent(ice_ice_collision);
			(*ice)->AddComponent(rigidBodyComponent);
			game_objects.insert(*ice);
		}


		player = new Player();
		PlayerBehaviourComponent* player_behaviour = new PlayerBehaviourComponent();
		player_behaviour->Create(engine, player, &game_objects, (ObjectPool<GameObject> *) &ice_pool);
		RenderComponent* player_render = new RenderComponent();
		player_render->Create(engine, player, &game_objects, "data/pengodown.bmp");
		player->Create();
		player->AddComponent(player_behaviour);
		player->AddComponent(player_render);
		player->AddReceiver(this);
		game_objects.insert(player);
		game_objects.insert(wall);

		enemy = new Enemy();
		EnemyBehaviourComponent* enemy_behaviour = new EnemyBehaviourComponent();
		enemy_behaviour->Create(engine, enemy, &game_objects, (ObjectPool<GameObject>*) & ice_pool);
		RenderComponent* enemy_render = new RenderComponent();
		enemy_render->Create(engine, enemy, &game_objects, "data/Bee.bmp");
		enemy->Create();
		enemy->AddComponent(enemy_behaviour);
		enemy->AddComponent(enemy_render);
		enemy->AddReceiver(this);
		game_objects.insert(enemy);
		game_objects.insert(wall);
	}

	virtual void Init()
	{
		wall->Init(Vector2D(0, 0));

		SDL_Delay(500);


		//Hardcoding the map layout.
		buildMap();

		player->Init();
		enemy->Init(Vector2D(8 + (16 * 13), 8 + (16 * 15)));

		enabled = true;
		id = "Game";
	}
	void initIceCoords (double x, double y){

		ice_pool.pool[iceCounter]->Init(Vector2D(8 + (16*x), 224+8 - (16*y)), iceCounter);
		iceCounter++;
		
	}

	virtual void Update(float dt)
	{
		AvancezLib::KeyStatus keys;
		engine->getKeyStatus(keys);
		if (keys.esc) {
			Destroy();
			engine->quit();
		}

		for (auto go = game_objects.begin(); go != game_objects.end(); go++)
			(*go)->Update(dt);
	}

	virtual void Draw()
	{
		engine->swapBuffers();
		engine->clearWindow();
	}

	virtual void Receive(Message m)
	{
	}

	virtual void Destroy()
	{
		SDL_Log("Game::Destroy");

		for (auto go = game_objects.begin(); go != game_objects.end(); go++)
			(*go)->Destroy();
	

		delete wall;
		delete player;
		delete enemy;
		ice_pool.Destroy();
	}
	void buildMap() {

		//Hardcoding the map layout.
		initIceCoords(1, 0);
		initIceCoords(1, 1);
		initIceCoords(2, 1);
		initIceCoords(5, 1);
		initIceCoords(6, 1);
		initIceCoords(7, 1);
		initIceCoords(8, 1);
		initIceCoords(9, 1);
		initIceCoords(11, 1);
		initIceCoords(3, 2);
		initIceCoords(7, 2);
		initIceCoords(11, 2);
		initIceCoords(1, 3);
		initIceCoords(3, 3);
		initIceCoords(4, 3);
		initIceCoords(5, 3);
		initIceCoords(7, 3);
		initIceCoords(9, 3);
		initIceCoords(10, 3);
		initIceCoords(11, 3);
		initIceCoords(1, 4);
		initIceCoords(7, 4);
		initIceCoords(9, 4);
		initIceCoords(11, 4);
		initIceCoords(1, 5);
		initIceCoords(2, 5);
		initIceCoords(3, 5);
		initIceCoords(4, 5);
		initIceCoords(5, 5);
		initIceCoords(6, 5);
		initIceCoords(7, 5);
		initIceCoords(9, 5);
		initIceCoords(11, 5);
		initIceCoords(5, 6);
		initIceCoords(9, 6);
		initIceCoords(0, 7);
		initIceCoords(1, 7);
		initIceCoords(3, 7);
		initIceCoords(5, 7);
		initIceCoords(7, 7);
		initIceCoords(8, 7);
		initIceCoords(9, 7);
		initIceCoords(10, 7);
		initIceCoords(11, 7);
		initIceCoords(12, 7);
		initIceCoords(1, 8);
		initIceCoords(3, 8);
		initIceCoords(5, 8);
		initIceCoords(7, 8);
		initIceCoords(1, 9);
		initIceCoords(2, 9);
		initIceCoords(3, 9);
		initIceCoords(5, 9);
		initIceCoords(7, 9);
		initIceCoords(8, 9);
		initIceCoords(9, 9);
		initIceCoords(10, 9);
		initIceCoords(11, 9);
		initIceCoords(1, 10);
		initIceCoords(5, 10);
		initIceCoords(7, 10);
		initIceCoords(11, 10);
		initIceCoords(1, 11);
		initIceCoords(3, 11);
		initIceCoords(4, 11);
		initIceCoords(5, 11);
		initIceCoords(7, 11);
		initIceCoords(9, 11);
		initIceCoords(10, 11);
		initIceCoords(11, 11);
		initIceCoords(1, 12);
		initIceCoords(3, 12);
		initIceCoords(5, 12);
		initIceCoords(7, 12);
		initIceCoords(3, 13);
		initIceCoords(5, 13);
		initIceCoords(7, 13);
		initIceCoords(9, 13);
		initIceCoords(11, 13);
		initIceCoords(3, 14);
		initIceCoords(7, 14);
		initIceCoords(9, 14);
		initIceCoords(11, 14);

	}
};