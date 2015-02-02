/**
 * @file    LifeGameController.h
 * @brief	ライフゲームのコントローラー クラス宣言.
 */
#ifndef __LIFEGAME_CONTROLLER_H__
#define __LIFEGAME_CONTROLLER_H__

#include "../Model/MatrixCell.h"
#include "../View/LifeGameViewOnCurses.h"
#include "../Lib/CellAttribute.h"

/**
 * @brief   ライフゲームのコントローラー クラス.
 * @note	MVCのコントローラー部.
 */
class LifeGameController
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
    LifeGameController();

    /**
     * @brief   デストラクタ.
     */
    virtual ~LifeGameController();

	/**
	 * @brief	セルの初期配置.
	 * @param	なし.
	 * @return	なし.
	 */
	void initialPlot();

	/**
	 * @brief	イベントループ.
	 * @param	なし.
	 * @return	イベント.
	 */
	LIFEGAME_EVENT eventLoop();

	/**
	 * @brief	イベントを取得.
	 * @param	なし.
	 * @return	イベント.
	 * @note	入力されたコマンドからイベントに変換.
	 */
	LIFEGAME_EVENT getEvent();

	/**
	 * @brief	何もしない. None Operation.
	 * @param	なし.
	 * @return	なし.
	 */
	void nop(){ }

	/**
	 * @brief	セルを再描画.
	 * @param	なし.
	 * @return	なし.
	 */
	void refreshCell();

	/**
	 * @brief	カーソルを上へ移動.
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

	/**
	 * @brief	カーソルのある位置のセルを 生or死 にする.(トグル動作).
	 * @param	なし.
	 * @return	なし.
	 */
	void plotCell();

	/**
	 * @brief	Modelのセル状態とViewの表示を同期させる.
	 * @param	なし.
	 * @return	なし.
	 */
	void syncStateModelToView();

private:
	/**
	 * @brief	LifeGame Model
	 */
	MatrixCell*				m_pcLifeGameModel;

	/**
	 * @brief	LifeGame View
	 */
	LifeGameViewOnCurses*	m_pcLifeGameView;

	/**
	 * @brief 前回受け取ったイベント.
	 */
	LIFEGAME_EVENT m_ePrevEvent;
};

#endif	// __LIFEGAME_CONTROLLER_H__

