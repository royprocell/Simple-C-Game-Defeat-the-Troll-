//Defeat the Troll: main.cpp
//main is the location from which the game loop is handled.
//Author: Roy Procell

#include <iostream>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

#include "EntityBoss.h"
#include "EntityPlayer.h"
#include "Game.h"

int main() {

	/***** PLACE YOUR FILE PROCESSING CODE HERE *****/

    //create the boss texture
    Texture bossTex;
    bossTex.create(32 * 3, 64 * 3);
    if (!bossTex.loadFromFile("boss.png"))
    {
        cerr << "Missing texture!" << endl;
        return -2;
    }

    //crease the player texture
    Texture playerTex;
    playerTex.create(32 * 3, 64 * 3);
    if (!playerTex.loadFromFile("player.png"))
    {
        cerr << "Missing texture!" << endl;
        return -2;
    }

    //create the bullet textures. 0 for player, 1-4 for boss.
    Texture bullet0Tex;
    bullet0Tex.create(32 * 3, 64 * 3);
    if (!bullet0Tex.loadFromFile("bullet0.png"))
    {
        cerr << "Missing texture!" << endl;
        return -2;
    }

    Texture bullet1Tex;
    bullet1Tex.create(32 * 3, 64 * 3);
    if (!bullet1Tex.loadFromFile("bullet1.png"))
    {
        cerr << "Missing texture!" << endl;
        return -2;
    }

    Texture bullet2Tex;
    bullet2Tex.create(32 * 3, 64 * 3);
    if (!bullet2Tex.loadFromFile("bullet2.png"))
    {
        cerr << "Missing texture!" << endl;
        return -2;
    }

    Texture bullet3Tex;
    bullet3Tex.create(32 * 3, 64 * 3);
    if (!bullet3Tex.loadFromFile("bullet3.png"))
    {
        cerr << "Missing texture!" << endl;
        return -2;
    }

    Texture bullet4Tex;
    bullet4Tex.create(32 * 3, 64 * 3);
    if (!bullet4Tex.loadFromFile("bullet4.png"))
    {
        cerr << "Missing texture!" << endl;
        return -2;
    }

    //initialize the boss
    EntityBoss e(32, 32, 32*3, 64*3, bossTex, bullet1Tex, bullet2Tex, bullet3Tex, bullet4Tex);
    e.e.SetHealth(100);

    //initialize the player
    EntityPlayer p((800 - 32*4), 32, 32*2, 64*2, playerTex, bullet0Tex);

    //initialize the game
    Game g;

    //initialize the font for this game
    Font f;
    if (!f.loadFromFile("data/arial.ttf"))
    {
        cerr << "Missing font!" << endl;
        return -1;
    }

	/***** END OF FILE PROCESSING *****/

    // creates the window object with an 800x600 resolution window
    RenderWindow window(VideoMode(800, 600), "Defeat the Troll!");
    window.setFramerateLimit(30);   //set max frame limit so the game doesn't play too fast

    //********************************
    //Game Introduction screen
    g.Introduction(&window, &f);
    //********************************

    while (true)    //this while loop lets us restart the game if we want to. the Game::Stats() function makes sure that this loop doesn't continue forever.
    {
        //if we return from the intro, we must be playing the game!
        g.SetIsPlaying(true);

        // Draw loop: Each iteration of this loop draws a single frame
        while (window.isOpen() && g.GetIsPlaying()) {

            // Erase the screen with white
            window.clear(Color::White);

            /***** PLACE YOUR UPDATE CODE HERE *****/
            e.Update(&p);
            p.Update(&e);
            /***** END OF UPDATE	*****/

            /***** PLACE YOUR DRAWING CODE HERE *****/
            e.Render(&window);
            p.Render(&window);
            g.PrintBossHealth(&window, &f, &e);
            g.PrintPlayerHealth(&window, &f, &p);
            /***** END OF DRAWING	*****/

            if (e.e.GetHealth() <= 0)   //if the troll dies, game ends
            {
                g.SetIsPlaying(false);
            }
            if (p.e.GetHealth() <= 0) //if player dies, game ends
            {
                g.SetIsPlaying(false);
            }

			// Apply all the draws to the screen

            window.display();

            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();
            }
        }

        //****************************
        //End game stats screen
        g.Stats(&window, &f, &e, &p);
        //****************************


		//reset the game for the next round. instead of creating a new EntityBoss/EntityPlayer, just "re-initialize" them to their starting values.
        e = EntityBoss(32, 32, 32 * 3, 64 * 3, bossTex, bullet1Tex, bullet2Tex, bullet3Tex, bullet4Tex);
        e.e.SetHealth(100);	//health normally initialized to 10, must reset to 100
        p = EntityPlayer((800 - 32 * 4), 32, 32 * 2, 64 * 2, playerTex, bullet0Tex);
        e.SetBulletsShot(0);	//reset the bullets shot for the stats at the end of the game!
        p.SetBulletsShot(0);
    }

    return EXIT_SUCCESS;
}
