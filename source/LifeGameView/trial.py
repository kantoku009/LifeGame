#! /usr/bin/python
# -*- coding: utf-8 -*-

import sys
import PyQt4.QtCore as QtCore
import PyQt4.QtGui as QtGui

from widget import Ui_Widget

class LifeGameViewWidget(QtGui.QMainWindow, Ui_Widget):

	def __init__(self, *args, **kw):
		QtGui.QMainWindow.__init__(self, *args, **kw)
		self.setupUi(self)

		for theRow in range(15):
			for theCol in range(15):
				if(theRow == theCol):
					#QTableWidgetのセルを選択.
					self.tableWidget.setCurrentCell(theRow, theCol)




def main():
	app = QtGui.QApplication(sys.argv)

	panel = LifeGameViewWidget()
	panel.setFixedSize(450, 450)

	main_window = QtGui.QMainWindow()
	main_window.setWindowTitle("LifeGame")
	main_window.setCentralWidget(panel)
	main_window.show()

	app.exec_()

if __name__ == '__main__':
	main()

