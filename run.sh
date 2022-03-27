#!/bin/bash
read -r -p "Run Task1? [Y/n] " task1
case $task1 in 
	[yY])
		cd res/
		rm *.txt
		echo "clean previous result"
		cd ..
		cd lexical/
   		g++ -std=c++11 -o test test.cpp convert.cpp lexer.cpp && ./test
		echo "task1 completed!"
		;;
	[nN])
		read -p "Please enter any key to exit" exit
		exit 1
		;;
	*)
		read -p "Please enter any key to exit" exit
		exit 1
esac
read -r -p "Run Task2? [Y/n] " task1
case $task1 in 
	[yY])
		
		;;
	[nN])
		read -p "Please enter any key to exit" exit
		exit 1
		;;
	*)
		read -p "Please enter any key to exit" exit
		exit 1
esac
read -p $'Complete task2!\x0aPlease enter any key to exit' exit
		exit 1
