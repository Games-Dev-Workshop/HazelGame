#pragma once

#include "Hazel.h"

#include <random>

class Ship;
class NPC;
class Background;
class BulletPool;

class SpaceGame : public Hazel::Layer
{
public:
	SpaceGame();
	virtual ~SpaceGame() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void fireBullet(glm::vec3 direction, glm::vec3 position);

	void OnUpdate(Hazel::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Hazel::Event& e) override;

	void seedRandomFloat();
	float getRandomFloat(float min, float max);
	glm::vec3 getRandomOffscreenPosition();
private:
	Hazel::OrthographicCameraController m_CameraController;

	std::mt19937 eng;
	std::uniform_real_distribution<float> randGen;
	
	// convert to hazel ptrs?
	Hazel::Ref<Ship> player;
	Hazel::Ref<NPC> npc;
	Hazel::Ref<NPC> npc2;
	Hazel::Ref<Background> background;
	Hazel::Ref<BulletPool> bulletPool;

	// for imgui overlay
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

};
