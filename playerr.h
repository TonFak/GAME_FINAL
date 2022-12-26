#pragma once
#include <SFML/Graphics.hpp>
class Player
{
private:
    float m_x, m_y, m_w, m_h;//координаты игрока х и у, высота ширина
    sf::String m_File;

public:
    float dx, speed; //ускорение (по х), сама скорость
    int dir; //направление движения игрока
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    Player(sf::String f, float x, float y, float w, float h) //При создании объекта класса будет задаваться имя файла, координату Х и У, ширину и высоту
    {
        dx = 0; speed = 0; dir = 0; m_File = f;
        m_w = w; m_h = h;
        image.loadFromFile("E:/git/Project_sfml/Project_SFML/images/" + m_File);//
        texture.loadFromImage(image);//закидываем изображение в текстуру
        sprite.setTexture(texture);//заливаем спрайт текстурой
        m_x = x; m_y = y;//координата появления спрайта
        sprite.setTextureRect(sf::IntRect(0, 0, w, h));
        sprite.setPosition(x, y);//Задаем спрайту один прямоугольник для вывода одного персонажа IntRect 
    }
    void update(float time) {} // принимает в себя время SFML, вследствие чего работает бесконечно, давая персонажу движение  
};