ascii-ttt
=========

This is a simple but effective implementation of the very popular board game 'Tic-Tac-Toe'
written in C. The graphics in it are all just ASCII characters. So it doesn't need any
special graphics libraries.

It stores scores in a binary file. So a score file of one computer may not be read properly
by another computer. So to run this program for the first time, make sure you have deleted
the existing `scores.b` file.

This game can be played in both single-player and double-player modes. For single-player
mode, there are three diffculty levels. In the hard difficulty level, we used the
*minimax* algorithm to make the computer unbeatable.


Requirements
------------

* Since it uses `windows.h` file, it only runs on Windows at the moment.
* The project was done in CodeBlocks IDE. So you need that IDE to open this project.


How to build
------------

Open `ttt.cbp` file with CodeBlocks, and build the project. Simple! :D

The executable file should be located inside the `bin` folder.
