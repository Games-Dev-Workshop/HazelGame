#include "Background.h"

Background::Background()
{

}

Background::~Background()
{

}

void Background::init()
{

}

void Background::draw()
{
	for (float y = -5.0f; y < 5.0f; y += 0.5f)
	{
		for (float x = -5.0f; x < 5.0f; x += 0.5f)
		{
			glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
			Hazel::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
		}
	}
}

void Background::update(Hazel::Timestep ts)
{

}
