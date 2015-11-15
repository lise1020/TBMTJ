# TBMTJ

Introduction
============

TBMTJ is a software to simulate the properties of electron transport in a 
nanowire. Blablabla...



Building
========

There are two parts of this software. One is the core libraries to do 
simulation. And the other one is a gui application to generate input file 
easily. For building the core libraries, I use the cmake as the build system. 
For the gui application, I use Qt as gui application. Please see the following 
instruction to build.



Requirement
===========

Core libraries
--------------

1. Armadillo (http://arma.sourceforge.net)
   I use the armadillo linear algebra library to manipulate the matrix.
   
   
Gui application
---------------

1. Qt5 (http://www.qt.io)
   The version I use is **Qt5.5**. 



For building TB core libraries
==============================

1. cmake .
2. make



For building TB Gui application
===============================

1. qmake .
2. make

