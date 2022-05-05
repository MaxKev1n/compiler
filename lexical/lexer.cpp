#include "header.h"

using namespace std;

chType lexer::chtypeDetect(char ch){
    if(let.find(ch) != let.end()){
        return letter;
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
        case ' ':{
            return space;
            break;
        }
        case '\n':{
            return space;
            break;
        }
        case ',':{
            return semicolon;
            break;
        }
        case '0':{
            return zero;
            break;
        }
        case ':':{
            return colon;
            break;
        }
        case '=':{
            return Equal;
            break;
        }
        case '{':{
            return bigLeftPar;
            break;
        }
        case '}':{
            return bigRightPar;
            break;
        }
        default:
            return epsilon;
            break;
        }
    }
}

string lexer::typeRecognition(string str){
    for(set<string>::iterator iter = keyword.begin(); iter != keyword.end(); ++iter){
        if(str == *iter)
            return "keyword";
    }
    for(set<string>::iterator iter = qualifier.begin(); iter != qualifier.end(); ++iter){
        if(str == *iter)
            return "qualifier";
    }
    for(set<string>::iterator iter = operators.begin(); iter != operators.end(); ++iter){
        if(str == *iter)
            return "operators";
    }
    if(str[0] >= '0' & str[0] <= '9')
        return "constant";
    return "identifier";
}

void lexer::run(string address_grammar, string address_txt, string address_output){
    NFA nfa;
    nfa.readGrammar(address_grammar);
    nfa.epClosure();
    //nfa.printEpClosure();

    DFA dfa(nfa);
    //dfa.printDFA();
    dfa.dumpDFA(address_output);

    vector<Tuple> res;
    string text;
    ifstream inf;
    inf.open(address_txt);
    int line = 1;
    int errorCount = 0;
    while(getline(inf, text)){
        text += '\n';
        string t = "";
        int curIndex = 0;
        for(int i = 0;i <= text.length();i++){
            curIndex = dfa.transformState(curIndex, text[i]);
            if(curIndex == 7){
                string type = typeRecognition(t);
                Tuple tuple(line, t, type);
                res.push_back(tuple);

                curIndex = 0;
                t = "";
            }else if(curIndex == -1 && (text[i] == ' ' || text[i] == '\n')){
                if(int(t[0]) != 0){
                    cout<<"ERROR in line "<<line<<", "<<t<<endl;
                    errorCount++;
                }
                curIndex = 0;
                t = "";
            }else if(curIndex == -1){
                curIndex = -1;
                t += text[i];
            }else{
                t += text[i];
            }
        }
        line++;
    }
    inf.close();

    if(errorCount != 0){
        cout<<"Exist "<<errorCount<<" wrong!"<<endl;
    }
    else{
        cout<<"Lexical Analyze Successfully!"<<endl;
    }
    cout<<string(40, '-')<<endl<<"dumping token!"<<endl<<string(40, '-')<<endl;

    string dir = address_output;
    if((access(dir.c_str(), 0) == -1)){
        mkdir(dir.c_str(), S_IRWXU | S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
    }
    if((access((dir + "/lexical").c_str(), 0) == -1)){
        mkdir((dir + "/lexical").c_str(), S_IRWXU | S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
    }

    std::ofstream ofs;
    ofs.open(address_output+"/lexical/token.txt");
    std::stringstream ss;
    int i;
    for (i = 0;i < res.size() - 1;i++) {
        ss<<res[i].line<<" "<<res[i].type<<" "<<res[i].str<<endl;
    }
    ss<<res[i].line<<" "<<res[i].type<<" "<<res[i].str;
    ofs << ss.rdbuf();
    ofs.close();
}
