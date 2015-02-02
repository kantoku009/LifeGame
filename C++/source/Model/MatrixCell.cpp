/**
 * @file    MatrixCell.cpp
 * @brief   全細胞（全セル）を管理するクラスの実装.
 */
#include "MatrixCell.h"

#include <iostream>		// デバッグ用.
#include <sstream>		// デバッグ用.
#include <string>		// デバッグ用.
using namespace std;

/***************************************
 * 初期化する.
 * 　・2次元配列のメモリ確保.
 * 　・セルを生成.
 * 　・隣接セルをリンクさせる.
 ***************************************/
void MatrixCell::init(long i_lColMax, long i_lRowMax)
{
    this->setColMax(i_lColMax);	// 横幅最大値 設定.
    this->setRowMax(i_lRowMax);	// 縦幅最大値 設定.
    this->makeCell();			// セルの生成.
    this->linkCell();			// 隣接セルをリンクさせる.
}

/******************************
 * セルを更新.
 *
 ******************************/
bool MatrixCell::refreshCell()
{
	// 隣接セルに自分自身の状態を通知する.
    this->sendStateToNeighborCell();
	// 次世代のセルを決定する.
    this->decideNextGeneration();

	return true;
}

/**********************************
 * セルを生成する.
 *
 * @@ToDo:NULLチェックをする事@@
 **********************************/
bool MatrixCell::makeCell()
{
    Cell* a_pcCell = 0;
	vector<Cell*> a_vecCell;

    for(long a_lRow=0; a_lRow<m_lRowMax; a_lRow++)
    {
        for(long a_lCol=0; a_lCol<m_lColMax; a_lCol++)
        {
            a_pcCell = new Cell();
            // @@ToDo@@

			a_vecCell.push_back(a_pcCell);
        }
		this->m_vecCellArray.push_back(a_vecCell);
		a_vecCell.clear();
    }

    return true;
}

/******************************************
 * 隣接セルをリンクさせる.
 ******************************************/
bool MatrixCell::linkCell()
{
    Cell* a_pcCell = 0;

     for(long a_lRow=0; a_lRow<m_lRowMax; a_lRow++)
    {
        for(long a_lCol=0; a_lCol<m_lColMax; a_lCol++)
        {
            a_pcCell = this->getCell(a_lCol, a_lRow);
			this->setNeighborCell(a_pcCell, a_lCol, a_lRow);
        }
    }
   
    return true;
}

/******************************************
 * 隣接セルを設定する.
 ******************************************/
bool MatrixCell::setNeighborCell(Cell* i_pcTargetCell, long i_lCol, long i_lRow)
{
	// 横の隣接セル（相対位置）.
	long a_rglCol[] =
	{
		-1, 0, 1,
		-1,    1,
		-1, 0, 1,
	};
	// 縦の隣接セル（相対位置）.
	long a_rglRow[] =
	{
		-1, -1, -1,
		 0,      0,
		 1,  1,  1,
	};

	for(long a_lIndex=0; a_lIndex<8; a_lIndex++)
	{
		// 隣接セル（縦）のインデックスを計算.
		long a_lNeighborCol = i_lCol + a_rglCol[a_lIndex];
		// 隣接セル（横）のインデックスを計算.
		long a_lNeighborRow = i_lRow + a_rglRow[a_lIndex];

		// インデックスの境界値をチェック.
		a_lNeighborCol = this->check_region(a_lNeighborCol, this->m_lColMax);
		a_lNeighborRow = this->check_region(a_lNeighborRow, this->m_lRowMax);

		// 隣接セルを取得.
		Cell* a_pcNeighborCell = this->getCell(a_lNeighborCol, a_lNeighborRow);

		// 隣接セルを設定.
		i_pcTargetCell->setNeighbor(a_pcNeighborCell);
	}

	return true;
}

/******************************************
 * 境界値をチェックする.
 *
 ******************************************/
long MatrixCell::check_region(long i_lValue, long i_lMax)
{
	long a_lValue = i_lValue;

	if		(0>a_lValue)		a_lValue = i_lMax -1;
	else if	(i_lMax<=a_lValue)	a_lValue = 0;
	else						a_lValue = i_lValue;

	return a_lValue;
}


/******************************************
 * 隣接セルに自分自身の状態を通知する.
 *
 * @@ToDo:NULLチェックをする事@@
 ******************************************/
bool MatrixCell::sendStateToNeighborCell()
{
    Cell* a_pcCell = 0;

    for(long a_lRow=0; a_lRow<m_lRowMax; a_lRow++)
    {
        for(long a_lCol=0; a_lCol<m_lColMax; a_lCol++)
        {
            a_pcCell = this->getCell(a_lCol, a_lRow);
            // @@ToDo@@

            a_pcCell->sendState();
        }
    }
    return true;
}

/******************************************
 * 次世代のセルを決定する.
 *
 * @@ToDo:NULLチェックをする事@@
 ******************************************/
bool MatrixCell::decideNextGeneration()
{
    Cell* a_pcCell = 0;

    for(long a_lRow=0; a_lRow<m_lRowMax; a_lRow++)
    {
        for(long a_lCol=0; a_lCol<m_lColMax; a_lCol++)
        {
            a_pcCell = this->getCell(a_lCol, a_lRow);
            // @@ToDo@@

            a_pcCell->decideState();
        }
    }

    return true;
}

/******************************************
 * 全セルの状態を表示.
 * デバッグ用.
 ******************************************/
string MatrixCell::dispAllCellState()
{
	stringstream a_strStream;

	for(long a_lRow=0; a_lRow<m_lRowMax; a_lRow++)
	{
		for(long a_lCol=0; a_lCol<m_lColMax; a_lCol++)
		{
			Cell* a_pcCell = this->getCell(a_lCol, a_lRow);
			CellAttribute::CELL_STATE a_eState = a_pcCell->getState();
			a_strStream << a_eState;
		}
		a_strStream << endl;
	}

	return a_strStream.str();
}

/******************************************
 * 隣接セルの生存数を表示.
 * デバッグ用.
 ******************************************/
string MatrixCell::dispNeighborAliveCell()
{
	stringstream a_strStream;

	for(long a_lRow=0; a_lRow<m_lRowMax; a_lRow++)
	{
		for(long a_lCol=0; a_lCol<m_lColMax; a_lCol++)
		{
			Cell* a_pcCell = this->getCell(a_lCol, a_lRow);
			a_strStream << a_pcCell->getNeighborAliveNum();
		}
		a_strStream << endl;
	}

	return a_strStream.str();
}

