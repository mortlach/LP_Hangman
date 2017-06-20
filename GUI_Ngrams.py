#!/usr/bin/env python
# -*- coding: utf-8 -*-
from PyQt4.QtGui import *
from PyQt4.QtCore import *

class GUI_Ngrams(QMainWindow):
    def __init__(self,data):
        QMainWindow.__init__(self)
        self.data = data
        self.tableWidget = QTableWidget()
        self.tableWidget.setColumnCount(len(data[0]))
        self.tableWidget.setRowCount(len(data))
        for row in range(len(self.data)):
            for column in range(len(self.data[0])):
                self.tableWidget.setItem(row, column, QTableWidgetItem(self.data[row][column]))
        self.tableWidget.resizeColumnsToContents()
        self.tableWidget.resizeRowsToContents()
        self.setCentralWidget(self.tableWidget)
        self.resize(300, 600)
        self.settings = QSettings("GUI_Ngrams", "LP_Hangman")
        if not self.settings.value("geometry") == None:
            self.restoreGeometry(self.settings.value("geometry").toByteArray())
        if not self.settings.value("windowState") == None:
            self.restoreState(self.settings.value("windowState").toByteArray())

    def closeEvent(self, event):
        self.settings.setValue("geometry", self.saveGeometry())
        self.settings.setValue("windowState", self.saveState())
        QMainWindow.closeEvent(self, event)