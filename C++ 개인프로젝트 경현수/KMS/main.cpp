#include "game.h"

int main()
{
    srand(time(NULL)); //랜덤
    const int width = 20; // 게임 가로 크기
    const int height = 20; // 게임 세로 크기
    Game game(width, height); // 게임 객체 생성

    while (!game.IsGameOver())
    {
        game.Draw(); // 화면 그리기
        game.Input(); // 사용자 입력 
        game.Logic(); // 게임 로직
        Sleep(100); // 게임 속도 조절 
    }
    return 0;
}