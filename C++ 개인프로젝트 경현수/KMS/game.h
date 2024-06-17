#pragma once

#include <iostream> 
#include <conio.h> // _kbhit(), _getch() 함수 사용을 위해, 키 입력을 받음
#include <ctime>   // srand() 함수 사용을 위해
#include <windows.h> // 윈도우API 사용을 위해

using namespace std;


class Snake
{
public:
    int x, y; //뱀 머리 좌표
    int tailX[100], tailY[100]; // 뱀 꼬리 좌표 배열
    int prevTailX[100], prevTailY[100]; // 현재 꼬리 위치를 저장할 배열 복사
    int nTail; // 꼬리의 길이
    enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; // 뱀 이동 방향
    eDirection dir; 

public:
    Snake(int width, int height); // 뱀 초기 위치
    void SetDirection(eDirection direction); //이동방향 설정 함수
    void Move();// 이동 함수
    bool Eat(int fruitX, int fruitY); // 먹이를 먹었는지 확인하는 메소드
    bool Collision(int width, int height);// 충돌 검사 메소드
    int GetX();  // 머리의 x좌표 
    int GetY(); // 머리의 y좌표 
    int GetNTail();  // 꼬리의 길이 
    int GetTailX(int index);  // index 위치의 꼬리의 x좌표 
    int GetTailY(int index); // index 위치의 꼬리의 y좌표
};

class Fruit //먹이 클래스
{
public:
    int x, y; //먹이 좌표

public:
    Fruit(int width, int height);
    int GetX();
    int GetY();
    void PlaceFruit(int width, int height); //먹이를 새로운 위치에 재배치
};

class Game
{
private:
    int width, height; //게임의 가로세로 크기
    Snake snake;
    Fruit fruit;
    bool gameOver;
    int score;

public:
    Game(int w, int h);
    void Draw(); //게임 화면 그리기 
    void Input(); // 사용자 키 입력
    void Logic(); //게임 기본 로직 
    bool IsGameOver(); 
};