#include "BulletPool.h"

#include <algorithm>
#include <iostream>


#include "Bullet.h"
#include "Ship.h"
#include "NPC.h"

BulletPool::BulletPool()
{
	liveCount = 0;
}

BulletPool::~BulletPool()
{
	for (int i = 0; i < POOL_SIZE; ++i)
	{
		bullets[i]->setState(Bullet::INACTIVE);
		bullets[i].reset();
	}
}
void BulletPool::init()
{
	
	for (int i = 0; i < POOL_SIZE; i++)
	{
		bullets[i].reset(new Bullet());
		bullets[i]->init();
		bullets[i]->setState(Bullet::INACTIVE); // shouldn't need this.
		freeList.push_back(i);
	}
}

void BulletPool::draw()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (bullets[i]->getState() == Bullet::LIVE)
			bullets[i]->draw();

	}
}

void BulletPool::update(Hazel::Timestep ts)
{
	HZ_PROFILE_FUNCTION();

	//for (int i = 0; i < POOL_SIZE; i++)
	for(Hazel::Ref<Bullet> bullet : bullets)
	{
		//if (bullets[i]->isActive())
		if (bullet->getState() == Bullet::LIVE)
		{
			bullet->update(ts);
		}
	}
}


void BulletPool::recycleBullets()
{
	HZ_PROFILE_FUNCTION();

	//for (int i = 0; i < POOL_SIZE; i++)
	for (Hazel::Ref<Bullet> bullet : bullets)
	{
		if (bullet->getState() == Bullet::DEAD)
			returnBullet(bullet);
	}
}

Hazel::Ref<Bullet> BulletPool::getBullet()
{
	if (freeList.empty())
		return nullptr;

	int nextFree = freeList.back();
	freeList.pop_back();
	liveCount++;

	return bullets[nextFree]; 
}

void BulletPool::returnBullet(Hazel::Ref<Bullet> used)
{
	bool found = false;

	int i = 0;
	while ( i < POOL_SIZE && found == false)
	{
		if (bullets[i].get() == used.get())
		{
			found = true;
			freeList.push_back(i);
			liveCount--;
			used->setState(Bullet::INACTIVE);
		}
		
		i++;
	}

	assert(found == true);
}

void BulletPool::processCollisions(Hazel::Ref<Ship> ship)
{
	//for (int i = 0; i < POOL_SIZE; i++)
	for (Hazel::Ref<Bullet> bullet : bullets)
	{
		//if (bullets[i]->isActive())
		if (bullet->getState() == Bullet::LIVE)
		{
			if (ship->collisionTest(bullet) == true)
			{
				ship->processCollision(bullet);
			}
		}
	}
}

void BulletPool::processCollisions(Hazel::Ref<NPC> ship)
{
	//for (int i = 0; i < POOL_SIZE; i++)
	for (Hazel::Ref<Bullet> bullet : bullets)
	{
		//if (bullets[i]->isActive())
		if (bullet->getState() == Bullet::LIVE)
		{
			if (ship->collisionTest(bullet) == true)
			{
				ship->processCollision(bullet);
			}
		}
	}
}

int BulletPool::getLiveCount() 
{
	return liveCount;
}
