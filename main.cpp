#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cctype>

void writeToFile(std::vector<std::string> in) {
    std::ofstream outputFile("plafile.txt", std::ios::trunc);
    if (!outputFile) {
        std::cout << "Error: Cannot open file for writing." << std::endl;
        return;
    }

    for(int i = 0; i < in.size(); i++) {
        outputFile << in[i] << std::endl; 
    }

    outputFile.close();
    std::cout << "Text written to file successfully." << std::endl;
}

std::string getNextValue() {
    int input;
    std::cin >> std::hex >> input;
    std::bitset<8> value(input);
    return value.to_string();
}

std::string getCode(std::string file) {
    std::ifstream codeIn(file);
    std::string codeOut;

    if (codeIn.is_open()) {
        std::stringstream buffer;
        buffer << codeIn.rdbuf();
        codeOut = buffer.str();
        
        codeIn.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }

    return codeOut;
}

std::vector<std::string> compile(std::vector<std::string> code) {
    std::vector<std::string> out;
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
    std::string value;
};

std::vector<token> tokenize(std::string code) {
    std::vector<token> out;
    for (int i = 0; i < code.size(); i++) {
        if (isspace(code[i])) {i++;}
        std::string atoken;
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

bool syntaxCheck(std::vector<token> tokens) {
    int cycle = 0;
    std::vector<token> line;
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

    void addLine(std::vector<Micro> instructions) {
        data.push_back(instructions);
    }

    std::vector<std::vector<Micro>> getData() {
        return data;
    }
private:
    char opcode;
    std::vector<std::vector<Micro>> data;
    std::string comment;
};

Micro stomic(std::string s) {
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

    char hexValue = std::stoi(hexString, nullptr, 16);

    return hexValue;
}

std::vector<std::string> translate(std::vector<token> code) {
    std::vector<std::string> pla;
    std::vector<std::vector<token>> lines;
    
    
    std::vector<token> line;
        
    for (int i = 0; i < code.size(); i++) { //splits the tokens into lines based on ";"
        if ((code[i].type == COMMENT) || (code[i].type == COMMA)) { //ignore comments and commas
        }else if (code[i].type == SEMICOLON) {
            lines.push_back(line);
            line.clear();
        } else {
            line.push_back(code[i]);
        }
    }


    for (int i = 0; i < lines.size(); i++) {

        Operation anop;

        anop.setCode(hexStringToChar(lines[i][1].value)); //sets anop's opcode to the hex value of the opcode token.

        i++;

        while (bool notDone = true) {
            std::vector<Micro> aline;
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
            std::vector<Micro> instructs;
            char opcode;
            

        };

        std::vector<std::vector<Micro>> opdata = anop.getData();
        std::vector<MicroLine> microlines;
        for (int j = 0; j < opdata.size(); j++) { //fills microlines with micro lines. Each loop is a new line.
            MicroLine currentline;
            currentline.opcode = anop.getCode();
            currentline.instructs = anop.getData()[j];
            currentline.cycle = j;
            microlines.push_back(currentline);
        }

        //need to convert each MiroLine from microlines into a string of pla data and push back the pla. After that, I've finished*!
        //*I still need to implement flags and comments on the pla file.

        for (int j = 0; j < microlines.size(); j++) {
            std::string currentline = "xxx000000000000 000000000000000000";
            std::string opcode = currentline.substr(3, 8);
            std::string clock = currentline.substr(11, 4);
            std::string instructions = currentline.substr(16, 18);

            opcode = std::bitset<8>(microlines[j].opcode).to_string(); //sets opcode to a binary string of the opcode
            clock = std::bitset<4>(i).to_string();
            for (int k = 0; k < microlines[j].instructs.size(); k++) {
                opcode.replace(microlines[j].instructs[k], 1, "1");
            }
        }
        
    }
    
    return pla;
}

int main() {

    
    std::string in;
    std::vector<std::string> out;

    in = getCode("input.zmac");

    std::vector<token> stuff = tokenize(in);

    if (syntaxCheck(stuff)) {
        std::vector<std::string> outData = translate(stuff);

        writeToFile(outData);

        std::cout << "finished!" << std::endl;
    } else {
        std::cout << "syntax error" << std::endl;
    }
    
    return 0;
}
