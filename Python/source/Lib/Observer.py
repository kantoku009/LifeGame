#! /usr/bin/python
# -*- coding: utf-8 -*-

# 参考URL.
# オブザーバーパターンの参考URL.
# http://mojix.org/2012/08/10/python-patterns
# https://github.com/faif/python-patterns/blob/master/observer.py 

_debug = False

# オブザーバークラス.
#	抽象クラス.
#	インスタンスは作成しないこと.
class Observer(object):
	def update(self, modifier=None):
		raise NotImplementedError

# 
class Subject(object):
	def __init__(self):
		self._observerList = []

	# Observerを登録する.
	def attach(self, observer):
		if not observer in self._observerList:
			self._observerList.append(observer)
	
	# Observerの登録解除する.
	def detach(self, observer):
		try:
			self._observerList.remove(observer)
		except ValueError:
			pass

	# Observerを持っているか否かを確認する.
	def hasObserver(self, observer):
		if observer in self._observerList: return True
		else: return False

	# Observerへ通知を更新.
	def notify(self, modifier=None):
		for observer in self._observerList:
			if observer != modifier:
				observer.update(self)



########################################################
# テスト関数とメイン関数.
#
#
#
#
########################################################
if __name__ == "__main__":
	# テスト用Subjectクラス.
	class Data(Subject):
		def __init__(self, name=''):
			Subject.__init__(self)
			self.name = name
			self._data = 0

		@property
		def data(self):
			return self._data

		@data.setter
		def data(self, value):
			self._data = value
			self.notify()

	# テスト用Observerクラス.
	class HexViewer(Observer):
		def update(self, subject):
			print('HexViewer: Subject %s has data 0x%x' % (subject.name, subject.data) )

	# テスト用observerクラス.
	class DecimalViewer(Observer):
		def update(self, subject):
			print('DecimalViewer: Subject %s has data %d' % (subject.name, subject.data) )

	# テスト実行関数.
	def test_observer():
		# オブジェクト生成.
		data1 = Data('Data 1')
		data2 = Data('Data 2')
		view1 = DecimalViewer()
		view2 = HexViewer()

		# オブザーバを登録.
		data1.attach(view1)
		data1.attach(view2)
		data2.attach(view2)
		data2.attach(view1)

		print("Has Observer view1 in data1?")
		print(data1.hasObserver(view1))

		print("Has Observer view2 in data1?")
		print(data1.hasObserver(view2))

		print("Has Observer view1 in data2?")
		print(data2.hasObserver(view1))

		print("Has Observer view2 in data2?")
		print(data2.hasObserver(view2))

		print("Setting Data 1 = 10")
		data1.data = 10

		print("Setting Data 2 = 15")
		data2.data = 15

		print("Setting Data 1 = 3")
		data1.data = 3

		print("Setting Data 2 = 5")
		data2.data = 5

		print("Detach HexViewer from data and data2.")
		data1.detach(view2)
		data2.detach(view2)

		print("Setting Data 1 = 10")
		data1.data = 10

		print("Setting Data 2 = 15")
		data2.data = 15

	###############################################
	# オブザーバーのテスト開始.
	#
	# 以下が出力されればOK.
	#
	# Has Observer view1 in data1?
	# True
	# Has Observer view2 in data1?
	# True
	# Has Observer view1 in data2?
	# True
	# Has Observer view2 in data2?
	# True
	# Setting Data 1 = 10
	# DecimalViewer: Subject Data 1 has data 10
	# HexViewer: Subject Data 1 has data 0xa
	# Setting Data 2 = 15
	# HexViewer: Subject Data 2 has data 0xf
	# DecimalViewer: Subject Data 2 has data 15
	# Setting Data 1 = 3
	# DecimalViewer: Subject Data 1 has data 3
	# HexViewer: Subject Data 1 has data 0x3
	# Setting Data 2 = 5
	# HexViewer: Subject Data 2 has data 0x5
	# DecimalViewer: Subject Data 2 has data 5
	# Detach HexViewer from data and data2.
	# Setting Data 1 = 10
	# DecimalViewer: Subject Data 1 has data 10
	# Setting Data 2 = 15
	# DecimalViewer: Subject Data 2 has data 15
	#
	###############################################
	test_observer()


