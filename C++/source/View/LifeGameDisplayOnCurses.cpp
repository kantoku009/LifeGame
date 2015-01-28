/**
 * @file    LifeGameDisplayOnCurses.cpp
 * @brief   ライフゲームの表示を管理するクラスの実装.
 */

#include "LifeGameDisplayOnCurses.h"


/******************
 * コンストラクタ
 ******************/
LifeGameDisplayOnCurses::LifeGameDisplayOnCurses()
{
    initDisplay();

    // ターミナルのウィンドウサイズを取得.
    long a_lRowMax = getRowMax();
    long a_lColMax = getColMax();

    // MatrixCellを生成.
    createMatrixCell(a_lColMax, a_lRowMax);

    m_ePrevEvent = EV_NONE;
}

/*****************
 * デストラクタ.
 *****************/
LifeGameDisplayOnCurses::~LifeGameDisplayOnCurses()
{
    endwin();
}

void LifeGameDisplayOnCurses::initDisplay()
{
    m_pWindow = initscr();      // cursesライブラリの初期化.
    nodelay(m_pWindow, true);   // 非ブロッキングモード.
    cbreak();                   // 行バッファリングをやめ，DeleteやBackSpaceを無効にする.
    noecho();                   // 入力された文字のエコーバックをしない.
}

/**************************
 * 座標 横方向 最大値
 **************************/
long LifeGameDisplayOnCurses::getColMax()
{
    return COLS;
}
/*************************
 * 座標 縦方向 最大値
 *************************/
long LifeGameDisplayOnCurses::getRowMax()
{
    return LINES;
}


/***************************
 * 1セルを描画.
 ***************************/
bool LifeGameDisplayOnCurses::drawOneCell(long i_lCol, long i_lRow)
{
    CellAttribute::CELL_STATE a_eState = getCellState(i_lCol, i_lRow);

    char a_ch;
    switch (a_eState)
    {
        case CellAttribute::ALIVE:
            a_ch = '*';
            break;
        case CellAttribute::DEAD:
            a_ch = ' ';
            break;
        default:
            a_ch = ' ';
            break;
    }
    mvaddch(i_lRow, i_lCol, a_ch);
    refresh();                      // curses ライブラリ.

    return true;
}

/*********************************************************************
 *
 * メンバー間数へのポインタは以下URLを参考
 * http://www7b.biglobe.ne.jp/robe/cpphtml/html03/cpp03057.html
 *
 *********************************************************************/
LifeGameDisplayOnCurses::LIFEGAME_EVENT LifeGameDisplayOnCurses::eventLoop()
{
    typedef void (LifeGameDisplayOnCurses::*RunEvent)();
    RunEvent a_pcRunEvent[EV_MAX] = {
        &LifeGameDisplayOnCurses::nop,          // EV_NONE.
        &LifeGameDisplayOnCurses::nop,          // EV_QUIT.
        &LifeGameDisplayOnCurses::nop,          // EV_PAUSE.
        &LifeGameDisplayOnCurses::refreshCell,  // EV_START.
        &LifeGameDisplayOnCurses::moveToUpper,  // EV_MOVE_UP_CURSOR.
        &LifeGameDisplayOnCurses::moveToLower,  // EV_MOVE_LOW_CURSOR.
        &LifeGameDisplayOnCurses::moveToRight,  // EV_MOVE_RIGHT_CURSOR.
        &LifeGameDisplayOnCurses::moveToLeft,   // EV_MOVE_LEFT_CURSOR.
        &LifeGameDisplayOnCurses::plotCell,     // EV_PLOTCELL.
    };
    LIFEGAME_EVENT a_eEvent = EV_NONE;

    // イベントを取得.
    a_eEvent = getEvent();

    // 取得したイベントがEV_NONEだった場合, 前回実行したイベントに差し替える.
    if( (EV_NONE==a_eEvent) && (EV_PAUSE==m_ePrevEvent) )
    {
        a_eEvent = EV_PAUSE;
    }
    else if( (EV_NONE==a_eEvent) && (EV_START==m_ePrevEvent))
    {
        a_eEvent = EV_START;
    }

    (this->*a_pcRunEvent[a_eEvent])();

    m_ePrevEvent = a_eEvent;
    return a_eEvent;
}

/**************************************
 * 入力された文字からイベントに変換
 **************************************/
LifeGameDisplayOnCurses::LIFEGAME_EVENT LifeGameDisplayOnCurses::getEvent()
{
    struct EVENT_CHARACTER_PAIR
    {
        char m_byCharacter;
        LIFEGAME_EVENT m_eEvent;
    };
    EVENT_CHARACTER_PAIR a_rgstPair[EV_MAX] = {
        { '\0',     EV_NONE},
        { 'q',      EV_QUIT},
        { 'p',      EV_PAUSE},
        { 's',      EV_START},
        { 'k',      EV_MOVE_UP_CURSOR},
        { 'j',      EV_MOVE_LOW_CURSOR},
        { 'l',      EV_MOVE_RIGHT_CURSOR},
        { 'h',      EV_MOVE_LEFT_CURSOR},
        { 'i',      EV_PLOTCELL},
    };
    char a_ch = '\0';
    LIFEGAME_EVENT a_eEvent = EV_NONE;

    // 入力された文字を取得.
    a_ch = static_cast<char>(getch());

    // 入力された文字をイベントに変換.
    int a_iElementNum = sizeof(a_rgstPair) / sizeof(a_rgstPair[0]) ;
    for(int theI=EV_NONE; theI<a_iElementNum; theI++)
    {
        if(a_ch == a_rgstPair[theI].m_byCharacter)
        {
            a_eEvent = a_rgstPair[theI].m_eEvent;
        }
    }

    return a_eEvent;
}

/********************
 * カーソルを上へ移動.
 ********************/
void LifeGameDisplayOnCurses::moveToUpper()
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
void LifeGameDisplayOnCurses::moveToLower()
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
void LifeGameDisplayOnCurses::moveToRight()
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
void LifeGameDisplayOnCurses::moveToLeft()
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

/**********************************************************
 * カーソルのある位置のセルを 生or死 にする.(トグル動作)
 **********************************************************/
void LifeGameDisplayOnCurses::plotCell()
{
    // カーソル位置を取得.
    int a_iCol = 0;
    int a_iRow = 0;
    getyx(m_pWindow, a_iRow, a_iCol);

    CellAttribute::CELL_STATE a_eState = getCellState(a_iCol, a_iRow);

    if(CellAttribute::ALIVE == a_eState ) a_eState = CellAttribute::DEAD;
    else a_eState = CellAttribute::ALIVE;

    setCellState(a_iCol, a_iRow, a_eState);
    drawOneCell(a_iCol, a_iRow);
}

/*************
 * 何もしない.
 *************/
void LifeGameDisplayOnCurses::nop()
{
    ExpressionCell::nop();
}

/***************
 * セルを再描画.
 ***************/
void LifeGameDisplayOnCurses::refreshCell()
{
    ExpressionCell::refreshCell();
}
