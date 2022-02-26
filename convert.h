#ifndef CONVERT_H
#define CONVERT_H

using namespace std;
#include "header.h"

struct NFA_Node
{
    public:
        int index;
        vector<int> nextNode;
        vector<chType> action;
        bool isVisit = false;
};


struct NFA{
    public:
        vector<NFA_Node> vec;

        NFA(){
            this->initialize();
        };

        void addNode(int curIndex, int nextIndex, chType action);
        void addNode(int curIndex, chType action); //go to final state
        void readGrammar(string address);
        int transformState(int curIndex, char ch);

    private:
        void initialize();
        
};

#endif