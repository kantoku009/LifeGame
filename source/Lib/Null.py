#! /usr/bin/python
# -*- coding: utf-8 -*-

#################################################################
# 参考URL.
#
# Nullオブジェクトパターンの参考URL.
# http://mojix.org/2012/08/10/python-patterns
# https://github.com/faif/python-patterns/blob/master/null.py
#
# Nullオブジェクトパターンについては以下を参考.
# http://www.nulab.co.jp/designPatterns/designPatterns4/designPatterns4-3.html#
#
# Python特殊メソッドの参考URL
# http://docs.python.jp/2/reference/datamodel.html#specialnames
#################################################################

# Nullオブジェクト クラス.
class Null(object):
	def __init__(self, *args, **kwargs):
		# 可変個の引数を受け取りに対応.
		# Ignore parameters.
		return None

	def __call__(self, *args, **kwargs):
		# 可変この引数を受け取りに対応.
		# Ignore method calls.
		return self

	def __getattr__(self, mname):
		# Ignore attribute requests.
		return self

	def __setattr__(self, name, value):
		# Ignore attribute setting.
		return self

	def __delattr__(self, name):
		# Ignore deleting attributes.
		return self

	def __repr__(self):
		# Return a string representation.
		return "<Null>"

	def __str__(self):
		# Convert to a string and return it.
		return "Null"


##################################################
# テスト関数とメイン関数.
#
##################################################
if __name__ == "__main__":

	#############################################
	# Nullオブジェクト テスト用関数.
	#
	#############################################

	# Nullオブジェクト生成 テスト.
	def _test_null_object_create():
		print("Test: Null object generate.")

		obj = Null()
		print("  obj=Null(): %s" % obj)

		obj = Null('value', param='value')
		print("  obj=Null('value, param='value'): %s" % obj)

	# Nullオブジェクト 属性変更 テスト
	def _test_null_object_attr():
		obj = Null()

		print("Test: Null object set attribute.")
		print("  (Does not act. Confirm that nothing is displayed.)")

		obj()

		obj('value')
		obj('value', param='value')

		obj.attr1
		obj.attr1.attr2

		obj.method1()
		obj.method1().method2()

		obj.method('value')
		obj.method(param='value')
		obj.method('value', param='value')
		obj.attr1.method1()
		obj.method1().attr1

		obj.attr1 = 'value'
		obj.attr1.attr2 = 'value'

		del obj.attr1
		del obj.attr1.attr2.attr3

	# Nullオブジェクト 文字列変換.
	def _test_null_object_string():
		obj = Null()

		print("Test: Null object representation and conversion to a string")

		if repr(obj) == '<Null>': print("  Null.__repr__():OK")
		else: print("  Null.__repr__():NG")

		if str(obj) == 'Null': print("  Null.__str__():OK")
		else: print("  Null.__str__():NG")

	# Nullオブジェクト テストコード.
	def test_null_object():
		# Nullオブジェクト生成 テスト.
		_test_null_object_create()

		# 属性の変更 テスト.
		_test_null_object_attr()

		# 文字列変換.
		_test_null_object_string()
	
	##################################################################
	# Nullオブジェクトのテスト開始.
	#
	# 以下が出力されればOK.
	#
	# Test: Null object generate.
	#   obj=Null(): Null
	#   obj=Null('value, param='value'): Null
	# Test: Null object set attribute.
	#   (Does not act. Confirm that nothing is displayed.)
	# Test: Null object representation and conversion to a string
	#   Null.__repr__():OK
	#   Null.__str__():OK
	#
	##################################################################
	test_null_object()
