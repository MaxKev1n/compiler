#include "header.h"

using namespace std;

chType lexer::chtypeDetect(char ch){
    if(let.find(ch) != let.end()){
        return letter;
    }
    else if(num.find(ch) != num.end()){
        return number;
    }
    else if(natNum.find(ch) != natNum.end()){
        return natNumber;
    }
    else{
        switch (ch)
        {
        case 'E':{
            return letter_E;
            break;
        }
        case 'i':{
            return letter_i;
            break;
        }
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
        case '.':{
            return dot;
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

    DFA dfa(nfa);
    dfa.printDFA();

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
        }
    }
    inf.close();
    for(int i = 0;i < res.size();i++){
        cout<<res[i]<<endl;
    }
}
