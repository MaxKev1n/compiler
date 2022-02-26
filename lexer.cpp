#include <iostream>
#include "header.h"
using namespace std;

chType lexer::chtypeDetect(char ch){
    if(let.find(ch) != let.end()){
        return letter;
    }
    else if(num.find(ch) != let.end()){
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
        for(int i = 0;i < text.length();i++){
            if(curIndex == 1){
                curIndex = 0;
                res.push_back(t);
            }
            else{
                curIndex = nfa.transformState(curIndex, text[i]);
                t += text[i];
            }
        }
    }
    inf.close();
    for(int i = 0;i < res.size();i++){
        cout<<res[i]<<endl;
    }
}