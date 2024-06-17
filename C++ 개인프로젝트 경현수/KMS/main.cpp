#include "game.h"

int main()
{
    srand(time(NULL)); //����
    const int width = 20; // ���� ���� ũ��
    const int height = 20; // ���� ���� ũ��
    Game game(width, height); // ���� ��ü ����

    while (!game.IsGameOver())
    {
        game.Draw(); // ȭ�� �׸���
        game.Input(); // ����� �Է� 
        game.Logic(); // ���� ����
        Sleep(100); // ���� �ӵ� ���� 
    }
    return 0;
}