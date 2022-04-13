#!/bin/bash
read -r -p "Run Task1? [Y/n] " task1
case $task1 in 
	[yY])
		cd res/
		rm *.txt
		echo "clean previous result"
		cd ..
		cd lexical/
   		g++ -std=c++11 -o run run.cpp convert.cpp lexer.cpp && ./run ../simulation/grammar.txt ../simulation/test.txt ../res
		echo "task1 completed!"
		;;
	[nN])
		echo "skip Task1"
		;;
	*)
		echo "skip Task1"
esac
read -r -p "Run Task2? [Y/n] " task1
case $task1 in 
	[yY])
		cd parser/
		g++ -std=c++11 -o parser parser.cpp && ./parser ../simulation/grammar1.txt
		echo "task2 completed!"
		;;
	[nN])
		read -p "Please enter any key to exit" exit
		exit 1
		;;
	*)
		read -p "Please enter any key to exit" exit
		exit 1
esac
#read -p $'Complete task!\x0aPlease enter any key to exit' exit
#		exit 1
