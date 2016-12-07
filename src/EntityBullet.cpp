//Defeat the Troll: EntityBullet.cpp
//EntityBullet is an entity created by both EntityPlayer and EntityBoss
//They are meant to do damage to either a player or a boss.
// Author: Roy Procell

#include "EntityBullet.h"
#include <SFML/Graphics.hpp>
using namespace sf;

EntityBullet::EntityBullet()
{
    //initialize the bullet to the default entity and leave the rest blank
    e = Entity();
    this->dx = 0;
    this->dy = 0;
    damage = 0;
}

EntityBullet::EntityBullet(double x, double y, double dx, double dy, int w, int h, int d, Texture &b)
{
    e = Entity(x, y, w, h);
    this->dx = dx;
    this->dy = dy;
    damage = d;
    bounds.setSize(Vector2f(e.GetWidth(), e.GetHeight()));
    bounds.setTexture(&b);
}

void EntityBullet::Update()
{
    //as long as the bullet is still on screen, the bullet is not dead
    if (e.GetX() < 800)
    {
        Move();
    }
    else
    {
        e.SetIsDead(true);
    }
}

void EntityBullet::Render(RenderWindow *w)
{
    //update the bullet's position, and draw it
    bounds.setPosition(e.GetX(), e.GetY());
    w->draw(bounds);
}

void EntityBullet::Move()
{
    //move function updates bullet's location with direction.
    e.SetX(e.GetX() + dx);
    e.SetY(e.GetY() + dy);
}

//getters and setters
RectangleShape EntityBullet::GetBounds()
{
    return bounds;
}

int EntityBullet::GetDamage()
{
    return damage;
}

double EntityBullet::GetDX()
{
    return dx;
}

double EntityBullet::GetDY()
{
    return dy;
}

void EntityBullet::SetDamage(int d)
{
    damage = d;
}

void EntityBullet::SetDX(double d)
{
    dx = d;
}

void EntityBullet::SetDY(double d)
{
    dy = d;
}