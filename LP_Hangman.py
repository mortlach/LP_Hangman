#!/usr/bin/env python
# -*- coding: utf-8 -*-
from PyQt4 import QtGui
import sys
import os
sys.path.append(os.path.join(sys.path[0],'GUI'))
sys.path.append(os.path.join(sys.path[0],'py'))
import LP_Hangman_Controller

# for testing delete pyc files
filelist = [ f for f in os.listdir(".") if f.endswith(".pyc") ]
for f in filelist:
    os.remove(f)

class LP_Hangman(QtGui.QApplication):
    def __init__(self,argv):
        QtGui.QWidget.__init__(self,argv)
        self.controller = LP_Hangman_Controller.LP_Hangman_Controller(argv)

if __name__ == '__main__':
    app = LP_Hangman(sys.argv)
    sys.exit(app.exec_())