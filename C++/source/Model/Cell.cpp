/**
 * @file    Cell.cpp
 * @brief   1細胞（1セル）を管理するクラスの実装.
 */
#include "Cell.h"

/******************************************
 *
 * 自分自身の状態を決定する.
 *
 ******************************************/
bool Cell::decideState()
{
    CellAttribute::CELL_STATE a_ePreviousState = this->m_cAttribute.getState();  // 前状態を記憶.
    CellAttribute::CELL_STATE a_eNextState = this->m_cAttribute.getState();


	// 次の状態を決定.
	if(      true == this->isBorn() )				a_eNextState = CellAttribute::ALIVE;	// 誕生.
	else if( true == this->isSurvive() )			a_eNextState = CellAttribute::ALIVE;	// 生存.
	else if( true == this->isUnderPopulation() )	a_eNextState = CellAttribute::DEAD;		// 過疎.
	else if( true == this->isOverPopulation() )		a_eNextState = CellAttribute::DEAD;		// 過密.

	// 隣接セルの生存数をクリア.
	this->m_lNeighborAliveNum = 0;

	// 次の状態を設定.
    this->m_cAttribute.setState(a_eNextState);

    bool a_bChanged = ( (a_ePreviousState==a_eNextState )? false:true );    // 自分自身の状態が変更されたか否かを確認. false:変更されていない. true:変更された.
    return a_bChanged;                                                      // 自分自身の状態が変更された事を返す.
}

/********************************************************************************
 *
 * 誕生.
 * 　自分自身と隣接セルの状態から, 誕生か否かを判定する.
 * 　死んでいるセルに隣接する生きたセルがちょうど3つあれば、次の世代が誕生する。
 *
 ********************************************************************************/
bool Cell::isBorn()
{
    // 自分自身の状態.
    CellAttribute::CELL_STATE a_eState = this->m_cAttribute.getState();

    if( (CellAttribute::DEAD==a_eState) && (3==this->m_lNeighborAliveNum) ) return true;
    else return false;
}

/*********************************************************************************
 *
 * 生存.
 * 　自分自身と隣接セルの状態から, 生存か否かを判定する.
 * 　生きているセルに隣接する生きたセルが2つか3つならば、次の世代でも生存する。
 *
 *********************************************************************************/
bool Cell::isSurvive()
{
    // 自分自身の状態.
    CellAttribute::CELL_STATE a_eState = this->m_cAttribute.getState();

    if( (CellAttribute::ALIVE==a_eState) && (2==this->m_lNeighborAliveNum|| 3==this->m_lNeighborAliveNum) ) return true;
    else return false;
}

/********************************************************************************
 *
 * 過疎.
 * 　自分自身と隣接セルの状態から, 過疎か否かを判定する.
 * 　生きているセルに隣接する生きたセルが1つ以下ならば、過疎により死滅する。
 *
 ********************************************************************************/
bool Cell::isUnderPopulation()
{
    // 自分自身の状態.
    CellAttribute::CELL_STATE a_eState = this->m_cAttribute.getState();

    if( (CellAttribute::ALIVE==a_eState) && (1>=this->m_lNeighborAliveNum) ) return true;
    else return false;
}

/******************************************************************************
 *
 * 過密.
 * 　自分自身と隣接セルの状態から, 過密か否かを判定する.
 * 　生きているセルに隣接する生きたセルが4つ以上ならば、過密により死滅する。
 *
 ******************************************************************************/
bool Cell::isOverPopulation()
{
    // 自分自身の状態.
    CellAttribute::CELL_STATE a_eState = this->m_cAttribute.getState();

    if( (CellAttribute::ALIVE==a_eState) && (4<=this->m_lNeighborAliveNum) ) return true;
    else return false;
}

