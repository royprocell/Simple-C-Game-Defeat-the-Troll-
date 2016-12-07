//Defeat the Troll: Game.h

//Author: Roy Procell
#pragma once

#include <SFML/Graphics.hpp>
#include "EntityPlayer.h"
#include "EntityBoss.h"

using namespace sf;

class Game
{
    public:
        Game();
        void Introduction(RenderWindow *w, Font *f);    //renders an introduction screen
        void Stats(RenderWindow *w, Font *f, EntityBoss *b, EntityPlayer *p);           //renders a screen with stats about the previous game
        bool GetIsPlaying();
        void SetIsPlaying(bool i);
        void PrintBossHealth(RenderWindow *w, Font *f, EntityBoss *b);
        void PrintPlayerHealth(RenderWindow *w, Font *f, EntityPlayer *p);
    private:
        bool isPlaying; //checks to see if we are actually playing the game
};

