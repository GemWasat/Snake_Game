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

void Snake::SetDirection(eDirection direction)//�� �̵����� ����
{
    if (dir != direction)
        dir = direction;
}

void Snake::Move()
{
    // ������ ��ġ�� ������Ʈ
    int prevX = x; // ���� �Ӹ��� x ��ǥ�� ����
    int prevY = y; // ���� �Ӹ��� y ��ǥ�� ����
    int prev2X, prev2Y; // ���� ������ ��ġ�� �ӽ÷� ������ ����

    // ���� ������ ��ġ�� ������ �迭�� ����
    int prevTailX[100];
    int prevTailY[100];
    for (int i = 0; i < nTail; i++) 
    {
        prevTailX[i] = tailX[i];
        prevTailY[i] = tailY[i];
    }

    // �Ӹ� �̵�
    switch (dir) // ���� �̵� ���⿡ ���� �Ӹ��� ��ġ�� ������Ʈ
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

    // ���� �̵�
    for (int i = 0; i < nTail; i++) // ������ ������ ��ҵ鿡 ���ؼ� �ݺ��մϴ�.
    {
        prev2X = tailX[i]; // ���� ������ x ��ǥ�� ����
        prev2Y = tailY[i]; // ���� ������ y ��ǥ�� ����
        tailX[i] = prevX; // ���� ������ x ��ǥ�� ���� ������ x ��ǥ�� ������Ʈ
        tailY[i] = prevY; // ���� ������ y ��ǥ�� ���� ������ y ��ǥ�� ������Ʈ
        prevX = prev2X; // prevX�� ���� ������ x ��ǥ�� ������Ʈ
        prevY = prev2Y; // prevY�� ���� ������ y ��ǥ�� ������Ʈ
    }

    // ������ �� ���� ������ ��ġ�� ���� ������ ��ġ�� ������Ʈ
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

        return true; // ���̸� �Ծ���
    }
    return false; // ���̸� ���� �ʾ���
}

bool Snake::Collision(int width, int height)// �浹 �˻�
{
    if (x >= width || x < 0 || y >= height || y < 0) // ������ �浹 �˻�
        return true; // �浹 �߻�
    for (int i = 0; i < nTail; i++) // ���� ������� �浹 �˻�
        if (tailX[i] == x && tailY[i] == y)
            return true; // �浹 �߻�
    return false; // �浹 ����
}

int Snake::GetX() { return x; } // �Ӹ��� x��ǥ 
int Snake::GetY() { return y; } // �Ӹ��� y��ǥ 
int Snake::GetNTail() { return nTail; } // ������ ���� 
int Snake::GetTailX(int index) { return tailX[index]; } // index ��ġ�� ������ x��ǥ 
int Snake::GetTailY(int index) { return tailY[index]; } // index ��ġ�� ������ y��ǥ

Fruit::Fruit(int width, int height)
{
    // ���μ��� ������ ���� �����ϰ� ����
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

void Fruit::PlaceFruit(int width, int height)//���� ���ġ
{
    x = rand() % width;
    y = rand() % height;
}

// Game Ŭ������ ��� �Լ� ����
Game::Game(int w, int h) : width(w), height(h), snake(w, h), fruit(w, h), gameOver(false), score(0) {}

void Game::Draw()
{
    system("cls"); // �ܼ� ȭ�� �����

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#"; // ���� ��
            if (i == snake.GetY() && j == snake.GetX())
                cout << "O"; // ���� �Ӹ� 
            else if (i == fruit.GetY() && j == fruit.GetX())
                cout << "F"; // ���� 
            else
            {
                bool print = false;
                // ���� ��� �κ� ����
                for (int k = 0; k < snake.GetNTail(); k++)
                {
                    if (snake.GetTailX(k) == j && snake.GetTailY(k) == i)
                    {
                        cout << "o"; // ���� ���� ���
                        print = true;
                    }
                }
                if (!print)
                    cout << " "; // �� ���� ���
            }
            if (j == width - 1)
                cout << "#"; // ������ ��
        }
        cout << endl;
    }
    //  ��
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    // ���� ���
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
    snake.Move(); // �� �̵�
    if (snake.GetX() == fruit.GetX() && snake.GetY() == fruit.GetY())
    { // ���̸� �Ծ����� Ȯ��
        score += 10; // ���� ����
        fruit.PlaceFruit(width, height); // ���ο� ���� ��ġ ����
        snake.Eat(fruit.GetX(), fruit.GetY()); // ���� ����
        snake.nTail++;
    }
    if (snake.Collision(width, height) || gameOver) //�浹Ȯ��
    { 
        cout << "Game Over!" << endl;
        cout << "Your Score: " << score << endl;
        gameOver = true; // ���� ����
        return;
    }
}

bool Game::IsGameOver()
{
    return gameOver;
}