#! /usr/bin/python
# -*- coding: utf-8 -*-


from Lib.Observer import Observer
from Lib.Observer import Subject


####################################
# Cellオブジェクト クラス.
# 細胞（セル）１個をあらわすクラス.
####################################
class Cell(Subject, Observer):
	__DEBUG = True
	ALIVE = 1
	DEAD = 0

	def __init__(self):
		# スーパークラスSubjectの初期化.
		Subject.__init__(self)
		# スーパークラスObserverの初期化.
		Observer.__init__(self)
		#メンバー変数の初期化.
		self.clear()

	def __str__(self):
		return "Cell"

	def __repr__(self):
		return "<Cell>"

	#メンバー変数の初期化.
	def clear(self):
		# 自分自身の状態.
		#   0:死滅.
		#   1:生存.
		self._current_state = Cell.DEAD # 現在の状態.
		self._next_state = Cell.DEAD	# 次の状態.
		# 隣接するセルの生存数.
		self._neighbor_alive_num = 0
		#自分自身の状態が変化したか？
		self._isChanged = False

	
	# 現世代のセル状態のgetter/setter.
	@property
	def current_state(self):
		return self._current_state
	@current_state.setter
	def current_state(self, state):
		if 0 <= state <= 1: self._current_state = state
		else: pass


	# 次世代のセル状態getter/setter.
	@property
	def next_state(self):
		return self._next_state
	@next_state.setter
	def next_state(self, state):
		if 0 <= state <= 1: self._next_state = state
		else: pass


	# 隣接セルの生存数 getter/setter.
	@property
	def neighbor_alive_num(self):
		return self._neighbor_alive_num
	@neighbor_alive_num.setter
	def neighbor_alive_num(self, num):
		self._neighbor_alive_num = num

	#自分自身の状態が変化したか？ getter/setter
	@property
	def isChanged(self):
		return self._isChanged
	@isChanged.setter
	def isChanged(self, i_Flag):
		self._isChanged = i_Flag


	# 通知を受け取る.
	def update(self, modifier=None):
		self.receive_state(modifier)	# modifierはCell()オブジェクトを想定している.


	# 隣接セルの状態を受け取る.
	def receive_state(self, neighbor_cell):
		# 状態の範囲チェックし, 範囲内ならば状態数をカウントする.
		if (Cell.ALIVE == neighbor_cell._current_state): self.neighbor_alive_num += 1
		else: pass


	# 隣接セルに自分自身の状態を送る.
	def send_state(self):
		self.notify(self)

	# セルの状態を次世代へ更新する.
	def refresh(self):
		if(self._current_state!=self._next_state): self._isChanged = True
		else: self._isChanged = False

		# 状態を更新.
		self._current_state = self._next_state
		# 状態を通知する.
		self.send_state()


	# 隣接セルの状態から次世代の状態を決定する.
	def decide_state(self):
		# 状態を決定.
		if  ( True == self._is_born() ):				self._next_state = Cell.ALIVE   # 誕生.
		elif( True == self._is_survive() ):				self._next_state = Cell.ALIVE   # 生存.
		elif( True == self._is_under_population() ):	self._next_state = Cell.DEAD	# 過疎.
		elif( True == self._is_over_population() ):		self._next_state = Cell.DEAD	# 過密.
		else: pass

		# 生存数 カウントクリア.
		self._neighbor_alive_num = 0


	# 自分自身と隣接セルの状態から, 誕生か否かを判定する.
	# note:死んでいるセルに隣接する生きたセルがちょうど3つあれば,次の世代が誕生する.
	def _is_born(self):
		if( (Cell.DEAD==self._current_state) and (3==self._neighbor_alive_num) ): return True
		else: return False
	

	# 自分自身と隣接セルの状態から, 生存か否かを判定する.
	# note:生きているセルに隣接する生きたセルが2つか3つならば, 次の世代でも生存する.
	def _is_survive(self):
		if ( (Cell.ALIVE==self._current_state) and (2==self._neighbor_alive_num or 3==self._neighbor_alive_num)): return True
		else: return False


	# 自分自身と隣接セルの状態から, 過疎か否かを判定する.
	# note:生きているセルに隣接する生きたセルが1つ以下ならば, 過疎により死滅する.
	def _is_under_population(self):
		if( (Cell.ALIVE==self._current_state) and (1>=self._neighbor_alive_num) ): return True
		else: return False
	

	# 自分自身と隣接セルの状態から, 過密か否かを判定する.
	# note:生きているセルに隣接する生きたセルが4つ以上ならば, 過密により死滅する.
	def _is_over_population(self):
		if( (Cell.ALIVE==self._current_state) and (4<=self._neighbor_alive_num) ): return True
		else: return False

