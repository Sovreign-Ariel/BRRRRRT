#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int binary_to_decimal(string bin);



int main()
{
  // Setting up variables to store data.

  int reg[8] = {0,0,0,0,0,0,0,0};
  int memory_array[256];
  vector<string> program_counter;
  string instruction, opcode;
  int dat_reg;

  // Opening file to store data in the program_counter.

  ifstream fin;
  fin.open("translated.txt");


  if (fin.fail())
  {
    cout << "Error\n\n";
    exit(0);
  }
  while(true)
  {
    if (fin.eof())
      break;
    else
    {
      getline(fin, instruction);
      program_counter.push_back(instruction);
    }
  }
  fin.close();

  // Checking the binary values in the program_counter to determine which operations are to be used.

  for (int pc = 0; pc < program_counter.size(); pc++)
  {
    instruction = program_counter[pc];
    opcode = instruction.substr(0, 5);
    if (opcode == "00001") // STO
    {
      dat_reg = binary_to_decimal(instruction.substr(13, 3));
      reg[dat_reg] = reg[0];
    }
    else if (opcode == "00010") // STI
    {
      dat_reg = binary_to_decimal(instruction.substr(13, 3));
      if (dat_reg > 7 || dat_reg < 0 || reg[dat_reg] > 255 || reg[dat_reg] < 0)
        cout << "Error: invalid indirect address in STI.\n\n";
      else
          memory_array[reg[dat_reg]] = reg[0];
    }
    else if (opcode == "00011") // LOD
    {
      dat_reg = binary_to_decimal(instruction.substr(13, 3));
      reg[0] = reg[dat_reg];
    }
    else if (opcode == "00100") // LDI
    {
      dat_reg = binary_to_decimal(instruction.substr(13, 3));
      if (dat_reg > 7 || dat_reg < 0 || reg[dat_reg] > 255 || reg[dat_reg] < 0)
        cout << "Error: invalid indirect address.\n\n";
      else
        reg[0] = memory_array[reg[dat_reg]];
    }
    else if (opcode == "00101") // HLT
    {
      exit(0);
    }
    else if (opcode == "00110") // CLR
    {
      for (int i = 0; i < 8; i++)
        reg[i] = 0;
    }
    else if (opcode == "00111") // INP
    {
      cout << "Please enter an integer value on the keyboard." << endl;
      cin  >> dat_reg;
      cout << endl;
      reg[0] = dat_reg;
    }
    else if (opcode == "01000") // OUP
    {
      cout << reg[0] << endl;
    }
    else if (opcode == "01001") // JMP
    {
      dat_reg = binary_to_decimal(instruction.substr(5, 8));
      pc = pc - (dat_reg + 1);
    }
    else if (opcode == "01010") // SKP
    {
      dat_reg = binary_to_decimal(instruction.substr(5, 8));
      if (dat_reg == 0)
      {
        if (reg[0] == 0)
          pc++;
      }
      else if (dat_reg == 1)
      {
        if (reg[0] > 0)
          pc++;
      }
      else if (dat_reg == 2)
      {
        if (reg[0] < 0)
          pc++;
      }
    }
    else if (opcode == "01011") // ADD
    {
      dat_reg = binary_to_decimal(instruction.substr(5, 8));
      reg[0] = reg[0] + dat_reg;
    }
    else if (opcode == "01100") // SUB
    {
      dat_reg = binary_to_decimal(instruction.substr(5, 8));
      reg[0] = reg[0] - dat_reg;
    }
    else if (opcode == "01101") // MUL
    {
      dat_reg = binary_to_decimal(instruction.substr(5, 8));
      reg[0] = reg[0] * dat_reg;
    }
    else if (opcode == "01110") // DIV
    {
      dat_reg = binary_to_decimal(instruction.substr(5, 8));
      reg[0] = reg[0] / dat_reg;
    }
    else if (opcode == "01111") // MOD
    {
      dat_reg = binary_to_decimal(instruction.substr(5, 8));
      reg[0] = reg[0] % dat_reg;
    }
    else if (opcode == "10000") // RND
    {
      if ((reg[0]%10) >= 5)
        reg[0] = reg[0] + (10 - (reg[0]%10));
      else
        reg[0] = reg[0] - (reg[0]%10);
    }
    else if (opcode == "10001") // ADI
    {
      dat_reg = binary_to_decimal(instruction.substr(13, 3));
      if (dat_reg > 7 || dat_reg < 0 || reg[dat_reg] > 255 || reg[dat_reg] < 0)
        cout << "Error: invalid indirect address in ADI.\n\n";
      else
        reg[0] = reg[0] + memory_array[reg[dat_reg]];
    }
    else if (opcode == "10010") // ADI
    {
      dat_reg = binary_to_decimal(instruction.substr(13, 3));
      if (dat_reg > 7 || dat_reg < 0 || reg[dat_reg] > 255 || reg[dat_reg] < 0)
        cout << "Error: invalid indirect address.\n\n";
      else
        reg[0] = reg[0] - memory_array[reg[dat_reg]];
    }
  }


  return 0;

}



int binary_to_decimal(string bin)
{
  int num = 0;
  for (int i = 0; i < bin.length(); i++)
  {
    if (bin[i] == '1')
      {
        num += pow(2, bin.length() - 1 - i);
      }
  }
  return num;
}
