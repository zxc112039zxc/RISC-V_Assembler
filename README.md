# RISC-V_Assembler for RV32I

## Input parameter:
    1. Input file address ex: /Users/steve/Desktop/projects/Assembler/input.txt
    2. Output file address ex: /Users/steve/Desktop/projects/Assembler/output.txt
## Output:
    Compiled successfully.
## Input file sample:
        add x2,x2,x23
        addi x24,x24,2
        bne x24,x23,L2
        sw x27,0(x10)
        beq x0,x0,L1
    L2: sw x1,0(x2)
    L1: addi x24,x24,1
## Output file sample:
    00000001011100010000000100110011
    00000000001011000000110000010011
    00000001011111000001011001100011
    00000001101101010010000000100011
    00000000000000000000010001100011
    00000000000100010010000000100011
    00000000000111000000110000010011
    
