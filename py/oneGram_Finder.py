#!/usr/bin/env python
# -*- coding: utf-8 -*-
# class that can read single word files
# based on rune-count
# and crop the words based on user-specified first letters
import os.path

class oneGram_Finder(object):
    def __init__(self):
        self.dictWords   = None # use the dictWords   corpus
        self.masterWords = None # use the masterWords corpus
        self.wordData = None    # Current word list
        self.onegramFiles = {}  # map of file names and location
        self.get_file_Data()      # builds onegramFiles
        self.whichWords = None  # variable to specify which corpus

    # return words starting with letters and runecount number of runes
    def get_data(self,letters,runecount):
        self.wordData = None
        file = self.onegramFiles[ letters[0].lower() + '_' + str(runecount) ]
        if file is not None:
            print('loading file ',file)
            self.wordData = self.get_file_data(file,letters)
        else:
            print('File does not exist')
        if self.wordData is not None:
            print('got words')
        else:
            print('found no words')
        return self.wordData

    def get_file_Data(self):
        root = os.path.join('.', 'ngram_data', '1gram')  #MAGIC_STRING
        for dir_, _, files in os.walk(root):
            for fileName in files:
                relDir = os.path.relpath(dir_, root)
                relFile = os.path.join(relDir, fileName)
                self.onegramFiles[fileName[:-4]] = os.path.join(root, relFile)
                #print(self.onegramFiles[fileName[:-4]])


    def get_file_data(self,file,letters):
        array = []
        letterslen = len(letters)
        #print('letterslen = ',str(letterslen))
        #print('self.whichWords = ", self.whichWords)
        with open(file, 'r') as ins:
            for line in ins:
                #a1 = line.replace('\n', '')
                a = line.replace('\n', '').split()
                if a[-2] == self.dictWords: # meh
                    #print('a[-2] = ', a[-2], ' and  ', self.dictWords)
                    if self.masterWords == self.whichWords:
                        #print('self.masterWords == self.whichWords breaking')
                        break
                if a[0][0:letterslen] == letters:
                    #print('adding ', line.replace('\n', ''))
                    a.pop(-2)
                    array.append( a  )
        if len(array) == 0:
            return None
        else:
            return array


