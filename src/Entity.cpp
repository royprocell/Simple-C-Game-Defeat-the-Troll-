//Defeat the Troll: Entity.cpp
//Entity is the basic building block of the boss, player, and bullet.
// Author: Roy Procell

#include "Entity.h"

#include <vector>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

Entity::Entity()
{
    _pos.resize(2); //resize the pos vector to 2, for x and y
	_isDead = false;
	_health = 10;
	_pos.at(0) = 0;
	_pos.at(1) = 0;
	_width = 10;
	_height = 10;
	_speed = 15.0;
}

Entity::Entity(double x, double y, int w, int h)
{
	_isDead = false;
	_health = 10;
	_speed = 15.0;
	
    _pos.resize(2);
	_pos.at(0) = x;
	_pos.at(1) = y;
	_width = w;
	_height = h;
}

//getters and setters
double Entity::GetX()
{
	return _pos.at(0);
}

double Entity::GetY()
{
	return _pos.at(1);
}

void Entity::MoveUp()
{
	_pos.at(1) -= _speed;
}

void Entity::MoveDown()
{
	_pos.at(1) += _speed;
}

double Entity::GetSpeed()
{
    return _speed;
}

int Entity::GetWidth()
{
    return _width;
}

int Entity::GetHeight()
{
    return _height;
}

int Entity::GetHealth()
{
    return _health;
}

void Entity::SetX(double x)
{
    _pos.at(0) = x;
}

void Entity::SetY(double y)
{
    _pos.at(1) = y;
}

void Entity::SetIsDead(bool b)
{
    _isDead = b;
}

bool Entity::GetIsDead()
{
    return _isDead;
}

void Entity::SetHealth(int h)
{
    _health = h;
}

void Entity::SetWidth(int w)
{
    _width = w;
}

void Entity::SetHeight(int h)
{
    _height = h;
}

void Entity::SetSpeed(double s)
{
    _speed = s;
}