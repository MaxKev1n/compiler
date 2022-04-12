#include "header.h"
#include "lexer.h"
#include "convert.h"
using namespace std;

int main(int argc,char *argv[]){
    lexer l;
    string address_grammar;
    string address_txt;
    string address_output;
    address_grammar = argv[1];
    address_txt =argv[2];
    address_output = argv[3];
    l.run(address_grammar, address_txt, address_output);
    return 0;
}
