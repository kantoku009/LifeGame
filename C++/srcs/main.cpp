/**
 * @file    main.cpp
 * @brief   ライフゲームのmain関数.
 */
#include <stdio.h>
#include <time.h>

#include "./View/LifeGameDisplayOnCurses.h"

#define DELAY   (1000*100)  // スリープの時間.単位はマイクロ秒.

int main(int argc, char* argv[])
{
    LifeGameDisplayOnCurses a_cDisplay;

    LifeGameDisplayOnCurses::LIFEGAME_EVENT a_eEvent = LifeGameDisplayOnCurses::EV_NONE;
    do{
        a_eEvent = a_cDisplay.eventLoop();
        usleep(DELAY);                  // スリープ.
    }while(LifeGameDisplayOnCurses::EV_QUIT != a_eEvent);

    return 0;
}
