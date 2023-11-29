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
        }         //one thing to note is that the opcode is defined as a microins. This doesn't matter because the opcode handling doesn't care about type.
    
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
    return true;     //sytax checking is yet to be implemented, as it's not exactly necessary.
}

enum Micro {
    res,
    ai,
    ao,
    bi,
    bo,
    ci,
    co,
    di,
    _do,
    adi,
    adc,
    ei,
    eo,
    ioi,
    ioo,
    opi,
    alu1,
    alu2,
    err
};

class Operation {
public:
    void setCode(char opcode) {
        this->opcode = opcode;
    }

    char getCode() {
        return opcode;
    }

    void addLine(vector<Micro> instructions) {
        data.push_back(instructions);
    }

    vector<vector<Micro>> getData() {
        return data;
    }
private:
    char opcode;
    vector<vector<Micro>> data;
    string comment;
};

Micro stomic(string s) {
    if (s == "res") {
        return res;
    } else if (s == "ai") {
        return ai;
    } else if (s == "ao") {
        return ao;
    } else if (s == "bi") {
        return bi;
    } else if (s == "bo") {
        return bo;
    } else if (s == "ci") {
        return ci;
    } else if (s == "co") {
        return co;
    } else if (s == "di") {
        return di;
    } else if (s == "do") {
        return _do;
    } else if (s == "adi") {
        return adi;
    } else if (s == "adc") {
        return adc;
    } else if (s == "ei") {
        return ei;
    } else if (s == "eo") {
        return eo;
    } else if (s == "ioi") {
        return ioi;
    } else if (s == "ioo") {
        return ioo;
    } else if (s == "opi") {
        return opi;
    } else if (s == "alu1") {
        return alu1;
    } else if (s == "alu2") {
        return alu2;
    } else {
        return err;
    }
}

char hexStringToChar(const std::string& hexString) {
    int hexValue = std::stoi(hexString, nullptr, 16);

    char charValue = static_cast<char>(hexValue);

    return charValue;
}

vector<string> translate(vector<token> code) {
    vector<string> pla;
    vector<vector<token>> lines;
    
    
    vector<token> line;
        
    for (int i; i < code.size(); i++) { //splits the tokens into lines based on ";"
        if ((code[i].type == COMMENT) || (code[i].type == COMMA)) { //ignore comments and commas
        }else if (code[i].type == SEMICOLON) {
            lines.push_back(line);
            line.clear();
        } else {
            line.push_back(code[i]);
        }
    }


    for (int i; i < lines.size(); i++) {

        Operation anop;

        anop.setCode(hexStringToChar(lines[i][2].value)); //sets anop's opcode to the hex value of the opcode token.

        i++;

        while (bool notDone = true) {
            vector<Micro> aline;
            if (lines[i][1].type == KEYWORD) {
                i--;  //decrement so that when the for loop increments, it's still at the op line
                notDone = false;
            } else {
                for (int j; j < lines[i].size(); j++) {
                    aline.push_back(stomic(lines[i][j].value));
                }
                anop.addLine(aline);

                if ((i + 1) < lines.size()) {i++;} else {notDone = false;}
            }
        }

        struct MicroLine {
            char cycle;
            vector<Micro> instructs;
            char opcode;
            

        };

        vector<vector<Micro>> opdata = anop.getData();
        vector<MicroLine> microlines;
        for (int i; i < opdata.size(); i++) { //fills microlines with micro lines. Each loop is a new line.
            MicroLine currentline;
            currentline.opcode = anop.getCode();
            currentline.instructs = anop.getData()[i];
            currentline.cycle = i;
            microlines.push_back(currentline);
        }

        //need to convert each MiroLine from microlines into a string of pla data and push back the pla. After that, I've finished*!
        //*I still need to implement flags and comments on the pla file.

        for (int i; i < microlines.size(); i++) {
            string currentline = "xxx000000000000 000000000000000000";
            string opcode = currentline.substr(3, 8);
            string clock = currentline.substr(11, 4);
            string instructions = currentline.substr(16, 18);

            opcode = bitset<8>(microlines[i].opcode).to_string(); //sets opcode to a binary string of the opcode
            clock = bitset<4>(i).to_string();
            for (int j; j < microlines[i].instructs.size(); j++) {
                //turn the proper bit of instructions.
            }
        }
        
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
