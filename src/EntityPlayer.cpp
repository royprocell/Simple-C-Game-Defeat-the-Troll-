//Defeat the Troll: EntityPlayer.cpp
//EntityPlayer is playable and fires bullets at the EntityBoss.
// Author: Roy Procell

#include "EntityPlayer.h"
#include "Entity.h"
#include "EntityBoss.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
using namespace sf;

EntityPlayer::EntityPlayer()
{
    //set player to default entity and leave everything else blank
    e = Entity();
    count = 0;
}

EntityPlayer::EntityPlayer(double x, double y, int w, int h, Texture &p, Texture &b1)
{
    e = Entity(x, y, w, h);
    count = 0;
    this->p = &p;
    this->b1 = &b1;
    //initialize the bounding box so we don't have to make a new one every render loop
    bounds.setSize(Vector2f(e.GetWidth(), e.GetHeight()));
    bounds.setTexture(&p);
}

void EntityPlayer::Update(EntityBoss *b)
{
    //initialize a keyboard
    Keyboard k;

    if (k.isKeyPressed(k.Up))
    {
        //make sure that the player can't go off screen
        if((e.GetY()) >= e.GetSpeed())
        {
            e.SetY(e.GetY() - e.GetSpeed());
        }
    }

    if (k.isKeyPressed(k.Down))
    {
        //make sure the player can't go off screen
        if ((e.GetY() + e.GetHeight()) <= (600 - e.GetSpeed()))
        {
            e.SetY(e.GetY() + e.GetSpeed());
        }
    }
    //press space to attack
    if (k.isKeyPressed(k.Space))
    {
        Attack(b);
    }

    for (int i = 0; i < bulletVector.size(); i++)
    {
        bulletVector.at(i).Update();
        //bv.at(i).Render(&w);

        //if the bullet exits the screen or hits the player, it is dead and needs to be deleted
        if (bulletVector.at(i).e.GetIsDead())
        {
            bulletVector.erase(bulletVector.begin() + i);
        }
        //if a bullet hits the boss, the boss takes damage and the bullet dies
        else if (bulletVector.at(i).GetBounds().getGlobalBounds().intersects(b->GetBounds().getGlobalBounds()))	//this line gets the rectangle object of the bullet and the player and then checks the bounds of that object.
        {
            b->e.SetHealth(b->e.GetHealth() - bulletVector.at(i).GetDamage());
            bulletVector.erase(bulletVector.begin() + i);
        }
    }
}

void EntityPlayer::Render(RenderWindow *w)
{
    //update the position of the bounds and render it
    bounds.setPosition(e.GetX(), e.GetY());
    w->draw(bounds);

    //render all of the bullets produced by the player
    for (int i = 0; i < bulletVector.size(); i++)
    {
        bulletVector.at(i).Render(w);
    }
}

void EntityPlayer::Attack(EntityBoss *b)
{
    //used to calculate when the player should fire bullets.
    //firing every tick would be way too fast, so we need the count variable to control it.
    if (count == 10)
    {
        EntityBullet bc = EntityBullet(e.GetX(), e.GetY() + (e.GetHeight() / 2), -15, 0, 32, 32, 1, *b1);
        bulletVector.push_back(bc);
        numBulletsShot++;
        count = 0;
    }

    count++;
}

EntityBoss EntityPlayer::GetBoss()  //used to get around circular header dependency
{
    return EntityBoss();
}

RectangleShape EntityPlayer::GetBounds()
{
    return bounds;
}

//texture getters and setters
void EntityPlayer::SetBullet1Texture(Texture *t)
{
    b1 = t;
}

void EntityPlayer::SetPlayerTexture(Texture *t)
{
    p = t;
}

Texture EntityPlayer::GetBullet1Texture()
{
    return *b1;
}

Texture EntityPlayer::GetPlayerTexture()
{
    return *p;
}

int EntityPlayer::GetBulletsShot()
{
    return numBulletsShot;
}

void EntityPlayer::SetBulletsShot(int b)
{
    numBulletsShot = b;
}