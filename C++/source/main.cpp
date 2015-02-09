/**
 * @file    main.cpp
 * @brief   ライフゲームのmain関数.
 */
#include <unistd.h>
#include "./Controller/LifeGameController.h"

#define DELAY   (100*1000)  // スリープの時間.単位はマイクロ秒.

int main(int argc, char* argv[])
{
	LifeGameController a_cController;

    LifeGameController::LIFEGAME_EVENT a_eEvent = LifeGameController::EV_NONE;
    do{
        a_eEvent = a_cController.eventLoop();
        usleep(DELAY);                  // スリープ.
    }while(LifeGameController::EV_QUIT != a_eEvent);

    return 0;
}

