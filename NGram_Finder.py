#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os
import os.path
from PyQt4 import QtCore
from ng_file_map import *

class NGram_Finder(QtCore.QObject):
    # not implemened, but maybe find n_grams in a new thread
    # we need some signals for that
    found_ngrams = QtCore.pyqtSignal()
    set_word_hints = QtCore.pyqtSignal()
    set_ngrams = QtCore.pyqtSignal()
    def __init__(self,parent=None):
        QtCore.QObject.__init__(self)
        self.dictWords   = None
        self.masterWords = None
        self.wordData = None
        self.onegramFiles = {}
        self.whichWords = None
        self.unique_data = []
        self.ngram_data  = []
        # which ngram to lookup
        self.ngram = None
        # word hints are letters at the start of each word to match
        self.word_hints = None
        self.file_line_data_length = 6 # MAGIC_NUMBER

    # not implemened, but maybe find n_grams in a new thread
    @QtCore.pyqtSlot()
    def get_ngram_data(self):
        self.get_Ngram_data(self.ngram, self.word_hints)
        self.found_ngrams.emit()

    def get_Ngram_data(self,ngram, word_hints):
        # get the files with the right ngram
        all_files = ng_file_map[ngram]
        final_files = []
        print('all_files = ',str(all_files))
        # cut the files to the ones that matche the 1st word of the n-gram
        if word_hints[0] == "*":# MAGIC_STRING
            final_files = all_files
        elif len(word_hints[0]) == 1:
            for file in all_files:
                if word_hints[0][0] == file[0]:
                    final_files.append(file)
        else:
            for file in all_files:
                if word_hints[0][0:2] == file[0:2]:
                    final_files.append(file)
        print('final_files = ',str(final_files))
        self.get_file_data(final_files,word_hints)

    def get_file_data(self,files,hints):
        # reset-local copies of words
        self.ngram_data = []
        self.unique_data = [[], [], [], []]
        for file in files:
            path_file = os.path.join('.', 'ngram_data', '4gram', file[0:2] , file )
            data = self.get_data(path_file,hints)
            if data is not None:
                for ngram in data:
                    self.ngram_data.append(ngram)
        for i in range(len( self.ngram_data[0]) - 1):
            words = list(set([t[i] for t in self.ngram_data]))
            for word in words:
                self.unique_data[i].append(word)


    def get_data(self, file, word_hints):
        array = []
        with open(file,'r') as ins:
            for line in ins:
                a = line.replace('\n', '').split() # MAGIC_STRING
                #print(a)
                if len(a) == self.file_line_data_length:# not sure this is needed, if ngram data is good
                    if a[-2] == self.dictWords:
                        if self.masterWords == self.whichWords:
                            #print('BREAKING!')
                            break
                    if self.ngram_matches_hints(a[0:4],word_hints[0:4]):  # MAGIC_NUMBER
                        a.pop(-2) # MAGIC_NUMBER
                        #print(appending ',str(a))
                        array.append(a)
        if len(array) == 0: # MAGIC_NUMBER
            print(file,' get_data is returning None')
            return None
        else:
            print(file,' get_data is returning data')
            return array

    def ngram_matches_hints(self,ngram,word_hints):
        r = True
        for gram, word_hint in zip(ngram, word_hints):
            if word_hint[0] != "*":  # MAGIC_STRING #
                if self.do_not_a_match(gram,word_hint):
                    r = False
                    break
        return r

    def do_not_a_match(self,word,test):
        if len(word) < len(test):
            return True
        if word[0:len(test)] != test:
            return True
        return False

