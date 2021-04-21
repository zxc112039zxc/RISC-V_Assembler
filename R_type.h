#ifndef R_TYPE_H
#define R_TYPE_H

#include <iostream>
#include <string>
#include "Instruction.h"
#include "InstructionDatabse.h"

using namespace std;

class R_type : public Instruction
{
private:
    string funct5;
    string funct2;
    string rs2;
    string rs1;
    string funct3;
    string rd;
    string opcode;

    void genFunct5();
    void genRs2();
    void genRs1();
    void genFunct3();
    void genRd();
    void genOpcode();

public:
    R_type(int inputIndex, string *inputReg, string inputLabel);
    ~R_type();

    void conversion();
    void output(ofstream &outputFile);
};

R_type::R_type(int inputIndex, string *inputReg, string inputLabel) : Instruction(inputIndex, inputReg, inputLabel)
{
    funct2 = "00";
}

R_type::~R_type()
{
}

void R_type::conversion()
{
    genFunct5();
    genRs2();
    genRs1();
    genFunct3();
    genRd();
    genOpcode();
}

void R_type::output(ofstream &outputFile)
{
    outputFile << funct5 << funct2 << rs2 << rs1 << funct3 << rd << opcode << endl;
}

void R_type::genFunct5()
{
    if (index == 29 || index == 30 || index == 33) //sub & sra & srai
    {
        funct5 = "01000";
    }
    else
    {
        funct5 = "00000";
    }
}

void R_type::genRs2()
{
    if (Reg[2][0] == 'x')
    {
        Reg[2].erase(0, 1);
    }
    rs2 = bitset<5>(stoi(Reg[2])).to_string(); //change decimal to binary
}

void R_type::genRs1()
{
    Reg[1].erase(0, 1);
    rs1 = bitset<5>(stoi(Reg[1])).to_string(); //change decimal to binary
}

void R_type::genFunct3()
{
    funct3 = instDatabase[index][2];
}

void R_type::genRd()
{
    Reg[0].erase(0, 1);
    rd = bitset<5>(stoi(Reg[0])).to_string(); //change decimal to binary
}

void R_type::genOpcode()
{
    opcode = instDatabase[index][3];
}

#endif