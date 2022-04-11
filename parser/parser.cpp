#include "parser.h"
using namespace std;

void Parser::readGrammar(string addr){
    string str;
    ifstream inf;
    inf.open(addr);
    while(getline(inf, str)){
        vector<string> stringList;
        regex ws_re("\\s+");
	    sregex_token_iterator pos(str.begin(), str.end(), ws_re, -1);
	    decltype(pos) end;
	    for (; pos != end; ++pos){
            stringList.push_back(pos->str());
        }
        Grammar grammar;
        grammar.setLeft(stoi(stringList[0]));

        bool isNewNT = true;
        for(int i = 0;i < this->nonTerminalList.size();i++){
            if(this->nonTerminalList[i] == grammar.getLeft()){
                isNewNT = false;
                break;
            }
        }
        if(isNewNT)
            nonTerminalList.push_back(grammar.getLeft());

        for(int i = 1;i < stringList.size();i++){
            for(vector<chType>::iterator iter = chTypeList.begin(); iter != chTypeList.end();++iter){
                if(iter->name == stringList[i]){
                    grammar.addRight(*iter);
                    break;
                }
            }
            grammar.addRight(chType(stoi(stringList[i])));
        }
        this->grammarList.push_back(grammar);
    }
    inf.close();
}

bool Parser::breakFistUnion(vector<int> count){
    int i = 0;
    for(vector<chType>::iterator iter = this->nonTerminalList.begin();iter != this->nonTerminalList.end();++iter,++i){
        if(count[i] != iter->nonTerminal.firstUnionCount())
            return false;
    }
    return true;
}

void Parser::getFirstUnion(){
    for(vector<Grammar>::iterator iter = this->grammarList.begin();iter != this->grammarList.end();++iter){
        if(iter->getRight(0) != nonTerminal){
            for(int i = 0;i < this->nonTerminalList.size();i++){
                if(nonTerminalList[i].nonTerminal == (iter->getLeft()).nonTerminal){
                    nonTerminalList[i].nonTerminal.addFirstUnion(iter->getRight(0));
                    break;
                }
            }
        }
    }
    while(1){
        vector<int> count;
        for(int i = 0;i < this->nonTerminalList.size();i++)
            count.push_back(nonTerminalList[i].nonTerminal.firstUnionCount());
        
        //calculate FirstUnion

        if(this->breakFistUnion(count))
            break;
    }
}

vector<chType> Parser::getFirstUnion(Grammar grammar, int index){
    vector<chType> rightList = grammar.getRightList();
    vector<chType> res;
    if(rightList[index] != nonTerminal){
        res.push_back(rightList[index]);
    }
    else{

    }
}