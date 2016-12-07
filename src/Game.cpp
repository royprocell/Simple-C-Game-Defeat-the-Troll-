//Defeat the Troll: Game.cpp
//Game handles the intro and stats screens.
//Author: Roy Procell

#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
using namespace sf;

#include "EntityPlayer.h"
#include "EntityBoss.h"

#include <iostream>
#include <string>
#include <ctime>
using namespace std;

#include <fstream>

Game::Game()
{
    isPlaying = false;
}

void Game::Introduction(RenderWindow *w, Font *f)
{
    //create the background image
    Texture t;
    t.create(800, 600);
    if (!t.loadFromFile("intro.png"))
    {
        cerr << "Missing texture!" << endl;
        exit(-2);
    }
    RectangleShape introScreen;
    introScreen.setSize(Vector2f(800, 600));
    introScreen.setPosition(0, 0);
    introScreen.setTexture(&t);

    //set intro text
    Text txt;
    txt.setFont(*f);
    txt.setPosition(0,0);
    txt.setString("Oh no! You've been visited by an INTERNET TROLL.\nUse meme magic to make \nhim go away!\n\nPress enter to play\n\nSpace to fire,\nUp/Down arrows to move");
    txt.setCharacterSize(32);
    txt.setColor(Color::Blue);
    txt.setStyle(Text::Bold | Text::Underlined);

    while (w->isOpen())
    {
        w->clear();
        w->draw(introScreen);
        w->draw(txt);
        w->display();

        Keyboard k;
        if (k.isKeyPressed(k.Return))   //if the player inputs return, play the game
        {
            break;
        }
        if (k.isKeyPressed(k.Q))    //if the player inputs q, close the program
        {
            w->close();
            exit(0);
        }
        Event event;
        while (w->pollEvent(event)) {
            if (event.type == Event::Closed)
            {
                w->close();
                exit(0);
            }
        }
    }
}

void Game::Stats(RenderWindow *w, Font *f, EntityBoss *b, EntityPlayer *p)
{
    //create the background image
    //we will reuse the image from the intro for the stats screen.
    Texture t;
    t.create(800, 600);
    if (!t.loadFromFile("intro.png"))
    {
        cerr << "Missing texture!" << endl;
        exit(-2);
    }
    RectangleShape introScreen;
    introScreen.setSize(Vector2f(800, 600));
    introScreen.setPosition(0, 0);
    introScreen.setTexture(&t);

    //set stats text
    Text txtOutcome;
    if (p->e.GetHealth() <= 0)//if the player died, he loses, otherwise he wins
    {
        txtOutcome.setFont(*f);
        txtOutcome.setPosition(0, 0);
        txtOutcome.setString("Oh no! The troll made you ragequit!");
        txtOutcome.setCharacterSize(32);
        txtOutcome.setColor(Color::Red);
        txtOutcome.setStyle(Text::Bold | Text::Underlined);
    }
    else
    {
        txtOutcome.setFont(*f);
        txtOutcome.setPosition(0, 0);
        txtOutcome.setString("Hooray! You defeated the troll!");
        txtOutcome.setCharacterSize(32);
        txtOutcome.setColor(Color::Green);
        txtOutcome.setStyle(Text::Bold | Text::Underlined);
    }

    //create strings out of the game data and concatenate them together
    //so we can create a text object and print them
    string stats;
    string playerBullets = to_string(p->GetBulletsShot());
    string bossBullets = to_string(b->GetBulletsShot());
    string playerHealth = to_string(p->e.GetHealth());
    string bossHealth = to_string(b->e.GetHealth());
    stats = "Stats:\n";
    stats += "Player Bullets Fired: ";
    stats += playerBullets;
    stats += "\nBoss Bullets Fired: ";
    stats += bossBullets;
    stats += "\nPlayer Health Remaining: ";
    stats += playerHealth;
    stats += "\nBoss Health Remaining: ";
    stats += bossHealth;

    Text txt;
    txt.setFont(*f);
    txt.setPosition(0, 64);
    txt.setString(stats);
    txt.setCharacterSize(32);
    txt.setColor(Color::Blue);
    txt.setStyle(Text::Bold | Text::Underlined);

    Text txtEnd;
    txtEnd.setFont(*f);
    txtEnd.setPosition(0, 600 - 38);
    txtEnd.setString("Press enter to play again or Q to quit");
    txtEnd.setCharacterSize(32);
    txtEnd.setColor(Color::Blue);
    txtEnd.setStyle(Text::Bold | Text::Underlined);

    //save the stats string to a file so the player can see how they did afterward
	ofstream statFile("stats.txt");
	statFile << stats;
	statFile.close();

    while (w->isOpen())
    {
        w->clear();
        w->draw(introScreen);
        w->draw(txtOutcome);
        w->draw(txt);
        w->draw(txtEnd);
        w->display();

        Keyboard k;
        if (k.isKeyPressed(k.Return))   //if the player inputs return, play the game again
        {
            break;
        }
        if (k.isKeyPressed(k.Q))    //if the player inputs q, close the program
        {
            w->close();
            exit(0);
        }
        Event event;
        while (w->pollEvent(event)) {
            if (event.type == Event::Closed)
            {
                w->close();
                exit(0);
            }
        }
    }
}

//getters and setters for the game
bool Game::GetIsPlaying()
{
    return isPlaying;
}

void Game::SetIsPlaying(bool i)
{
    isPlaying = i;
}

void Game::PrintBossHealth(RenderWindow *w, Font *f, EntityBoss *b)
{
    //creates a text object and prints the health of the boss.
    Text txt;
    txt.setFont(*f);
    txt.setPosition(0, 0);
    txt.setString("Boss Health:");
    txt.setCharacterSize(32);
    txt.setColor(Color::Red);
    txt.setStyle(Text::Bold);
    w->draw(txt);

    string h = to_string(b->e.GetHealth());
    Text txt1;
    txt1.setFont(*f);
    txt1.setPosition(0, 32);
    txt1.setString(h);
    txt1.setCharacterSize(32);
    txt1.setColor(Color::Red);
    txt1.setStyle(Text::Bold);
    w->draw(txt1);
}

void Game::PrintPlayerHealth(RenderWindow *w, Font *f, EntityPlayer *p)
{
    //creates a text object and prints the health of the boss.
    Text txt;
    txt.setFont(*f);
    txt.setPosition(580, 0);
    txt.setString("Player Health:");
    txt.setCharacterSize(32);
    txt.setColor(Color::Red);
    txt.setStyle(Text::Bold);
    w->draw(txt);

    string h = to_string(p->e.GetHealth());
    Text txt1;
    txt1.setFont(*f);
    txt1.setPosition(760, 32);
    txt1.setString(h);
    txt1.setCharacterSize(32);
    txt1.setColor(Color::Red);
    txt1.setStyle(Text::Bold);
    w->draw(txt1);
}