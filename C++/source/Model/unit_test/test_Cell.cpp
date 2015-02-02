/***********************************
 * Cellクラスのユニットテスト
 ***********************************/

#include <iostream>
#include "../Cell.h"

void print_test_result(const char* i_pMessage, bool i_bIsSuccess)
{
	std::cout << i_pMessage << ": ";
	if(i_bIsSuccess) std::cout << "OK";
	else std::cout << "NG";
	std::cout << std::endl;
}

// セルの生成をテスト.
bool test_cell_generate()
{
	// セルを生成.
	Cell a_cCell;

	bool a_bIsSuccess = (CellAttribute::DEAD==a_cCell.getState());
	return a_bIsSuccess;
}

// セルの状態を設定をテスト.
bool test_setState()
{
	// セルを生成.
	Cell a_cCell;

	// セルの状態を設定.
	a_cCell.setState(CellAttribute::ALIVE);

	bool a_bIsSuccess = (CellAttribute::ALIVE==a_cCell.getState());
	return a_bIsSuccess;
}

// 隣接セルから自分に状態が通知されるかをテスト.
// a_cNeighborCell→a_cSelfCellに状態が通知できるかをテストする.
bool test_sendState()
{
	// セルを生成.
	Cell a_cSelfCell;
	Cell a_cNeighborCell;

	// セルの状態を設定.
	a_cNeighborCell.setState(CellAttribute::ALIVE);

	// 隣接セルを設定.
	a_cNeighborCell.setNeighbor(&a_cSelfCell);

	// 隣接セルから自分に状態を通知.
	a_cNeighborCell.sendState();

	// 隣接セルの生存数を取得.
	long a_lNeighborAliveNum = a_cSelfCell.getNeighborAliveNum();

	bool a_bIsSuccess = (1==a_lNeighborAliveNum);
	return a_bIsSuccess;
}

// セルの誕生をテスト.
bool test_cell_born()
{
	Cell a_cSelfCell;
	Cell a_rgcNeighborCell[3];

	// 自分自身の状態を"死"に設定.
	a_cSelfCell.setState(CellAttribute::DEAD);

	// 隣接セルの設定と通知.
	long a_lMax = sizeof(a_rgcNeighborCell) / sizeof(a_rgcNeighborCell[0]);
	Cell* a_pcCell = a_rgcNeighborCell;
	for(long a_lIndex=0; a_lIndex<a_lMax; a_lIndex++)
	{
		a_pcCell->setState(CellAttribute::ALIVE);
		a_pcCell->setNeighbor(&a_cSelfCell);
		a_pcCell->sendState();
		a_pcCell++;
	}

	// 自分自身の状態を決定.
	a_cSelfCell.decideState();

	bool a_bIsSuccess = (CellAttribute::ALIVE== a_cSelfCell.getState());
	return a_bIsSuccess;
}

// セルの生存をテスト その１.
bool test_cell_survive1()
{
	Cell a_cSelfCell;
	Cell a_rgcNeighborCell[2];

	// 自分自身の状態を"生"に設定.
	a_cSelfCell.setState(CellAttribute::ALIVE);

	// 隣接セルの設定と通知.
	long a_lMax = sizeof(a_rgcNeighborCell) / sizeof(a_rgcNeighborCell[0]);
	Cell* a_pcCell = a_rgcNeighborCell;
	for(long a_lIndex=0; a_lIndex<a_lMax; a_lIndex++)
	{
		a_pcCell->setState(CellAttribute::ALIVE);
		a_pcCell->setNeighbor(&a_cSelfCell);
		a_pcCell->sendState();
		a_pcCell++;
	}

	// 自分自身の状態を決定.
	a_cSelfCell.decideState();

	bool a_bIsSuccess = (CellAttribute::ALIVE== a_cSelfCell.getState());
	return a_bIsSuccess;
}

// セルの生存をテスト その２.
bool test_cell_survive2()
{
	Cell a_cSelfCell;
	Cell a_rgcNeighborCell[3];

	// 自分自身の状態を"生"に設定.
	a_cSelfCell.setState(CellAttribute::ALIVE);

	// 隣接セルの設定と通知.
	long a_lMax = sizeof(a_rgcNeighborCell) / sizeof(a_rgcNeighborCell[0]);
	Cell* a_pcCell = a_rgcNeighborCell;
	for(long a_lIndex=0; a_lIndex<a_lMax; a_lIndex++)
	{
		a_pcCell->setState(CellAttribute::ALIVE);
		a_pcCell->setNeighbor(&a_cSelfCell);
		a_pcCell->sendState();
		a_pcCell++;
	}

	// 自分自身の状態を決定.
	a_cSelfCell.decideState();

	bool a_bIsSuccess = (CellAttribute::ALIVE== a_cSelfCell.getState());
	return a_bIsSuccess;
}

