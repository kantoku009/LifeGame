/**
 * @file    ExpressionCell.cpp
 * @brief   細胞（セル）の表示を管理するクラスの実装.
 */


#include "ExpressionCell.h"

/*******************************
 * セルを管理するクラスを生成.
 *******************************/
bool ExpressionCell::createMatrixCell(long i_lColMax, long i_lRowMax)
{
    m_pcMatrixCell = new MatrixCell(i_lColMax, i_lRowMax);
    if(m_pcMatrixCell == 0) return false;

    m_pcMatrixCell->attach(this);

    // セルの初期配置を実施.
    initialPlot();

    // 盤面に全セルの状態を描画.
    drawAllCell();

    return true;
}


/**************************
 * 全てのセルの状態を表示.
 **************************/
bool ExpressionCell::drawAllCell()
{
    long a_lColMax = m_pcMatrixCell->getColMax();
    long a_lRowMax = m_pcMatrixCell->getRowMax();

    for(long a_lRow=0; a_lRow<a_lRowMax; a_lRow++)
    {
        for(long a_lCol=0; a_lCol<a_lColMax; a_lCol++)
        {
            drawOneCell(a_lCol, a_lRow);
        }
    }
    return true;
}

/***************************
 * Observerパターンの通知.
 ***************************/
bool ExpressionCell::update(Information* i_pcInformation)
{
    CellAttribute* a_pcCellAttribute = static_cast<CellAttribute*>(i_pcInformation);
    long a_lCol = a_pcCellAttribute->getCol();
    long a_lRow = a_pcCellAttribute->getRow();

    drawOneCell(a_lCol, a_lRow);
    return true;
}

/*********************
 * セルの初期配置.
 *********************/
void ExpressionCell::initialPlot()
{
    // 蜂の巣 (固定物体)
    m_pcMatrixCell->setCellState(3,1, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(4,1, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(2,2, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(5,2, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(3,3, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(4,3, CellAttribute::ALIVE);
    
    // ブロック (固定物体)
    m_pcMatrixCell->setCellState(3,5, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(4,5, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(3,6, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(4,6, CellAttribute::ALIVE);

    // 船 (固定物体)
    m_pcMatrixCell->setCellState(3,8, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(4,8, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(2,9, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(4,9, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(2,10, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(3,10, CellAttribute::ALIVE);

    // ブリンカー (振動子)
    m_pcMatrixCell->setCellState(10,1, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(10,2, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(10,3, CellAttribute::ALIVE);

    // ブリンカー (振動子)
    m_pcMatrixCell->setCellState(6,5, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(7,5, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(8,5, CellAttribute::ALIVE);

    // ブリンカー (振動子)
    m_pcMatrixCell->setCellState(12,5, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(13,5, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(14,5, CellAttribute::ALIVE);

    // ブリンカー (振動子)
    m_pcMatrixCell->setCellState(10,7, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(10,8, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(10,9, CellAttribute::ALIVE);

    // グライダー (移動物体)
    m_pcMatrixCell->setCellState(2,15, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(3,18, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(1,17, CellAttribute::ALIVE);  
    m_pcMatrixCell->setCellState(2,17, CellAttribute::ALIVE);
    m_pcMatrixCell->setCellState(3,17, CellAttribute::ALIVE);
}


