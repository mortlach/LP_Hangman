#!/usr/bin/env python
# -*- coding: utf-8 -*-
from PyQt4.QtGui import *
from PyQt4.QtCore import *
import sys

class GUI_wordHints(QTableWidget):
    def __init__(self,data):
        QTableWidget.__init__(self)
        self.data = data
        self.tableWidget =  QTableWidget()
        self.setColumnCount(len(data[0]))
        self.setRowCount(len(data))
        for row in range(len(self.data)):
            for column in range(len(self.data[0])):
                self.setItem(row, column, QTableWidgetItem(self.data[row][column]))
        self.resizeColumnsToContents()
        self.resizeRowsToContents()