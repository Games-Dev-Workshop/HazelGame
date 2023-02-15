#pragma once

#include "Hazel.h"

class Ship;

class NPC
{
private: 
	Hazel::Ref<Ship>player;
	Hazel::Ref<Hazel::Texture2D> m_CheckerboardTexture;
	float rotation;
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec2 size;
	glm::vec3 forward;
	static const float MAX_VELOCITY;
	
 
	float safeDistance;
	float slowingRadius;

	void manouver();
	void attack();

	glm::vec3 calculateFiringPosition();
	void manouver(glm::vec3 firingPos);
public:
	NPC();
	~NPC();

	void init();
	void draw();
	void update(Hazel::Timestep ts);

	void setPlayer(Hazel::Ref<Ship>player);
	Hazel::Ref<Ship> getPlayer();

	glm::vec3 getForward();
};

