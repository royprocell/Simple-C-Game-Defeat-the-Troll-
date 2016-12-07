//Defeat the Troll: EntityPlayer.h

// Author: Roy Procell

#pragma once

#include "Entity.h"
#include "EntityBoss.h"
#include <SFML/Graphics.hpp>
using namespace sf;
#include "EntityBullet.h"
#include <vector>
using namespace std;

class EntityBoss;   //used to get around circular header dependency

class EntityPlayer
{
public:
    EntityBoss GetBoss();
    EntityPlayer();
    Entity e;   //holds basic info such as position, height, width...
    EntityPlayer(double x, double y, int w, int h, Texture &p, Texture &b1);
    void Attack(EntityBoss *b);
    void Update(EntityBoss *b);
    void Render(RenderWindow *w);
    RectangleShape GetBounds();

    void SetPlayerTexture(Texture *t);
    void SetBullet1Texture(Texture *t);

    Texture GetPlayerTexture();
    Texture GetBullet1Texture();

    int GetBulletsShot();
    void SetBulletsShot(int b);

private:
    int count;  //used to count how long to wait before firing a bullet
    //texture p is for the player, b1 is for the player's bullets
    Texture *p;
    Texture *b1;
    //this is the bullet vector where all bullets are stored
    vector<EntityBullet> bulletVector;
    RectangleShape bounds;
    int numBulletsShot;
};