// セルの過疎をテスト その１.
bool test_cell_under_population1()
{
	Cell a_cSelfCell;
	Cell a_rgcNeighborCell[1];

	// 自分自身の状態を"生"に設定.
	a_cSelfCell.setState(CellAttribute::ALIVE);

	// 隣接セルの設定と通知.
	long a_lMax = sizeof(a_rgcNeighborCell) / sizeof(a_rgcNeighborCell[0]);
	Cell* a_pcCell = a_rgcNeighborCell;
	for(long a_lIndex=0; a_lIndex<a_lMax; a_lIndex++)
	{
		a_pcCell->setState(CellAttribute::ALIVE);
		a_pcCell->setNeighbor(&a_cSelfCell);
		a_pcCell->sendState();
		a_pcCell++;
	}

	// 自分自身の状態を決定.
	a_cSelfCell.decideState();

	bool a_bIsSuccess = (CellAttribute::DEAD== a_cSelfCell.getState());
	return a_bIsSuccess;
}

// セルの過疎をテスト その２.
bool test_cell_under_population2()
{
	Cell a_cSelfCell;
	Cell a_rgcNeighborCell[1];

	// 自分自身の状態を"生"に設定.
	a_cSelfCell.setState(CellAttribute::ALIVE);

	// 隣接セルの設定と通知.
	long a_lMax = sizeof(a_rgcNeighborCell) / sizeof(a_rgcNeighborCell[0]);
	Cell* a_pcCell = a_rgcNeighborCell;
	for(long a_lIndex=0; a_lIndex<a_lMax; a_lIndex++)
	{
		a_pcCell->setState(CellAttribute::DEAD);
		a_pcCell->setNeighbor(&a_cSelfCell);
		a_pcCell->sendState();
		a_pcCell++;
	}

	// 自分自身の状態を決定.
	a_cSelfCell.decideState();

	bool a_bIsSuccess = (CellAttribute::DEAD== a_cSelfCell.getState());
	return a_bIsSuccess;
}


// セルの過密をテスト その１.
bool test_cell_over_population1()
{
	Cell a_cSelfCell;
	Cell a_rgcNeighborCell[4];

	// 自分自身の状態を"生"に設定.
	a_cSelfCell.setState(CellAttribute::ALIVE);

	// 隣接セルの設定と通知.
	long a_lMax = sizeof(a_rgcNeighborCell) / sizeof(a_rgcNeighborCell[0]);
	Cell* a_pcCell = a_rgcNeighborCell;
	for(long a_lIndex=0; a_lIndex<a_lMax; a_lIndex++)
	{
		a_pcCell->setState(CellAttribute::ALIVE);
		a_pcCell->setNeighbor(&a_cSelfCell);
		a_pcCell->sendState();
		a_pcCell++;
	}

	// 自分自身の状態を決定.
	a_cSelfCell.decideState();

	bool a_bIsSuccess = (CellAttribute::DEAD== a_cSelfCell.getState());
	return a_bIsSuccess;
}

// セルの過密をテスト その２.
bool test_cell_over_population2()
{
	Cell a_cSelfCell;
	Cell a_rgcNeighborCell[5];

	// 自分自身の状態を"生"に設定.
	a_cSelfCell.setState(CellAttribute::ALIVE);

	// 隣接セルの設定と通知.
	long a_lMax = sizeof(a_rgcNeighborCell) / sizeof(a_rgcNeighborCell[0]);
	Cell* a_pcCell = a_rgcNeighborCell;
	for(long a_lIndex=0; a_lIndex<a_lMax; a_lIndex++)
	{
		a_pcCell->setState(CellAttribute::ALIVE);
		a_pcCell->setNeighbor(&a_cSelfCell);
		a_pcCell->sendState();
		a_pcCell++;
	}

	// 自分自身の状態を決定.
	a_cSelfCell.decideState();

	bool a_bIsSuccess = (CellAttribute::DEAD== a_cSelfCell.getState());
	return a_bIsSuccess;
}

bool test_Cell()
{
	bool a_bIsSuccess = false;

	// セルの生成をテスト.
	a_bIsSuccess = test_cell_generate();
	print_test_result("test_cell_generate", a_bIsSuccess);

	// セルの状態を設定をテスト.
	a_bIsSuccess = test_setState();
	print_test_result("test_setState", a_bIsSuccess);

	// 隣接セルに自分の状態を通知するテスト.
	a_bIsSuccess = test_sendState();
	print_test_result("test_sendState", a_bIsSuccess);

	// セルの誕生をテスト.
	a_bIsSuccess = test_cell_born();
	print_test_result("test_cell_born", a_bIsSuccess);

	// セルの生存をテスト その１.
	a_bIsSuccess = test_cell_survive1();
	print_test_result("test_cell_survive1", a_bIsSuccess);
	
	// セルの生存をテスト その２.
	a_bIsSuccess = test_cell_survive2();
	print_test_result("test_cell_survive2", a_bIsSuccess);

	// セルの過疎をテスト その１.
	a_bIsSuccess = test_cell_under_population1();
	print_test_result("test_cell_under_population1", a_bIsSuccess);

	// セルの過疎をテスト その２.
	a_bIsSuccess = test_cell_under_population2();
	print_test_result("test_cell_under_population2", a_bIsSuccess);

	// セルの過密をテスト その１.
	a_bIsSuccess = test_cell_over_population1();
	print_test_result("test_cell_over_population1", a_bIsSuccess);
	
	// セルの過密をテスト その２.
	a_bIsSuccess = test_cell_over_population2();
	print_test_result("test_cell_over_population2", a_bIsSuccess);

	return true;
}

int main()
{
	test_Cell();
	return 0;
}

