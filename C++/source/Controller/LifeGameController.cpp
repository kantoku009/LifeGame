/**
 * @file    LifeGameController.cpp
 * @brief   ライフゲームの表示を管理するクラスの実装.
 */

#include "LifeGameController.h"

LifeGameController::LifeGameController()
{
	m_ePrevEvent = EV_NONE;

	// Viewを生成.
	m_pcLifeGameView = new LifeGameViewOnCurses();
	long a_lRow = m_pcLifeGameView->getRowMax();
	long a_lCol = m_pcLifeGameView->getColMax();

	// Modelを生成.
	m_pcLifeGameModel = new MatrixCell(a_lCol, a_lRow);

	// セルの初期配置.
	this->initialPlot();
	this->syncStateModelToView();
}

LifeGameController::~LifeGameController()
{
	if(m_pcLifeGameModel!= 0) delete m_pcLifeGameModel;
	if(m_pcLifeGameView != 0) delete m_pcLifeGameView;
}

/*****************
 * セルの初期配置.
 *****************/
void LifeGameController::initialPlot()
{
	// 蜂の巣 (固定物体)
	m_pcLifeGameModel->setCellState(3,1, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(4,1, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(2,2, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(5,2, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(3,3, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(4,3, CellAttribute::ALIVE);
	// ブロック (固定物体)
	m_pcLifeGameModel->setCellState(3,5, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(4,5, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(3,6, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(4,6, CellAttribute::ALIVE);
	// 船 (固定物体)
	m_pcLifeGameModel->setCellState(3,8, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(4,8, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(2,9, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(4,9, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(2,10, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(3,10, CellAttribute::ALIVE);
	// ブリンカー (振動子)
	m_pcLifeGameModel->setCellState(10,1, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(10,2, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(10,3, CellAttribute::ALIVE);
	// ブリンカー (振動子)
	m_pcLifeGameModel->setCellState(6,5, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(7,5, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(8,5, CellAttribute::ALIVE);
	// ブリンカー (振動子)
	m_pcLifeGameModel->setCellState(12,5, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(13,5, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(14,5, CellAttribute::ALIVE);
	// ブリンカー (振動子)
	m_pcLifeGameModel->setCellState(10,7, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(10,8, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(10,9, CellAttribute::ALIVE);
	// グライダー (移動物体)
	m_pcLifeGameModel->setCellState(2,15, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(3,18, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(1,17, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(2,17, CellAttribute::ALIVE);
	m_pcLifeGameModel->setCellState(3,17, CellAttribute::ALIVE);
}

/*********************************************************************
 *
 * メンバー関数へのポインタは以下URLを参考
 * http://www7b.biglobe.ne.jp/robe/cpphtml/html03/cpp03057.html
 *
 *********************************************************************/
LifeGameController::LIFEGAME_EVENT LifeGameController::eventLoop()
{
    typedef void (LifeGameController::*RunEvent)();
    RunEvent a_pcRunEvent[EV_MAX] = {
        &LifeGameController::nop,          // EV_NONE.
        &LifeGameController::nop,          // EV_QUIT.
        &LifeGameController::nop,          // EV_PAUSE.
        &LifeGameController::refreshCell,  // EV_START.
        &LifeGameController::moveToUpper,  // EV_MOVE_UP_CURSOR.
        &LifeGameController::moveToLower,  // EV_MOVE_LOW_CURSOR.
        &LifeGameController::moveToRight,  // EV_MOVE_RIGHT_CURSOR.
        &LifeGameController::moveToLeft,   // EV_MOVE_LEFT_CURSOR.
        &LifeGameController::plotCell,     // EV_PLOTCELL.
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
 * 入力されたコマンドからイベントに変換
 **************************************/
LifeGameController::LIFEGAME_EVENT LifeGameController::getEvent()
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

    // 入力されたコマンドを取得.(Viewから取得)
    a_ch = m_pcLifeGameView->getCommand();

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

/***********************
 * カーソルを上へ移動.
 ***********************/
void LifeGameController::moveToUpper()
{
	m_pcLifeGameView->moveToUpper();
}

/***********************
 * カーソルを下へ移動.
 ***********************/
void LifeGameController::moveToLower()
{
	m_pcLifeGameView->moveToLower();
}

/***********************
 * カーソルを右へ移動.
 ***********************/
void LifeGameController::moveToRight()
{
	m_pcLifeGameView->moveToRight();
}

/***********************
 * カーソルを左へ移動.
 ***********************/
void LifeGameController::moveToLeft()
{
	m_pcLifeGameView->moveToLeft();
}

/**********************************************************
 * カーソルのある位置のセルを 生or死 にする.(トグル動作)
 **********************************************************/
void LifeGameController::plotCell()
{
    // カーソル位置Viewから取得.
    int a_iCol = m_pcLifeGameView->getCol();
    int a_iRow = m_pcLifeGameView->getRow();

	// セルの状態をModelから取得.
    CellAttribute::CELL_STATE a_eState = m_pcLifeGameModel->getCellState(a_iCol, a_iRow);

	// セルの状態を反転させる.
	a_eState = (CellAttribute::ALIVE==a_eState)? CellAttribute::DEAD : CellAttribute::ALIVE;

	// セルの状態をModelへ設定.
    m_pcLifeGameModel->setCellState(a_iCol, a_iRow, a_eState);

	// セルの状態をViewへ設定.
    m_pcLifeGameView->draw(a_iCol, a_iRow, a_eState);
}

/***************
 * セルを再描画.
 ***************/
void LifeGameController::refreshCell()
{
	m_pcLifeGameModel->refreshCell();
	this->syncStateModelToView();
}

/********************************************
 * Modelのセル状態とViewの表示を同期させる.
 ********************************************/
void LifeGameController::syncStateModelToView()
{
	CellAttribute::CELL_STATE a_eState;

	for(long a_lRow=0; a_lRow<m_pcLifeGameView->getRowMax(); a_lRow++)
	{
		for(long a_lCol=0; a_lCol<m_pcLifeGameView->getColMax(); a_lCol++)
		{
			// Modelから状態を取得.
			a_eState = m_pcLifeGameModel->getCellState(a_lCol, a_lRow);
			// Viewへ状態を描画.
			m_pcLifeGameView->draw(a_lCol, a_lRow, a_eState);
		}
	}
}

