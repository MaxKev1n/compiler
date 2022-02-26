#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
using namespace std;

struct chType{
    public:
        int id;
        string name;
        
        chType(int i, string n) : id(i), name(n){}
        chType(){};

        bool operator==(const chType &right){
            return this->id == right.id;
        }
};

struct NFA_Node
{
    public:
        int index;
        vector<int> nextNode;
        vector<chType> action;
        bool isVisit = false;
};


struct lexer
{
    public:
        static chType chtypeDetect(char ch);
        void run(string address_grammar, string address_txt);
    private:
        
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

    private:
        void initialize();
        
};


chType letter(0, "letter");
chType number(1, "number");
chType underline(2, "underline");
chType midLeftPar(3, "midLeftPar");
chType midRightPar(4, "midRightPar");
chType Plus(5, "Plus");
chType Minus(6, "Minus");
chType logAnd(7, "logAnd");
chType logOr(8, "logOr");
chType logNot(9, "logNot");
chType logXor(10, "logXor");
chType rightArrow(11, "rightArrow");
chType leftArrow(12, "leftArrow");
chType semicolon(13, "semicolon");
chType multi(14, "multi");
chType smallLeftPar(15, "smallLeftPar");
chType smallRightPar(16, "smallRightPar");
chType dollar(17, "dollar");
chType epsilon(18, "epsilon");

set<char> let {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                         'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
set<char> num {'0','1','2','3','4','5','6','7','8','9'};
vector<chType> chTypeList {letter, number, underline, midLeftPar, midRightPar, Plus, Minus, logAnd, logOr,
                           logNot, logXor, rightArrow, leftArrow, semicolon, multi, smallLeftPar,smallRightPar,
                           dollar, epsilon};