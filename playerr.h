#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
    double dx, dy, x, y, speed, moveTimer;
    double w, h, health;
    bool life, isMove, onGround;
    float CurrentFrame = 0;//хранит текущий кадр
    sf::Texture texture;
    sf::Sprite sprite;
    sf::String name;//различим врагов по имени и дадим каждому свое действие в update в зависимости от имени
    Entity(sf::Image& image, float X, float Y, float W, float H, sf::String Name) 
    {
        x = X; y = Y; w = W; h = H; name = Name; 
        speed = 0; health = 100; dx = 0; dy = 0; moveTimer = 0;
        life = true; onGround = false; isMove = false;
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setOrigin(w / 2, h / 2);
    }
}; 

class Player : public Entity
{
public:
    enum { left, right, jump, left2, right2, jump2, stay, stay2 } state1, state2;//добавляем тип перечисления - состояние объекта
    Player(sf::Image& image, float X, float Y, float W, float H, sf::String Name) :Entity(image, X, Y, W, H, Name) //При создании объекта класса будет задаваться имя файла, координату Х и У, ширину и высоту
    {
        state1 = stay;
        state2 = stay2;
        if (name == "Player1")
        {
            sprite.setTextureRect(sf::IntRect(70, 5, W, H));
        }
        if (name == "Player2")
        {
            sprite.setTextureRect(sf::IntRect(4, 4, W, H));
        }
    }
    void control()
    {
        if (name == "Player1")
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))//анимация передвижения влево 1 персонажа 
            {
                state1 = left;
                speed = 0.1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//вправо 1
            {
                state1 = right;
                speed = 0.1;
            }
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (onGround))
            {
                state1 = jump;
                dy = -0.6;
                onGround = false;
            }
        }
        if (name == "Player2")
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))//анимация передвижения влево 1 персонажа 
            {
                state2 = left2;
                speed = 0.1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))//вправо 1
            {
                state2 = right2;
                speed = 0.1;
            }
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && (onGround))
            {
                state2 = jump2;
                dy = -0.6;
                onGround = false;
            }
        }
       
    }
    void update(float time) // принимает в себя время SFML, вследствие чего работает бесконечно, давая персонажу движение  
    {
        control();//функция управления персонажем
        if (name == "Player1")
        {
            switch (state1)//тут делаются различные действия в зависимости от состояния
            {
            case right: dx = speed;
                CurrentFrame += 0.005 * time;
                if (CurrentFrame > 5) CurrentFrame -= 4;
                sprite.setTextureRect(sf::IntRect(59 * int(CurrentFrame), 0, 59, 68));
                break;//состояние идти вправо
            case left: dx = -speed;
                CurrentFrame += 0.005 * time;
                if (CurrentFrame > 5) CurrentFrame -= 4;
                sprite.setTextureRect(sf::IntRect(59 * int(CurrentFrame), 0, -59, 68));
                break;//состояние идти влево
            }
        }
        if (name == "Player2")
        {
            switch (state2)
            {
            case right2: dx = speed;
                CurrentFrame += 0.005 * time;
                if (CurrentFrame > 5) CurrentFrame -= 4;
                sprite.setTextureRect(sf::IntRect(46 * int(CurrentFrame), 0, 46, 76));
                break;//состояние идти вправо
            case left2: dx = -speed;
                CurrentFrame += 0.005 * time;
                if (CurrentFrame > 5) CurrentFrame -= 4;
                sprite.setTextureRect(sf::IntRect(46 * int(CurrentFrame), 0, -46, 76));
                break;//состояние идти влево
            }
        }
        x += dx * time;
        checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
        y += dy * time;
        checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y
        if (!isMove) speed = 0;
        sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
        dy = dy + 0.0015 * time;
        //делаем притяжение к земле
    }
    float getplayercoordinateX() 
    {
        return x;
    }
    float getplayercoordinateY() 
    {
        return y;
    }
    void checkCollisionWithMap(float Dx, float Dy)//ф ция проверки столкновений с картой
    {
        if (y > 375) { y = 375;  dy = 0; onGround = true; }//по Y вниз=>идем в пол(стоим на месте) или падаем. В этот момент надо вытолкнуть персонажа и поставить его на землю, при этом говорим что мы на земле тем самым снова можем прыгать
        if (x > 1176-w/2) { x = 1176-w/2; }//с правым краем карты
        if (x < 0) { x = w/2; }// с левым краем карты
    }
};

    class Enemy :public Entity 
    {
    public:
        Enemy(sf::Image& image, float X, float Y, float W, float H, sf::String Name) :Entity(image, X, Y, W, H, Name) 
        {
            if (name == "Enemy") 
            {
                sprite.setTextureRect(sf::IntRect(0, 0, W, H));
                dx = 0.1;//даем скорость.этот объект всегда двигается
            }
        }
        void checkCollisionWithMap(float Dx, float Dy)//ф ция проверки столкновений с картой
        {
            if (x > 1176 - w / 2) { x = 1176 - w / 2; }//с правым краем карты
            if (x < 0) { x = w / 2; }// с левым краем карты
            
        }
        void update(float time)
        {
            if (name == "Enemy") {//для персонажа с таким именем логика будет такой
                int n = 1;
                moveTimer += time;         
                if (moveTimer>3000)
                {
                    dx *= -1; moveTimer = 0; 
                    n = -n;
                }//меняет направление примерно каждые 3 сек   
              CurrentFrame += 0.005 * time;
                if (CurrentFrame > 6) CurrentFrame -= 5;
                sprite.setTextureRect(sf::IntRect(104.5 * int(CurrentFrame), 0, n*104.5, 180));

                checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
                x += dx * time;
                sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
                if (health <= 0) { life = false; }
            }
        }
    };
     