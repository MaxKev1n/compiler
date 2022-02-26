#include "header.h"

using namespace std;

void NFA::initialize(){
    NFA_Node head;
    NFA_Node tail;

    head.index = 0;
    tail.index = 1;

    this->vec.push_back(head);
    this->vec.push_back(tail);
    this->NFA_set.insert(0);
    this->NFA_set.insert(1);
}

void NFA::addNode(int curIndex, int nextIndex, chType action){
    NFA_Node newNode;
    newNode.index = nextIndex;

    bool nodeIsNew = true;
    for(int i = 0;i < this->vec[curIndex].nextNode.size();i++){
        if((this->vec[curIndex].nextNode[i] == newNode.index) && (this->vec[curIndex].action[i] == action)){
            nodeIsNew = false;
        }
    }
    if(nodeIsNew){
        this->vec[curIndex].nextNode.push_back(nextIndex);
        this->vec[curIndex].action.push_back(action);
    }

    if(this->NFA_set.find(nextIndex) == this->NFA_set.end()){
        this->NFA_set.insert(nextIndex);
        this->vec.insert(this->vec.begin() + nextIndex, newNode);
    }
}

void NFA::addNode(int curIndex, chType action){
    bool nodeIsNew = true;
    for(int i = 0;i < this->vec[curIndex].nextNode.size();i++){
        if((this->vec[curIndex].nextNode[i] == 1) && (this->vec[curIndex].action[i] == action)){
            nodeIsNew = false;
        }
    }
    if(nodeIsNew){
        this->vec[curIndex].nextNode.push_back(1);
        this->vec[curIndex].action.push_back(action);
    }

}

void NFA::readGrammar(string address){
    string grammar;
    ifstream inf;
    inf.open(address);
    while(getline(inf, grammar)){
        vector<string> stringList;
        regex ws_re("\\s+");
	    sregex_token_iterator pos(grammar.begin(), grammar.end(), ws_re, -1);
	    decltype(pos) end;
	    for (; pos != end; ++pos){
            stringList.push_back(pos->str());
        }
        if(stringList.size() == 2){
            int curIndex = stoi(stringList[0]);
            chType action;
            for(vector<chType>::iterator iter = chTypeList.begin(); iter != chTypeList.end();++iter){
                if(iter->name == stringList[1]){
                    action = (*iter);
                    break;
                }
            }
            this->addNode(curIndex, action);
        }
        else{
            int curIndex = stoi(stringList[0]);
            int nextIndex = stoi(stringList[2]);
            chType action;
            for(vector<chType>::iterator iter = chTypeList.begin(); iter != chTypeList.end();++iter){
                if(iter->name == stringList[1]){
                    action = (*iter);
                    break;
                }
            }
            this->addNode(curIndex, nextIndex, action);
        }
    }
    inf.close();
}

int NFA::transformState(int curIndex, char ch){
    if(curIndex == -1){
        return -1;
    }
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
