# RFID-project

Project purpose: Automatic inventory count at the libraries.

Short description about the technology and how its made (7 minutes) : https://www.youtube.com/watch?v=JcE0S0DQXEs&ab_channel=%D7%94%D7%A4%D7%A7%D7%95%D7%9C%D7%98%D7%94%D7%9C%D7%94%D7%A0%D7%93%D7%A1%D7%AA%D7%97%D7%A9%D7%9E%D7%9C%D7%95%D7%9E%D7%97%D7%A9%D7%91%D7%99%D7%9D%D7%91%D7%98%D7%9B%D7%A0%D7%99%D7%95%D7%9FECETECHNION


The files i added:

-c++ server:

In here we connect to the serial port which recieves data wirelessly, operating the machine that counts the books, create database of books that have been
read and making statistical search on books location.

-arduino files: 

one file is for the pc transiver which we can find on the countrfit and the second is the motor controller which is on the shelve.

-antenna files:

gerber files of 2 antennas that we created for the project

-ui

ui in pyqt5 which displays the location of the book on the shelve
