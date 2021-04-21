#ifndef S_TYPE_H
#define S_TYPE_H

#include <iostream>
#include <string>
#include "Instruction.h"
#include "InstructionDatabse.h"

using namespace std;

class S_type : public Instruction
{
private:
    string imm11_5;
    string rs2;
    string rs1;
    string funct3;
    string imm4_0;
    string opcode;

    void genImm11_5();
    void genRs2();
    void genRs1();
    void genFunct3();
    void genImm4_0();
    void genOpcode();
    void seperate();

public:
    S_type(int inputIndex, string *inputReg, string inputLabel);
    ~S_type();

    void conversion();
    void output(ofstream &outputFile);
};

S_type::S_type(int inputIndex, string *inputReg, string inputLabel) : Instruction(inputIndex, inputReg, inputLabel)
{
}

S_type::~S_type()
{
}

void S_type::conversion()
{
    seperate();
    genImm11_5();
    genRs2();
    genRs1();
    genFunct3();
    genImm4_0();
    genOpcode();
}

void S_type::output(ofstream &outputFile)
{
    outputFile << imm11_5 << rs2 << rs1 << funct3 << imm4_0 << opcode << endl;
}

void S_type::genImm11_5()
{
    Reg[2] = bitset<12>(stoi(Reg[2])).to_string(); //change decimal to binary
    imm11_5.assign(Reg[2], 0, 7);
}

void S_type::genRs2()
{
    if (Reg[0][0] == 'x')
    {
        Reg[0].erase(0, 1);
    }
    rs2 = bitset<5>(stoi(Reg[0])).to_string(); //change decimal to binary
}

void S_type::genRs1()
{
    Reg[1].erase(0, 1);
    rs1 = bitset<5>(stoi(Reg[1])).to_string(); //change decimal to binary
}

void S_type::genFunct3()
{
    funct3 = instDatabase[index][2];
}

void S_type::genImm4_0()
{
    imm4_0.assign(Reg[2], 7, 5);
}

void S_type::genOpcode()
{
    opcode = instDatabase[index][3];
}

void S_type::seperate()
{
    Reg[2] = Reg[2].assign(Reg[1], 0, Reg[1].find("(", 0));
    Reg[1].erase(0, Reg[2].length() + 1);
    Reg[1].erase(Reg[1].begin() + Reg[1].find(')'), Reg[1].end());
}

#endif