#pragma once

#include <iostream> 
#include <conio.h> // _kbhit(), _getch() �Լ� ����� ����, Ű �Է��� ����
#include <ctime>   // srand() �Լ� ����� ����
#include <windows.h> // ������API ����� ����

using namespace std;


class Snake
{
public:
    int x, y; //�� �Ӹ� ��ǥ
    int tailX[100], tailY[100]; // �� ���� ��ǥ �迭
    int prevTailX[100], prevTailY[100]; // ���� ���� ��ġ�� ������ �迭 ����
    int nTail; // ������ ����
    enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; // �� �̵� ����
    eDirection dir; 

public:
    Snake(int width, int height); // �� �ʱ� ��ġ
    void SetDirection(eDirection direction); //�̵����� ���� �Լ�
    void Move();// �̵� �Լ�
    bool Eat(int fruitX, int fruitY); // ���̸� �Ծ����� Ȯ���ϴ� �޼ҵ�
    bool Collision(int width, int height);// �浹 �˻� �޼ҵ�
    int GetX();  // �Ӹ��� x��ǥ 
    int GetY(); // �Ӹ��� y��ǥ 
    int GetNTail();  // ������ ���� 
    int GetTailX(int index);  // index ��ġ�� ������ x��ǥ 
    int GetTailY(int index); // index ��ġ�� ������ y��ǥ
};

class Fruit //���� Ŭ����
{
public:
    int x, y; //���� ��ǥ

public:
    Fruit(int width, int height);
    int GetX();
    int GetY();
    void PlaceFruit(int width, int height); //���̸� ���ο� ��ġ�� ���ġ
};

class Game
{
private:
    int width, height; //������ ���μ��� ũ��
    Snake snake;
    Fruit fruit;
    bool gameOver;
    int score;

public:
    Game(int w, int h);
    void Draw(); //���� ȭ�� �׸��� 
    void Input(); // ����� Ű �Է�
    void Logic(); //���� �⺻ ���� 
    bool IsGameOver(); 
};