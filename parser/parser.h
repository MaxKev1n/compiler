#ifndef _PARSER_H
#define _PARSER_H
#include "header.h"
using namespace std;

struct NonTerminal
{
    private:
        int id;
        set<int> firstUnion;

    public:
        NonTerminal() { this->id = 0; }
        NonTerminal(int id) : id(id) {};

        bool operator==(const NonTerminal &right) { return this->id == right.id; }
        void addFirstUnion(int terminal) { this->firstUnion.insert(terminal); }
        void addFirstUnion(set<int> firstUnion, bool hasEp);
        set<int> getFirstUnion() { return this->firstUnion; }
        int firstUnionCount() { return this->firstUnion.size(); }
        void printFirstUnion();
        int getId() { return this->id; }
};

struct chType{
    public:
        int id;
        string name;
        NonTerminal nonTerminal;
        
        chType(int i, string n) : id(i), name(n){}
        chType(){};
        chType(int i) : id(24), name("nonTerminal") { this->nonTerminal = NonTerminal(i); }

        bool operator==(const chType &right){
            return this->id == right.id;
        }

        bool operator==(const chType &right) const{
            return this->id == right.id;
        }

        bool operator!=(const chType &right){
            return this->id != right.id;
        }

        bool operator<(const chType &right) const{
            return this->id < right.id;
        }

        bool isNonTerminal() { return this->id == 24; }
};

const chType letter(0, "letter");
const chType natNumber(1, "natNumber");
const chType underline(2, "underline");
const chType midLeftPar(3, "midLeftPar");
const chType midRightPar(4, "midRightPar");
const chType Plus(5, "Plus");
const chType Minus(6, "Minus");
const chType logAnd(7, "logAnd");
const chType logOr(8, "logOr");
const chType logNot(9, "logNot");
const chType logXor(10, "logXor");
const chType rightArrow(11, "rightArrow");
const chType leftArrow(12, "leftArrow");
const chType semicolon(13, "semicolon");
const chType multi(14, "multi");
const chType smallLeftPar(15, "smallLeftPar");
const chType smallRightPar(16, "smallRightPar");
const chType dollar(17, "dollar");
const chType epsilon(18, "epsilon");
const chType dot(19, "dot");
const chType letter_E(20, "letter_E");
const chType letter_i(21, "letter_i");
const chType space(22, "space");
const chType zero(23, "zero");
const chType nonTerminal(24, "nonTerminal");
const chType Sign(25, "Sign");

const set<char> let {'a','b','c','d','e','f','g','h','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                         'A','B','C','D', 'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
const set<char> natNum {'1','2','3','4','5','6','7','8','9'};

static vector<chType> chTypeList {letter, natNumber, underline, midLeftPar, midRightPar, Plus, Minus, logAnd, logOr,
                           logNot, logXor, rightArrow, leftArrow, semicolon, multi, smallLeftPar,smallRightPar,
                           dollar, epsilon, dot, letter_E, letter_i, space, zero, Sign};

const set<string> keyword {"define", "switch", "iwire", "owire", "oreg", "wire", "reg", "mod", "default",
                            "case", "if", "else", "elseif"};

const set<string> qualifier {"abstract", "public", "private", "override", "const"};

const set<string> operators {"[", "]", "+", "-", "&", "|", "~", "^", ">>", "<<", ">>>", "(", ")", "*", "<", ">"};

const set<chType> terminalList {};

struct Tuple{
    private:
        int line;
        string str;
        string type;
    public:
        Tuple();
        Tuple(int line, string str, string type) : line(line), str(str), type(type){};

        int getLine() { return this->line; }
        string getStr() { return this->str; }
        string getType() { return this->type; }

        void setLine(int line) { this->line = line; }
        void setStr(string str) { this->str = str; }
        void setType(string type) { this->type = type; }
};

struct Grammar
{
    private:
        chType left;
        vector<chType> right;

    public:
        chType getLeft() { return this->left; }
        chType getRight(int index) { return this->right[index]; }
        vector<chType> getRightList() { return this->right; }
        void setLeft(int i) { this->left = chType(i); }
        void addRight(chType ch) { this->right.push_back(ch); }
};

struct Closure{
    public:
        int index;
        int lastIndex;
        chType moveType;
        vector<chType> moveTypeList;
        vector<bool> visitMatrix;
        vector<int> nextState;
        vector<chType> returnList;
        vector<int> returnIndex;

        struct Action{
            public:
                int type; //0: NULL, 1: shift, 2: return, 3: accept
                int number;

                Action() { type = 0; }
                Action(int type, int number) : type(type), number(number) {}
                Action(int type) : type(type) {}

                bool operator==(const Action &right) const{
                    if(this->type == 3 && right.type == 3){
                        return this->type == right.type;
                    }
                    else{
                        return (this->type == right.type) && (this->number == right.number);
                    }
                }
        };

        struct Goto{
            public:
                int number; //-1: NULL

                Goto() { number = -1; }
                Goto(int number) : number(number) {}

                bool operator==(const Goto &right) const{
                    return this->number == right.number;
                }
        };

    private:
        struct LR1_Grammar{
            public:
                int index; //dot at chType's left
                chType left;
                vector<chType> right;
                chType rightTerminal;
                int grammarIndex; //index in the input

                LR1_Grammar() {}
                LR1_Grammar(chType left, vector<chType> right, int index, int grammarIndex) : left(left), right(right), index(index), grammarIndex(grammarIndex) {}
                bool operator==(const LR1_Grammar &right) const{
                    return (this->index == right.index) && (this->right == right.right) && (this->rightTerminal == right.rightTerminal) && (this->left == right.left);
                }
                void printGrammar();
        };

    public:
        vector<LR1_Grammar> grammarList;
        vector<Action> ActionList;
        vector<Goto> GotoList;

        void initial(vector<Grammar> grammarList, vector<chType> nonTerminalList, Closure originClosure, chType moveType);
        void initial(vector<Grammar> grammarList, vector<chType> nonTerminalList);
        vector<LR1_Grammar> getGrammarList() { return this->grammarList; }
        int nextVisit();
        vector<chType> getRightTerminal(vector<chType> nonTerminalList, vector<chType> str);
        int getGrammarIndex(int index) { return this->grammarList[index].grammarIndex; }

        Closure() {}
        bool operator==(const Closure &right) const{
            return (this->moveType == right.moveType) && (this->grammarList == right.grammarList);
        }
};

struct Parser
{
    private:
        vector<Grammar> grammarList;
        vector<chType> nonTerminalList;
        vector<Closure> closureList;
        
    public:
        int getNonTerminalIndex(int nonTerminal);
        void readGrammar(string addr);
        void getFirstUnion();
        bool breakFirstUnion(vector<int> count);
        void printFirstUnion();
        void printGrammar();
        void printNonTerminalList();
        void createClosureList();
        void printClosureList();
        void dumpClosure(string address_output);
        void constructTable();

};


#endif