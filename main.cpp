#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cctype>
using namespace std;

void writeToFile(vector<string> in) {
    ofstream outputFile("plafile.txt", ios::trunc);
    if (!outputFile) {
        cout << "Error: Cannot open file for writing." << endl;
        return;
    }

    for(int i = 0; i < in.size(); i++) {
        outputFile << in[i] << endl; 
    }

    outputFile.close();
    cout << "Text written to file successfully." << endl;
}

string getNextValue() {
    int input;
    cin >> hex >> input;
    bitset<8> value(input);
    return value.to_string();
}

string getCode(string file) {
    ifstream codeIn(file);
    string codeOut;

    if (codeIn.is_open()) {
        stringstream buffer;
        buffer << codeIn.rdbuf();
        codeOut = buffer.str();
        
        codeIn.close();
    } else {
        cout << "Unable to open file" << endl;
    }

    return codeOut;
}

vector<string> compile(vector<string> code) {
    vector<string> out;
    int i = 1;
    
    return out;
}

bool isAlphaNumeric(char ch) {
    return (std::isalpha(ch) || std::isdigit(ch));
}

enum tokenType {
    KEYWORD,
    COMMA,
    SEMICOLON,
    MICROINS,
    COMMENT,
    RESET_MACRO
};

struct token {
    tokenType type;
    string value;
};

vector<token> tokenize(string code) {
    vector<token> out;
    for (int i = 0; i < code.size(); i++) {
        if (isspace(code[i])) {i++;}
        string atoken;
        bool notDone = true;

        do {
            atoken.push_back(code[i]);
            if (isAlphaNumeric(code[i + 1])) {
                i++;
            } else {
                notDone = false;
            }
        } while (notDone);
        
        if (atoken == "op") {
            out.push_back({KEYWORD, atoken});
        } else if(atoken == ",") {
            out.push_back({COMMA, atoken});
        } else if(atoken == ";") {
            out.push_back({SEMICOLON, atoken});
        } else if(atoken[0] == '#') {
            out.push_back({COMMENT, atoken});
        } else if(atoken == "reset") {
            out.push_back({RESET_MACRO, atoken});
        } else {
            out.push_back({MICROINS, atoken});
        }
    
    }
        
    
    return out;
}

bool syntaxCheck(vector<token> tokens) {
    int cycle = 0;
    vector<token> line;
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i].type == COMMENT) { //ignore comments
            
        } else {
            
        }
    }
    return true;
}

enum Micro {
    ae,
    ac,
    ei,
    eo
};

class Operation {
public:
    
private:
    char opcode;
    vector<vector<Micro>> data;
};

vector<string> translate(vector<token> code) {
    vector<string> pla;
    vector<vector<token>> lines;
    
    
    vector<token> line;
        
    for (int i; i < code.size(); i++) {
        if (code[i].type == COMMENT) { //ignore comments
        }else if (code[i].type == SEMICOLON) {
            lines.push_back(line);
            line.clear();
        } else {
            line.push_back(code[i]);
        }
    }

    int opNumber;
    int current = 0;
    while(bool notDone = true) {

        
        
    }
    
    return pla;
}

int main() {

    
    string in;
    vector<string> out;

    in = getCode("input.zmac");

    vector<token> stuff = tokenize(in);

    if (syntaxCheck(stuff)) {
        vector<string> outData = translate(stuff);

        writeToFile(outData);

        cout << "finished!" << endl;
    } else {
        cout << "syntax error" << endl;
    }
    
    return 0;
}
