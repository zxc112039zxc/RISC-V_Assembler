#ifndef I_TYPE_H
#define I_TYPE_H

#include <iostream>
#include <string>
#include "Instruction.h"
#include "InstructionDatabse.h"

using namespace std;

class I_type : public Instruction
{
private:
    string imm11_0;
    string rs1;
    string funct3;
    string rd;
    string opcode;

    void genImm11_0();
    void genRs1();
    void genFunct3();
    void genRd();
    void genOpcode();
    void seperate();

public:
    I_type(int inputIndex, string *inputReg, string inputLabel);
    ~I_type();

    void conversion();
    void output(ofstream &outputFile);
};

I_type::I_type(int inputIndex, string *inputReg, string inputLabel) : Instruction(inputIndex, inputReg, inputLabel)
{
}

I_type::~I_type()
{
}

void I_type::conversion()
{
    genImm11_0();
    genRs1();
    genFunct3();
    genRd();
    genOpcode();
}

void I_type::output(ofstream &outputFile)
{
    outputFile << imm11_0 << rs1 << funct3 << rd << opcode << endl;
}

void I_type::genImm11_0()
{
    if ((index >= 13 && index <= 16) || index == 18)
    {
        seperate();
    }

    imm11_0 = bitset<12>(stoi(Reg[2])).to_string(); //change decimal to binary
}

void I_type::genRs1()
{
    Reg[1].erase(0, 1);
    rs1 = bitset<5>(stoi(Reg[1])).to_string(); //change decimal to binary
}

void I_type::genFunct3()
{
    funct3 = instDatabase[index][2];
}

void I_type::genRd()
{
    Reg[0].erase(0, 1);
    rd = bitset<5>(stoi(Reg[0])).to_string(); //change decimal to binary
}

void I_type::genOpcode()
{
    opcode = instDatabase[index][3];
}

void I_type::seperate()
{
    Reg[2] = Reg[2].assign(Reg[1], 0, Reg[1].find("(", 0));
    Reg[1].erase(0, Reg[2].length() + 1);
    Reg[1].erase(Reg[1].begin() + Reg[1].find(')'), Reg[1].end());
}

#endif