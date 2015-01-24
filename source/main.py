#! /usr/bin/python
# -*- coding: utf-8 -*-

import sys
import PyQt4.QtCore as QtCore
import PyQt4.QtGui as QtGui

from LifeGameModel.Cell import Cell
from LifeGameModel.Cell import CellArray
from LifeGameView.widget import Ui_Widget
from Lib.Observer import Observer

class ViewCell(QtGui.QTableWidgetItem, Observer):
	def __init__(self):
		QtGui.QTableWidgetItem.__init__(self)
		Observer.__init__(self)
	
	def update(self, modifier=None):
		self.receive_state(modifier)
	
	def receive_state(self, i_SelfCell):
		#セルの状態に変化が無かったら、何もせずリターン.
		if(False == i_SelfCell.isChanged): return

		theState = i_SelfCell.current_state
		if(Cell.ALIVE == theState): theSelect = True
		else: theSelect = False
		self.setSelected(theSelect)




class LifeGameViewWidget(QtGui.QMainWindow, Ui_Widget):
	INTERVAL = 200
	SIZE = 30

	def __init__(self, *args, **kw):
		QtGui.QMainWindow.__init__(self, *args, **kw)
		self.setupUi(self)

		self._CellArray = CellArray(self.SIZE, self.SIZE)
		self.set_Geometry_size(self.SIZE, self.SIZE)

		#ダブクリックで編集しないようにする.
		self.tableWidget.setEditTriggers(QtGui.QAbstractItemView.NoEditTriggers)

		#self.setFixedSize(370, 400)

		#タイマーの設定.
		self._interval = self.INTERVAL
		self._timer = QtCore.QTimer(parent=self)
		self._timer.setInterval(self._interval)
		#タイマーと動作を繋げる.
		self._timer.timeout.connect(self.do_loop)

		#ボタンと動作を繋げる.
		self.start_pushButton.clicked.connect(self.start_action)
		self.pause_pushButton.clicked.connect(self.pause_action)
		self.once_pushButton.clicked.connect(self.once_action)

	def set_Geometry_size(self, i_Row, i_Col):
		self.tableWidget.setRowCount(i_Row)
		self.tableWidget.setColumnCount(i_Col)

		Hsize = self.tableWidget.horizontalHeader().defaultSectionSize()
		Vsize = self.tableWidget.verticalHeader().defaultSectionSize()
		self.tableWidget.setGeometry(QtCore.QRect(20, 50, (i_Row+2)*Vsize, (i_Col+2)*Hsize))

		for theRow in range(i_Row):
			for theCol in range(i_Col):
				theItem = ViewCell()
				self.tableWidget.setItem(theRow, theCol, theItem)
				theCell = self._CellArray.get_cell(theCol, theRow)
				theCell.attach(theItem)


	#全ての表示用セルの状態を更新.
	#どこで使用する？
	def updateAll_view_cell(self):
		theRowMax = self._CellArray.row_max
		theColMax = self._CellArray.col_max
		for theColIndex in range(theColMax):
			for theRowIndex in range(theRowMax):
				self.set_view_cell(theRowIndex, theColIndex)

	#表示用セルの更新.
	#どこで使用する？
	def set_view_cell(self, i_Row, i_Col):
		theState = self._CellArray.get_state(i_Col, i_Row)
		if(Cell.ALIVE == theState): theCommand = QtGui.QItemSelectionModel.Select
		else: theCommand = QtGui.QItemSelectionModel.Deselect
		self.tableWidget.setCurrentCell(i_Row, i_Col, theCommand)

	#全てのモデル用セルの状態を更新.
	def updateAll_model_cell(self):
		theRowMax = self._CellArray.row_max
		theColMax = self._CellArray.col_max
		for theColIndex in range(theColMax):
			for theRowIndex in range(theRowMax):
				self.set_model_cell(theRowIndex, theColIndex)

	#モデル用セルの設定.
	def set_model_cell(self, i_Row, i_Col):
		theItem = self.tableWidget.item(i_Row, i_Col)
		theFlags = theItem.isSelected()
		if(True == theFlags): theState = Cell.ALIVE
		else: theState = Cell.DEAD
		self._CellArray.set_state(i_Col, i_Row, theState)


	def do_loop(self):
		self._CellArray.refresh()
		
	def start_action(self):
		#表示用セルを選択不可に設定.
		self.tableWidget.setSelectionMode(QtGui.QAbstractItemView.NoSelection)
		#モデル用セルを全てクリアする.
		self._CellArray.all_cell_clear()
		#モデル用セルを設定.(表示用セルの状態を設定する)
		self.updateAll_model_cell()
		#更新用タイマースタート.
		self._timer.start()

	def pause_action(self):
		#表示用セルを選択可に設定.
		self.tableWidget.setSelectionMode(QtGui.QAbstractItemView.MultiSelection)
		#更新用タイマーストップ.
		self._timer.stop()

	def once_action(self):
		#表示用セルを選択可に設定.
		self.tableWidget.setSelectionMode(QtGui.QAbstractItemView.MultiSelection)
		#更新用タイマーストップ.
		self._timer.stop()

		#モデル用セルを全てクリアする.
		self._CellArray.all_cell_clear()
		#モデル用セルを設定.(表示用セルの状態を設定する)
		self.updateAll_model_cell()
		self._CellArray.refresh()
	


def main():
	app = QtGui.QApplication(sys.argv)

	panel = LifeGameViewWidget()

	main_window = QtGui.QMainWindow()
	main_window.setWindowTitle("LifeGame")
	main_window.setCentralWidget(panel)
	main_window.show()

	app.exec_()

if __name__ == '__main__':
	main()