# セルの集合体.
class CellArray(object):
	__DEBUG = False

	# セルの集合を初期化.
	def __init__(self, i_Col, i_Row):
		self._col_max = i_Col
		self._row_max = i_Row

		self._cell_array = []
		for theRow in range(self._row_max):
			theTempList = []
			for theCol in range(self._col_max):
				theElement = Cell()
				theTempList.append(theElement)
			self._cell_array.append(theTempList)

		#隣接セルのリンクを作成.
		self.link_cell()


	@property
	def col_max(self): return self._col_max

	@property
	def row_max(self): return self._row_max

	# taget_cellの隣接セルをリンクさせる.
	# 　※ObserverをSubjectへ登録する.
	def set_neighbor(self, target_cell, col, row):
		# 横の隣接セル.（相対位置）.
		_rglCol = [
				-1, 0, 1,
				-1,	   1,
				-1, 0, 1, ]
		# 縦の隣接セル.（相対位置）.
		_rglRow = [
				-1, -1, -1,
				 0,	     0,
				 1,  1,  1, ]

		if(True==CellArray.__DEBUG): print("set_neighbor:(%d,%d)"%(col,row))	#debug用出力.
		for counter in range(8):
			# 隣接セル(縦)のインデックスを計算.
			neighbor_row = row + _rglRow[counter]
			# 隣接セル(横)のインデックスを計算.
			neighbor_col = col + _rglCol[counter]

			# インデックスの境界値をチェック.
			neighbor_row = self.check_region(neighbor_row, self.row_max)
			neighbor_col = self.check_region(neighbor_col, self.col_max)

			# 隣接セルを取得.
			neighbor_cell = self._cell_array[neighbor_row][neighbor_col]
			# 隣接セルを設定.
			neighbor_cell.attach(target_cell)
			if(True==CellArray.__DEBUG): print("  %s:(%d,%d)"%(neighbor_cell,neighbor_col,neighbor_row))	#debug用出力.
		if(True==CellArray.__DEBUG): print("")		#debug用出力.
	
	# 境界値をチェックする.
	def check_region(self, i_Value, i_Max):
		a_Value = i_Value
		if(0 > a_Value): a_Value = i_Max - 1
		elif(i_Max <= a_Value): a_Value = 0
		else: a_Value = i_Value
		return a_Value

	# 隣接するセルをリンクする.
	def link_cell(self):
		for row in range(self._row_max):
			for col in range(self._col_max):
				# リンクさせたいセルを取得.
				target_cell= self._cell_array[row][col]
				if(isinstance(target_cell, Cell)): 
					self.set_neighbor(target_cell, col, row)


	# セルを更新する.
	def refresh(self):
		# 次世代の状態を決定する.
		for line in self._cell_array:
			for cell in line:
				cell.decide_state()

		# 次世代の状態に遷移する.
		for line in self._cell_array:
			for cell in line:
				cell.refresh()

	# セルの状態を取得.
	def get_state(self, col, row):
		# 境界値をチェック.
		a_Col = self.check_region(col, self.col_max)
		a_Row = self.check_region(row, self.row_max)
		# セルの状態を取得.
		theCell = self._cell_array[a_Row][a_Col]
		theMyState = theCell.current_state
		return theMyState


	# セルの状態を設定.
	def set_state(self, col, row, state):
		# 境界値をチェック.
		a_Col = self.check_region(col, self.col_max)
		a_Row = self.check_region(row, self.row_max)
		# セルの状態を設定.
		self._cell_array[a_Row][a_Col].current_state = state
		self._cell_array[a_Row][a_Col].send_state()

	# セルを取得.
	def get_cell(self, col, row):
		# 境界値のチェック.
		a_Col = self.check_region(col, self.col_max)
		a_Row = self.check_region(row, self.row_max)
		# セルを取得.
		return self._cell_array[a_Row][a_Col]

	#全てのセルをクリア.
	def all_cell_clear(self):
		for theRow in range(self._row_max):
			for theCol in range(self._col_max):
				self._cell_array[theRow][theCol].clear()


	# CellArrayを表示.
	def disp(self):
		__DEBUG = False		# True:Cellの生存/死滅を表示. False:隣接Cellの生存数を表示.
		for y in range(self.row_max):
			for x in range(self.col_max):
				# Cellの状態を取得.
				_disp_char= self.get_state(x, y)
	
				if(True==__DEBUG):
					# 隣接Cellの生存数を取得.
					_disp_char = self._cell_array[y][x]._neighbor_alive_num
	
				# 数値以外だったら, 空文字とする.
				if( False == isinstance(_disp_char,int) ): _disp_char = ""
	
				# 文字表示. ※コンマを入れると改行しない.
				print(_disp_char),
	
			# y行目として改行する
			print("")
 

