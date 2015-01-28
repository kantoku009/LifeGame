/**
 * @file    CellAttribute.h
 * @brief   細胞（セル）の属性情報クラス.
 */
#ifndef __CELL_ATTRIBUTE_H__
#define __CELL_ATTRIBUTE_H__

#include "../Lib/Observer.h"

/**
 * @brief   細胞（セル）の属性情報.
 * @note    細胞（セル）が持っている属性.（has-aの関係）.
 * @note    MatrixCellからExpressionCellに情報を受け渡すのにも使用する.
 * @note    受け渡す情報は以下.
 * @note        ・座標位置 横方向.
 * @note        ・座標位置 縦方向.
 * @note        ・セルの状態.
 */
class CellAttribute : public Information
{
public:
    /**
     * @brief   Cellの状態の定義.
     * @note    DEAD:死滅.
     * @note    ALIVE:生存.
     */
    enum CELL_STATE { DEAD=0, ALIVE, CELL_STATE_MAX };

    /**
     * @brief   コンストラクタ.
     * @param   なし.
     */
    CellAttribute() { }

    /**
     * @brief   コンストラクタ.
     * @param   long i_lCol 座標位置（横方向）
     * @param   long i_lRow 座標位置（縦方向）
     * @param   bool i_eState   Cellの状態.
     * @see     Cellの状態はCELL_STATEを参照.
     */
    CellAttribute(long i_lCol, long i_lRow, CELL_STATE i_eState)
    {
        m_lCol = i_lCol;
        m_lRow = i_lRow;
        m_eState = i_eState;
    }

    /**
     * @brief   座標位置（横方向）を取得.
     * @param   なし.
     * @return  座標位置（横方向）.
     */
    long getCol() const { return m_lCol; }

    /**
     * @brief   座標位置（縦方向）を取得.
     * @param   なし.
     * @return  座標位置（縦方向）.
     */
    long getRow() const { return m_lRow; }

    /**
     * @brief   状態を取得.
     * @param   なし.
     * @return  状態.
     * @see     状態はCELL_STATEを参照.
     */
    CELL_STATE getState() const { return m_eState; }

    /**
     * @brief   座標位置（横方向）を設定.
     * @param   座標位置（横方向）.
     * @return  なし.
     */
    void setCol(long i_lCol){ m_lCol = i_lCol; }

    /**
     * @brief   座標位置（縦方向）を設定.
     * @param   座標位置（縦方向）.
     * @return  なし.
     */
    void setRow(long i_lRow){ m_lRow = i_lRow; }

    /**
     * @brief   状態を設定.
     * @param   状態.
     * @return  なし.
     * @see     状態はCELL_STATEを参照.
     */
    void setState(CELL_STATE i_eState){ m_eState = i_eState; }
private:
    /**
     * @brief   座標位置（横方向）.
     */
    long        m_lCol;

    /**
     * @brief   座標位置（縦方向）.
     */
    long        m_lRow;

    /**
     * @brief   状態.
     * @see     状態はCELL_STATEを参照.
     */
    CELL_STATE  m_eState;

};

#endif  // __CELL_ATTRIBUTE_H__
