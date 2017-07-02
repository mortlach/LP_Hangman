# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'Ui_wordWidget.ui'
#
# Created by: PyQt4 UI code generator 4.11.4
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

class Ui_wordWidget(object):
    def setupUi(self, wordWidget):
        wordWidget.setObjectName(_fromUtf8("wordWidget"))
        wordWidget.resize(122, 125)
        wordWidget.setMinimumSize(QtCore.QSize(110, 125))
        self.layoutWidget = QtGui.QWidget(wordWidget)
        self.layoutWidget.setGeometry(QtCore.QRect(0, 0, 111, 131))
        self.layoutWidget.setObjectName(_fromUtf8("layoutWidget"))
        self.verticalLayout = QtGui.QVBoxLayout(self.layoutWidget)
        self.verticalLayout.setSpacing(3)
        self.verticalLayout.setObjectName(_fromUtf8("verticalLayout"))
        self.runes = QtGui.QLabel(self.layoutWidget)
        self.runes.setMinimumSize(QtCore.QSize(100, 20))
        self.runes.setMaximumSize(QtCore.QSize(100, 20))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.runes.setFont(font)
        self.runes.setObjectName(_fromUtf8("runes"))
        self.verticalLayout.addWidget(self.runes)
        self.radioButton = QtGui.QRadioButton(self.layoutWidget)
        self.radioButton.setMinimumSize(QtCore.QSize(100, 20))
        self.radioButton.setMaximumSize(QtCore.QSize(100, 20))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.radioButton.setFont(font)
        self.radioButton.setObjectName(_fromUtf8("radioButton"))
        self.verticalLayout.addWidget(self.radioButton)
        self.checkBox = QtGui.QCheckBox(self.layoutWidget)
        self.checkBox.setMinimumSize(QtCore.QSize(100, 20))
        self.checkBox.setMaximumSize(QtCore.QSize(100, 20))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.checkBox.setFont(font)
        self.checkBox.setObjectName(_fromUtf8("checkBox"))
        self.verticalLayout.addWidget(self.checkBox)
        self.textEdit = QtGui.QTextEdit(self.layoutWidget)
        self.textEdit.setMinimumSize(QtCore.QSize(100, 20))
        self.textEdit.setMaximumSize(QtCore.QSize(100, 20))
        font = QtGui.QFont()
        font.setPointSize(8)
        self.textEdit.setFont(font)
        self.textEdit.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
        self.textEdit.setHorizontalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
        self.textEdit.setObjectName(_fromUtf8("textEdit"))
        self.verticalLayout.addWidget(self.textEdit)
        self.comboBox = QtGui.QComboBox(self.layoutWidget)
        self.comboBox.setMinimumSize(QtCore.QSize(100, 20))
        self.comboBox.setMaximumSize(QtCore.QSize(100, 20))
        font = QtGui.QFont()
        font.setPointSize(8)
        self.comboBox.setFont(font)
        self.comboBox.setObjectName(_fromUtf8("comboBox"))
        self.verticalLayout.addWidget(self.comboBox)

        self.retranslateUi(wordWidget)
        QtCore.QMetaObject.connectSlotsByName(wordWidget)

    def retranslateUi(self, wordWidget):
        wordWidget.setWindowTitle(_translate("wordWidget", "Form", None))
        self.runes.setText(_translate("wordWidget", "TextLabel", None))
        self.radioButton.setText(_translate("wordWidget", "NGram Start", None))
        self.checkBox.setText(_translate("wordWidget", "Use as hint", None))

