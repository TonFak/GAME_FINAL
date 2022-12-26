#include <SFML/Graphics.hpp>
#include "playerr.h"
#include "game.h"

int main()
{
    sf::Image back_image;
    back_image.loadFromFile("E:/git/Project_sfml/Project_SFML/images/back.png");//загружаем файл для фона
    sf::Texture back;//текстура фона
    back.loadFromImage(back_image);//заряжаем текстуру картинкой
    sf::Sprite s_back;//создаём спрайт для фона
    s_back.setTexture(back);//заливаем текстуру спрайтом
    s_back.setPosition(0, 0);

    sf::RenderWindow window(sf::VideoMode(1176, 530), "Yep");
    float CurrentFrame = 0;//хранит текущий кадр
    sf::Clock clock;
    sf::Event event;

    Player tut("tut.png", 70, 356, 32, 89);
    Player netut("Gl.png", 700, 362, 56, 81);

    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 500;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close(); // закрыть через Esc


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))//анимация передвижения влево 1 персонажа 
            {
                tut.dir = 1; netut.speed = 0.1;
                CurrentFrame += 0.2 * time;
                if (CurrentFrame > 16) CurrentFrame -= 15;
                tut.sprite.setTextureRect(sf::IntRect(34.1 * int(CurrentFrame), 0, -34.1, 89));
                tut.sprite.move(-1 * time, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//вправо 1
            {
                tut.dir = 0; netut.speed = 0.1;
                CurrentFrame += 0.2 * time;
                if (CurrentFrame > 16) CurrentFrame -= 16;
                tut.sprite.setTextureRect(sf::IntRect(34.1 * int(CurrentFrame), 0, 34, 89));
                tut.sprite.move(1 * time, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))//дополнительная анимация 1
            {
                CurrentFrame += 0.5 * time;
                if (CurrentFrame > 4) CurrentFrame -= 4;
                tut.sprite.setTextureRect(sf::IntRect(46 * int(CurrentFrame), 180, 46, 89));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //анимация передвижения влево 2 персонажа 
            {
                tut.dir = 1; netut.speed = 0.1;
                CurrentFrame += 0.5 * time;
                if (CurrentFrame > 4) CurrentFrame -= 3;
                netut.sprite.setTextureRect(sf::IntRect(47 * int(CurrentFrame), 0, -47, 72));
                netut.sprite.move(-1 * time, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //вправо 2
            {
                tut.dir = 0; netut.speed = 0.1;
                CurrentFrame += 0.5 * time;
                if (CurrentFrame > 4) CurrentFrame -= 4;
                netut.sprite.setTextureRect(sf::IntRect(45 * int(CurrentFrame), 0, 45, 72));
                netut.sprite.move(1 * time, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) //дополнительная анимация 2
            {
                CurrentFrame += 0.2 * time;
                if (CurrentFrame > 6) CurrentFrame -= 6;
                netut.sprite.setTextureRect(sf::IntRect(51 * int(CurrentFrame), 80, 51, 90));
            }

        }
        tut.update(time);
        netut.update(time);
        window.clear();
        window.draw(s_back);// вывести фон
        window.draw(tut.sprite);// вывести персонажа 1
        window.draw(netut.sprite);// вывести персонажа 2
        window.display();
    }

    return 0;
}
