#ifndef SB_TYPE_H
#define SB_TYPE_H

#include <iostream>
#include <string>
#include "Instruction.h"
#include "InstructionDatabse.h"

using namespace std;

class SB_type : public Instruction
{
private:
    string imm12_10_5;
    string rs2;
    string rs1;
    string funct3;
    string imm4_1_11;
    string opcode;

    void genImm12_10_5();
    void genRs2();
    void genRs1();
    void genFunct3();
    void genImm4_1_11();
    void genOpcode();

public:
    SB_type(int inputIndex, string *inputReg, string inputLabel);
    ~SB_type();

    void conversion();
    void output(ofstream &outputFile);
};

SB_type::SB_type(int inputIndex, string *inputReg, string inputLabel) : Instruction(inputIndex, inputReg, inputLabel)
{
    target = inputReg[2];
}

SB_type::~SB_type()
{
}

void SB_type::conversion()
{
    genImm12_10_5();
    genRs2();
    genRs1();
    genFunct3();
    genImm4_1_11();
    genOpcode();
}

void SB_type::output(ofstream &outputFile)
{
    outputFile << imm12_10_5 << rs2 << rs1 << funct3 << imm4_1_11 << opcode << endl;
}

void SB_type::genImm12_10_5()
{
    Reg[2] = bitset<13>(jump * 4).to_string(); //change decimal to binary
    imm12_10_5.assign(Reg[2], 0, 1);
    imm12_10_5.append(Reg[2], 2, 6);
}

void SB_type::genRs2()
{
    if (Reg[1][0] == 'x')
    {
        Reg[1].erase(0, 1);
    }
    rs2 = bitset<5>(stoi(Reg[1])).to_string(); //change decimal to binary
}

void SB_type::genRs1()
{
    if (Reg[0][0] == 'x')
    {
        Reg[0].erase(0, 1);
    }
    rs1 = bitset<5>(stoi(Reg[0])).to_string(); //change decimal to binary
}

void SB_type::genFunct3()
{
    funct3 = instDatabase[index][2];
}

void SB_type::genImm4_1_11()
{
    imm4_1_11.assign(Reg[2], 8, 4);
    imm4_1_11.append(Reg[2], 1, 1);
}

void SB_type::genOpcode()
{
    opcode = instDatabase[index][3];
}

#endif