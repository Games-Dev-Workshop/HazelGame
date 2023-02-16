#pragma once

#include "Hazel.h"

class Bullet
{
private: 
	Hazel::Ref<Hazel::Texture2D> m_CheckerboardTexture;
	float rotation;
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec2 size;
	static const float MAX_VELOCITY;
public:
	Bullet();
	~Bullet();

	void init();
	void draw();
	void update(Hazel::Timestep ts);

};

