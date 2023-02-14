#include "NPC.h"
#include "Ship.h"

#include <glm/glm.hpp> // normalise
#include <glm/gtx/fast_square_root.hpp> // fast normalise 

const float NPC::MAX_VELOCITY = 1.0f;

NPC::NPC()
{
	rotation = 0.0f;
	position = { 0.0f, 0.0f, 0.0f };
	size = { 1.0f, 1.0f };
	velocity = { 0.0f,0.0f,0.0f };
	target = { 0.0f,0.0f,0.0f };
	forward = { 0.0f,1.0f,0.0f };

	safeDistance = 4.0f; // needs playing with?!
}

NPC::~NPC()
{

}

void NPC::init()
{
	m_CheckerboardTexture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
}

void NPC::draw()
{
	Hazel::Renderer2D::DrawRotatedQuad(position, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 1.0f);
}

void NPC::setPlayer(Hazel::Ref<Ship> player)
{
	this->player = player;
}

Hazel::Ref<Ship> NPC::getPlayer()
{
	return player;
}

void NPC::update(Hazel::Timestep ts)
{
	HZ_PROFILE_FUNCTION();	

	// Do we have a player?
	if (player == nullptr) return;

	// identify firing position (close but not too close on current heading). 
	glm::vec3 target = this->calculateFiringPosition();

	// if not in position
	if (target == position)
	{
		// move to firing position
		manouver(target);
	}
	else
	{
		// attack.
		attack();
	}

	position += velocity *= ts.GetSeconds();

}

glm::vec3 NPC::getForward()
{
	return forward;
}

void NPC::manouver(glm::vec3 firingPos)
{
	HZ_PROFILE_FUNCTION();
	glm::vec3 npcToPlayer;
	float slowingRadius = safeDistance;
	
	// Vector in direction of the player
	npcToPlayer = this->position - player->getPosition();
	// Get the distance
	float distance = npcToPlayer.length();

	glm::vec3 forward = getForward();

	float scale = NPC::MAX_VELOCITY * (distance / slowingRadius);
	
	// target Velocity!
	forward *= scale;

	if (forward.length() > 1.0f) 
	{
		glm::normalize(forward);
		velocity += forward; // go forwards
	}
	else 
	{
		// In earlier code this was set to velocity?  
		// I'm not sure why ... oh wait is that what's 
		// wrong with the NPC in the java game?
		velocity = { 0.0f,0.0f,0.0f };
	}

	// call a function to rotate to point forward!!
}

void NPC::attack()
{
	HZ_PROFILE_FUNCTION();

	// Fire projectile ... oh, better write one.

}

glm::vec3 NPC::calculateFiringPosition()
{
	HZ_PROFILE_FUNCTION();
	glm::vec3 playerToNpc;
	glm::vec3 target;

	// Vector in direction of the player
	playerToNpc = this->position - player->getPosition();

	// normalise - just the direction 
	// glm::normalize(playerToNpc);
	glm::fastNormalize(playerToNpc);

	// scale - gives a point at the 'safe distance' from the player allowing us to fire. 
	playerToNpc *= safeDistance;

	// add to position - calculate this with reference to the player's position.  
	target = player->getPosition();
	target += playerToNpc;

	return target;
}

