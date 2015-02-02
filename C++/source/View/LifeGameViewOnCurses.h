/**
 * @file    LifeGameViewOnCurses.h
 * @brief   ライフゲームの表示を管理するクラスの宣言.
 */
#ifndef __LIFEGAME_VIEW_H__
#define __LIFEGAME_VIEW_H__

#include <curses.h>

#include "../Lib/CellAttribute.h"

/**
 * @brief   ライフゲームの表示を管理するクラス.
 * @note    UNIX環境のcursesで表示する事を想定している.
 * @note    以下URLを参考にした.
 * @note    http://www.kis-lab.com/serikashiki/man/ncurses.html
 */
class LifeGameViewOnCurses
{
public:

    /**
     * @brief   コンストラクタ.
     */
    LifeGameViewOnCurses()
	{
	    this->initDisplay();
	}

    /**
     * @brief   デストラクタ.
     */
    virtual ~LifeGameViewOnCurses()
	{
		endwin();		// curses ライブラリ.
	}

    /**
     * @brief   座標位置 横方向の最大.
	 * @note	curses ライブラリ.
     */
    long getColMax()
	{
		return COLS;
	}

    /**
     * @brief   座標位置 縦方向の最大.
	 * @note	curses ライブラリ.
     */
    long getRowMax()
	{
		return LINES;
	}

	/**
	 * @brief	カーソルの位置(x座標)を取得.
	 */
	long getCol()
	{
		int a_iRow, a_iCol;
		getyx(m_pWindow, a_iRow, a_iCol);
		return (a_iCol);
	}
	/**
	 * @brief	カーソルの位置(y座標)を取得.
	 */
	long getRow()
	{
		int a_iRow,a_iCol;
		getyx(m_pWindow, a_iRow, a_iCol);
		return (a_iRow);
	}

    /**
     * @brief   現カーソル上にセルの状態を描画.
     * @param   CellAttribute::CELL_STATE i_eState   セルの状態.
     * @return  成功/失敗. 
     */
    bool draw(int i_iCol, int i_iRow, CellAttribute::CELL_STATE i_eState);

	/**
	 * @brief	ユーザーから入力されたコマンドを取得.
	 * @param	なし.
	 * @return	入力されたコマンド.
	 */
	char getCommand() const
	{
		return static_cast<char>(getch());
	}

    /**
     * @brief   カーソルを上へ移動.
	 * @param	なし.
	 * @return	なし.
     */
    void moveToUpper();

    /**
     * @brief   カーソルを下へ移動.
	 * @param	なし.
	 * @return	なし.
     */
    void moveToLower();

    /**
     * @brief   カーソルを右へ移動.
	 * @param	なし.
	 * @return	なし.
     */
    void moveToRight();

    /**
     * @brief   カーソルを左へ移動.
	 * @param	なし.
	 * @return	なし.
     */
    void moveToLeft();

private:
	/**
	 * @brief	表示する文字の定義.
	 */
	static const int m_piDispCharacter[CellAttribute::CELL_STATE_MAX];

    /**
     * @brief   cursesのウィンドウ.
     */
    WINDOW* m_pWindow;

    /**
     * @brief   curses初期化.
     * @param   なし.
     * @return  なし.
     */
    void initDisplay();
};

#endif  // __LIFEGAME_VIEW_H__

