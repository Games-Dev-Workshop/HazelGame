#include "Ship.h"

#include <glm/glm.hpp> // normalise
#include <glm/gtx/fast_square_root.hpp> // fast normalise 

#include "Bullet.h"

const float Ship::MAX_VELOCITY = 1.0f;
const float Ship::HULL_COOLDOWN_MAX = 4.0f;
const float Ship::HULL_TIMER_MAX = 4.0f;

Ship::Ship()
{
	rotation = 0.0f;
	position = { 0.0f, 0.0f, 0.0f };
	size = { 1.0f, 1.0f };
	velocity = { 0.0f,0.0f,0.0f };
	colliderOn = true;
	collisionRadius = 0.5f;
	hullTimer = HULL_TIMER_MAX;
	hullCooldown = 0.0f;
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

	if (Hazel::Input::IsKeyPressed(Hazel::Key::P)) 
	{
		// turn hull penetratable - turn off collisions!
		if (collides())
		{
			hullOff();
		}
		else
		{
			hullOn();
		}
	}

	updateHullStatus(ts);

	velocity = glm::fastNormalize(velocity);
	velocity *= Ship::MAX_VELOCITY;

	position += velocity *= ts.GetSeconds();

}

void Ship::hullOn()
{
	collisionsOn();
	hullCooldown = HULL_COOLDOWN_MAX;
}

void Ship::hullOff()
{
	collisionsOff();
	hullTimer = HULL_TIMER_MAX;
}

void Ship::updateHullStatus(Hazel::Timestep ts)
{
	if (!collides()) // collider off hull timer goes down. 
	{
		if (hullTimer > 0.0f)
			hullTimer -= ts;
		else
		{
			hullOn();
		}

		if (hullCooldown < HULL_COOLDOWN_MAX)
			hullCooldown += ts;
		else
		{
	
		}
	}
	else // collider is on hull timer goes down. 
	{


		if (hullCooldown > 0.0f)
			hullCooldown -= ts;
		else
		{

		}

		if (hullTimer < HULL_TIMER_MAX)
			hullTimer += ts;
		else
		{

		}
	}
}

bool Ship::collisionTest(Hazel::Ref<Bullet> bull) 
{
	glm::vec3 distance = position;
	distance -= bull->getPosition();

	if (glm::length(distance) < (getCollisionRadius() + bull->getCollisionRadius()))
	{
		return true;
	}

	return false;
}


void Ship::processCollision(Hazel::Ref<Bullet> bull)
{
	if (this->colliderOn)
	{
		// player takes damage
		bull->setState(Bullet::DEAD);
	}
	else
	{
		// player doesn't take damage
	}
}

float Ship::getHullTimer()
{
	return hullTimer;
}

float Ship::getHullCooldown()
{
	return hullCooldown;
}
