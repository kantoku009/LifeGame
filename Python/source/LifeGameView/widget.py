# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'widget.ui'
#
# Created: Thu Sep 25 23:05:08 2014
#      by: PyQt4 UI code generator 4.11.1
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_Widget(object):
    def setupUi(self, Widget):
        Widget.setObjectName(_fromUtf8("Widget"))
        Widget.resize(370, 400)
        Widget.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.gridLayoutWidget = QtGui.QWidget(Widget)
        self.gridLayoutWidget.setGeometry(QtCore.QRect(20, 10, 321, 32))
        self.gridLayoutWidget.setObjectName(_fromUtf8("gridLayoutWidget"))
        self.gridLayout = QtGui.QGridLayout(self.gridLayoutWidget)
        self.gridLayout.setMargin(0)
        self.gridLayout.setObjectName(_fromUtf8("gridLayout"))
        self.start_pushButton = QtGui.QPushButton(self.gridLayoutWidget)
        self.start_pushButton.setObjectName(_fromUtf8("start_pushButton"))
        self.gridLayout.addWidget(self.start_pushButton, 0, 0, 1, 1)
        self.pause_pushButton = QtGui.QPushButton(self.gridLayoutWidget)
        self.pause_pushButton.setObjectName(_fromUtf8("pause_pushButton"))
        self.gridLayout.addWidget(self.pause_pushButton, 0, 1, 1, 1)
        self.once_pushButton = QtGui.QPushButton(self.gridLayoutWidget)
        self.once_pushButton.setObjectName(_fromUtf8("once_pushButton"))
        self.gridLayout.addWidget(self.once_pushButton, 0, 2, 1, 1)
        self.tableWidget = QtGui.QTableWidget(Widget)
        self.tableWidget.setGeometry(QtCore.QRect(20, 50, 328, 326))
        self.tableWidget.setFrameShape(QtGui.QFrame.StyledPanel)
        self.tableWidget.setFrameShadow(QtGui.QFrame.Sunken)
        self.tableWidget.setLineWidth(1)
        self.tableWidget.setEditTriggers(QtGui.QAbstractItemView.AnyKeyPressed|QtGui.QAbstractItemView.DoubleClicked|QtGui.QAbstractItemView.SelectedClicked)
        self.tableWidget.setSelectionMode(QtGui.QAbstractItemView.MultiSelection)
        self.tableWidget.setRowCount(15)
        self.tableWidget.setColumnCount(15)
        self.tableWidget.setObjectName(_fromUtf8("tableWidget"))
        self.tableWidget.horizontalHeader().setVisible(True)
        self.tableWidget.horizontalHeader().setDefaultSectionSize(20)
        self.tableWidget.horizontalHeader().setHighlightSections(True)
        self.tableWidget.verticalHeader().setVisible(True)
        self.tableWidget.verticalHeader().setDefaultSectionSize(20)

        self.retranslateUi(Widget)
        QtCore.QMetaObject.connectSlotsByName(Widget)

    def retranslateUi(self, Widget):
        Widget.setWindowTitle(_translate("Widget", "Widget", None))
        self.start_pushButton.setText(_translate("Widget", "Start", None))
        self.pause_pushButton.setText(_translate("Widget", "Pause", None))
        self.once_pushButton.setText(_translate("Widget", "Once", None))

