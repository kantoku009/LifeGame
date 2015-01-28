/**
 * @file    LifeGameDisplayOnCurses.h
 * @brief   ライフゲームの表示を管理するクラスの宣言.
 */
#ifndef __LIFEGAME_DISPLAY_H__
#define __LIFEGAME_DISPLAY_H__

#include <curses.h>

#include "../Model/CellAttribute.h"
#include "ExpressionCell.h"

// クラスの前方宣言
class MatrixCell;

/**
 * @brief   ライフゲームの表示を管理するクラス.
 * @note    UNIX環境のcursesで表示する事を想定している.
 * @note    以下URLを参考にした.
 * @note    http://www.kis-lab.com/serikashiki/man/ncurses.html
 */
class LifeGameDisplayOnCurses : public ExpressionCell
{
public:
    /**
     * @brief   イベント定義.
     */
    enum LIFEGAME_EVENT {
        EV_NONE,
        EV_QUIT,
        EV_PAUSE,
        EV_START,
        EV_MOVE_UP_CURSOR,
        EV_MOVE_LOW_CURSOR,
        EV_MOVE_RIGHT_CURSOR,
        EV_MOVE_LEFT_CURSOR,
        EV_PLOTCELL,
        EV_MAX,
    };

    /**
     * @brief   コンストラクタ.
     */
    LifeGameDisplayOnCurses();

    /**
     * @brief   デストラクタ.
     */
    virtual ~LifeGameDisplayOnCurses();

    /**
     * @brief   座標位置 横方向の最大.
     */
    long getColMax();

    /**
     * @brief   座標位置 縦方向の最大.
     */
    long getRowMax();

    /**
     * @brief   1セルを描画.
     */
    bool drawOneCell(long i_lCol, long i_lRow);

    /**
     * @brief   イベントループ.
     */
    LIFEGAME_EVENT eventLoop();

    /**
     * @brief   イベントを取得.
     * @param   なし.
     * @return  イベント.
     * @note    入力された文字からイベントに変換.
     */
    LIFEGAME_EVENT getEvent();

    /**
     * @brief   何もしない. None Operation.
     */
    void nop();
    /**
     * @brief セルを再描画.
     */
    void refreshCell();
    /**
     * @brief   カーソルを上へ移動.
     */
    void moveToUpper();
    /**
     * @brief   カーソルを下へ移動.
     */
    void moveToLower();
    /**
     * @brief   カーソルを右へ移動.
     */
    void moveToRight();
    /**
     * @brief   カーソルを左へ移動.
     */
    void moveToLeft();
    /**
     * @brief   カーソルのある位置のセルを 生or死 にする.(トグル動作)
     */
    void plotCell();

private:
    /**
     * @brief   curses初期化.
     * @param   なし.
     * @return  なし.
     */
    void initDisplay();

    /**
     * @brief   cursesのウィンドウ.
     */
    WINDOW* m_pWindow;

    /**
     * @brief   前回受け取ったイベント.
     */
    LIFEGAME_EVENT m_ePrevEvent;
};

#endif  // __LIFEGAME_DISPLAY_H__
