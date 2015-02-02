/**
 * @file    CellAttribute.h
 * @brief   細胞（セル）の属性情報クラス.
 */
#ifndef __CELL_ATTRIBUTE_H__
#define __CELL_ATTRIBUTE_H__

#include "Observer.h"

/**
 * @brief   細胞（セル）の属性情報.
 * @note    細胞（セル）が持っている属性.（has-aの関係）.
 * @note    MatrixCellからExpressionCellに情報を受け渡すのにも使用する.
 * @note    受け渡す情報は以下.
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
     * @param   bool i_eState   Cellの状態.
     * @see     Cellの状態はCELL_STATEを参照.
     */
	CellAttribute()
	{
		this->m_eState = CellAttribute::DEAD;
	}

    /**
     * @brief   コンストラクタ.
     * @param   bool i_eState   Cellの状態.
     * @see     Cellの状態はCELL_STATEを参照.
     */
    CellAttribute(CELL_STATE i_eState)
    {
        this->m_eState = i_eState;
    }

    /**
     * @brief   状態を取得.
     * @param   なし.
     * @return  状態.
     * @see     状態はCELL_STATEを参照.
     */
    CELL_STATE getState() const { return m_eState; }

    /**
     * @brief   状態を設定.
     * @param   状態.
     * @return  なし.
     * @see     状態はCELL_STATEを参照.
     */
    void setState(CELL_STATE i_eState){ m_eState = i_eState; }

private:
    /**
     * @brief   状態.
     * @see     状態はCELL_STATEを参照.
     */
    CELL_STATE  m_eState;
};

#endif  // __CELL_ATTRIBUTE_H__
