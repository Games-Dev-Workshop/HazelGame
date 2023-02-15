#include "NPC.h"
#include "Ship.h"

#include <glm/glm.hpp> // normalise
#include <glm/gtx/fast_square_root.hpp> // fast normalise 

const float NPC::MAX_VELOCITY = 1.0f;

NPC::NPC()
{
	rotation = 0.0f;
	position = { 3.0f, 0.0f, 0.0f };
	size = { 1.0f, 1.0f };
	velocity = { 0.0f,0.0f,0.0f };
	forward = { 0.0f,1.0f,0.0f };

	safeDistance = 3.0f; // needs playing with?!
	slowingRadius = 1.0f;
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
	//glm::vec3 target = player->getPosition();
	glm::vec3 target = this->calculateFiringPosition();

	// diff vector 
	glm::vec3 diff = position;
	diff -= target;

	// if not in position
	float distanceToTarget = glm::length(diff);
	if (distanceToTarget > 0.1f)
	{
		// move to firing position
		// sets velocity
		manouver(target);
	}
	else
	{
		// attack.
		// also sets velocity. 
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
	
	// Vector in direction of the player
	npcToPlayer = player->getPosition() - this->position;
	// Get the distance
	float distance = glm::length(npcToPlayer);

	glm::vec3 targetVelocity = npcToPlayer;
	targetVelocity = glm::fastNormalize(npcToPlayer);

	float scale = NPC::MAX_VELOCITY * (distance / slowingRadius);
	
	// target Velocity!
	targetVelocity *= scale;

	if (glm::length(targetVelocity) > NPC::MAX_VELOCITY)
	{
		targetVelocity = glm::fastNormalize(targetVelocity);
		targetVelocity *= NPC::MAX_VELOCITY;
	}

	velocity = targetVelocity;

	// call a function to rotate to point forward!!
}

void NPC::attack()
{
	HZ_PROFILE_FUNCTION();
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	

	// Fire projectile ... oh, better write one.

}

glm::vec3 NPC::calculateFiringPosition()
{
	HZ_PROFILE_FUNCTION();
	glm::vec3 playerToNpc;
	glm::vec3 target;

	// Vector in direction of the player
	playerToNpc = player->getPosition() - this->position;

	// normalise - just the direction 
	// glm::normalize(playerToNpc);
	playerToNpc = glm::fastNormalize(playerToNpc);

	// scale - gives a point at the 'safe distance' from the player allowing us to fire. 
	playerToNpc *= safeDistance;

	// add to position - calculate this with reference to the player's position.  
	target = player->getPosition();
	target += playerToNpc;

	return target;
}

