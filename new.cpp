#include "new.h"
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
    for(int i = 0;i < this->vec.size();i++){
        cout<<this->vec[i].index<<endl;
        for(int j = 0;j < this->vec[i].nextNode.size();j++){
            cout<<this->vec[i].nextNode[j]<<endl;
        }
        for(int j = 0;j < this->vec[i].action.size();j++){
            cout<<this->vec[i].action[j].name<<endl;
        }
        cout<<"---"<<endl;
    }
}

int NFA::transformState(int curIndex, char ch){
    if(curIndex == -1){
        return -1;
    }
    NFA_Node curNode = this->vec[curIndex];
    int index = 0;
    for(vector<chType>::iterator iter = curNode.action.begin(); iter != curNode.action.end();++iter, ++index){
        chType curType = lexer::chtypeDetect(ch);
        cout<<curType.name<<" ";
        if(curType == (*iter)){
            return curNode.nextNode[index];
        }
    }
    return -1;
}

chType lexer::chtypeDetect(char ch){
    if(let.find(ch) != let.end()){
        return letter;
    }
    else if(num.find(ch) != num.end()){
        return number;
    }
    else{
        switch (ch)
        {
        case '_':{
            return underline;
            break;
        }
        case '[':{
            return midLeftPar;
            break;
        }
        case ']':{
            return midRightPar;
            break;
        }
        case '+':{
            return Plus;
            break;
        }
        case '-':{
            return Minus;
            break;
        }
        case '&':{
            return logAnd;
            break;
        }
        case '|':{
            return logOr;
            break;
        }
        case '~':{
            return logNot;
            break;
        }
        case '^':{
            return logXor;
            break;
        }
        case '>':{
            return rightArrow;
            break;
        }
        case '<':{
            return leftArrow;
            break;
        }
        case ';':{
            return semicolon;
            break;
        }
        case '*':{
            return multi;
            break;
        }
        case '(':{
            return smallLeftPar;
            break;
        }
        case ')':{
            return smallRightPar;
            break;
        }
        case '$':{
            return dollar;
            break;
        }
        default:
            return epsilon;
            break;
        }
    }
}

void lexer::run(string address_grammar, string address_txt){
    NFA nfa;
    nfa.readGrammar(address_grammar);

    vector<string> res;
    string text;
    ifstream inf;
    inf.open(address_txt);
    while(getline(inf, text)){
        string t = "";
        int curIndex = 0;
        for(int i = 0;i <= text.length();i++){
            curIndex = nfa.transformState(curIndex, text[i]);
            if(curIndex == 1){
                curIndex = 0;
                res.push_back(t);
                t = "";
            }else if((curIndex == -1) && (lexer::chtypeDetect(text[i]) == epsilon)){
                curIndex = 0;
                t = "";
            }
            else{
                t += text[i];
            }
            cout<<i<<":"<<curIndex<<":"<<t<<endl;
        }
        cout<<"###"<<endl;
    }
    inf.close();
    for(int i = 0;i < res.size();i++){
        cout<<res[i]<<endl;
    }
}

int main(){
    lexer l;
    l.run("/home/czh/compiler/grammar.txt", "/home/czh/compiler/test.txt");
    return 0;
}