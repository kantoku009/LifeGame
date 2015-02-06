/**
 * @file    MatrixCellAttribute.h
 * @brief   MatrixCellの属性情報クラス.
 */
#ifndef __MATRIXCELL_ATTRIBUTE_H__
#define __MATRIXCELL_ATTRIBUTE_H__

#include "Observer.h"
#include "CellAttribute.h"

/**
 * @brief   MatrixCellの属性情報.
 * @note    MatrixCellが持っている属性.（has-aの関係）.
 * @note    受け渡す情報は以下.
 *	        ・セルの状態.
 *			・座標.
 */
class MatrixCellAttribute : public Information
{
public:
    /**
     * @brief   コンストラクタ.
     * @param   bool i_eState   Cellの状態.
     * @see     Cellの状態はCELL_STATEを参照.
     */
	MatrixCellAttribute()
	{
		this->m_cCellAttribute.setState(CellAttribute::DEAD);
		this->m_lCol = -1;
		this->m_lRow = -1;
	}

    /**
     * @brief   コンストラクタ.
     * @param   bool i_eState   Cellの状態.
     * @see     Cellの状態はCELL_STATEを参照.
     */
    MatrixCellAttribute(long i_lCol, long i_lRow, CellAttribute::CELL_STATE i_eState)
    {
        this->m_cCellAttribute.setState(i_eState);
		this->m_lCol = i_lCol;
		this->m_lRow = i_lRow;
    }

    /**
     * @brief   状態を取得.
     * @param   なし.
     * @return  状態.
     * @see     状態はCELL_STATEを参照.
     */
	CellAttribute::CELL_STATE getState() const { return m_cCellAttribute.getState(); }

    /**
     * @brief   状態を設定.
     * @param   状態.
     * @return  なし.
     * @see     状態はCELL_STATEを参照.
     */
    void setState(CellAttribute::CELL_STATE i_eState){ m_cCellAttribute.setState(i_eState); }

	/**
	 * @brief	MatrixCell 横座標を取得.
	 * @param	なし.
	 * @return	横座標.
	 */
	long getCol() const { return this->m_lCol; }

	/**
	 * @brief	MatrixCell 横座標を設定.
	 * @param	横座標.
	 * @return	なし.
	 */
	void setCol(long i_lCol) { this->m_lCol = i_lCol; }

	/**
	 * @brief	MatrixCell 縦座標を取得.
	 * @param	なし.
	 * @return	縦座標.
	 */
	long getRow() const { return this->m_lRow; }

	/**
	 * @brief	MatrixCell 縦座標を設定.
	 * @param	縦座標.
	 * @return	なし.
	 */
	void setRow(long i_lRow) { this->m_lRow = i_lRow; }

private:
    /**
     * @brief   状態.
     * @see     状態はCELL_STATEを参照.
     */
    CellAttribute	m_cCellAttribute;

	/**
	 * @brief	横座標.
	 */
	long m_lCol;

	/**
	 * @brief	縦座標.
	 */
	long m_lRow;
};

#endif  // __MATRIXCELL_ATTRIBUTE_H__
