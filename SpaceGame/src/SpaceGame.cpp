#include "SpaceGame.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Ship.h"
#include "NPC.h"
#include "Background.h"
#include "BulletPool.h"
#include "Bullet.h"

#include <iostream>

SpaceGame::SpaceGame()
	: Layer("SpaceGame"), m_CameraController(1280.0f / 720.0f)
{
	m_CameraController.SetZoomLevel(-5.0f);

}

void SpaceGame::OnAttach()
{
	HZ_PROFILE_FUNCTION();

	bulletPool.reset(new BulletPool());
	bulletPool->init();

	player.reset(new Ship());
	player->init();

	npc.reset(new NPC());
	npc->init();

	npc->setPlayer(player);

	Hazel::Ref<SpaceGame> game;
	game.reset(this);
	npc->setGame(game);

	background.reset(new Background());
	background->init();


}

void SpaceGame::OnDetach()
{
	HZ_PROFILE_FUNCTION();

	player.reset();
	npc.reset();
	background.reset();
	bulletPool.reset();
}

void SpaceGame::OnUpdate(Hazel::Timestep ts)
{
	HZ_PROFILE_FUNCTION();

	// Render
	Hazel::Renderer2D::ResetStats();
	{
		HZ_PROFILE_SCOPE("Renderer Prep");
		Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hazel::RenderCommand::Clear();
	}

	{

		HZ_PROFILE_SCOPE("Renderer Draw");
		Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());

		//Draw ship
		if(player->isLive())
			player->draw();

		//Draw npc
		if(npc->isLive())
			npc->draw();

		// Draw bullet pool
		bulletPool->draw();
		
		Hazel::Renderer2D::EndScene();

		Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
		
		//Draw background
		background->draw();

		Hazel::Renderer2D::EndScene();
	}

	{
		HZ_PROFILE_SCOPE("Updates")
		// Update
		//m_CameraController.OnUpdate(ts);
		background->update(ts);
		player->update(ts);
		npc->update(ts);

		bulletPool->update(ts);
		bulletPool->processCollisions(player);
		bulletPool->processCollisions(npc);
		bulletPool->recycleBullets();

		if (!player->isLive())
			player->respawn();
	}
}

void SpaceGame::OnImGuiRender()
{
	HZ_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = Hazel::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	//ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	glm::vec3 target = npc->getTarget();
	ImGui::Text("NPC target: <%f, %f, %f>", target.x, target.y, target.z);

	glm::vec3 playerPos = player->getPosition();
	ImGui::Text("Player position: <%f, %f, %f>", playerPos.x, playerPos.y, playerPos.z);

	float bullets;
	bullets = bulletPool->getLiveCount();
	ImGui::Text("Bullets live: <%d>", bullets);

	if(player->collides())
		ImGui::Text("Player sheilds are down");
	else
		ImGui::Text("Player sheilds are up");

	float hullTimer = player->getHullTimer();
	float hullCooldown = player->getHullCooldown();

	ImGui::Text("Hull timer: %f", hullTimer);
	ImGui::Text("Hull cooldown: %f", hullCooldown);

	ImGui::End();
}

void SpaceGame::OnEvent(Hazel::Event& e)
{
	//m_CameraController.OnEvent(e);

	Hazel::KeyCode key;

	if (e.GetCategoryFlags() & Hazel::EventCategoryKeyboard) {

		switch (e.GetEventType())
		{
		case Hazel::EventType::KeyPressed:
			key = dynamic_cast<Hazel::KeyPressedEvent&>(e).GetKeyCode();
			switch (key)
			{
			case Hazel::Key::Escape:
				std::cout << "Escape Pressed" << std::endl;
				break;
			case Hazel::Key::Space:
				
				break;
			}
			break;
		case Hazel::EventType::KeyReleased:
			key = dynamic_cast<Hazel::KeyReleasedEvent&>(e).GetKeyCode();
			switch (key)
			{
			case Hazel::Key::Escape:
				std::cout << "Escape Released" << std::endl;
				break;
			}
			break;
		case Hazel::EventType::KeyTyped:
			break;
		default:
			break;
		}
	}
}

void SpaceGame::fireBullet(glm::vec3 direction, glm::vec3 position)
{
	Hazel::Ref<Bullet> bullet = bulletPool->getBullet();

	if (bullet == nullptr) return;

	bullet->init();
	bullet->setDirection(direction);
	bullet->setPosition(position);
	bullet->setState(Bullet::LIVE);
}

