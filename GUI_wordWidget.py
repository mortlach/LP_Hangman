#!/usr/bin/env python
# -*- coding: utf-8 -*-
from PyQt4 import QtGui, QtCore
from Ui_wordWidget import Ui_wordWidget

class GUI_wordWidget(QtGui.QMainWindow, Ui_wordWidget):
    wordRadioSignal = QtCore.pyqtSignal(int)
    def __init__(self):
        QtGui.QWidget.__init__(self)
        self.setupUi(self)
        self.name = None
        self.radioButton.toggled.connect(lambda: self.handle_areaRadio(self.radioButton))
        self.checkBox.toggled.connect(lambda: self.handle_checkBox(self.checkBox))
        self.runecount = 0
        self.isActive = False
        self.isChecked = False
        self.comboBox.activated.connect(self.update_textBox)

    def update_textBox(self):
        print('update_textBox')
        self.textEdit.setPlainText(str(self.comboBox.currentText()))

    def handle_areaRadio(self,r):
        if r.isChecked() == True:
            self.wordRadioSignal.emit(self.name)

    def handle_checkBox(self,r):
        self.isChecked = r.isChecked()
        print('handle_checkBox')

    def activate(self):
        #self.radioButton.setEnabled(True)
        self.checkBox.setEnabled(True)
        self.comboBox.setEnabled(True)

    def deactivate(self):
        #self.radioButton.setEnabled(False)
        self.checkBox.setEnabled(False)
        self.comboBox.setEnabled(False)