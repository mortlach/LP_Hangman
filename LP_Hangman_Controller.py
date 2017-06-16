#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys, os
#get the magnet enums used to define magnet types and  PSU states
import LP_Data
from PyQt4 import QtGui, QtCore
from GUI_mainView import GUI_mainView
from oneGram_Finder import *
from NGram_Finder import *
from GUI_wordHints import *
from GUI_Ngrams import *

#from GUI_wordWidget import GUI_wordWidget

# this class handles everything
class LP_Hangman_Controller(object):
    def __init__(self,argv):
        # initilaize the VELA_CLARA_MagnetControl,
        # from this object we can get all flavours of magnet controller
        self.mainView = GUI_mainView()
        self.mainView.show()
        self.lengths = [3,4,6,9]
        self.sectionChoice = None
        self.sentenceChoice = None
        self.currentSentence = None
        self.currentNumWords = None
        self.dictWords   = 'D' #MAGIC_STRING
        self.masterWords = 'M' #MAGIC_STRING
        self.whichWords  = None
        # class that can find single words
        self.oneGram_Finder = oneGram_Finder()
        # the Ngram finder (currently N=4)
        self.NGram_Finder = NGram_Finder()
        # button to choose a sentence from the LP
        self.mainView.getSentence.clicked.connect(self.handle_getSentence)
        # Global Setting to use Master or normal Dictionary
        self.mainView.dictWords.toggled.connect(self.handle_whichDict)
        # intialise to dictionary words
        self.mainView.dictWords.setChecked(True)
        # button to find single words of given rune-count and initial letters
        self.mainView.showWordsList.clicked.connect(self.handle_show1Grams)
        # set the corpus names in oneGram_Finder
        self.oneGram_Finder.dictWords   = self.dictWords
        self.oneGram_Finder.masterWords = self.masterWords
        # list of 1gram words
        self.wordHints   = None
        self.NgramsHints = None
        # set the corpus names in NGram_Finder
        self.NGram_Finder.dictWords = self.dictWords
        self.NGram_Finder.masterWords = self.masterWords
        self.NGram_Finder.found_ngrams.connect(self.handle_found_ngrams)
        # button to find n-grams based on word-rune-counts and word hints
        self.mainView.findNGrams.clicked.connect(self.handle_findNgrams)
        # Setup the ngram_worker_thread and move the NGram_Finder into it.
        #self.worker_thread = QtCore.QThread()
        #self.NGram_Finder.moveToThread(self.worker_thread)



    def handle_findNgrams(self):
        if self.mainView.ngram_chosen:
            self.NgramsHints = None
            print('chosen ngram ',str(self.mainView.ngram_counts) )
            ngram_word_hints = self.mainView.get_word_hints()
            print( 'ngram_word_hints',str(ngram_word_hints))
            self.mainView.titleLabel.setText( 'searching for '
                             + str(self.mainView.ngram_counts)
                             + ' with hints '
                             +  str(ngram_word_hints) ) # MAGIC_STRING
            QtGui.qApp.processEvents()

            self.NGram_Finder.ngram = self.mainView.ngram_counts
            self.NGram_Finder.word_hints = ngram_word_hints

            self.NGram_Finder.get_ngram_data()

            #self.worker_thread.started.connect(self.NGram_Finder.get_ngram_data)
            #self.worker_thread.start()
            #self.NGram_Finder.get_Ngram_data(self.mainView.ngram_counts,ngram_word_hints)


        else:
            print('handle_findNgrams NO N_gram Selected!')
            self.mainView.titleLabel.setText('Patience is a Virtue')  # MAGIC_STRING

    def handle_found_ngrams(self):
        print('handle_found_ngrams recieved')
        self.NgramsHints = GUI_Ngrams(self.NGram_Finder.ngram_data)
        self.NgramsHints.show()
        self.mainView.set_combo_boxes(self.NGram_Finder.unique_data)
        self.mainView.titleLabel.setText('Patience is a Virtue') # MAGIC_STRING



    def handle_show1Grams(self):
        words = self.oneGram_Finder.get_data(
                    str(self.mainView.partWord.toPlainText()).lower(),
                    self.mainView.runeCount.value())
        self.wordHints = GUI_wordHints(words)
        self.wordHints.show()


    def handle_getSentence(self):
        self.mainView.ngram_count = []
        self.mainView.ngram_chosen = False

        self.currentSection = self.mainView.lpSection.value()
        self.currentSentence = self.mainView.lpSentence.value()
        print('getting section =  ',str(self.currentSection),' sentence = ',str(self.currentSentence))

        print('Length of LP_Data.lp_sentences ',str(len(LP_Data.lp_sentences)))

        for section in LP_Data.lp_sentences:
            print('Length of LP_Data.lp_sentences[section] = ',str(len(section)))

        # get runeword sentence and lengths()
        self.currentSentence = LP_Data.lp_sentences[self.currentSection][self.currentSentence]
        self.currentNumWords = len(self.currentSentence)
        print(self.currentSentence)
        print('currentSentence  =  ',str(len(self.currentSentence)))
        self.mainView.setImage(self.currentSection,self.currentSentence)
        self.mainView.setWordWidgets(self.currentSentence)


    def handle_whichDict(self):
        if self.mainView.dictWords.isChecked() == True:
            self.oneGram_Finder.whichWords = self.dictWords
            self.NGram_Finder.whichWords = self.dictWords
        else:
            self.oneGram_Finder.whichWords = self.masterWords
            self.NGram_Finder.whichWords = self.masterWords
        print('new self.oneGram_Finder.whichWords is ', self.oneGram_Finder.whichWords)
        print('new self.NGram_Finder.whichWords is ',  self.NGram_Finder.whichWords)