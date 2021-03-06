#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

int reg[7] = {0, 0, 0, 0, 0, 0, 0};

void readOpcode(string opcode);
void store(int value, int reg_num);
void load(string reg_num);
void halt();
void clear();
void input(int value, int reg_num);
void output();
void jump();
void skip();
void addition(int value);
void subtraction(int value);

int main()
{

}

void readOpcode(string opcode)
{
  if (opcode == "STO")
    store();
  else if (opcode == "LOD")
    load();
  else if (opcode == "HLT")
    halt();
  else if (opcode == "CLR")
    clear();
  else if (opcode == "INP")
    input();
  else if (opcode == "OUP")
    output();
  else if (opcode == "JMP")
    jump();
  else if (opcode == "SKP")
    skip();
  else if (opcode == "ADD")
    addition();
  else if (opcode == "SUB")
    subtraction();
  else if (opcode == "MUL")
    multiplication();
  else if (opcode == "DIV")
    division();
  else if (opcode == "MOD")
    modulus();
  else if (opcode == "RND")
    brrrrrt_round();
  else
    cout << "Invalid operation." << endl;
  return;
}

void store(int value, int reg_num)
{
  if (reg >= 0 && <= 7)
    reg[reg_num] = value;
  else
   cout << "Invalid operation in function STORE\n\n";
}

void load(int reg_num)
{
  if (reg_num >= 0 && reg_num <= 7)
    reg0 = reg[reg_num];
  else
   cout << "Invalid operation in function LOAD\n\n";
}

void halt()
{
  exit(0);
}

void clear()
{
  reg[0] = 0;
}

void input(int value. int reg_num)
{
  if (reg_num >= 0 && reg_num <= 7)
    reg[reg_num] = value;
  else
   cout << "Invalid operation in function INPUT\n\n";
}

void output()
{
  cout << reg[0] << endl; << endl;
}

void jump() //implement a vector to keep track of the program counter
{

}

void skip() //implement a vector to keep track of the program counter
{

}

void addition(int value)
{
  reg[0] = reg[0] + value;
}

void subtraction(int value)
{
  reg[0] = reg[0] - value;
}
