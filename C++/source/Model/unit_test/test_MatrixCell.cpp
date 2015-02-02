/*************************************
 * MatrixCellクラスのユニットテスト
 *************************************/

#include <iostream>
#include <string>
#include <sstream>

#include "../Cell.h"
#include "../MatrixCell.h"

using namespace std;

static int gDEBUG = false;

bool print_debug_result(const char* i_pMessage, string i_pResult)
{
	cout << i_pMessage << endl;
	cout << i_pResult;
	return true;
}

bool test_checkResult(string i_strRightAnswer, string i_strCheck)
{
	bool a_bIsResult = i_strRightAnswer.compare(i_strCheck);
	return (0==a_bIsResult);
}

void print_test_result(const char* i_pMessage, bool i_bIsSuccess)
{
	cout << i_pMessage << ": ";
	if(i_bIsSuccess) cout << "OK";
	else cout << "NG";
	cout << endl;
}

// CellMatrixの生成のテスト.
bool test_matrix_cell_generate()
{
	// 期待する結果の文字列.（結果こうなれば正解）.
	string a_strRightAnswer("00000\n00000\n00000\n00000\n00000\n");
	
	// MatrixCellを生成.
	MatrixCell a_cMatrixCell(5L, 5L);

	// 結果を取得.
	string a_strResult = a_cMatrixCell.dispAllCellState();

	// 「期待する結果」と「結果」が同じならば, OK.
	bool a_bIsSuccess = test_checkResult(a_strRightAnswer, a_cMatrixCell.dispAllCellState());
	return a_bIsSuccess;
}

// セルの状態を設定のテスト.
bool test_matrix_cell_setState()
{
	// 期待する結果の文字列.（結果こうなれば正解）.
	string a_strRightAnswer("00000\n00000\n00100\n00000\n00000\n");
	
	// MatrixCellを生成.
	MatrixCell a_cMatrixCell(5L, 5L);

	// (2,2)のセルを"生"にする.
	a_cMatrixCell.setCellState(2L, 2L, CellAttribute::ALIVE);

	// セルの状態を表示.
	if(gDEBUG) print_debug_result("test_matrix_cell_setState: ", a_cMatrixCell.dispAllCellState());

	// 結果を取得.
	string a_strResult = a_cMatrixCell.dispAllCellState();

	// 「期待する結果」と「結果」が同じならば, OK.
	bool a_bIsSuccess = test_checkResult(a_strRightAnswer, a_cMatrixCell.dispAllCellState());
	return a_bIsSuccess;
}

// セルの誕生をテスト.
bool test_cell_born()
{
	// 期待する結果の文字列.（結果がこうなれば正解）.
	string a_strRightAnswer("00000\n00000\n00100\n00000\n00000\n");

	// MatrixCellを生成.
	MatrixCell a_cMatrixCell(5L, 5L);

	// テスト用にセルの状態を設定.
	a_cMatrixCell.setCellState(1, 1, CellAttribute::ALIVE);
	a_cMatrixCell.setCellState(3, 1, CellAttribute::ALIVE);
	a_cMatrixCell.setCellState(2, 3, CellAttribute::ALIVE);

	// 更新前のセルの状態を表示.
	if(gDEBUG)	print_debug_result("--- test_cell_born: before ---", a_cMatrixCell.dispAllCellState());

	// セルの状態を更新.
	a_cMatrixCell.refreshCell();

	// 更新後のセルの状態を表示.
	if(gDEBUG) print_debug_result("--- test_cell_born: after ---", a_cMatrixCell.dispAllCellState());

	// 「期待する結果」と「結果」が同じならば, OK
	bool a_bIsSuccess = test_checkResult(a_strRightAnswer, a_cMatrixCell.dispAllCellState());
	return a_bIsSuccess;
}

