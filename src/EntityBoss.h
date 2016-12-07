//Defeat the Troll: EntityBoss.h

// Author: Roy Procell

#pragma once

#include "Entity.h"
#include "EntityBullet.h"
#include "EntityPlayer.h"

#include <vector>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

class EntityPlayer; //used to get around circular header dependency

class EntityBoss
{
	public:
        EntityPlayer GetPlayer();
		Entity e;   //holds basic info like position, height, width...
		EntityBoss();
		EntityBoss(double x, double y, int w, int h, Texture &b, Texture &b1, Texture &b2, Texture &b3, Texture &b4);
		void Attack(EntityPlayer *p);
		void Update(EntityPlayer *p);
		void Render(RenderWindow *w);
        RectangleShape GetBounds();

        Texture GetBossTexture();
        Texture GetBullet1Texture();
        Texture GetBullet2Texture();
        Texture GetBullet3Texture();
        Texture GetBullet4Texture();

        void SetBossTexture(Texture *t);
        void SetBullet1Texture(Texture *t);
        void SetBullet2Texture(Texture *t);
        void SetBullet3Texture(Texture *t);
        void SetBullet4Texture(Texture *t);
        int GetBulletsShot();
        void SetBulletsShot(int b);

	private:
		void AttackSpecialThree(EntityPlayer *p);   //attack 3 needs a player because it is not random, it tracks the player
        //this boolean tells which way the boss is moving.
        //0 for down, 1 for up.
        bool direction;
        int count;
        vector<EntityBullet> bulletVector;
        //texture b is the boss texture, and b1-b4 are the bullet texture depending on how much health the boss has
        Texture *b;
        Texture *b1;
        Texture *b2;
        Texture *b3;
        Texture *b4;
        RectangleShape bounds;
		void AttackSpecialTwo();
		void AttackSpecialOne();
		void AttackSpecialFour();
        int numBulletsShot;
};