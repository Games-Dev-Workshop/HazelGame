#pragma once

#include "Hazel.h"

class Ship;
class NPC;
class Background;

class SpaceGame : public Hazel::Layer
{
public:
	SpaceGame();
	virtual ~SpaceGame() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Hazel::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Hazel::Event& e) override;
private:
	Hazel::OrthographicCameraController m_CameraController;
	
	// convert to hazel ptrs?
	std::shared_ptr<Ship> player;
	std::shared_ptr<NPC> npc;
	std::shared_ptr<Background> background;

	// for imgui overlay
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};
