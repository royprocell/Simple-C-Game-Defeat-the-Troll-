//Defeat the Troll: EntityBoss.cpp
//EntityBoss is an AI that fires EntityBullets at an EntityPlayer.
// Author: Roy Procell

#include "EntityBoss.h"
#include "EntityBullet.h"
#include "EntityPlayer.h"
#include <vector>
#include <random>
#include <iostream>
using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
using namespace sf;

EntityBoss::EntityBoss()
{
    //initialize the boss to the default entity and leave everything else blank
	e = Entity();
    direction = 0;
    count = 0;
}

EntityBoss::EntityBoss(double x, double y, int w, int h, Texture &b, Texture &b1, Texture &b2, Texture &b3, Texture &b4)
{
	e = Entity(x, y, w, h);
    direction = 0;
    count = 0;
    this->b = &b;
    this->b1 = &b1;
    this->b2 = &b2;
    this->b3 = &b3;
    this->b4 = &b4;
    //initialize the bounding box so we don't have to create a new one each render loop
    bounds.setSize(Vector2f(e.GetWidth(), e.GetHeight()));
    bounds.setTexture(&b);
}

void EntityBoss::Attack(EntityPlayer *p)
{
    //based on the boss's health, choose a different special attack
    //the count variable ensures that the boss fires bullets at a reasonable rate
    //the count is reset after each successful attack, and if the count gets too high it is reset.
	if(e.GetHealth() >= 75)
	{
        if (count == 15)
        {
            AttackSpecialOne();
            count = 0;
        }
	}
    if (e.GetHealth() >= 50 && e.GetHealth() < 75)
	{
        if (count == 30)
        {
            AttackSpecialTwo();
            count = 0;
        }
	}
	if (e.GetHealth() >= 25 && e.GetHealth() < 50)
	{
        if (count == 20)
        {
            AttackSpecialThree(p);
            count = 0;
        }
	}
	if (e.GetHealth() < 25)
	{
        if (count == 13)
        {
            AttackSpecialFour();
            count = 0;
        }
	}
    if (count > 35)
    {
        count = 0;
    }
    count++;
}

void EntityBoss::Update(EntityPlayer *p)
{
    Attack(p);
	
    for (int i = 0; i < bulletVector.size(); i++)
    {
        bulletVector.at(i).Update();

        //if the bullet exits the screen or hits the player, it is dead and needs to be deleted
        if (bulletVector.at(i).e.GetIsDead())
        {
            bulletVector.erase(bulletVector.begin() + i);
        }
        //the bullet hits a player, does its damage, and then dies
        else if (bulletVector.at(i).GetBounds().getGlobalBounds().intersects(p->GetBounds().getGlobalBounds()))	//this line gets the rectangle object of the bullet and the player and then checks the bounds of that object.
        {
            p->e.SetHealth(p->e.GetHealth() - bulletVector.at(i).GetDamage());
            bulletVector.erase(bulletVector.begin() + i);
        }
    }

    //if the troll is below the top of the screen and his direction is up, move him up
    if (e.GetY() >= e.GetSpeed() && direction)
    {
        e.MoveUp();
    }
    //if the troll is above the bottom of the screen and his direction is down, move him down
    else if ((e.GetY() + e.GetHeight()) <= (600 - e.GetSpeed()) && !direction)
    {
        e.MoveDown();
    }

    //if the troll hits the top of the screen, switch his direction
    if (e.GetY() <= e.GetSpeed())
    {
        direction = false;
    }
    //if the troll hits the bottom of the screen, switch his direction
    else if ((e.GetY() + e.GetHeight()) >= (600 - e.GetSpeed()))
    {
        direction = true;
    }

    //every 1 in 100 chance, the troll will randomly change direction. gives it a little more difficulty!
    if ((rand() % 100) < 1)
    {
        if (direction)
        {
            direction = false;
        }
        else
        {
            direction = true;
        }
    }
}

void EntityBoss::Render(RenderWindow *w)
{
    //render the bullets that the boss has fired
    for (int i = 0; i < bulletVector.size(); i++)
    {
        bulletVector.at(i).Render(w);
    }

    //update the boss's position and render him
    bounds.setPosition(e.GetX(), e.GetY());
	w->draw(bounds);
}

