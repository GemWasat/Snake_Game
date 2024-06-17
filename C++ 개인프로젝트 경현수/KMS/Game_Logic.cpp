#include "game.h"
#include <conio.h>

using namespace std;

Snake::Snake(int width, int height)
{
    x = width / 2;
    y = height / 2;
    dir = STOP;
    nTail = 0;
}

void Snake::SetDirection(eDirection direction)//뱀 이동방향 설정
{
    if (dir != direction)
        dir = direction;
}

void Snake::Move()
{
    // 꼬리의 위치를 업데이트
    int prevX = x; // 현재 머리의 x 좌표를 저장
    int prevY = y; // 현재 머리의 y 좌표를 저장
    int prev2X, prev2Y; // 이전 꼬리의 위치를 임시로 저장할 변수

    // 현재 꼬리의 위치를 저장할 배열을 복사
    int prevTailX[100];
    int prevTailY[100];
    for (int i = 0; i < nTail; i++) 
    {
        prevTailX[i] = tailX[i];
        prevTailY[i] = tailY[i];
    }

    // 머리 이동
    switch (dir) // 현재 이동 방향에 따라 머리의 위치를 업데이트
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    // 꼬리 이동
    for (int i = 0; i < nTail; i++) // 꼬리의 나머지 요소들에 대해서 반복합니다.
    {
        prev2X = tailX[i]; // 이전 꼬리의 x 좌표를 저장
        prev2Y = tailY[i]; // 이전 꼬리의 y 좌표를 저장
        tailX[i] = prevX; // 현재 꼬리의 x 좌표를 이전 꼬리의 x 좌표로 업데이트
        tailY[i] = prevY; // 현재 꼬리의 y 좌표를 이전 꼬리의 y 좌표로 업데이트
        prevX = prev2X; // prevX를 이전 꼬리의 x 좌표로 업데이트
        prevY = prev2Y; // prevY를 이전 꼬리의 y 좌표로 업데이트
    }

    // 복사해 둔 이전 꼬리의 위치를 현재 꼬리의 위치로 업데이트
    for (int i = 0; i < nTail - 1; i++) 
    {
        tailX[i + 1] = prevTailX[i];
        tailY[i + 1] = prevTailY[i];
    }
}

bool Snake::Eat(int fruitX, int fruitY)
{
    if (x == fruitX && y == fruitY)
    {
        
        int newTailX = x;
        int newTailY = y;

        tailX[nTail] = newTailX;
        tailY[nTail] = newTailY;
        
        nTail++;

        return true; // 먹이를 먹었음
    }
    return false; // 먹이를 먹지 않았음
}

bool Snake::Collision(int width, int height)// 충돌 검사
{
    if (x >= width || x < 0 || y >= height || y < 0) // 벽과의 충돌 검사
        return true; // 충돌 발생
    for (int i = 0; i < nTail; i++) // 뱀의 몸통과의 충돌 검사
        if (tailX[i] == x && tailY[i] == y)
            return true; // 충돌 발생
    return false; // 충돌 없음
}

int Snake::GetX() { return x; } // 머리의 x좌표 
int Snake::GetY() { return y; } // 머리의 y좌표 
int Snake::GetNTail() { return nTail; } // 꼬리의 길이 
int Snake::GetTailX(int index) { return tailX[index]; } // index 위치의 꼬리의 x좌표 
int Snake::GetTailY(int index) { return tailY[index]; } // index 위치의 꼬리의 y좌표

Fruit::Fruit(int width, int height)
{
    // 가로세로 범위에 먹위 랜덤하게 생성
    x = rand() % width; 
    y = rand() % height;
}

int Fruit::GetX()
{
    return x;
}

int Fruit::GetY()
{
    return y;
}

void Fruit::PlaceFruit(int width, int height)//먹이 재배치
{
    x = rand() % width;
    y = rand() % height;
}

// Game 클래스의 멤버 함수 구현
Game::Game(int w, int h) : width(w), height(h), snake(w, h), fruit(w, h), gameOver(false), score(0) {}

void Game::Draw()
{
    system("cls"); // 콘솔 화면 지우기

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#"; // 왼쪽 벽
            if (i == snake.GetY() && j == snake.GetX())
                cout << "O"; // 뱀의 머리 
            else if (i == fruit.GetY() && j == fruit.GetX())
                cout << "F"; // 먹이 
            else
            {
                bool print = false;
                // 꼬리 출력 부분 수정
                for (int k = 0; k < snake.GetNTail(); k++)
                {
                    if (snake.GetTailX(k) == j && snake.GetTailY(k) == i)
                    {
                        cout << "o"; // 뱀의 꼬리 출력
                        print = true;
                    }
                }
                if (!print)
                    cout << " "; // 빈 공간 출력
            }
            if (j == width - 1)
                cout << "#"; // 오른쪽 벽
        }
        cout << endl;
    }
    //  벽
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    // 점수 출력
    cout << "Score: " << score << endl;
    cout << "Tail : " << snake.nTail << endl;
}

void Game::Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            snake.SetDirection(Snake::LEFT);
            break;
        case 'd':
            snake.SetDirection(Snake::RIGHT);
            break;
        case 'w':
            snake.SetDirection(Snake::UP);
            break;
        case 's':
            snake.SetDirection(Snake::DOWN);
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }


}

void Game::Logic()
{
    snake.Move(); // 뱀 이동
    if (snake.GetX() == fruit.GetX() && snake.GetY() == fruit.GetY())
    { // 먹이를 먹었는지 확인
        score += 10; // 점수 증가
        fruit.PlaceFruit(width, height); // 새로운 먹이 위치 설정
        snake.Eat(fruit.GetX(), fruit.GetY()); // 꼬리 증가
        snake.nTail++;
    }
    if (snake.Collision(width, height) || gameOver) //충돌확인
    { 
        cout << "Game Over!" << endl;
        cout << "Your Score: " << score << endl;
        gameOver = true; // 게임 종료
        return;
    }
}

bool Game::IsGameOver()
{
    return gameOver;
}