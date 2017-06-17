Liber-Primus Hangman demo v0.1

Introduction: This is a working demo, with limited testing.  It’s all prototpye code ;-) 
The purpose of this app is to help find possible phrases that could be in the Liber Primus.

Requires: python 2 or 3 and PyQT4 or windows binary LP_Hangman.exe

Tested on linux and Windows 7

Get ngram data: can’t share on git too big a file compressed, please see
https://www.dropbox.com/s/36irgziw9o75b5z/ngram_data.7z?dl=0

Uncompress ngram_data.7z

Important: ngram_data files must be in this relative path  
<install>\ngram_data\4gram\<letters>\file.text
And
<install>\ngram_data\1gram/<letter>/file.text

It’s way too big: The way of separating n-gram data into many files makes access fast, but takes up much more space. This can probably be improved. But don’t we all have many spare GB?  

Run: LP_Hangman.py

Known Issues:  The Liber Primus sentences structure is basically correct, 
but without punctuation at the moment. Sentences with less than 4 words will 
result in undefined behaviour.  Yeah, we know there’s a lot of data, we’ll keep working on that.  

MORE HELP: http://webchat.freenode.net/?channels=cicadasolvers
