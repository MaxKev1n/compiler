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
        if(action == epsilon){
            bool newNode =true;
            for(int i = 0;i < this->vec[curIndex].epSet.size();i++){
                if(nextIndex == this->vec[curIndex].epSet[i])
                    newNode = false;
            }
            if(newNode){
                this->vec[curIndex].nextNode.push_back(nextIndex);
                this->vec[curIndex].action.push_back(action);
                this->vec[curIndex].epSet.push_back(nextIndex);
            }
        }else{
            this->vec[curIndex].nextNode.push_back(nextIndex);
            this->vec[curIndex].action.push_back(action);
        }
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

void NFA::epClosure(){
    int numNode = this->vec.size();
    for(int i = 0;i < numNode;i++){
        int visited[numNode] = {0};
        NFA_Node node = this->vec[i];
        stack<int> s;
        s.push(i);
        while(!s.empty()){
            int currentNum = s.top();
            NFA_Node currentNode = this->vec[currentNum];
            for(int index = 0;index < currentNode.epSet.size();index++){
                int epSetIndex = currentNode.epSet[index];
                if(visited[epSetIndex] == 0){
                    s.push(epSetIndex);
                    visited[epSetIndex] = 1;
                    node.epClosure.push_back(epSetIndex);
                }
            }
            s.pop();
        }
        this->vec[i] = node;
    }
}

void NFA::printEpClosure(){
    for(vector<NFA_Node>::iterator iter = this->vec.begin();iter != this->vec.end();++iter){
        cout<<iter->index<<": ";
        iter->printEpClosure();
    }
}

int DFA::transformState(int curIndex, char ch){
    if(curIndex == -1){
        return -1;
    }
    DFA_state curState = this->vec[curIndex];
    int index = 0;
    for(vector<chType>::iterator iter = curState.action.begin(); iter != curState.action.end();++iter, ++index){
        chType curType = lexer::chtypeDetect(ch);
        if(curType == (*iter)){
            return curState.nextState[index];
        }
    }
    return -1;
}

bool DFA::allVisited(){
    for(vector<DFA_state>::iterator iter = this->vec.begin(); iter != this->vec.end();++iter){
        if(iter->isVisit == false){
            return false;
        }
    }
    return true;
}

bool DFA::isNew(set<int> newSet){
    if(newSet.size() == 0){
        return false;
    }
    for(vector<DFA_state>::iterator iter = this->vec.begin(); iter != this->vec.end();++iter){
        if(iter->NFA_state_set == newSet){
            return false;
        }
    }
    return true;
}

void DFA::initialize(NFA nfa){
    DFA_state head;
    head.index = 0;
    head.NFA_state_set.insert(0);
    this->vec.push_back(head);
    int index = 0;
    while(!allVisited()){
        DFA_state state = this->vec[index];
        for(vector<chType>::iterator iter = chTypeList.begin(); iter != chTypeList.end();++iter){
            if(*iter == epsilon)
                continue;
            set<int> tempMoveSet;
            for(set<int>::iterator iter2 = state.NFA_state_set.begin(); iter2!= state.NFA_state_set.end();++iter2){
                NFA_Node tempNode = nfa.vec[*iter2];
                for(int i = 0;i < tempNode.action.size();i++){
                    if((*iter) == tempNode.action[i])
                        tempMoveSet.insert(tempNode.nextNode[i]);
                }
            }

            set<int> tempSet = tempMoveSet;
            for(set<int>::iterator iter2 = tempSet.begin(); iter2!= tempSet.end();++iter2){
                NFA_Node node = nfa.vec[*iter2];
                for(int i = 0;i < node.epClosure.size();i++){
                    tempSet.insert(node.epClosure[i]);
                }
            }

            if(tempSet.size() > 0 && (this->isNew(tempSet))){
                DFA_state newState;
                newState.index = this->vec.size();
                newState.NFA_state_set = tempSet;

                this->vec.push_back(newState);
                this->vec[index].nextState.push_back(newState.index);
                this->vec[index].action.push_back(*iter);
            }else if(tempSet.size() > 0){
                for(vector<DFA_state>::iterator iter2 = this->vec.begin(); iter2 != this->vec.end();++iter2){
                    if(iter2->NFA_state_set == tempSet){
                        this->vec[index].nextState.push_back(iter2->index);
                        this->vec[index].action.push_back(*iter);
                    }
                }
            }
        }
        this->vec[index].isVisit = true;
        index++;
    }
}

void NFA_Node::printEpClosure(){
    for(vector<int>::iterator iter = this->epClosure.begin();iter != this->epClosure.end();++iter)
        cout<<*iter<<" ";
    cout<<endl;
}

void DFA::printDFA(){
    cout<<"This is DFA lists!!!"<<endl<<"----------"<<endl;

    for(vector<DFA_state>::iterator iter = this->vec.begin(); iter != this->vec.end();++iter){
        cout<<"index: "<<iter->index<<endl;
        for(set<int>::iterator iter2 = iter->NFA_state_set.begin(); iter2!= iter->NFA_state_set.end();++iter2){
            cout<<*iter2<<" ";
        }
        cout<<endl;
        for(int i = 0;i < iter->nextState.size();i++){
            cout<<"action: "<<iter->action[i].name<<" "<<"nextState: "<<iter->nextState[i]<<endl;
        }
        cout<<"----------"<<endl;
    }
}