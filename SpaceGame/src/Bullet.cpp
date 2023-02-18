#include "Bullet.h"

#include <glm/glm.hpp> // normalise
#include <glm/gtx/fast_square_root.hpp> // fast normalise 

const float Bullet::MAX_VELOCITY = 5.0f;

Bullet::Bullet()
{
	rotation = 0.0f;
	position = { 0.0f, 0.0f, 0.0f };
	size = { 1.0f, 1.0f };
	velocity = { 0.0f,0.0f,0.0f };

	active = false;
}

Bullet::~Bullet()
{

}
void Bullet::init()
{
	m_CheckerboardTexture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");

	active = false;
}

void Bullet::draw()
{
	Hazel::Renderer2D::DrawRotatedQuad(position, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 1.0f);
}

void Bullet::update(Hazel::Timestep ts)
{
	HZ_PROFILE_FUNCTION();

	

	position += (velocity *= ts.GetSeconds());

}

void Bullet::setDirection(glm::vec3 direction)
{
	velocity = glm::fastNormalize(direction);
	velocity *= Bullet::MAX_VELOCITY;
}

void Bullet::setPosition(glm::vec3 position) 
{
	this->position = position;
}
