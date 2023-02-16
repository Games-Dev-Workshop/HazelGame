#include "Ship.h"

#include <glm/glm.hpp> // normalise
#include <glm/gtx/fast_square_root.hpp> // fast normalise 

const float Ship::MAX_VELOCITY = 1.0f;

Ship::Ship()
{
	rotation = 0.0f;
	position = { 0.0f, 0.0f, 0.0f };
	size = { 1.0f, 1.0f };
	velocity = { 0.0f,0.0f,0.0f };
}

Ship::~Ship()
{

}

glm::vec3 Ship::getPosition()
{
	return position;
}

void Ship::init()
{
	m_CheckerboardTexture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Ship::draw()
{
	Hazel::Renderer2D::DrawRotatedQuad(position, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 1.0f);
}

void Ship::update(Hazel::Timestep ts)
{
	HZ_PROFILE_FUNCTION();

	if (Hazel::Input::IsKeyPressed(Hazel::Key::A))
	{
		velocity.x = 1.0f;
	}
	else if (Hazel::Input::IsKeyPressed(Hazel::Key::D))
	{
		velocity.x = -1.0f;
	}
	else 
	{
		// put decay here;
		velocity.x = 0.0f;
	}

	if (Hazel::Input::IsKeyPressed(Hazel::Key::W))
	{
		velocity.y = -1.0f;
	}
	else if (Hazel::Input::IsKeyPressed(Hazel::Key::S))
	{
		velocity.y = 1.0f;
	}
	else
	{
		// put decay here;
		velocity.y = 0.0f;
	}

	velocity = glm::fastNormalize(velocity);
	velocity *= Ship::MAX_VELOCITY;

	position += velocity *= ts.GetSeconds();

}
