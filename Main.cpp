#pragma once
#include "Generation.h"

// La map est générée en "temps réel" à travers les différents bruits
// Les FLECHES permettent de se déplacer dans la génération
// ESPACE pour stopper le déplacement
// CLIC GAUCHE lance une nouvelle Génération
// LIBNOISE est la libraire que j'ai utilisé

//Si j'avais eu le temps j'aurais mieux géré le calcul de la génération ET l'architecture
//chaque case est recalculée chaque frame (lors de déplacements) alors que j'aurais pu que recalculer les nouvelles cases

//Sinon trés bon exercice très interessant et on a envie de continuer tellement on peux faire de choses



int main()
{
    const unsigned int xHeight = 1000;
    const unsigned int yWidth = 1000;
    sf::RenderWindow window(sf::VideoMode(yWidth, xHeight), "Perlin2DGeneration");

    sf::Sprite spriteToDraw;
    Generation myGen;
    myGen.StartGeneration();
    spriteToDraw = myGen.Render();

    while (window.isOpen())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if ((event.type == sf::Event::MouseButtonPressed) && (event.key.code == sf::Mouse::Button::Left)) {
                //std
                myGen.dir.x = 0;
                myGen.dir.y = 0;
                myGen.StartGeneration();
            }

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up))
            {
                myGen.dir.y = -1;
                myGen.dir.x = 0;
                
                    //dir.y = 0;
            }
            if ((event.type == sf::Event::KeyPressed)  && (event.key.code == sf::Keyboard::Down)) {

                myGen.dir.y = 1;
                myGen.dir.x = 0;
                
                    //dir.y = 0;
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left))
            {
                    myGen.dir.x = -1;
                    myGen.dir.y = 0;
                
                    //dir.x = 0;
            }
            if ((event.type == sf::Event::KeyPressed)  && (event.key.code == sf::Keyboard::Right))
            {
                myGen.dir.x = 1;
                myGen.dir.y = 0;
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
            {
                myGen.dir.x = 0;
                myGen.dir.y = 0;
            }
            
        }

        window.clear(); 
        myGen.SpriteUpdateOnInput();
        spriteToDraw = myGen.Render();
        window.draw(spriteToDraw);
        window.display();
    }
    return 0;
}
