/**
 * @file    MatrixCell.cpp
 * @brief   全細胞（全セル）を管理するクラスの実装.
 */
#include "MatrixCell.h"

MatrixCell::MatrixCell(long i_lColMax, long i_lRowMax)
{
    init(i_lColMax, i_lRowMax);
}

MatrixCell::~MatrixCell()
{

}

void MatrixCell::setCellState(long i_lCol, long i_lRow, CellAttribute::CELL_STATE i_eState)
{
    Cell* a_pcCell = getCell(i_lCol, i_lRow);

    //CellAttribute::CELL_STATE a_eState;
    //if(true == i_eState) a_eState = CellAttribute::ALIVE;
    //else a_eState = CellAttribute::DEAD;
    a_pcCell->setState(i_eState);
}

CellAttribute::CELL_STATE MatrixCell::getCellState(long i_lCol, long i_lRow)
{
    CellAttribute::CELL_STATE a_eState;
    Cell* a_pcCell = getCell(i_lCol, i_lRow);
    a_eState = a_pcCell->getState();

    return a_eState;
}

/***************************************
 * 初期化する.
 * 　・2次元配列のメモリ確保.
 * 　・セルを生成.
 * 　・隣接セルをリンクさせる.
 ***************************************/
void MatrixCell::init(long i_lColMax, long i_lRowMax)
{
    
    // 2次元配列のメモリ確保.
    m_vecCellArray.reserve(i_lRowMax);
    for(long a_lRow=0; a_lRow<i_lRowMax; a_lRow++)
    {
        m_vecCellArray[a_lRow].reserve(i_lColMax);
    }

    setColMax(i_lColMax);   // 横幅最大値 設定.
    setRowMax(i_lRowMax);   // 縦幅最大値 設定.
    makeCell();             // セルの生成.
    linkNeighborCell();     // 隣接セルをリンクさせる.
}

/**********************************
 * セルを生成する.
 *
 * @@ToDo:NULLチェックをする事@@
 **********************************/
bool MatrixCell::makeCell()
{
    Cell* a_pcCell = 0;

    for(long a_lRow=0; a_lRow<m_lRowMax; a_lRow++)
    {
        for(long a_lCol=0; a_lCol<m_lColMax; a_lCol++)
        {
            a_pcCell = new Cell(a_lCol, a_lRow);
            // @@ToDo@@

            a_pcCell->attach(this);
            m_vecCellArray[a_lRow][a_lCol] = a_pcCell;
        }
    }

    return true;
}


/******************************************
 * 隣接セルをリンクさせる.
 *
 ******************************************/
bool MatrixCell::linkNeighborCell()
{
    Cell* a_pcCell = 0;

     for(long a_lRow=0; a_lRow<m_lRowMax; a_lRow++)
    {
        for(long a_lCol=0; a_lCol<m_lColMax; a_lCol++)
        {
            a_pcCell = getCell(a_lCol, a_lRow);
            a_pcCell->setNeighbor(this);
        }
    }
   
    return true;
}


/*********************************
 * update
 *
 * @@ToDo:NULLチェックをする事.
 *********************************/
bool MatrixCell::update(Information* i_pcInformation)
{
    notify(i_pcInformation);

    return true;
}

/******************************
 * セルを更新.
 *
 ******************************/
bool MatrixCell::refreshCell()
{
    notifyNeighborCell();
    calcNextGeneration();
    return true;
}

/******************************************
 * 隣接セルに自分自身の状態を通知する.
 *
 * @@ToDo:NULLチェックをする事@@
 ******************************************/
bool MatrixCell::notifyNeighborCell()
{
    Cell* a_pcCell = 0;

    for(long a_lRow=0; a_lRow<m_lRowMax; a_lRow++)
    {
        for(long a_lCol=0; a_lCol<m_lColMax; a_lCol++)
        {
            a_pcCell = getCell(a_lCol, a_lRow);
            // @@ToDo@@

            a_pcCell->sendStateToNeighborCell();
        }
    }
    return true;
}

/******************************************
 * 次世代のセルを計算する.
 *
 * @@ToDo:NULLチェックをする事@@
 ******************************************/

bool MatrixCell::calcNextGeneration()
{
    Cell* a_pcCell = 0;

    for(long a_lRow=0; a_lRow<m_lRowMax; a_lRow++)
    {
        for(long a_lCol=0; a_lCol<m_lColMax; a_lCol++)
        {
            a_pcCell = getCell(a_lCol, a_lRow);
            // @@ToDo@@

            a_pcCell->decideState();

        }
    }

    return true;
}

/*****************************************
 * セルの横位置／縦位置からセルを取得する.
 *
 *****************************************/
Cell* MatrixCell::getCell(long i_lCol, long i_lRow)
{
    Cell* a_pcCell = m_vecCellArray[i_lRow][i_lCol];
    return a_pcCell;
}


