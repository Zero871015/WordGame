# WordGame

## Description

A popular word game involves finding words from a grid of randomly generated
letters. Words must be at least three letters long and formed from adjoining letters. Letters
may not be reused and it is valid to move across diagonals. As an example, consider the 4x4 grid
of letters below.


A| B| C| D
-|--|--|--
E| F| G| H
I| J| K| L
M| N| O| P


The word "FAB" is valid (letters in the upper left corner) and the word "KNIFE" is valid. The
word "BABE" is not valid because the "B" may not be reused. The word "MINE" is not valid
because the "E" is not adjacent to the "N".


Write a program that uses a 4x4 two dimensional array to represent the game board. The
program should read the words from the text file words.txt and then use a recursion algorithm
to determine if the word may be formed from the letters on the game board. The program
should output all valid words from the file that are on the game board.

## Note
* Please put "words.txt" on the folder which contain the execution file(.exe).
* One code use set to recursive find the words, another use trie sort data.

## Info
* E-mail: zero871015@gmail.com
* Date:05/15/2018
