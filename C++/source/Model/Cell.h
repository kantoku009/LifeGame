/**
 * @file    Cell.h
 * @brief   1細胞（1セル）を管理するクラスの宣言.
 */

#ifndef __CELL_H__
#define __CELL_H__

#include "../Lib/Observer.h"
#include "../Lib/CellAttribute.h"

/**
 * @brief 細胞（セル）1個をあらわすクラス.
 */
class Cell : public Subject, Observer
{
public:

    /**
     * @brief   コンストラクタ.
     */
    Cell()
	{
		this->init();
	}

    /**
     * @brief   デストラクタ.
     */
    virtual ~Cell() { }

    /**
     * @brief   初期化.
     * @param   なし.
     * @return  なし.
     */
    void init()
	{
		this->m_lNeighborAliveNum = 0;
		this->m_cAttribute.setState(CellAttribute::DEAD);
	}

    /**
     * @brief   自分自身のセルの状態を取得.
     * @param   なし.
     * @return  セルの状態.(DEAD/ALIVE).
     * @retval  DEAD    死滅.
     * @retval  ALIVE   生存.
     */
    CellAttribute::CELL_STATE getState() const
    {
        return (this->m_cAttribute.getState());
    }

    /**
     * @brief   自分自身のセルの状態を設定.
     * @param   CellAttribute::CELL_STATE i_eState 設定したい状態.
     * @return  なし.
     */
    void setState(CellAttribute::CELL_STATE i_eState)
    {
        this->m_cAttribute.setState(i_eState);
    }

    /**
     * @brief   隣接セルを設定する.
     * @param   Cell* i_pCell	隣接セル.
     * @return  なし.
     */
    void setNeighbor(Cell* i_pCell)
	{
		this->attach(i_pCell);
	}

    /**
     * @brief   隣接セルに自分の状態を通知する.
     * @param   なし.
     * @return  通知に成功/失敗を返す.
     * @retval  true    成功.
     * @retval  false   失敗.
     */
    bool sendState()
	{
		this->notify(&(this->m_cAttribute));
	    return true;
	}

    /**
     * @brief   自分自身の状態を決定する.
     * @param   なし.
     * @return  前状態から変更があったかを返す.
     * @retval  true    変更有り.
     * @retval  false   変更無し.
     * @note    隣接セルの状態から自分自身の状態を決定する.<br>
     *          記憶していた隣接セルの状態をクリアする.<br>
     */
    bool decideState();

	/**
	 * @brief	Subjectから通知を受信.
	 * @param	Information* i_pcInformation セルの属性.
	 * @return	成功/失敗.
	 * @note	CellAttributeのインスタンスが渡されることを想定している.
	 */
	bool update(Information* i_pcInformation)
	{
		this->receiveStateFromNeighborCell( static_cast<CellAttribute*>(i_pcInformation) );
		return true;
	}

	/**
	 * @brief	隣接セルの生存数を取得.
	 * @param	なし.
	 * @return	隣接セルの生存数.
	 * @note	デバッグ用.
	 */
	long getNeighborAliveNum() const
	{
		return this->m_lNeighborAliveNum;
	}

private:
    
    /**
     * @brief   自分自身のセルの属性.
     * @note    状態を保持する.
     */
    CellAttribute m_cAttribute;

    /**
     * @brief   隣接セルの生存数.
     */
    long m_lNeighborAliveNum;

    /**
     * @brief   隣接セルの状態を受け取る.
     * @param   CellAttribute::CELL_STATE i_eState 隣接セルの状態(DEAD/ALIVE)
     * @return  結果.
     * @retval  true    成功.
     * @retval  false   失敗.
     */
    bool receiveStateFromNeighborCell(CellAttribute* i_pcCellAttribute)
	{
		if(CellAttribute::ALIVE == i_pcCellAttribute->getState())
		{
			this->m_lNeighborAliveNum++;
		}
		return true;
	}

    /**
     * @brief   自分自身と隣接セルの状態から, 誕生か否かを判定する.
     * @param   なし.
     * @return  セルの状態がALIVEとなるかを返す.
     * @retval  true    セルの状態がALIVEとなる.
     * @retval  false   セルの状態は変更無し.
     * @note    死んでいるセルに隣接する生きたセルがちょうど3つあれば,次の世代が誕生する.
     */
    bool isBorn();

    /**
     * @brief   自分自身と隣接セルの状態から, 生存か否かを判定する.
     * @param   なし.
     * @return  セルの状態がALIVEとなるかを返す.
     * @retval  true    セルの状態がALIVEとなる.
     * @retval  false   セルの状態は変更無し.
     * @note    生きているセルに隣接する生きたセルが2つか3つならば, 次の世代でも生存する.
     */
    bool isSurvive();

    /**
     * @brief   自分自身と隣接セルの状態から, 過疎か否かを判定する.
     * @param   なし.
     * @return  セルの状態がDEADとなるかを返す.
     * @retval  true    セルの状態がDEADとなる.
     * @retval  false   セルの状態は変更無し.
     * @note    生きているセルに隣接する生きたセルが1つ以下ならば, 過疎により死滅する.
     */
    bool isUnderPopulation();

    /**
     * @brief   自分自身と隣接セルの状態から, 過密か否かを判定する.
     * @param   なし.
     * @return  セルの状態がDEADとなるを返す.
     * @retval  true    セルの状態がDEADとなる.
     * @retval  false   セルの状態は変更無し.
     * @note    生きているセルに隣接する生きたセルが4つ以上ならば, 過密により死滅する.
     */
    bool isOverPopulation();

};

#endif  //__CELL_H__
