/**********************************************
 * LifeGameViewOnCursesクラスのユニットテスト
 *
 * テストを実行すると以下のことが可能.
 * q: 終了
 * a: '*'を書き込む
 * d: '*'を消去
 * k: カーソルを上へ移動
 * j: カーソルを下へ移動
 * h: カーソルを左へ移動
 * l: カーソルを右へ移動
 *
 * ※カーソルの移動はviと同じ
 **********************************************/

#include <iostream>
#include <unistd.h>
#include "../LifeGameViewOnCurses.h"
#include "../../Lib/CellAttribute.h"

void draw(LifeGameViewOnCurses* i_pcLifeGameView, CellAttribute::CELL_STATE i_eState)
{
	int a_iRow = i_pcLifeGameView->getRow();
	int a_iCol = i_pcLifeGameView->getCol();
	i_pcLifeGameView->draw(a_iCol, a_iRow, i_eState);
}

char getCommand(LifeGameViewOnCurses* i_pcLifeGameView)
{
    // 入力されたコマンドを取得.
    char a_ch = '\0';
    a_ch = i_pcLifeGameView->getCommand();

	switch (a_ch)
	{
		case 'k':
			i_pcLifeGameView->moveToUpper();
			break;
		case 'j':
			i_pcLifeGameView->moveToLower();
			break;
		case 'l':
			i_pcLifeGameView->moveToRight();
			break;
		case 'h':
			i_pcLifeGameView->moveToLeft();
			break;
		case 'a':
			draw(i_pcLifeGameView, CellAttribute::ALIVE);
			break;
		case 'd':
			draw(i_pcLifeGameView, CellAttribute::DEAD);
			break;
		case 'q':
		default:
			break;
	}
    return a_ch;
}


bool test_LifeGameDisplayOnCurses()
{
	LifeGameViewOnCurses a_pcLifeGameView;
	char a_ch;

	do{
		a_ch = getCommand(&a_pcLifeGameView);
	}while('q'!=a_ch);

	return true;
}

int main()
{
	test_LifeGameDisplayOnCurses();
	return 0;
}

