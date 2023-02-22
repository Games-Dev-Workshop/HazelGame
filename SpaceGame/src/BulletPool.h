#pragma once

#include "Hazel.h"

#include <deque>

class Bullet;
class Ship;

class BulletPool
{
private:
	static const int POOL_SIZE = 100;
	std::array<Hazel::Ref<Bullet>, POOL_SIZE> bullets;
	std::deque<int> freeList;
public:
	BulletPool();
	~BulletPool();

	void init();
	void draw();
	void update(Hazel::Timestep ts);

	Hazel::Ref<Bullet> getBullet();
	void returnBullet(Hazel::Ref<Bullet>);

	void processCollisions(Hazel::Ref<Ship>);
};

