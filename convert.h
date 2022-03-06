#pragma once
#include "header.h"

using namespace std;

struct chType;
struct lexer;

struct NFA_Node
{
    public:
        int index;
        vector<int> nextNode;
        vector<chType> action;
        vector<int> epSet;
        bool isVisit = false;
};

struct NFA{
    public:
        vector<NFA_Node> vec;
        set<int> NFA_set;

        NFA(){
            this->initialize();
        };

        void addNode(int curIndex, int nextIndex, chType action);
        void addNode(int curIndex, chType action); //go to final state
        void readGrammar(string address);
        int transformState(int curIndex, char ch);
        vector<int> epClosure(int curIndex);

    private:
        void initialize();
        
};

struct DFA_state{
    public:
        int index;
        set<int> NFA_state_set;
        vector<int> nextState;
        vector<chType> action;
        bool isVisit = false;
};

struct DFA{
    public:
        vector<DFA_state> vec;

        DFA(NFA nfa){
            this->initialize(nfa);
        }

        void printDFA();
        int transformState(int curIndex, char ch);
    
    private:
        void initialize(NFA nfa);
        bool allVisited();
        bool isNew(set<int>  newSet);
};