#include "BulletPool.h"

#include <algorithm>

#include "Bullet.h"

BulletPool::BulletPool()
{
	
}

BulletPool::~BulletPool()
{

}
void BulletPool::init()
{
	for (int i = 0; i < POOL_SIZE; ++i)
	{
		bullets[i].reset(new Bullet());
		bullets[i]->setActive(false); // shouldn't need this.
		freeList.push_back(i);
	}
}

void BulletPool::draw()
{
	for (Hazel::Ref<Bullet> bullet : bullets)
	{
		if (bullet->isActive())
			draw();

	}
}

void BulletPool::update(Hazel::Timestep ts)
{
	HZ_PROFILE_FUNCTION();

	for (Hazel::Ref<Bullet> bullet : bullets)
	{
		if (bullet->isActive())
			update(ts);

	}

}

Hazel::Ref<Bullet> BulletPool::getBullet()
{
	int nextFree = freeList.back();
	freeList.pop_back();

	return bullets[nextFree]; 
}

void BulletPool::returnBullet(Hazel::Ref<Bullet> used)
{
	used->setActive(false);

	bool found = false;

	int i = 0;
	while ( i < POOL_SIZE && found == false)
	{
		if (bullets[i] == used)
		{
			found = true;
			freeList.push_back(i);
		}
		
		i++;
	}

	assert(found == false);
}
