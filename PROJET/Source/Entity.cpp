#include <Book/Entity.hpp>

#include <cassert>

Entity::Entity()
{

}

Entity::~Entity()
{

}

Entity::Entity(int hitpoints)
: mVelocity()
, mHitPoints(hitpoints)
{
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::marcher(sf::Vector2f velocity)
{
	mVelocity += velocity;
}

void Entity::marcher(float vx, float vy)
{
	mVelocity.x += vx;
	mVelocity.y += vy;
}

int Entity::getHitPoints() const
{
	return mHitPoints;
}

void Entity::repair(int points)
{
	assert(points > 0);

	mHitPoints += points;
}

void Entity::damage(int points)
{
	assert(points > 0);

	mHitPoints -= points;
}

void Entity::destroy()
{
<<<<<<< HEAD
	mVelocity.x += vx;
	mVelocity.y += vy;
=======
	mHitPoints = 0;
>>>>>>> master
}

bool Entity::isDestroyed() const
{
	return mHitPoints <= 0;
}

void Entity::updateCurrent(sf::Time dt, CommandQueue& commands)
{	
	move(mVelocity * dt.asSeconds());
}

void Entity::updateCurrent(sf::Time dt)
{
    move(mVelocity * dt.asSeconds());
}