##################################################
# テスト関数とメイン関数.
#
##################################################
if __name__ == "__main__":

	#######################################
	# CellArray表示のテスト.
	#
	# 表示確認：
	# 　0:死滅.
	# 　1:生存.
	# 以下と表示されれば OK.
	# Test: display
	#	
	# 0 0 0  
	# 0 1 0  
	# 0 0 0  
	#
	######################################
	def test_cell_array_disp():
		cell_array = CellArray(5, 5)
		cell_array.link_cell()

		cell_array.set_state(2, 2, 1)
		print("Test: display")
		cell_array.disp()


	#######################################
	# Cell誕生のテスト.
	#
	# 確認事項：
	# 　真ん中のCellが0から1へ変化する事を確認.
	#
	# 条件:
	# 　死んでいるセルに隣接する生きたセルが
	# 　ちょうど3つあれば,次の世代が誕生する.
	#
	# 表示確認：
	# 　0:死滅.
	# 　1:生存.
	# 以下と表示されれば OK.
	# Test: Born
	# ---before---
	#	  
	#  1 0 1  
	#  0 0 0  
	#  0 1 0  
	#	  
	# ---after---
	#	  
	#  0 0 0  
	#  0 1 0  
	#  0 0 0  
	#	 
	########################################
	def test_cell_array_born():
		cell_array = CellArray(5, 5)
		cell_array.link_cell()

		cell_array.set_state(1, 1, 1)
		cell_array.set_state(2, 1, 0)
		cell_array.set_state(3, 1, 1)

		cell_array.set_state(1, 2, 0)
		cell_array.set_state(2, 2, 0)	# 自分自身のセルを(2,2)とし、死滅状態とする.
		cell_array.set_state(3, 2, 0)

		cell_array.set_state(1, 3, 0)
		cell_array.set_state(2, 3, 1)
		cell_array.set_state(3, 3, 0)

		print("Test: Born")
		print("---before---")
		cell_array.disp()
		cell_array.refresh()
		print("---after---")
		cell_array.disp()


	###################################
	# Cell生存のテスト.
	#
	# 確認事項：
	#　 真ん中のCellが1から変化しない事を確認.
	#
	# 条件:
	# 　生きているセルに隣接する生きたセルが2つか3つならば, 
	# 　次の世代でも生存する.
	#
	# 表示確認：
	# 　0:死滅.
	# 　1:生存.
	# 以下と表示されれば OK.
	# Test: survive
	# ---before---
	#	  
	#  0 0 1  
	#  0 1 0  
	#  1 0 0  
	#	  
	# ---after---
	#	  
	#  0 0 0  
	#  0 1 0  
	#  0 0 0  
	#	 
	###################################
	def test_cell_array_survive():
		cell_array = CellArray(5, 5)
		cell_array.link_cell()

		cell_array.set_state(1, 1, 0)
		cell_array.set_state(2, 1, 0)
		cell_array.set_state(3, 1, 1)

		cell_array.set_state(1, 2, 0)
		cell_array.set_state(2, 2, 1)	# 自分自身のセルを(2,2)とし、生存状態とする.
		cell_array.set_state(3, 2, 0)

		cell_array.set_state(1, 3, 1)
		cell_array.set_state(2, 3, 0)
		cell_array.set_state(3, 3, 0)

		print("Test: survive")
		print("---before---")
		cell_array.disp()
		cell_array.refresh()
		print("---after---")
		cell_array.disp()


	#########################################
	# Cell過疎のテスト.
	#
	# 確認事項：
	# 　真ん中のCellが0から1へ変化する事を確認.
	#
	# 条件:
	# 　生きているセルに隣接する生きたセルが1つ以下ならば, 
	# 　過疎により死滅する.
	#
	# 表示確認：
	# 　0:死滅.
	# 　1:生存.
	# 以下と表示されれば OK.
	# Test: under population
	# ---before---
	#	  
	#  0 0 1  
	#  0 1 0  
	#  0 0 0  
	#	  
	# ---after---
	#	  
	#  0 0 0  
	#  0 0 0  
	#  0 0 0  
	#	  
	######################################### 
	def test_cell_array_under_population():
		cell_array = CellArray(5, 5)
		cell_array.link_cell()

		cell_array.set_state(1, 1, 0)
		cell_array.set_state(2, 1, 0)
		cell_array.set_state(3, 1, 1)

		cell_array.set_state(1, 2, 0)
		cell_array.set_state(2, 2, 1)	# 自分自身のセルを(2,2)とし、生存状態とする.
		cell_array.set_state(3, 2, 0)

		cell_array.set_state(1, 3, 0)
		cell_array.set_state(2, 3, 0)
		cell_array.set_state(3, 3, 0)

		print("Test: under population")
		print("---before---")
		cell_array.disp()
		cell_array.refresh()
		print("---after---")
		cell_array.disp()


	########################################
	# Cell過密のテスト.
	#
	# 確認事項：
	# 　真ん中のCellが0から1へ変化する事を確認.
	#
	# 条件:
	# 　生きているセルに隣接する生きたセルが4つ以上ならば, 
	# 　過密により死滅する.
	#
	# 表示確認：
	# 　0:死滅.
	# 　1:生存.
	# 以下と表示されれば OK.
	# Test: over population
	# ---before---
	#	  
	#  0 1 0  
	#  1 1 1  
	#  0 1 0  
	#	  
	# ---after---
	#	  
	#  1 1 1  
	#  1 0 1  
	#  1 1 1  
	#  
	##########################################
	def test_cell_array_over_population():
		cell_array = CellArray(5, 5)
		cell_array.link_cell()

		# Cellの初期状態.
		cell_array.set_state(1, 1, 0)
		cell_array.set_state(2, 1, 1)
		cell_array.set_state(3, 1, 0)

		cell_array.set_state(1, 2, 1)
		cell_array.set_state(2, 2, 1)	# 自分自身のセルを(2,2)とし、生存状態とする.
		cell_array.set_state(3, 2, 1)

		cell_array.set_state(1, 3, 0)
		cell_array.set_state(2, 3, 1)
		cell_array.set_state(3, 3, 0)

		print("Test: over population")
		print("---before---")
		cell_array.disp()
		cell_array.refresh()
		print("---after---")
		cell_array.disp()


	def test_cell_array():
		# CellArray表示のテスト.
		test_cell_array_disp()

		# Cell誕生のテスト.
		test_cell_array_born()

		# Cell生存のテスト.
		test_cell_array_survive()

		# Cell過疎のテスト.
		test_cell_array_under_population()

		# Cell過密のテスト.
		test_cell_array_over_population()

	#メイン.
	test_cell_array()
