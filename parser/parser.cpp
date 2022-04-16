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
            if(this->nonTerminalList[i].nonTerminal == grammar.getLeft().nonTerminal){
                isNewNT = false;
                break;
            }
        }
        if(isNewNT)
            nonTerminalList.push_back(grammar.getLeft());

        for(int i = 1;i < stringList.size();i++){
            bool res = false;
            for(vector<chType>::iterator iter = chTypeList.begin(); iter != chTypeList.end();++iter){
                if(iter->name == stringList[i]){
                    grammar.addRight(*iter);
                    res = true;
                    break;
                }
            }
            if(!res)
                grammar.addRight(chType(stoi(stringList[i])));
        }
        this->grammarList.push_back(grammar);
    }
    inf.close();
}

void NonTerminal::printFirstUnion(){
    cout<<this->id<<" ";
    for(set<int>::iterator iter = this->firstUnion.begin();iter != this->firstUnion.end();++iter){
        for(int i = 0;i < chTypeList.size();i++){
            if(*iter == chTypeList[i].id)
                cout<<chTypeList[i].name<<" ";
        }
    }
}

void NonTerminal::addFirstUnion(set<int> firstUnion, bool hasEp){
    if(hasEp){
        for(set<int>::iterator iter = firstUnion.begin();iter != firstUnion.end();++iter){
            this->addFirstUnion(*iter);
        }
    }
    else{
        for(set<int>::iterator iter = firstUnion.begin();iter != firstUnion.end();++iter){
            if(*iter != epsilon.id)
                this->addFirstUnion(*iter);
        }
    }
}

int Parser::getNonTerminalIndex(int nonTerminal){
    int grammarListIndex;
    for(grammarListIndex = 0;grammarListIndex < this->nonTerminalList.size();grammarListIndex++){
        if(this->nonTerminalList[grammarListIndex].nonTerminal.getId() == nonTerminal){
            return grammarListIndex;
        }
    }
    assert(grammarListIndex < this->nonTerminalList.size());
    return 0;
}

bool Parser::breakFirstUnion(vector<int> count){
    int i = 0;
    for(vector<chType>::iterator iter = this->nonTerminalList.begin();iter != this->nonTerminalList.end();++iter,++i){
        if(count[i] != iter->nonTerminal.firstUnionCount())
            return false;
    }
    return true;
}

void Parser::getFirstUnion(){
    for(vector<Grammar>::iterator iter = this->grammarList.begin();iter != this->grammarList.end();++iter){
        if(!(iter->getRight(0).isNonTerminal())){
            int grammarListIndex = this->getNonTerminalIndex(iter->getLeft().nonTerminal.getId());
            this->nonTerminalList[grammarListIndex].nonTerminal.addFirstUnion(iter->getRight(0).id);
        }
    }
    int index = 0;
    while(1){
        vector<int> count;
        for(int i = 0;i < this->nonTerminalList.size();i++)
            count.push_back(nonTerminalList[i].nonTerminal.firstUnionCount());
        
        for(vector<Grammar>::iterator iter = this->grammarList.begin();iter != this->grammarList.end();++iter){
            int grammarListIndex = this->getNonTerminalIndex((iter->getLeft()).nonTerminal.getId());

            if(!(iter->getRight(0).isNonTerminal())){
                this->nonTerminalList[grammarListIndex].nonTerminal.addFirstUnion(iter->getRight(0).id);
            }
            else{
                int rightSize = iter->getRightList().size();
                int i;
                for(i = 0;i < rightSize;i++){
                    if(iter->getRight(i).isNonTerminal()){
                        bool res = false;  //true: has grammar nT->epsilon, false: no grammar nT->epsilon
                        for(vector<Grammar>::iterator iter2 = this->grammarList.begin();iter2 != this->grammarList.end();++iter2){
                            if((iter->getRight(i).nonTerminal == iter2->getLeft().nonTerminal) && (iter2->getRight(0) == epsilon) && (iter2->getRightList().size() == 1)){
                                int Index = this->getNonTerminalIndex(iter2->getLeft().nonTerminal.getId());
                                this->nonTerminalList[grammarListIndex].nonTerminal.addFirstUnion(this->nonTerminalList[Index].nonTerminal.getFirstUnion(), false);
                                res = true;
                                break;
                            }
                        }
                        if(!res)
                            break;
                    }
                    else{
                        break;
                    }
                }
                if(i < rightSize){
                    if(iter->getRight(i).isNonTerminal()){
                        int Index = this->getNonTerminalIndex(iter->getRight(i).nonTerminal.getId());
                        this->nonTerminalList[grammarListIndex].nonTerminal.addFirstUnion(this->nonTerminalList[Index].nonTerminal.getFirstUnion(), true);
                    }
                    else{
                        this->nonTerminalList[grammarListIndex].nonTerminal.addFirstUnion(iter->getRight(i).id);
                    }
                }
                else{
                    this->nonTerminalList[grammarListIndex].nonTerminal.addFirstUnion(epsilon.id);
                }
            }
        }
        if(this->breakFirstUnion(count))
            break;
    }
}

