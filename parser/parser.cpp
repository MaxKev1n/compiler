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

void Closure::LR1_Grammar::printGrammar(){
    cout<<this->left.nonTerminal.getId()<<"->";
    for(int i = 0;i < this->right.size();i++){
        if(this->right[i].isNonTerminal()){
            cout<<this->right[i].nonTerminal.getId()<<" ";
        }
        else{
            cout<<this->right[i].name<<" ";
        }
    }
    cout<<","<<index<<","<<this->rightTerminal.name<<endl;
}

void Closure::initial(vector<Grammar> grammarList, vector<chType> nonTerminalList){
    this->index = 0;
    this->lastIndex = 0;
    LR1_Grammar firstGrammar(grammarList[0].getLeft(), grammarList[0].getRightList(), 0, 0);
    firstGrammar.rightTerminal = Sign;
    this->grammarList.push_back(firstGrammar);

    while(1){
        vector<LR1_Grammar> tempList = this->grammarList;

        for(int i = 0;i < this->grammarList.size();i++){
            chType ch = this->grammarList[i].right[0];
            if(ch.isNonTerminal()){
                for(int j = 0;j < grammarList.size();j++){
                    if(ch.nonTerminal == grammarList[j].getLeft().nonTerminal){
                        LR1_Grammar newGrammar(ch, grammarList[j].getRightList(), 0, j);
                        vector<chType> str;
                        for(int index = this->grammarList[i].index + 1;index < this->grammarList[i].right.size();index++){
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
        if(isBreak){
            for(int i = 0;i < this->grammarList.size();i++){
                if((!this->grammarList[i].rightTerminal.isNonTerminal()) && (this->grammarList[i].index == this->grammarList[i].right.size())){
                    returnList.push_back(this->grammarList[i].rightTerminal);
                    returnIndex.push_back(this->grammarList[i].grammarIndex);
                }
            }
            for(int i = 0;i < this->grammarList.size();i++){
                LR1_Grammar grammar = this->grammarList[i];
                if(grammar.index < grammar.right.size()){
                    bool isNewMoveType = true;
                    for(int j = 0;j < this->moveTypeList.size();j++){
                        if(grammar.right[grammar.index].isNonTerminal()){
                            if(grammar.right[grammar.index].nonTerminal == this->moveTypeList[j].nonTerminal){
                                isNewMoveType = false;
                                break;
                            }
                        }
                        else{
                            if(grammar.right[grammar.index] == this->moveTypeList[j]){
                                isNewMoveType = false;
                                break;
                            }
                        }
                    }
                    if(isNewMoveType){
                        this->moveTypeList.push_back(grammar.right[grammar.index]);
                        this->visitMatrix.push_back(false);
                    }
                }
            }
            break;
        }
    }
}

void Closure::initial(vector<Grammar> grammarList, vector<chType> nonTerminalList, Closure originClosure, chType moveType){
    this->moveType = moveType;
    for(int i = 0;i < originClosure.grammarList.size();i++){
        LR1_Grammar grammar = originClosure.grammarList[i];
        if(grammar.index >= grammar.right.size())
            continue;
        if(moveType.isNonTerminal()){
            if(moveType.nonTerminal == grammar.right[grammar.index].nonTerminal){
                grammar.index++;
                this->grammarList.push_back(grammar);
            }
        }
        else{
            if(moveType == grammar.right[grammar.index]){
                grammar.index++;
                this->grammarList.push_back(grammar);
            }
        }
    }

    while(1){
        vector<LR1_Grammar> tempList = this->grammarList;
        for(int i = 0;i < this->grammarList.size();i++){
            int rightIndex = this->grammarList[i].index;

            if(rightIndex == this->grammarList[i].right.size())
                continue;

            chType ch = this->grammarList[i].right[rightIndex];
            if(ch.isNonTerminal()){
                for(int j = 0;j < grammarList.size();j++){
                    if(ch.nonTerminal == grammarList[j].getLeft().nonTerminal){
                        LR1_Grammar newGrammar(ch, grammarList[j].getRightList(), 0, j);
                        vector<chType> str;
                        for(int index = this->grammarList[i].index + 1;index < this->grammarList[i].right.size();index++){
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
        if(isBreak){
            this->lastIndex = originClosure.index;
            for(int i = 0;i < this->grammarList.size();i++){
                LR1_Grammar grammar = this->grammarList[i];
                if(grammar.index < grammar.right.size()){
                    bool isNewMoveType = true;
                    for(int j = 0;j < this->moveTypeList.size();j++){
                        if(grammar.right[grammar.index].isNonTerminal()){
                            if(grammar.right[grammar.index].nonTerminal == this->moveTypeList[j].nonTerminal){
                                isNewMoveType = false;
                                break;
                            }
                        }
                        else{
                            if(grammar.right[grammar.index] == this->moveTypeList[j]){
                                isNewMoveType = false;
                                break;
                            }
                        }
                    }
                    if(isNewMoveType){
                        this->moveTypeList.push_back(grammar.right[grammar.index]);
                        this->visitMatrix.push_back(false);
                    }
                }
            }
            break;
        }
    }
}

int Closure::nextVisit(){
    for(int i = 0;i < this->visitMatrix.size();i++){
        if(!this->visitMatrix[i])
            return i;
    }
    return -1;
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
    //calculate closureList
    stack<int> closureStack;
    closureStack.push(0);

    while(!closureStack.empty()){
        int index = closureStack.top();
        Closure originClosure = closureList[index];
        int nextVisit = originClosure.nextVisit();
        if(nextVisit == -1){
            closureStack.pop();
        }
        else{
            Closure newClosure;
            chType moveType = originClosure.moveTypeList[nextVisit];
            newClosure.initial(this->grammarList, this->nonTerminalList, originClosure, moveType);
            bool isNew = true;
            for(int i = 0;i < this->closureList.size();i++){
                if(newClosure == this->closureList[i])
                    isNew = false;
            }
            if(isNew){
                int newIndex = this->closureList.size();
                newClosure.index = newIndex;
                closureList[index].visitMatrix[nextVisit] = true;
                closureList[index].nextState.push_back(newIndex);
                closureList.push_back(newClosure);
                closureStack.push(newIndex);
            }
            else{
                closureList[index].visitMatrix[nextVisit] = true;
            }
        }
        
    }
}

void Parser::dumpClosure(string address_output){
    cout<<"dumping Closure List!"<<endl<<string(40, '-')<<endl;

    std::ofstream ofs;
    ofs.open(address_output+"/Closure.txt");
    std::stringstream ss;
    for(vector<Closure>::iterator iter = this->closureList.begin(); iter != this->closureList.end();++iter){
        ss<<"Closure index: "<<iter->index<<endl;
        ss<<"Last Closure index: "<<iter->lastIndex<<endl<<endl;
        ss<<"Next Closure and its move chType: "<<endl;
        for(int i = 0;i < iter->moveTypeList.size();i++){
            ss<<iter->nextState[i]<<" ";
            if(iter->moveTypeList[i].isNonTerminal()){
                ss<<iter->moveTypeList[i].name<<'.'<<iter->moveTypeList[i].nonTerminal.getId()<<endl;
            }
            else{
                ss<<iter->moveTypeList[i].name<<endl;
            }
        }
        ss<<endl;
        if(iter->moveType.isNonTerminal()){
            ss<<"Move chType: "<<iter->moveType.name<<'.'<<iter->moveType.nonTerminal.getId()<<endl<<endl;
        }
        else{
            ss<<"Move chType: "<<iter->moveType.name<<endl<<endl;
        }
        for(int i = 0;i < iter->grammarList.size();i++){
            ss<<"GrammarIndex: "<<iter->getGrammarIndex(i)<<"  ";
            ss<<iter->grammarList[i].left.nonTerminal.getId()<<"->";
            for(int j = 0;j < iter->grammarList[i].right.size();j++){
                if(iter->grammarList[i].index == j)
                    ss<<".";
                if(iter->grammarList[i].right[j].isNonTerminal()){
                    ss<<iter->grammarList[i].right[j].nonTerminal.getId()<<" ";
                }
                else{
                    ss<<iter->grammarList[i].right[j].name<<" ";
                }
            }
            if(iter->grammarList[i].index == iter->grammarList[i].right.size())
                ss<<".";
            ss<<","<<iter->grammarList[i].rightTerminal.name<<endl;
        }
        ss<<endl<<"Action Row:"<<endl;
        for(int i = 0;i < chTypeList.size();i++){
            ss<<chTypeList[i].name<<": ";
            if(iter->ActionList[i].type == 1){
                ss<<"S"<<iter->ActionList[i].number;
            }
            else if(iter->ActionList[i].type == 2){
                ss<<"r"<<iter->ActionList[i].number;
            }
            else if(iter->ActionList[i].type == 3){
                ss<<"acc";
            }
            ss<<endl;
        }
        ss<<endl<<"Goto Row:"<<endl;
        for(int i = 0;i < this->nonTerminalList.size();i++){
            ss<<this->nonTerminalList[i].nonTerminal.getId()<<": ";
            if(iter->GotoList[i].number != -1){
                ss<<iter->GotoList[i].number;
            }
            ss<<endl;
        }
        ss<<"----------"<<endl;
    }
    ofs << ss.rdbuf();
    ofs.close();
}

void Parser::constructTable(){
    for(int i = 0;i < this->closureList.size();i++){
        //state accept
        if((this->closureList[i].grammarList[0].left.nonTerminal.getId() == 0) && (this->closureList[i].grammarList[0].index == 1) && (this->closureList[i].grammarList[0].rightTerminal == Sign)){
            for(int j = 0;j < chTypeList.size();j++){
                if(chTypeList[j] == Sign){
                    this->closureList[i].ActionList.push_back(Closure::Action(3));
                }
                else{
                    this->closureList[i].ActionList.push_back(Closure::Action());
                }
            }
            for(int j = 0;j < this->nonTerminalList.size();j++){
                this->closureList[i].GotoList.push_back(Closure::Goto());
            }
            continue;
        }
        //other states
        //construct action table
        for(int j = 0;j < chTypeList.size();j++){
            //return
            for(int m = 0;m < this->closureList[i].returnList.size();m++){
                if(this->closureList[i].returnList[m] == chTypeList[j]){
                    this->closureList[i].ActionList.push_back(Closure::Action(2, this->closureList[i].returnIndex[m]));
                }
            }
            //shift or null
            bool hasMoveType = false;
            int k;
            for(k = 0;k < this->closureList[i].moveTypeList.size();k++){
                if(this->closureList[i].moveTypeList[k] == chTypeList[j]){
                    hasMoveType = true;
                    break;
                }
            }
            if(hasMoveType){
                this->closureList[i].ActionList.push_back(Closure::Action(1, this->closureList[i].nextState[k]));
            }
            else{
                this->closureList[i].ActionList.push_back(Closure::Action());
            }
        }
        //construct goto table
        for(int j = 0;j < this->nonTerminalList.size();j++){
            bool hasMoveType = false;
            int m;
            for(m = 0;m < this->closureList[i].moveTypeList.size();m++){
                if(this->closureList[i].moveTypeList[m].isNonTerminal() && (this->closureList[i].moveTypeList[m].nonTerminal == this->nonTerminalList[j].nonTerminal)){
                    hasMoveType = true;
                    break;
                }
            }
            if(hasMoveType){
                this->closureList[i].GotoList.push_back(Closure::Goto(this->closureList[i].nextState[m]));
            }
            else{
                this->closureList[i].GotoList.push_back(Closure::Goto());
            }
        }
    }
}

void Parser::printClosureList(){
    cout<<"This is the result of closure calculate"<<endl<<string(40, '-')<<endl;
    for(int i = 0;i < this->closureList.size();i++){
        cout<<"closure index:"<<i<<endl;
        for(int j = 0;j < this->closureList[i].grammarList.size();j++)
            this->closureList[i].grammarList[j].printGrammar();
        cout<<endl;
    }
    cout<<string(40, '-')<<endl;;
}

int main(int argc,char *argv[]){
    Parser parser;
    string address_grammar;
    string address_output;
    address_grammar = argv[1];
    address_output = argv[2];
    parser.readGrammar(address_grammar);
    parser.printGrammar();
    parser.getFirstUnion();
    parser.printFirstUnion();
    parser.createClosureList();
    parser.constructTable();
    parser.dumpClosure(address_output);
    return 0;
}