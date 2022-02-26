#include <iostream>
#include "header.h"
using namespace std;

void NFA::initialize(){
    NFA_Node head;
    NFA_Node tail;

    head.index = 0;
    tail.index = 1;

    this->vec.push_back(head);
    this->vec.push_back(tail);
}

void NFA::addNode(int curIndex, int nextIndex, chType action){
    NFA_Node newNode;
    newNode.index = nextIndex;
    this->vec[curIndex].nextNode.push_back(nextIndex);
    this->vec[curIndex].action.push_back(action);
    this->vec.insert(this->vec.begin(), newNode);
}

void NFA::addNode(int curIndex, chType action){
    this->vec[curIndex].nextNode.push_back(1);
    this->vec[curIndex].action.push_back(action);
}

int NFA::transformState(int curIndex, char ch){
    NFA_Node curNode = this->vec[curIndex];
    int index = 0;
    for(vector<chType>::iterator iter = curNode.action.begin(); iter != curNode.action.end();++iter, ++index){
        chType curType = lexer::chtypeDetect(ch);
        if(curType == (*iter)){
            return curNode.nextNode[index];
        }
    }
    return -1;
}