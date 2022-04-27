#!/bin/bash
export COMPILERPATH=$(pwd)
read -r -p "Run Task1? [Y/n] " task1
case $task1 in 
	[yY])
		cd $COMPILERPATH
		cd res/lexical
		rm *
		echo -e "clean previous result\n "
		cd $COMPILERPATH/lexical
   		g++ -std=c++11 -o run run.cpp convert.cpp lexer.cpp && ./run ../simulation/grammar.txt ../simulation/test.txt ../res
		echo -e "task1 completed!\n "
		;;
	[nN])
		echo -e "skip Task1\n "
		;;
	*)
		echo -e "skip Task1\n "
esac
read -r -p "Run Task2? [Y/n] " task1
case $task1 in 
	[yY])
		cd $COMPILERPATH
		cd res/parser
		rm -r *
		echo -e "clean previous result\n "
		cd $COMPILERPATH/parser
		g++ -std=c++11 -o parser parser.cpp && ./parser ../simulation/grammar1.txt ../res ../res/lexical/token.txt
		python3 dumpTable.py
		python3 dumpAnalysis.py
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
