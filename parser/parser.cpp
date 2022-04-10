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

void NonTerminal::getFirstUnion(){
    
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