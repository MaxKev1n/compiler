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
        for(vector<chType>::iterator iter = chTypeList.begin(); iter != chTypeList.end();++iter){
            if(iter->name == stringList[0]){
                grammar.setLeft(*iter);
                break;
            }
        }
        for(int i = 1;i < stringList.size();i++){
            for(vector<chType>::iterator iter = chTypeList.begin(); iter != chTypeList.end();++iter){
                if(iter->name == stringList[i]){
                    grammar.addRight(*iter);
                    break;
                }
            }
        }
    }
    inf.close();
}