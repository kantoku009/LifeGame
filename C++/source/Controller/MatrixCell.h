/**
 * @file MatrixCell.h
 * @brief   全細胞（全セル）を管理するクラスの宣言.
 */

#ifndef __MATRIXCELL_H__
#define __MATRIXCELL_H__

#include <vector>

#include "../Lib/Observer.h"
#include "../Model/CellAttribute.h"
#include "../Model/Cell.h"

/**
 * @brief   全細胞（全セル）を管理するクラス.
 * @note    Cellを管理する.
 */
class MatrixCell : public Observer , public Subject
{
public:

    /**
     * @brief   コンストラクタ.
     */
    MatrixCell(long i_lColMax, long i_lRowMax);

    /**
     * @brief   デストラクタ.
     */
    virtual ~MatrixCell();

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
    long getColMax() const { return m_lColMax; }

    /**
     * @brief   セルの縦最大幅を取得.
     * @param   なし.
     * @return  セルの縦最大幅.
     */
    long getRowMax() const { return m_lRowMax; }

    /**
     * @brief       Observerパターンの通知.
     * @param       Information* i_pcInformation Observerパターンのsubjectから通知されるメッセージ.
     * @return      結果を返す.
     */
    bool update(Information* i_pcInformation);

    /**
     * @brief   全セルの更新を行う.
     * @param   なし.
     * @return  更新の結果.
     * @retval  true    成功.
     * @retval  false   失敗.
     */
    bool refreshCell();

    /**
     * @brief   セルを取得する.
     * @param   long i_lCol 取得したいセルの横位置.
     * @param   long i_lRow 取得したいセルの縦位置.
     * @return  セル
     */
    Cell* getCell(long i_lCol, long i_lRow);

    /**
     * @brief   セルの状態を設定する.
     * @param   long i_lCol セルの座標位置（横方向）
     * @param   long i_lRow セルの座標位置（縦方向）
     * @param   CellAttribute::CELL_STATE i_eState 設定したいセルの状態
     * @return  なし.
     */
    void setCellState(long i_lCol, long i_lRow, CellAttribute::CELL_STATE i_eState);

    /**
     * @brief   セルの状態を取得する.
     * @param   long i_lCol セルの座標位置（横方向）
     * @param   long i_lRow セルの座標位置（縦方向）
     * @return  セルの状態. 0:死 1:生
     * @retval  true    生
     * @retval  false   死
     */
    CellAttribute::CELL_STATE getCellState(long i_lCol, long i_lRow);

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
    bool linkNeighborCell();

    /**
     * @brief       隣接セルに自分自身の状態を通知する.
     * @param       なし.
     * @return      通知結果.
     * @retval      true    成功.
     * @retval      false   失敗.
     */
    bool notifyNeighborCell();

    /**
     * @brief       次世代のセルを計算する.
     * @param       なし.
     * @return      通知結果.
     * @retval      true    成功.
     * @retval      false   失敗.
     */
    bool calcNextGeneration();

    /**
     * @brief   セル横最大幅を設定.
     * @param   セル横最大幅.
     * @return  なし.
     * @note    将来的には, セル横最大幅を可変にしたい.
     *          privateにしておくことで, プログラム実行中に変更不可としている.
     */
    void setColMax(long i_lColMax){ m_lColMax = i_lColMax; }

    /**
     * @brief   セルの縦最大幅を設定.
     * @param   セル横最大幅.
     * @return  なし.
     * @note    将来的には, セル縦最大幅を可変にしたい.
     *          privateにしておくことで, プログラム実行中に変更不可としている.
     */
    void setRowMax(long i_lRowMax){ m_lRowMax = i_lRowMax; }

};

#endif  //__MATRIXCELL_H__