// セルの生存をテスト.
bool test_cell_survive()
{
	// 期待する結果の文字列.（結果がこうなれば正解）.
	string a_strRightAnswer("00000\n00000\n00100\n00000\n00000\n");

	// MatrixCellを生成.
	MatrixCell a_cMatrixCell(5L, 5L);

	// テスト用にセルの状態を設定.
	a_cMatrixCell.setCellState(3, 1, CellAttribute::ALIVE);
	a_cMatrixCell.setCellState(2, 2, CellAttribute::ALIVE);
	a_cMatrixCell.setCellState(1, 3, CellAttribute::ALIVE);

	//// 更新前のセルの状態を表示.
	if(gDEBUG) print_debug_result("--- test_cell_survive: before ---", a_cMatrixCell.dispAllCellState());

	// セルの状態を更新.
	a_cMatrixCell.refreshCell();

	//// 更新後のセルの状態を表示.
	if(gDEBUG) print_debug_result("--- test_cell_survive: after ---", a_cMatrixCell.dispAllCellState());

	// 「期待する結果」と「結果」が同じならば, OK
	bool a_bIsSuccess = test_checkResult(a_strRightAnswer, a_cMatrixCell.dispAllCellState());
	return a_bIsSuccess;
}

// セルの過疎をテスト.
bool test_cell_under_population()
{
	// 期待する結果の文字列.（結果がこうなれば正解）.
	string a_strRightAnswer("00000\n00000\n00000\n00000\n00000\n");

	// MatrixCellを生成.
	MatrixCell a_cMatrixCell(5L, 5L);

	// テスト用にセルの状態を設定.
	a_cMatrixCell.setCellState(3, 1, CellAttribute::ALIVE);
	a_cMatrixCell.setCellState(2, 2, CellAttribute::ALIVE);

	//// 更新前のセルの状態を表示.
	if(gDEBUG) print_debug_result("--- test_cell_under_population: before ---", a_cMatrixCell.dispAllCellState());

	// セルの状態を更新.
	a_cMatrixCell.refreshCell();

	//// 更新後のセルの状態を表示.
	if(gDEBUG) print_debug_result("--- test_cell_under_population: after ---", a_cMatrixCell.dispAllCellState());

	// 「期待する結果」と「結果」が同じならば, OK
	bool a_bIsSuccess = test_checkResult(a_strRightAnswer, a_cMatrixCell.dispAllCellState());
	return a_bIsSuccess;
}

// セルの過密をテスト.
bool test_cell_over_population()
{
	// 期待する結果の文字列.（結果がこうなれば正解）.
	string a_strRightAnswer("00000\n01110\n01010\n01110\n00000\n");

	// MatrixCellを生成.
	MatrixCell a_cMatrixCell(5L, 5L);

	// テスト用にセルの状態を設定.
	a_cMatrixCell.setCellState(2, 1, CellAttribute::ALIVE);
	a_cMatrixCell.setCellState(1, 2, CellAttribute::ALIVE);
	a_cMatrixCell.setCellState(2, 2, CellAttribute::ALIVE);
	a_cMatrixCell.setCellState(3, 2, CellAttribute::ALIVE);
	a_cMatrixCell.setCellState(2, 3, CellAttribute::ALIVE);

	//// 更新前のセルの状態を表示.
	if(gDEBUG) print_debug_result("--- test_cell_under_population: before ---", a_cMatrixCell.dispAllCellState());

	// セルの状態を更新.
	a_cMatrixCell.refreshCell();

	//// 更新後のセルの状態を表示.
	if(gDEBUG) print_debug_result("--- test_cell_under_population: after ---", a_cMatrixCell.dispAllCellState());

	// 「期待する結果」と「結果」が同じならば, OK
	bool a_bIsSuccess = test_checkResult(a_strRightAnswer, a_cMatrixCell.dispAllCellState());
	return a_bIsSuccess;
}

bool test_Matrix_Cell()
{
	bool a_bIsSuccess = false;

	// CellMatrixの生成のテスト.
	a_bIsSuccess = test_matrix_cell_generate();
	print_test_result("test_matrix_cell_generate", a_bIsSuccess);

	// セルの状態を設定のテスト.
	a_bIsSuccess = test_matrix_cell_setState();
	print_test_result("test_matrix_cell_setState", a_bIsSuccess);

	// セルの誕生をテスト.
	a_bIsSuccess = test_cell_born();
	print_test_result("test_cell_born", a_bIsSuccess);

	// セルの生存をテスト.
	a_bIsSuccess = test_cell_survive();
	print_test_result("test_cell_survive", a_bIsSuccess);

	// セルの過疎をテスト.
	a_bIsSuccess = test_cell_under_population();
	print_test_result("test_cell_under_population", a_bIsSuccess);

	// セルの過密をテスト.
	a_bIsSuccess = test_cell_over_population();
	print_test_result("test_cell_over_population", a_bIsSuccess);

	return true;
}

int main()
{
	test_Matrix_Cell();
	return 0;
}

