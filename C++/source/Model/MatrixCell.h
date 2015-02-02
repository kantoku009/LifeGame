/**
 * @file MatrixCell.h
 * @brief   全細胞（全セル）を管理するクラスの宣言.
 */

#ifndef __MATRIXCELL_H__
#define __MATRIXCELL_H__

#include <vector>
#include <string>

#include "../Lib/Observer.h"
#include "../Lib/CellAttribute.h"
#include "Cell.h"

/**
 * @brief   全細胞（全セル）を管理するクラス.
 * @note    Cellを管理する.
 */
class MatrixCell
{
public:
    /**
     * @brief   コンストラクタ.
     */
    MatrixCell(long i_lColMax, long i_lRowMax)
	{
		this->init(i_lColMax, i_lRowMax);
	}

    /**
     * @brief   デストラクタ.
     */
	virtual ~MatrixCell() { }

    /**
     * @brief   初期化.
     * @param   なし.
     * @return  なし.
     */
    void init(long i_lColMax, long i_lRowMax);

    /**
     * @brief   セルの横最大幅を取得.
     * @param   なし.
     * @return  セルの横最大幅.
     */
    long getColMax() const { return this->m_lColMax; }

    /**
     * @brief   セルの縦最大幅を取得.
     * @param   なし.
     * @return  セルの縦最大幅.
     */
    long getRowMax() const { return this->m_lRowMax; }

    /**
     * @brief   セルを取得する.
     * @param   long i_lCol 取得したいセルの横位置.
     * @param   long i_lRow 取得したいセルの縦位置.
     * @return  セル
     */
    Cell* getCell(long i_lCol, long i_lRow)
	{
		Cell* a_pcCell = this->m_vecCellArray[i_lRow][i_lCol];
		return a_pcCell;
	}

    /**
     * @brief   セルの状態を設定する.
     * @param   long i_lCol セルの座標位置（横方向）
     * @param   long i_lRow セルの座標位置（縦方向）
     * @param   CellAttribute::CELL_STATE i_eState 設定したいセルの状態
     * @return  なし.
     */
    void setCellState(long i_lCol, long i_lRow, CellAttribute::CELL_STATE i_eState)
	{
		Cell* a_pcCell = this->getCell(i_lCol, i_lRow);
		a_pcCell->setState(i_eState);
	}

    /**
     * @brief   セルの状態を取得する.
     * @param   long i_lCol セルの座標位置（横方向）
     * @param   long i_lRow セルの座標位置（縦方向）
     * @return  セルの状態. 0:死 1:生
     * @retval  true    生
     * @retval  false   死
     */
    CellAttribute::CELL_STATE getCellState(long i_lCol, long i_lRow)
	{
		Cell* a_pcCell = this->getCell(i_lCol, i_lRow);
		CellAttribute::CELL_STATE a_eState = a_pcCell->getState();
		return a_eState;
	}

    /**
     * @brief   全セルの更新を行う.
     * @param   なし.
     * @return  更新の結果.
     * @retval  true    成功.
     * @retval  false   失敗.
     */
    bool refreshCell();

	/**
	 * @brief	全セルの状態を表示.
	 * @note	デバッグ用.
	 */
	std::string dispAllCellState();

	/**
	 * @brief	隣接セルの生存数を表示.
	 * @note	デバッグ用.
	 */
	std::string dispNeighborAliveCell();

private:
    /**
     * @brief   セルの横最大幅.
     */
    long m_lColMax;

    /**
     * @brief   セルの縦最大幅.
     */
    long m_lRowMax;

    /**
     * @brief   セルの集合体.
     */
    std::vector< std::vector <Cell*> > m_vecCellArray;

    /**
     * @brief   セルを生成する.
     * @param   なし.
     * @return  処理結果を返す.
     * @retval  true    全セルの生成に成功.
     * @retval  false   セルの生成に失敗.
     */
    bool makeCell();

    /**
     * @brief   隣接セルをリンクさせる.
     * @param   なし.
     * @return  なし.
     */
    bool linkCell();

	/**
	 * @brief	隣接セルを設定する.
	 * @param	Cell* i_pcTargetCell 隣接セルを設定するセル.
	 * @param	long i_lCol	設定するセルの横位置.
	 * @param	long i_lRow 設定するセルの縦位置.
	 * @return	成功/失敗.
	 */
	bool setNeighborCell(Cell* i_pcTargetCell, long i_lCol, long i_lRow);

	/**
	* @brief	境界値をチェックする.
	* @param	long i_lValue チェックしたい値.
	* @param	long i_lMax チェックしたい値の最大値.
	* @note		引数i_lValueが境界値だった場合, 以下とする.
	*			・最大値 = 最小値(0).
	*			つまり, 境界値は存在せず(2次元の場合)球面となる.
	*/
	long check_region(long i_lValue, long i_lMax);

    /**
     * @brief       隣接セルに自分自身の状態を通知する.
     * @param       なし.
     * @return      通知結果.
     * @retval      true    成功.
     * @retval      false   失敗.
     */
    bool sendStateToNeighborCell();

    /**
     * @brief       次世代のセルを決定する.
     * @param       なし.
     * @return      通知結果.
     * @retval      true    成功.
     * @retval      false   失敗.
     */
    bool decideNextGeneration();

    /**
     * @brief   セル横最大幅を設定.
     * @param   セル横最大幅.
     * @return  なし.
     * @note    将来的には, セル横最大幅を可変にしたい.
     *          privateにしておくことで, プログラム実行中に変更不可としている.
     */
    void setColMax(long i_lColMax){ this->m_lColMax = i_lColMax; }

    /**
     * @brief   セルの縦最大幅を設定.
     * @param   セル横最大幅.
     * @return  なし.
     * @note    将来的には, セル縦最大幅を可変にしたい.
     *          privateにしておくことで, プログラム実行中に変更不可としている.
     */
    void setRowMax(long i_lRowMax){ this->m_lRowMax = i_lRowMax; }

};

#endif  //__MATRIXCELL_H__
