#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <fstream>

using namespace std;

class Instruction
{
protected:
    int index;
    int jump;
    string Reg[3];
    string label;
    string target;
    Instruction(int inputIndex, string *inputReg, string inputLabel);

public:
    Instruction();
    virtual ~Instruction();

    virtual void conversion(){};
    virtual void output(ofstream &outputFile){};

    string getLabel();
    string getTarget();
    void setJump(int inputJump);
};

Instruction::Instruction(int inputIndex, string *inputReg, string inputLabel)
{
    index = inputIndex;
    for (size_t i = 0; i < 3; i++)
    {
        Reg[i] = inputReg[i];
    }
    label = inputLabel;
    jump = 0;
    target = "";
}

Instruction::Instruction()
{
}

Instruction::~Instruction()
{
}

string Instruction::getLabel()
{
    return label;
}

string Instruction::getTarget()
{
    return target;
}

void Instruction::setJump(int inputJump)
{
    jump = inputJump;
}

#endif