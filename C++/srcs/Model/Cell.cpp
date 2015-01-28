/**
 * @file    Cell.cpp
 * @brief   1細胞（1セル）を管理するクラスの実装.
 */
#include "../Controller/MatrixCell.h"
#include "Cell.h"

Cell::Cell(long i_lCol, long i_lRow)
{
    init(i_lCol, i_lRow);
}

Cell::~Cell()
{
}

/****************************
 * 初期化.
 ****************************/
void Cell::init(long i_lCol, long i_lRow)
{
    m_cAttribute.setCol(i_lCol);
    m_cAttribute.setRow(i_lRow);
    m_cAttribute.setState(CellAttribute::DEAD);

    for(int theI=CellAttribute::DEAD; theI<CellAttribute::CELL_STATE_MAX; theI++)
    {
        m_rglNeighborStateNum[theI] = 0;
    }

    for(int theI=TOP_LEFT; theI<NEIGHBOR_MAX; theI++)
    {
        m_pcNeighborCell[theI] = 0;
    }
}

/*************************************************
 * 境界値をチェックする.
 *************************************************/
long Cell::checkRegion(long i_lValue, long i_lMax)
{
    long a_lValue = i_lValue;

    if( 0 > a_lValue ) a_lValue = i_lMax - 1;
    else if(i_lMax <= a_lValue) a_lValue = 0;

    return a_lValue;
}

/**************************************************************
 * 隣接セルを設定する.
 * 隣接セルの方向と番号は, NEIGHBOR_POSITIONを想定している.
 **************************************************************/
void Cell::setNeighbor(MatrixCell* i_pcMatrixCell)
{
    // 横の隣接セル.（相対位置）.
    long a_rglCol[Cell::NEIGHBOR_MAX] = {
        -1, 0, 1,
        -1,    1,
        -1, 0, 1,
    };
    // 縦の隣接セル.（相対位置）.
    long a_rglRow[Cell::NEIGHBOR_MAX] = {
        -1, -1, -1,
         0,      0,
         1,  1,  1,
    };
    long a_lColMax = i_pcMatrixCell->getColMax();
    long a_lRowMax = i_pcMatrixCell->getRowMax();

    for(int theI=TOP_LEFT; theI<NEIGHBOR_MAX; theI++)
    {
        long a_lCol = m_cAttribute.getCol() + a_rglCol[theI];
        long a_lRow = m_cAttribute.getRow() + a_rglRow[theI];

        a_lCol = checkRegion(a_lCol, a_lColMax);
        a_lRow = checkRegion(a_lRow, a_lRowMax);

        m_pcNeighborCell[theI] = i_pcMatrixCell->getCell(a_lCol, a_lRow);
    }
}

/******************************************
 *
 * 自分自身の状態を決定する.
 *
 ******************************************/
bool Cell::decideState()
{
    bool a_bRet=false;
    CellAttribute::CELL_STATE a_ePreviousState = m_cAttribute.getState();  // 前状態を記憶.
    CellAttribute::CELL_STATE a_eNextState = m_cAttribute.getState();

    if( false == a_bRet )
    {
        // 誕生.
        a_bRet = isBorn();
        if( true == a_bRet ) a_eNextState=CellAttribute::ALIVE;
    }

    if( false == a_bRet )
    {
        // 生存.
        a_bRet = isSurvive();
        if( true == a_bRet ) a_eNextState=CellAttribute::ALIVE;
    }

    if( false == a_bRet )
    {
        // 過疎.
        a_bRet = isUnderPopulation();
        if( true == a_bRet ) a_eNextState=CellAttribute::DEAD;
    }

    if(false == a_bRet)
    {
        // 過密.
        a_bRet = isOverPopulation();
        if( true == a_bRet ) a_eNextState=CellAttribute::DEAD;
    }
    m_cAttribute.setState(a_eNextState);

    for(int theI=CellAttribute::DEAD; theI<CellAttribute::CELL_STATE_MAX; theI++)
    {
        m_rglNeighborStateNum[theI] = 0;
    }

    bool a_bChanged = ( (a_ePreviousState==a_eNextState )? false:true );    // 自分自身の状態が変更されたか否かを確認. false:変更されていない. true:変更された.
    if(true == a_bChanged) notify(&m_cAttribute);                           // 自分自身の状態が変更された事を通知する.
    return a_bChanged;                                                      // 自分自身の状態が変更された事を返す.
}

/****************************************************************
 *
 * 隣接セルに自分の状態を通知する.
 *
 ****************************************************************/
bool Cell::sendStateToNeighborCell()
{
    CellAttribute::CELL_STATE a_eState = m_cAttribute.getState();

    for(int theI=TOP_LEFT; theI<NEIGHBOR_MAX; theI++)
    {
        m_pcNeighborCell[theI]->receiveStateFromNeighborCell(a_eState);
    }

    return true;
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
    // 隣接するセルの生存数.
    long a_lNeighborAliveNum = m_rglNeighborStateNum[CellAttribute::ALIVE];

    // 自分自身の状態.
    CellAttribute::CELL_STATE a_eState = m_cAttribute.getState();

    if( (CellAttribute::DEAD==a_eState) && (3==a_lNeighborAliveNum) ) return true;
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
    // 隣接するセルの生存数.
    long a_lNeighborAliveNum = m_rglNeighborStateNum[CellAttribute::ALIVE];

    // 自分自身の状態.
    CellAttribute::CELL_STATE a_eState = m_cAttribute.getState();

    if( (CellAttribute::ALIVE==a_eState) && (2==a_lNeighborAliveNum || 3==a_lNeighborAliveNum) ) return true;
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
    // 隣接するセルの生存数.
    long a_lNeighborAliveNum = m_rglNeighborStateNum[CellAttribute::ALIVE];

    // 自分自身の状態.
    CellAttribute::CELL_STATE a_eState = m_cAttribute.getState();

    if( (CellAttribute::ALIVE==a_eState) && (1>=a_lNeighborAliveNum) ) return true;
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
    // 隣接するセルの生存数.
    long a_lNeighborAliveNum = m_rglNeighborStateNum[CellAttribute::ALIVE];

    // 自分自身の状態.
    CellAttribute::CELL_STATE a_eState = m_cAttribute.getState();

    if( (CellAttribute::ALIVE==a_eState) && (4<=a_lNeighborAliveNum) ) return true;
    else return false;
}

/**************************************************************
 *
 * 隣接セルから状態を受け取る
 *
 **************************************************************/
bool Cell::receiveStateFromNeighborCell(CellAttribute::CELL_STATE i_eState)
{
    bool a_bRet = false;

    m_rglNeighborStateNum[i_eState]++;

    return a_bRet;
}


