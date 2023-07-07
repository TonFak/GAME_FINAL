#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "playerr.h"
#include "game.h"
#include "iostream"


int main()
{
    sf::Image back_image;
    back_image.loadFromFile("E:/git/GAME_FINAL/GAME_FINAL/images/back.png");//загружаем файл для фона
    sf::Texture back;//текстура фона
    back.loadFromImage(back_image);//заряжаем текстуру картинкой
    sf::Sprite s_back;//создаём спрайт для фона
    s_back.setTexture(back);//заливаем текстуру спрайтом
    s_back.setPosition(0, 0);

    sf::Music music;//создаем объект музыки
    music.openFromFile("E:/git/GAME_FINAL/GAME_FINAL/mus.ogg");//загружаем файл
    music.play();//воспроизводим музыку

    sf::Music dr;//создаем объект музыки
    dr.openFromFile("E:/git/GAME_FINAL/GAME_FINAL/dr.ogg");//загружаем файл


    sf::RenderWindow window(sf::VideoMode(1176, 530), "Yep");
    
    sf::Clock clock;
    sf::Event event;

    sf::Image heroImage;
    heroImage.loadFromFile("E:/git/GAME_FINAL/GAME_FINAL/images/wow.png");

    sf::Image enemyImage;
    enemyImage.loadFromFile("E:/git/GAME_FINAL/GAME_FINAL/images/enemy.png");

    sf::Image heroImage2;
    heroImage2.loadFromFile("E:/git/GAME_FINAL/GAME_FINAL/images/Gl.png");

    Player tut(heroImage, 4, 4, 60, 68, "Player1");
    Player netut(heroImage2, 500, 366, 51, 75,"Player2");
    Enemy enemy(enemyImage, 700, 260, 100, 180, "Enemy");
 
    while (window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            dr.play();//воспроизводим музыку
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
        {
            dr.stop();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            music.stop();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
        {
            music.play();
        }

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 500;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close(); // закрыть через Esc
   
        }
        tut.update(time);
        enemy.update(time);
        netut.update(time);
        window.clear();
        window.draw(s_back);// вывести фон
        window.draw(tut.sprite);// вывести персонажа 1
        window.draw(netut.sprite);// вывести персонажа 2
        window.draw(enemy.sprite);
        window.display();
    }

    return 0;
}