void EntityBoss::AttackSpecialThree(EntityPlayer *p)
{
    int j = 0;
    //this if else if block is used to determine the y (int j) direction of the bullet.
    //the goal is to aim it towards the player.
    if (e.GetY() < p->e.GetY())
    {
        j = ((p->e.GetY() - e.GetY())) / 50;
    }
    else if (e.GetY() > p->e.GetY())
    {
        j = -((e.GetY() - (p->e.GetY())) / 50);
    }

    //create a new bullet and add it to the bullet vector.
    //the bullet will stay in memory because the bullet vector is outside of this function.
    EntityBullet b = EntityBullet(e.GetX(), e.GetY() + e.GetHeight() / 2, 15, j, 32, 32, 1, *b3);
    bulletVector.push_back(b);
    numBulletsShot++;
}

EntityPlayer EntityBoss::GetPlayer()    //used to get around circular header dependency
{
    return EntityPlayer();
}

RectangleShape EntityBoss::GetBounds()
{
    return bounds;
}

void EntityBoss::AttackSpecialTwo()
{
    //does a spray of bullets towards the player.
    EntityBullet b = EntityBullet(e.GetX(), e.GetY() + e.GetHeight()/2, 15, 15, 32, 32, 1, *b2);
    bulletVector.push_back(b);
    numBulletsShot++;

    EntityBullet b1 = EntityBullet(e.GetX(), e.GetY() + e.GetHeight() / 2, 15, -15, 32, 32, 1, *b2);
    bulletVector.push_back(b1);
    numBulletsShot++;

    EntityBullet b5 = EntityBullet(e.GetX(), e.GetY() + e.GetHeight() / 2, 15, 7.5, 32, 32, 1, *b2);
    bulletVector.push_back(b5);
    numBulletsShot++;

    EntityBullet b3 = EntityBullet(e.GetX(), e.GetY() + e.GetHeight() / 2, 15, -7.5, 32, 32, 1, *b2);
    bulletVector.push_back(b3);
    numBulletsShot++;

    EntityBullet b4 = EntityBullet(e.GetX(), e.GetY() + e.GetHeight() / 2, 15, 0, 32, 32, 1, *b2);
    bulletVector.push_back(b4);
    numBulletsShot++;
}

void EntityBoss::AttackSpecialOne()
{
    //shoots one medium-fast bullet straight forward.
    EntityBullet b = EntityBullet(e.GetX(), e.GetY() + e.GetHeight() / 2, 20, 0, 32, 32, 1, *b1);
    bulletVector.push_back(b);
    numBulletsShot++;
}

void EntityBoss::AttackSpecialFour()
{
    //shoots one fast bullet straight forward.
    EntityBullet b = EntityBullet(e.GetX(), e.GetY() + e.GetHeight() / 2, 30, 0, 32, 32, 1, *b4);
    bulletVector.push_back(b);
    numBulletsShot++;
}

//getters and setters for textures
Texture EntityBoss::GetBossTexture()
{
    return *b;
}

Texture EntityBoss::GetBullet1Texture()
{
    return *b1;
}

Texture EntityBoss::GetBullet2Texture()
{
    return *b2;
}

Texture EntityBoss::GetBullet3Texture()
{
    return *b3;
}

Texture EntityBoss::GetBullet4Texture()
{
    return *b4;
}

void EntityBoss::SetBossTexture(Texture *t)
{
    b = t;
}

void EntityBoss::SetBullet1Texture(Texture *t)
{
    b1 = t;
}

void EntityBoss::SetBullet2Texture(Texture *t)
{
    b2 = t;
}

void EntityBoss::SetBullet3Texture(Texture *t)
{
    b3 = t;
}

void EntityBoss::SetBullet4Texture(Texture *t)
{
    b4 = t;
}

int EntityBoss::GetBulletsShot()
{
    return numBulletsShot;
}

void EntityBoss::SetBulletsShot(int b)
{
    numBulletsShot = b;
}