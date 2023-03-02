#pragma once

#include "Hazel.h"

class Bullet
{
public: 
	enum State { LIVE = 0, DEAD, INACTIVE };
private:
	Hazel::Ref<Hazel::Texture2D> m_CheckerboardTexture;
	float rotation;
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec2 size;
	static const float MAX_VELOCITY;
	static const float MAX_LIFETIME;
	Bullet::State state;
	float life;
	float collisionRadius;
	int hitPoints;
public:
	Bullet();
	~Bullet();

	void init();
	void setDirection(glm::vec3 direction);
	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();

	void draw();
	void update(Hazel::Timestep ts);

	inline State getState() { return state; };
	inline void setState(State a) { state = a; };

	int getHitPoints();

	inline float getCollisionRadius() { return collisionRadius; };
	inline void setCollisionRadius(float cr) { collisionRadius = cr; };
};

