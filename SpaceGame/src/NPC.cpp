#include "NPC.h"
#include "Ship.h"
#include "Bullet.h"
#include "SpaceGame.h"

#include <glm/glm.hpp> // normalise
#include <glm/gtx/fast_square_root.hpp> // fast normalise 

const float NPC::MAX_VELOCITY = 1.0f;
const float NPC::MAX_COOLDOWN = 2.0f;

NPC::NPC()
{
	rotation = 0.0f;
	position = { 3.0f, 0.0f, 0.0f };
	size = { 1.0f, 1.0f };
	velocity = { 0.0f,0.0f,0.0f };
	forward = { 0.0f,1.0f,0.0f };
	target = { 0.0f,0.0f,0.0f };
	safeDistance = 3.0f; // needs playing with?!
	slowingRadius = 1.0f;
	cooldown = 0.0f;
	collisionRadius = 1.0f;
	health = MAX_HEALTH;
}

NPC::~NPC()
{

}

void NPC::init()
{
	m_CheckerboardTexture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");

	cooldown = MAX_COOLDOWN;
}

void NPC::draw()
{
	Hazel::Renderer2D::DrawRotatedQuad(position, size, rotation, m_CheckerboardTexture, 1.0f);
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
	//target = player->getPosition();
	target = this->calculateFiringPosition();

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

	if (cooldown > 0.0f)
	{
		cooldown -= ts;
	}
	
	glm::vec3 delta = velocity;
	delta *= ts.GetSeconds();
	position += delta;

}

glm::vec3 NPC::getForward()
{
	return forward;
}

void NPC::manouver(glm::vec3 firingPos)
{
	HZ_PROFILE_FUNCTION();
	glm::vec3 npcToFiringPos;
	
	// Vector in direction of the target
	npcToFiringPos = firingPos - this->position;
	// Get the distance
	float distance = glm::length(npcToFiringPos);

	glm::vec3 targetVelocity = npcToFiringPos;
	targetVelocity = glm::fastNormalize(npcToFiringPos);

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
	if (cooldown < 0.0f)
	{
		velocity = glm::vec3(0.0f, 0.0f, 0.0f);

		glm::vec3 vecToPlayer = player->getPosition() - position;
		vecToPlayer = glm::fastNormalize(vecToPlayer);

		// Fire projectile ... oh, better write one.
		fire(vecToPlayer);
		cooldown = MAX_COOLDOWN;
	}	
}

glm::vec3 NPC::calculateFiringPosition()
{
	HZ_PROFILE_FUNCTION();
	glm::vec3 playerToNpc;


	// Vector in direction of the player
	playerToNpc = this->position - player->getPosition();

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

glm::vec3 NPC::getTarget() 
{
	return target;
}

void NPC::setGame(Hazel::Ref<SpaceGame>game)
{
	this->game = game;
}

void NPC::fire(glm::vec3 direction)
{
	if (this->game == nullptr) return;

	glm::vec bulletSpawnPos = position;
	glm::vec offset = direction * glm::fastLength(size); 
	bulletSpawnPos = bulletSpawnPos + offset;

	//todo fix this so bullet is infront of NPC
	game->fireBullet(direction, bulletSpawnPos);
}

void NPC::respawn()
{
	//position = { 3.0f, 0.0f, 0.0f };
	position = game->getRandomOffscreenPosition();
	health = MAX_HEALTH;
}

void NPC::takeHit(int hit)
{
	if (health > 0)
		health -= hit;
}

bool NPC::isLive()
{
	if (health < 1)
		return false;
	else
		return true;
}

bool NPC::collisionTest(Hazel::Ref<Bullet> bull)
{
	glm::vec3 distance = position;
	distance -= bull->getPosition();

	if (glm::length(distance) < (getCollisionRadius() + bull->getCollisionRadius()))
	{
		return true;
	}

	return false;
}


void NPC::processCollision(Hazel::Ref<Bullet> bull)
{
	// player takes damage
	this->takeHit(bull->getHitPoints());

	// bullet dies
	bull->setState(Bullet::DEAD);
	
}
