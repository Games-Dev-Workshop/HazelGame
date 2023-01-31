#include "Ship.h"

Ship::Ship()
{
	rotation = 0.0f;
	position = { 2.0f, 0.0f, 0.0f };
	size = { 1.0f, 1.0f };
}

Ship::~Ship()
{

}

void Ship::init()
{
	m_CheckerboardTexture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Ship::draw()
{
	Hazel::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 1.0f);
}

void Ship::update(Hazel::Timestep ts)
{
	rotation += ts * 50.0f;
}
