//Defeat the Troll: EntityBullet.h

// Author: Roy Procell

#pragma once

#include "Entity.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class EntityBullet
{
public:
    EntityBullet();
    Entity e;   //holds basic info like position, height, width...
    EntityBullet(double x, double y, double dx, double dy, int w, int h, int d, Texture &b);
    void Update();
    void Render(RenderWindow *w);
    RectangleShape GetBounds();
    int GetDamage();
    double GetDX();
    double GetDY();

    void SetDamage(int d);
    void SetDX(double d);
    void SetDY(double d);

private:
    int damage;
    //used to determine the direction that the bullet should move
    double dx;
    double dy;
    void Move();
    RectangleShape bounds;
};

