#pragma once
#include <SFML/Graphics.hpp>
class Player
{
private:
    float m_x, m_y, m_w, m_h;//���������� ������ � � �, ������ ������
    sf::String m_File;

public:
    float dx, speed; //��������� (�� �), ���� ��������
    int dir; //����������� �������� ������
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    Player(sf::String f, float x, float y, float w, float h) //��� �������� ������� ������ ����� ���������� ��� �����, ���������� � � �, ������ � ������
    {
        dx = 0; speed = 0; dir = 0; m_File = f;
        m_w = w; m_h = h;
        image.loadFromFile("E:/git/Project_sfml/Project_SFML/images/" + m_File);//
        texture.loadFromImage(image);//���������� ����������� � ��������
        sprite.setTexture(texture);//�������� ������ ���������
        m_x = x; m_y = y;//���������� ��������� �������
        sprite.setTextureRect(sf::IntRect(0, 0, w, h));
        sprite.setPosition(x, y);//������ ������� ���� ������������� ��� ������ ������ ��������� IntRect 
    }
    void update(float time) {} // ��������� � ���� ����� SFML, ���������� ���� �������� ����������, ����� ��������� ��������  
};