vector<chType> Closure::getRightTerminal(vector<chType> nonTerminalList, vector<chType> str){
    vector<chType> res;
    for(int i = 0;i < str.size();i++){
        if(str[i].isNonTerminal()){
            chType NT;
            for(int j = 0;j < nonTerminalList.size();j++){
                if(nonTerminalList[j] == str[i])
                    NT = nonTerminalList[j];
            }
            bool hasEp = false;
            set<int> firstUnion = NT.nonTerminal.getFirstUnion();
            for(set<int>::iterator iter = firstUnion.begin();iter != firstUnion.end();++iter){
                if(*iter == 18)
                    hasEp = true;
                else{
                    for(int index = 0;index < chTypeList.size();index++){
                        if(*iter == chTypeList[index].id){
                            res.push_back(chTypeList[index]);
                            break;
                        }
                    }
                }
            }
            if(!hasEp)
                break;
        }
        else{
            res.push_back(str[i]);
            break;
        }
    }
    return res;
}

void Closure::initial(vector<Grammar> grammarList, vector<chType> nonTerminalList){
    LR1_Grammar firstGrammar(grammarList[0].getLeft(), grammarList[0].getRightList(), 0);
    firstGrammar.rightTerminal = Sign;
    this->grammarList.push_back(firstGrammar);

    while(1){
        vector<LR1_Grammar> tempList = this->grammarList;

        for(int i = 0;i < this->grammarList.size();i++){
            chType ch = this->grammarList[i].right[0];
            if(ch.isNonTerminal()){
                for(int j = 0;j < grammarList.size();j++){
                    if(ch.nonTerminal == grammarList[j].getLeft().nonTerminal){
                        LR1_Grammar newGrammar(ch, grammarList[j].getRightList(), 0);
                        vector<chType> str;
                        for(int index = 1;index < this->grammarList[i].right.size();index++){
                            str.push_back(this->grammarList[i].right[index]);
                        }
                        str.push_back(this->grammarList[i].rightTerminal);
                        vector<chType> rightTerminalList = this->getRightTerminal(nonTerminalList, str);
                        for(int index = 0;index < rightTerminalList.size();index++){
                            LR1_Grammar tempGrammar = newGrammar;
                            tempGrammar.rightTerminal = rightTerminalList[index];
                            bool isNew = true;
                            for(int k = 0;k < this->grammarList.size();k++){
                                if(tempGrammar == this->grammarList[k]){
                                    isNew = false;
                                    break;
                                }
                            }
                            if(isNew)
                                this->grammarList.push_back(tempGrammar);
                        }
                    }
                }
            }
        }

        bool isBreak = true;
        for(int i = 0;i < this->grammarList.size();i++){
            int j;
            for(j = 0;j < tempList.size();j++){
                if(this->grammarList[i] == tempList[j])
                    break;
            }
            if(j == tempList.size()){
                isBreak = false;
                break;
            }
        }
    if(isBreak)
        break;
    }
}

