#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "R_type.h"
#include "I-type.h"
#include "S_type.h"
#include "U-type.h"
#include "UJ-type.h"
#include "SB-type.h"
#include "InstructionDatabse.h"

using namespace std;


int binarySearch(string target)
{
    int left = 0, right = NUM_OF_INST, index = left + (right - left) / 2;
    while (instDatabase[index][0] != target)
    {
        index = left + (right - left) / 2;
        if (instDatabase[index][0] < target)
        {
            left = index + 1;
        }
        if (instDatabase[index][0] > target)
        {
            right = index - 1;
        }
    }

    return index;
}

void genJump()
{
    
}

int main()
{
    ifstream inputFile("input.txt", ios::in);
    ofstream outputFile("output.txt", ios::out);
    string inputStr, inputInst, inputReg[3], inputRR, inputLabel = "";
    stringstream inputSS;
    vector<Instruction*> instructions;

    //check if file open sucessful
    if (!inputFile)
    {
        cout << "Can not open file." << endl;
        return 1;
    }

    //input instructions from input.txt
    while (getline(inputFile, inputStr)) //using stringstream to process data
    {
        inputSS << inputStr;
        inputSS >> inputInst;

        //process label
        if (inputInst.find(':') != string::npos) //using symbol(:) to check if have label
        {
            size_t pos = inputInst.find(':'); //find (:) position
            inputInst.erase(pos); //earse (:)
            inputLabel = inputInst; // assign to inputLabel
            inputInst.clear(); //clear inputInst
            inputSS >> inputInst; //assign real instruction to inputInst
        }

        for (size_t i = 0; getline(inputSS, inputRR, ','); i++) //put input register to string array of inputReg
        {
            inputRR.erase(0, inputRR.find_first_not_of(" ")); //avoid space
            inputReg[i] = inputRR;
        }

        //use binary search to get index
        int index = binarySearch(inputInst);

        //put instructions to vector
        if (instDatabase[index][1] == "R") //R-type
        {
            R_type *Rtype = new R_type(index, inputReg, inputLabel);
            instructions.push_back(Rtype);
        }
        else if (instDatabase[index][1] == "I") //I-type
        {
            I_type *Itype = new I_type(index, inputReg, inputLabel);
            instructions.push_back(Itype);
        }
        else if (instDatabase[index][1] == "S") //S-type
        {
            S_type *Stype = new S_type(index, inputReg, inputLabel);
            instructions.push_back(Stype);
        }
        else if (instDatabase[index][1] == "U") //U-type
        {
            U_type *Utype = new U_type(index, inputReg, inputLabel);
            instructions.push_back(Utype);
        }
        else if (instDatabase[index][1] == "UJ") //UJ-type
        {
            UJ_type *UJtype = new UJ_type(index, inputReg, inputLabel);
            instructions.push_back(UJtype);
        }
        else if (instDatabase[index][1] == "SB") //SB-type
        {
            SB_type *SBtype = new SB_type(index, inputReg, inputLabel);
            instructions.push_back(SBtype);
        }

        //initialize stringstream
        inputSS.str("");
        inputSS.clear();
    }

    //generate jump value
    for (size_t i = 0; i < instructions.size(); i++)
    {
        if (instructions[i]->getTarget() != "") //check if have target to jump
        {
            for (size_t j = 0; j < instructions.size(); j++)
            {
                if (instructions[i]->getTarget() == instructions[j]->getLabel()) //jump to where
                {
                    instructions[i]->setJump(j - i); //set jump value
                    break;
                }
            }
        }
    }
    
    //conversion instruction to machine code
    //output machin code to output.txt
    for (size_t i = 0; i < instructions.size(); i++)
    {
        instructions[i]->conversion();
        instructions[i]->output(outputFile);
    }

    cout << "Compiled successfully." << endl;
    inputFile.close();
    outputFile.close();
}