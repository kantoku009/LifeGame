/**
 * @file    LifeGameViewOnCurses.cpp
 * @brief   ライフゲームの表示を管理するクラスの実装.
 */

#include "LifeGameViewOnCurses.h"

// 表示する文字の定義.
const int LifeGameViewOnCurses::m_piDispCharacter[CellAttribute::CELL_STATE_MAX] = { ' ', '*', };

/***************************
 * curses初期化.
 ***************************/
void LifeGameViewOnCurses::initDisplay()
{
    m_pWindow = initscr();      // cursesライブラリの初期化.
    nodelay(m_pWindow, true);   // 非ブロッキングモード.
    cbreak();                   // 行バッファリングをやめ，DeleteやBackSpaceを無効にする.
    noecho();                   // 入力された文字のエコーバックをしない.
}

/**********************************
 * 現カーソル上にセルの状態を描画.
 **********************************/
bool LifeGameViewOnCurses::draw(int i_iCol, int i_iRow, CellAttribute::CELL_STATE i_eState)
{
	// 表示する文字を設定.
	int a_iChar = this->m_piDispCharacter[i_eState];
    mvaddch(i_iRow, i_iCol, a_iChar);	// curses ライブラリ.
    refresh();							// curses ライブラリ.

    return true;
}

/********************
 * カーソルを上へ移動.
 ********************/
void LifeGameViewOnCurses::moveToUpper()
{
    int a_iRow=0;
    int a_iCol=0;

    // カーソル位置を取得.
    getyx(m_pWindow, a_iRow, a_iCol);

    a_iRow--;
    if(0 > a_iRow) a_iRow=getRowMax()-1;

    // カーソルを移動.
    move(a_iRow, a_iCol);
}

/********************
 * カーソルを下へ移動.
 ********************/
void LifeGameViewOnCurses::moveToLower()
{
    int a_iCol=0;
    int a_iRow=0;

    // カーソル位置を取得.
    getyx(m_pWindow, a_iRow, a_iCol);

    a_iRow++;
    if(getRowMax() <= a_iRow) a_iRow=0;

    // カーソルを移動.
    move(a_iRow, a_iCol);
}

/********************
 * カーソルを右へ移動.
 ********************/
void LifeGameViewOnCurses::moveToRight()
{
    int a_iCol=0;
    int a_iRow=0;

    // カーソル位置を取得.
    getyx(m_pWindow, a_iRow, a_iCol);

    a_iCol++;
    if(getColMax() <= a_iCol) a_iCol=0;

    // カーソルを移動.
    move(a_iRow, a_iCol);
}

/********************
 * カーソルを左へ移動.
 ********************/
void LifeGameViewOnCurses::moveToLeft()
{
    int a_iCol=0;
    int a_iRow=0;

    // カーソル位置を取得.
    getyx(m_pWindow, a_iRow, a_iCol);

    a_iCol--;
    if(0 > a_iCol) a_iCol=getColMax()-1;

    // カーソルを移動.
    move(a_iRow, a_iCol);
}


