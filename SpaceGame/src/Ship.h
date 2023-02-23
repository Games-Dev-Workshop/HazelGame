#pragma once

#include "Hazel.h"

class Bullet;

class Ship
{
private: 
	Hazel::Ref<Hazel::Texture2D> m_CheckerboardTexture;
	float rotation;
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec2 size;
	static const float MAX_VELOCITY;
	float collisionRadius;
	bool colliderOn;

	static const float HULL_COOLDOWN_MAX;
	float hullCooldown;
	static const float HULL_TIMER_MAX;
	float hullTimer;
public:
	Ship();
	~Ship();

	void init();
	void draw();
	void update(Hazel::Timestep ts);

	glm::vec3 getPosition();

	inline float getCollisionRadius() { return collisionRadius; };
	inline void setCollisionRadius(float cr) { collisionRadius = cr; };

	inline bool collides() { return colliderOn; };
	inline void collisionsOn() { colliderOn = true; };
	inline void collisionsOff() { colliderOn = false; };

	bool collisionTest(Hazel::Ref<Bullet> bull);
	void processCollision(Hazel::Ref<Bullet> bull);

};

