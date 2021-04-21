#ifndef UJ_TYPE_H
#define UJ_TYPE_H

#include <iostream>
#include <string>
#include "Instruction.h"
#include "InstructionDatabse.h"

using namespace std;

class UJ_type : public Instruction
{
private:
    string imm20_10_1_11_19_22;
    string rd;
    string opcode;

    void genImm20_10_1_11_19_22();
    void genRd();
    void genOpcode();

public:
    UJ_type(int inputIndex, string *inputReg, string inputLabel);
    ~UJ_type();

    void conversion();
    void output(ofstream &outputFile);
};

UJ_type::UJ_type(int inputIndex, string *inputReg, string inputLabel) : Instruction(inputIndex, inputReg, inputLabel)
{
}

UJ_type::~UJ_type()
{
}

void UJ_type::conversion()
{
    genImm20_10_1_11_19_22();
    genRd();
    genOpcode();
}

void UJ_type::output(ofstream &outputFile)
{
    outputFile << imm20_10_1_11_19_22 << rd << opcode << endl;
}

void UJ_type::genImm20_10_1_11_19_22()
{
    Reg[1] = bitset<21>(stoi(Reg[1])).to_string(); //change decimal to binary
    imm20_10_1_11_19_22.assign(Reg[1], 0, 1);
    imm20_10_1_11_19_22.append(Reg[1], 10, 10);
    imm20_10_1_11_19_22.append(Reg[1], 9, 1);
    imm20_10_1_11_19_22.append(Reg[1], 1, 8);
}

void UJ_type::genRd()
{
    if (Reg[0][0] == 'x')
    {
        Reg[0].erase(0, 1);
    }
    rd = bitset<5>(stoi(Reg[0])).to_string();
}

void UJ_type::genOpcode()
{
    opcode = instDatabase[index][3];
}

#endif