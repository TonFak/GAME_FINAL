#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
    double dx, dy, x, y, speed, moveTimer;
    double w, h, health;
    bool life, isMove, onGround;
    float CurrentFrame = 0;//������ ������� ����
    sf::Texture texture;
    sf::Sprite sprite;
    sf::String name;//�������� ������ �� ����� � ����� ������� ���� �������� � update � ����������� �� �����
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
    enum { left, right, jump, left2, right2, jump2, stay, stay2 } state1, state2;//��������� ��� ������������ - ��������� �������
    Player(sf::Image& image, float X, float Y, float W, float H, sf::String Name) :Entity(image, X, Y, W, H, Name) //��� �������� ������� ������ ����� ���������� ��� �����, ���������� � � �, ������ � ������
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))//�������� ������������ ����� 1 ��������� 
            {
                state1 = left;
                speed = 0.1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//������ 1
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))//�������� ������������ ����� 1 ��������� 
            {
                state2 = left2;
                speed = 0.1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))//������ 1
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
    void update(float time) // ��������� � ���� ����� SFML, ���������� ���� �������� ����������, ����� ��������� ��������  
    {
        control();//������� ���������� ����������
        if (name == "Player1")
        {
            switch (state1)//��� �������� ��������� �������� � ����������� �� ���������
            {
            case right: dx = speed;
                CurrentFrame += 0.005 * time;
                if (CurrentFrame > 5) CurrentFrame -= 4;
                sprite.setTextureRect(sf::IntRect(59 * int(CurrentFrame), 0, 59, 68));
                break;//��������� ���� ������
            case left: dx = -speed;
                CurrentFrame += 0.005 * time;
                if (CurrentFrame > 5) CurrentFrame -= 4;
                sprite.setTextureRect(sf::IntRect(59 * int(CurrentFrame), 0, -59, 68));
                break;//��������� ���� �����
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
                break;//��������� ���� ������
            case left2: dx = -speed;
                CurrentFrame += 0.005 * time;
                if (CurrentFrame > 5) CurrentFrame -= 4;
                sprite.setTextureRect(sf::IntRect(46 * int(CurrentFrame), 0, -46, 76));
                break;//��������� ���� �����
            }
        }
        x += dx * time;
        checkCollisionWithMap(dx, 0);//������������ ������������ �� �
        y += dy * time;
        checkCollisionWithMap(0, dy);//������������ ������������ �� Y
        if (!isMove) speed = 0;
        sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
        dy = dy + 0.0015 * time;
        //������ ���������� � �����
    }
    float getplayercoordinateX() 
    {
        return x;
    }
    float getplayercoordinateY() 
    {
        return y;
    }
    void checkCollisionWithMap(float Dx, float Dy)//� ��� �������� ������������ � ������
    {
        if (y > 375) { y = 375;  dy = 0; onGround = true; }//�� Y ����=>���� � ���(����� �� �����) ��� ������. � ���� ������ ���� ���������� ��������� � ��������� ��� �� �����, ��� ���� ������� ��� �� �� ����� ��� ����� ����� ����� �������
        if (x > 1176-w/2) { x = 1176-w/2; }//� ������ ����� �����
        if (x < 0) { x = w/2; }// � ����� ����� �����
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
                dx = 0.1;//���� ��������.���� ������ ������ ���������
            }
        }
        void checkCollisionWithMap(float Dx, float Dy)//� ��� �������� ������������ � ������
        {
            if (x > 1176 - w / 2) { x = 1176 - w / 2; }//� ������ ����� �����
            if (x < 0) { x = w / 2; }// � ����� ����� �����
            
        }
        void update(float time)
        {
            if (name == "Enemy") {//��� ��������� � ����� ������ ������ ����� �����
                int n = 1;
                moveTimer += time;         
                if (moveTimer>3000)
                {
                    dx *= -1; moveTimer = 0; 
                    n = -n;
                }//������ ����������� �������� ������ 3 ���   
              CurrentFrame += 0.005 * time;
                if (CurrentFrame > 6) CurrentFrame -= 5;
                sprite.setTextureRect(sf::IntRect(104.5 * int(CurrentFrame), 0, n*104.5, 180));

                checkCollisionWithMap(dx, 0);//������������ ������������ �� �
                x += dx * time;
                sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
                if (health <= 0) { life = false; }
            }
        }
    };
     