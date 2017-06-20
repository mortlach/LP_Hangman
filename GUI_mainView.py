#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sip
import sys
from Ui_mainView import Ui_mainView
from  GUI_wordWidget import GUI_wordWidget

if sys.version_info[0] < 3:
    sip.setapi('QString', 1)
else:
    sip.setapi('QString', 2)
    QString = str

# try:
#     from PyQt4.QtCore import QString
# except ImportError:
#     QString = str

from PyQt4 import QtCore, QtGui
try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    _fromUtf8 = lambda s: s

class GUI_mainView(QtGui.QMainWindow, Ui_mainView):
    #closing = QtCore.pyqtSignal()# custom close signal to send to controller
    def __init__(self):
        QtGui.QWidget.__init__(self)
        self.setupUi(self)
        # map of word widgets, keyed by their place in the senence
        self.wordWidgets = {}
        # do this better, based on raw LP data to be imported

        self.lpSentence.setMaximum( 23 )#MAGIC_NUMBER
        # GUI layout varibale
        self.maxWordsPerLine = 12       #MAGIC_NUMBER
        # varibale to group the wordWidget radiobuttons
        self.wordRadioButons = QtGui.QButtonGroup()
        # what is N
        self.NgramN = 4                 #MAGIC_NUMBER
        self.activeWord = None
        self.runeCount.setValue(3) # MAGIC_NUMBER
        # string giving runecounts for chosen ngram
        self.ngram_counts = ''
        # has any choice in n-grma been made yet
        self.ngram_chosen = False

    def delete_word_widgets(self):
        for key in self.wordWidgets:
            self.wordWidgetGrid.removeWidget(self.wordWidgets[key])
            sip.delete(self.wordWidgets[key])
            self.wordWidgets[key] = None
        self.wordWidgets = {}

    def setImage(self,currentSection,currentSentence):
        # need to get the right image, maybe have images for each sentences ?
        # with the runes highlighted in a differnet color?
        # getImage(sentence_number)
        self.qPixMap1 = QtGui.QPixmap('20.jpg').scaledToWidth(self.frame.frameGeometry().width())
        self.qPixMap2 = QtGui.QPixmap('21.jpg').scaledToWidth(self.frame.frameGeometry().width())
        self.lpImage1.setPixmap(self.qPixMap1)
        self.lpImage2.setPixmap(self.qPixMap2)

    def set_combo_boxes(self, words):
        for i in range(len(words)):
            self.wordWidgets[self.activeWord + i].comboBox.clear()
            self.wordWidgets[self.activeWord + i].comboBox.addItems(sorted(words[i]))

    def setWordWidgets(self,currentSentence):
        self.delete_word_widgets()
        wordCounter = 0
        row = 0
        column = 0
        # iterate word in sentence and create a wordWidget for each word
        for i in range(0,len(currentSentence)):
            self.wordWidgets[i] = GUI_wordWidget()
            # name is word number
            self.wordWidgets[i].name = i
            self.wordWidgets[i].runecount = len(currentSentence[i])
            # label runecount then runes
            lab2 = str(self.wordWidgets[i].runecount) + ' ' + "".join(currentSentence[i])

            if sys.version_info[0] < 3:
                label = QtCore.QString.fromUtf8(lab2)
            else:
                label = str(lab2)
            self.wordWidgets[i].runes.setText(label)
            self.wordWidgetGrid.addWidget( self.wordWidgets[i],row ,column)
            self.wordWidgets[i].show()
            # add the radio button
            self.wordRadioButons.addButton(self.wordWidgets[i].radioButton)
            self.wordWidgets[i].wordRadioSignal.connect(self.handle_areaRadio)
            wordCounter += 1
            column += 1
            if column == self.maxWordsPerLine:
                column = 0
                row += 1
            # deactivate radio buttons at sentencce end
            if i + self.NgramN  > len(currentSentence):
                self.wordWidgets[i].radioButton.setEnabled(False)

    # loop through active words and if they are checked
    # append text to word_hints and return
    def get_word_hints(self):
        print('get_word_hints getting word hints')
        word_hints = []
        for count in range(self.NgramN):
            if self.wordWidgets[self.activeWord + count ].isChecked:
                hint = str(self.wordWidgets[self.activeWord + count].textEdit.toPlainText())
                if len(hint) == 1:
                    if self.wordWidgets[self.activeWord + count ].runecount == 1:
                        hint += '_' # MAGIC_STRING
                if hint == '':
                    hint = '*' # MAGIC_STRING
                print(self.activeWord,count)
                print('Word Hint ',str(count),' = ',hint)
                word_hints.append(hint)
            else:
                word_hints.append( '*' ) # MAGIC_STRING
        print('Final Word hints are = ',str(word_hints))
        return word_hints



    def handle_areaRadio(self,i):
        self.ngram_chosen = True
        self.ngram_counts = ''
        for count in range(self.NgramN):
            self.ngram_counts += str(self.wordWidgets[i+count].runecount) + '_' # MAGIC_STRING
        self.ngram_counts = self.ngram_counts[:-1]
        self.activeWord = i
        print('Active word = ', str(self.activeWord ))

        for num in range(0,len(self.wordWidgets)):
            if self.activeWord <= num <= self.activeWord+self.NgramN-1:
                self.wordWidgets[num].activate()
                self.wordWidgets[num].isActive = True
            else:
                self.wordWidgets[num].deactivate()
                self.wordWidgets[num].isActive = False

