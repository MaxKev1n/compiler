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
        bool operator!=(const NonTerminal &right) { return this->id != right.id; }
        bool operator!=(const NonTerminal &right) const{ return this->id != right.id; }
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
        chType(int i) : id(49), name("nonTerminal") { this->nonTerminal = NonTerminal(i); }

        bool operator==(const chType &right){
            return this->id == right.id;
        }

        bool operator==(const chType &right) const{
            return this->id == right.id;
        }

        bool operator!=(const chType &right){
            return this->id != right.id;
        }

        bool operator!=(const chType &right) const{
            return this->id != right.id;
        }

        bool operator<(const chType &right) const{
            return this->id < right.id;
        }

        bool isNonTerminal() { return this->id == 49; }
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
const chType Sign(24, "Sign");
const chType colon(25, "colon");
const chType Equal(26, "equal");
const chType bigLeftPar(27, "bigLeftPar");
const chType bigRightPar(28, "bigRightPar");

const chType Define(29, "define");
const chType Swich(30, "switch");
const chType Iwire(31, "iwire");
const chType Owire(32, "owire");
const chType Oreg(33, "oreg");
const chType Wire(34, "wire");
const chType Reg(35, "reg");
const chType Mod(36, "mod");
const chType Default(37, "default");
const chType Case(38, "case");
const chType If(39, "if");
const chType Else(40, "else");
const chType Abstract(41, "abstract");
const chType Public(42, "public");
const chType Private(43, "private");
const chType Override(44, "override");
const chType Const(45, "const");
const chType identifier(46, "identifier");
const chType constValue(47, "constValue");
const chType endmod(48, "endmod");
const chType nonTerminal(49, "nonTerminal");

const set<char> let {'a','b','c','d','e','f','g','h','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                         'A','B','C','D', 'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
const set<char> natNum {'1','2','3','4','5','6','7','8','9'};

static vector<chType> chTypeList {letter, natNumber, underline, midLeftPar, midRightPar, Plus, Minus, logAnd, logOr,
                           logNot, logXor, rightArrow, leftArrow, semicolon, multi, smallLeftPar,smallRightPar,
                           dollar, epsilon, dot, letter_E, letter_i, space, zero, Sign, colon, Equal, bigLeftPar, bigRightPar,
                           Define, Swich, Iwire, Owire, Oreg, Wire, Reg, Mod, Default, Case, If, Else,
                           Abstract, Public, Private, Override, Const, identifier, constValue, endmod};

const vector<string> keyword {"define", "switch", "iwire", "owire", "oreg", "wire", "reg", "mod", "endmod", "default",
                            "case", "if", "else"};

const vector<string> qualifier {"abstract", "public", "private", "override", "const"};

const vector<string> operators {"[", "]", "+", "-", "&", "|", "~", "^", ">>", "<<", ">>>", "(", ")", "*", "<", ">", "{", "}"};

const set<chType> terminalList {};

struct Tuple{
    private:
        int line;
        string str;
        string type;
        chType ch;
    public:
        Tuple();
        Tuple(int line, string str, string type) : line(line), str(str), type(type){};

        int getLine() { return this->line; }
        string getStr() { return this->str; }
        string getType() { return this->type; }
        chType getCh() { return this->ch; }

        void setLine(int line) { this->line = line; }
        void setStr(string str) { this->str = str; }
        void setType(string type) { this->type = type; }
        void setCh(chType ch) { this->ch = ch; }
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
                    if(this->index != right.index)
                        return false;
                    if(this->right.size() != right.right.size())
                        return false;
                    for(int i = 0;i < this->right.size();i++){
                        if(this->right[i] == right.right[i]){
                            if(this->right[i].id == 49 && (this->right[i].nonTerminal != right.right[i].nonTerminal))
                                return false;
                        }
                        else{
                            return false;
                        }
                    }
                    if(this->rightTerminal != right.rightTerminal)
                        return false;
                    if(this->left.nonTerminal != right.left.nonTerminal)
                        return false;
                    return true;
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
        void printClosure();

        Closure() {}
        bool operator==(const Closure &right) const{
            return (this->moveType == right.moveType) && (this->grammarList == right.grammarList);
        }
};

struct Stage{
    public:
        int index;
        int line;
        stack<chType> symbolStack;
        stack<int> stateStack;
        vector<chType> inputStr;
        string Action;
        int Goto;

        Stage();
        Stage(int index) : index(index) {};
};

struct Parser
{
    private:
        vector<Grammar> grammarList;
        vector<chType> nonTerminalList;
        vector<Closure> closureList;
        vector<Tuple> tupleList;
        vector<Stage> stageList;
        
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
        void constructTable();
        void dumpData(string address_output);
        void readToken(string address_token);
        void processStr();
};


#endif