void Closure::initial(vector<Grammar> grammarList, vector<chType> nonTerminalList, Closure originClosure, chType moveType){
    this->grammarList = originClosure.getGrammarList();
    this->moveType = moveType;

    while(1){
        vector<LR1_Grammar> tempList = this->grammarList;

        for(int i = 0;i < this->grammarList.size();i++){
            int rightIndex = this->grammarList[i].index;
            chType ch = this->grammarList[i].right[rightIndex];
            if(ch.isNonTerminal()){
                for(int j = 0;j < grammarList.size();j++){
                    if(ch.nonTerminal == grammarList[j].getLeft().nonTerminal){
                        LR1_Grammar newGrammar(ch, grammarList[j].getRightList(), 0);
                        vector<chType> str;
                        for(int index = 1;index < this->grammarList[i].right.size();index++){
                            str.push_back(this->grammarList[i].right[index]);
                        }
                        str.push_back(this->grammarList[i].rightTerminal);
                        vector<chType> rightTerminalList = this->getRightTerminal(nonTerminalList, str);
                        for(int index = 0;index < rightTerminalList.size();index++){
                            LR1_Grammar tempGrammar = newGrammar;
                            tempGrammar.rightTerminal = rightTerminalList[index];
                            bool isNew = true;
                            for(int k = 0;k < this->grammarList.size();k++){
                                if(tempGrammar == this->grammarList[k]){
                                    isNew = false;
                                    break;
                                }
                            }
                            if(isNew)
                                this->grammarList.push_back(tempGrammar);
                        }
                    }
                }
            }
        }

        bool isBreak = true;
        for(int i = 0;i < this->grammarList.size();i++){
            int j;
            for(j = 0;j < tempList.size();j++){
                if(this->grammarList[i] == tempList[j])
                    break;
            }
            if(j == tempList.size()){
                isBreak = false;
                break;
            }
        }
        if(isBreak)
            break;
    }
}

void Parser::printFirstUnion(){
    cout<<"This is the result of first union"<<endl<<string(40, '-')<<endl;
    for(int i = 0;i < this->nonTerminalList.size();i++){
        this->nonTerminalList[i].nonTerminal.printFirstUnion();
        cout<<endl;
    }
    cout<<string(40, '-')<<endl;
}

void Parser::printGrammar(){
    cout<<"This is the result of grammar list"<<endl<<string(40, '-')<<endl;
    for(int i = 0;i < this->grammarList.size();i++){
        cout<<this->grammarList[i].getLeft().nonTerminal.getId()<<" ";
        vector<chType> right = this->grammarList[i].getRightList();
        for(int j = 0;j < right.size();j++){
            if(right[j].isNonTerminal()){
                cout<<right[j].nonTerminal.getId()<<" ";
            }
            else{
                cout<<right[j].name<<" ";
            }
        }
        cout<<endl;
    }
    cout<<string(40, '-')<<endl;
}

void Parser::printNonTerminalList(){
    for(int i = 0;i < this->nonTerminalList.size();i++)
        cout<<this->nonTerminalList[i].nonTerminal.getId()<<" ";
    cout<<endl;
}

void Parser::createClosureList(){
    Closure closure0;
    closure0.index = 0;
    closure0.initial(this->grammarList, this->nonTerminalList);
    this->closureList.push_back(closure0);
    while(1){
        vector<Closure> tempList = this->closureList;

        bool isBreak = true;
        for(int i = 0;i < this->closureList.size();i++){
            int j;
            for(j = 0;j < tempList.size();j++){
                if(this->closureList[i] == tempList[j])
                    break;
            }
            if(j == tempList.size()){
                isBreak = false;
                break;
            }
        }
        if(isBreak)
            break;
    }
}

int main(int argc,char *argv[]){
    Parser parser;
    string address_grammar;
    address_grammar = argv[1];
    parser.readGrammar(address_grammar);
    parser.printGrammar();
    parser.getFirstUnion();
    parser.printFirstUnion();
    return 0;
}