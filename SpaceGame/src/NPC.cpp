#include "NPC.h"
#include "Ship.h"

const float NPC::MAX_VELOCITY = 1.0f;

NPC::NPC()
{
	rotation = 0.0f;
	position = { 0.0f, 0.0f, 0.0f };
	size = { 1.0f, 1.0f };
	velocity = { 0.0f,0.0f,0.0f };
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

	// locate player


	// identify firing position (close but not too close on current heading). 

	// if not in position
		// move to firing position
	//else
		// attach.

	position += velocity *= ts.GetSeconds();

}

void manouver(glm::vec3 firingPos)
{
	HZ_PROFILE_FUNCTION();

}

void NPC::attack()
{
	HZ_PROFILE_FUNCTION();

}

glm::vec3 NPC::calculateFiringPosition()
{
	HZ_PROFILE_FUNCTION();
	glm::vec3 playerToNpc;
	glm::vec3 target;

	playerToNpc = this->position - player->getPosition();

	// normalise 

	// scale

	// add to position. 
}

