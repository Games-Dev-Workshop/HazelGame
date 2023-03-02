#pragma once

#include "Hazel.h"

class Ship;
class SpaceGame;
class Bullet;

class NPC
{
private: 
	Hazel::Ref<Ship>player;
	Hazel::Ref<SpaceGame>game;

	Hazel::Ref<Hazel::Texture2D> m_CheckerboardTexture;
	float rotation;
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec2 size;
	glm::vec3 forward;
	glm::vec3 target;
	float collisionRadius;
	static const float MAX_VELOCITY;
 
	float safeDistance;
	float slowingRadius;
	
	float cooldown;
	static const float MAX_COOLDOWN;

	void manouver();
	void attack();

	glm::vec3 calculateFiringPosition();
	void manouver(glm::vec3 firingPos);

	void fire(glm::vec3 direction);

	static const int MAX_HEALTH = 1;
	int health;
	void takeHit(int hit);

public:
	NPC();
	~NPC();

	void init();
	void draw();
	void update(Hazel::Timestep ts);

	void setPlayer(Hazel::Ref<Ship>player);
	Hazel::Ref<Ship> getPlayer();

	glm::vec3 getForward();
	glm::vec3 getTarget();

	void setGame(Hazel::Ref<SpaceGame>game);

	bool isLive();
	void respawn();

	inline float getCollisionRadius() { return collisionRadius; };
	inline void setCollisionRadius(float cr) { collisionRadius = cr; };

	bool collisionTest(Hazel::Ref<Bullet> bull);
	void processCollision(Hazel::Ref<Bullet> bull);
};

