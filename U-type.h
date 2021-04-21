#ifndef U_TYPE_H
#define U_TYPE_H

#include <iostream>
#include <string>
#include "Instruction.h"
#include "InstructionDatabse.h"

using namespace std;

class U_type : public Instruction
{
private:
    string imm31_12;
    string rd;
    string opcode;

    void genImm31_12();
    void genRd();
    void genOpcode();

public:
    U_type(int inputIndex, string *inputReg, string inputLabel);
    ~U_type();

    void conversion();
    void output(ofstream &outputFile);
};

U_type::U_type(int inputIndex, string *inputReg, string inputLabel) : Instruction(inputIndex, inputReg, inputLabel)
{
}

U_type::~U_type()
{
}

void U_type::conversion()
{
    genImm31_12();
    genRd();
    genOpcode();
}

void U_type::output(ofstream &outputFile)
{
    outputFile << imm31_12 << rd << opcode << endl;
}

void U_type::genImm31_12()
{
    imm31_12 = bitset<20>(stoi(Reg[1])).to_string(); //change decimal to binary
}

void U_type::genRd()
{
    if (Reg[0][0] == 'x')
    {
        Reg[0].erase(0, 1);
    }
    rd = bitset<5>(stoi(Reg[0])).to_string(); //change decimal to binary
}

void U_type::genOpcode()
{
    opcode = instDatabase[index][3];
}

#endif