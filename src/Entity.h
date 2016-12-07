//Defeat the Troll: Entity.h

// Author: Roy Procell

#pragma once

#include <vector>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

class Entity
{
	public:
		Entity();
		Entity(double x, double y, int w, int h);
		double GetX();
		double GetY();
		void MoveUp();
		void MoveDown();
        int GetHealth();
        int GetWidth();
        int GetHeight();
        double GetSpeed();
        
        void SetHealth(int h);
        void SetWidth(int w);
        void SetHeight(int h);
        void SetSpeed(double s);
        void SetX(double x);
        void SetY(double y);

        bool GetIsDead();
        void SetIsDead(bool b);

	private:
		bool _isDead;
		int _health;
		vector<double> _pos;    //position vector
		int _width;
		int _height;
		double _speed;
};