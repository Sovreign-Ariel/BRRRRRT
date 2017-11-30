#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

void readOpcode(string opcode);

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
  else if (opcode == "CEL")
    ceiling();
  else if (opcode == "FLR")
    floor();
  else if (opcode == "RND")
    round();
  else
    cout << "Invalid operation." << endl;
  return;
}
