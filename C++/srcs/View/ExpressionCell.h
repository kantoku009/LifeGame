/**
 * @file    ExpressionCell.h
 * @brief   細胞（セル）の表示を管理するクラスの宣言 及び 実装.
 */

#ifndef __EXPRESSION_CELL_H__
#define __EXPRESSION_CELL_H__

#include "../Lib/Observer.h"
#include "../Model/CellAttribute.h"
#include "../Controller/MatrixCell.h"

/**
 * @brief   細胞（セル）の表示を管理するクラス.
 */
class ExpressionCell : public Observer
{
public:

    /**
     * @brief   コンストラクタ.
     */
    ExpressionCell()
    {
        m_pcMatrixCell = 0;
    }

    /**
     * @brief   デストラクタ.
     */
    virtual ~ExpressionCell(){ }
    
    /**
     * @brief   セルを管理するクラスを生成.
     * @param   long i_lCol 盤面の横最大値
     * @param   long i_lRow 盤面の縦最大値
     * @return  生成の結果.
     * @retval  true    成功.
     * @retval  false   失敗.
     */
    bool createMatrixCell(long i_lColMax, long i_lRowMax);

    /**
     * @brief   セルの状態を取得.
     * @param   long i_lCol 座標位置 横方向.
     * @param   long i_lRow 座標位置 縦方向.
     * @return  セルの状態.
     * @retval  CellAttribute::ALIVE    生存.
     * @retval  CellAttribute::DEAD     死滅.
     */
    CellAttribute::CELL_STATE getCellState(long i_lCol, long i_lRow)
    {
        return m_pcMatrixCell->getCellState(i_lCol, i_lRow);
    }

    /**
     * @brief   セルの状態を設定.
     * @param   long i_lCol 座標位置 横方向.
     * @param   long i_lRow 座標位置 縦方向.
     * @param   bool i_eState   セルの状態.
     * @return  なし.
     */
    void setCellState(long i_lCol, long i_lRow, CellAttribute::CELL_STATE i_eState)
    {
        m_pcMatrixCell->setCellState(i_lCol, i_lRow, i_eState);
    }

    /**
     * @brief   全てのセルの状態を表示.
     * @param   なし.
     * @return  なし.
     * @note    実際の表示は, drawOneCell()を呼び出している.
     */
    bool drawAllCell();

    /**
     * @brief   １つのセルの状態を表示.
     * @param   long i_lCol 座標位置 横方向.
     * @param   long i_lRow 座標位置 縦方向.
     * @param   CellAttribute::CELL_STATE i_eState   セルの状態.
     * @return  成功/失敗. (現状, 成功しか返していない).
     * @note    移植性を考量して, 純粋仮想関数としている. 
     * @note    実際に描画はExpressionCellを継承したクラスで行う.
     */
    virtual bool drawOneCell(long i_lCol, long i_lRow) = 0;

    /**
     * @brief   Observerパターンの通知.
     * @param   Information* i_pcInformation Observerパターンのsubjectから通知されるメッセージ.
     * @return  成功/失敗. (現状, 成功しか返していない).
     */
    bool update(Information* i_pcInformation);

    /**
     * @brief   セルの初期配置.
     * @param   なし.
     * @return  なし.
     */
    void initialPlot();

    /**
     * @brief   None Operation. 何もしない.
     */
    void nop(){ }

    /**
     * @brief   セルを再描画.
     */
    void refreshCell() { m_pcMatrixCell->refreshCell(); }

private:

    /**
     * @brief   細胞（セル）を管理するクラス.
     */
    MatrixCell* m_pcMatrixCell;

};

#endif  // __EXPRESSION_CELL_H__
