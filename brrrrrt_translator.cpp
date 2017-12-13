#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

string readOpcode(string opcode, int vr);
string decimal_to_binary(int value);
string data_pad(string unpadded_data);
string reg_pad(string orig_reg);

string store(int reg_num);
string store_indirect(int reg_num);
string load(int reg_num);
string load_indirect(int reg_num);
string halt(); // does not require any data field.
string clear(); // does not require any data field.
string input(int value);
string output(); // does not require any data field.
string jump(int value);
string skip(int value);
string addition(int value);
string subtraction(int value);
string multiplication(int value);
string division(int value);
string brrrrrt_modulus(int value);
string brrrrrt_round();

int main()
{
  vector<string> instruction_list;
  string instr, op, vr, new_instr;

  ifstream fin;
  fin.open("sample.txt");
  while(true)
  {
    if (fin.eof())
      break;
    else
    {
      getline(fin, instr);
      cout << instr << endl;
      if (instr.length() > 4)
      {
        op = instr.substr(0,3);
        vr = instr.substr(4,3);
      }
      else
      {
        op = instr.substr(0,3);
        vr = "0";
      }
      new_instr = readOpcode(op, stoi(vr));
      instruction_list.push_back(new_instr);
    }
  }
  fin.close();
  ofstream fout;
  fout.open("translated.txt");
  for (int i = 0; i < instruction_list.size(); i++)
  {
    fout << instruction_list[i] << endl;
  }
  fout.close();

  return 0;
}

string readOpcode(string opcode, int vr) // Reads an opcode and adds interperets the instruction.
{
  string new_instruction;
  if (opcode == "STO")
    new_instruction = store(vr);
  else if (opcode == "STI")
    new_instruction = store_indirect(vr);
  else if (opcode == "LOD")
    new_instruction = load(vr); // update reg 0 with the value located in another register
  else if (opcode == "LDI")
    new_instruction = load_indirect(vr); // update reg 0 with the value of an address located in another register
  else if (opcode == "HLT")
    new_instruction = halt(); // ends program
  else if (opcode == "CLR")
    new_instruction = clear(); // clears all register values
  else if (opcode == "INP")
    new_instruction = input(vr); // update reg 0 with user entered input.
  else if (opcode == "OUP")
    new_instruction = output(); // displays the value currently in reg 0.
  else if (opcode == "JMP")
    new_instruction = jump(vr); // jumps back n steps.
  else if (opcode == "SKP")
    new_instruction = skip(vr); // skips if reg 0 value is < 0, = 0, or > 0.
  else if (opcode == "ADD")
    new_instruction = addition(vr); // adds a number to reg 0.
  else if (opcode == "SUB")
    new_instruction = subtraction(vr); // subtracts a number from reg 0.
  else if (opcode == "MUL")
    new_instruction = multiplication(vr); // multiplies reg 0 by a number.
  else if (opcode == "DIV")
    new_instruction = division(vr); // divides reg 0 by a number.
  else if (opcode == "MOD")
    new_instruction = brrrrrt_modulus(vr); // the remainder of reg 0 after being divided by a number.
  else if (opcode == "RND")
    new_instruction = brrrrrt_round(); // rounds reg 0 to the nearest tenth.
  else
    new_instruction = cout << "Invalid operation." << endl;
  return new_instruction;
}



string decimal_to_binary(int value)
{ // Decimal to binary conversion.
  int new_dividend = value;
  string binary_string = "";
  while (new_dividend > 0)
  {
    binary_string = binary_string + to_string(new_dividend % 2);
    new_dividend = new_dividend / 2;
  }
  reverse(binary_string.begin(), binary_string.end());

  return binary_string;
} // Sends back the value converted to binary in string format.



string data_pad(string orig_data)
{ // Adds leading 0s to the extend the data field to 8 bits if not already 8 bits wide.
  string padded_data = "";
  int field_length = 8;
  while (field_length - orig_data.length() > 0)
  {
    padded_data = padded_data + "0";  // Adding the leading 0s
    field_length--;
  }
  padded_data = padded_data + orig_data;  // Combining the leading zeros and the original data.
  return padded_data;
} // Returns the string with the correct data field width.



string reg_pad(string orig_reg)
{ // Adds leading 0s to the extend the memory field to 3 bits if not already 3 bits wide.
  string padded_reg = "";
  int field_length = 3;
  while (field_length - orig_reg.length() > 0)
  {
    padded_reg = padded_reg + "0";  // Adding the leading 0s
    field_length--;
  }
  padded_reg = padded_reg + orig_reg;  // Combining the leading zeros and the original data.
  return padded_reg;
} // Returns the string with the correct memory field width.



string store(int reg_num)
{ // Stores the value of register 0 in another register.
  string instruction = "0000100000000"; // Decimal = 1.
  if (reg_num >= 0 && reg_num <= 7) // cynthia is cute
    instruction = instruction + reg_pad(decimal_to_binary(reg_num));
  return instruction;
} // Returns the string with the instruction translated to binary.



string store_indirect(int reg_num)
{ // Stores the value of register 0 in the address of another register. The address that the register holds must be between 0 and 255.
  string instruction = "0001000000000"; // Decimal = 2.
  instruction = instruction + reg_pad(decimal_to_binary(reg_num));
  return instruction;
} // Returns the string with the instruction translated to binary.



string load(int reg_num)
{ // Loads a value that is located in a register and updates the AC.
  string instruction = "00011"; // Decimal = 3.
  string data_field = "00000000"; // No data field required for this opcode; Set to 00000000 by default.
  if (reg_num >= 0 && reg_num <= 7)
    instruction = instruction + data_field + reg_pad(decimal_to_binary(reg_num));
  return instruction;
} // Returns the string with the instruction translated to binary.



string load_indirect(int reg_num)
{ // Loads a value from a location in memory using a memory address from a register.
  string instruction = "00100"; // Decimal = 4.
  string data_field = "00000000"; // No data field required for this opcode; Set to 00000000 by default.
  if (reg_num >= 0 && reg_num <= 7)
    instruction = instruction + data_field + reg_pad(decimal_to_binary(reg_num));
  return instruction;
} // Returns the string with the instruction translated to binary.



string halt()
{ // Ends the program.
  string instruction = "0010100000000000"; // Decimal = 5.
  return instruction;
} // Returns the string with the instruction translated to binary.



string clear()
{ // Clears ALL registers
  string instruction = "0011000000000000"; // Decimal = 6.
  return instruction;
} // Returns the string with the instruction translated to binary.



string input(int value)
{ // Stores a value in a register 0.
  string instruction = "00111"; // Decimal = 7.
  instruction = instruction + data_pad(decimal_to_binary(value)) + "000";
  return instruction;
} // Returns the string with the instruction translated to binary.



string output()
{ // Outputs the value of the AC which is register 0.
  string instruction = "0100000000000000"; // Decimal = 8.
  return instruction;
} // Returns the string with the instruction translated to binary.



string jump(int value)
{ // Jumps BACKWARDS n steps.
  string instruction = "01001"; // Decimal = 9.
  instruction = instruction + data_pad(decimal_to_binary(value)) + "000";
  return instruction;
} // Returns the string with the instruction translated to binary.



string skip(int value)
{ // Skips a step if the value in register 0 is negative, 0, or positive.
  string instruction = "01010"; // Decimal = 10.
  instruction = instruction + data_pad(decimal_to_binary(value)) + "000";
  return instruction;
} // Returns the string with the instruction translated to binary.



string addition(int value)
{ // Adds a number to the accumlator; accumlator register is register value 000.
  string instruction = "01011"; // Decimal = 11.
  instruction = instruction + data_pad(decimal_to_binary(value)) + "000";
  return instruction;
} // Returns the string with the instruction translated to binary.



string subtraction(int value)
{ // Subtracts a number from the accumulator; accumlator register is register value 000.
  string instruction = "01100"; // Decimal = 12.
  instruction = instruction + data_pad(decimal_to_binary(value)) + "000";
  return instruction;
} // Returns the string with the instruction translated to binary.



string multiplication(int value)
{ // Multiplies the accumulator by a number.
  string instruction = "01111"; // Decimal = 14.
  instruction = instruction + data_pad(decimal_to_binary(value)) + "000";
  return instruction;
}



string division(int value)
{ // Divides the accumulator by a number.
  string instruction = "01110"; // Decimal = 14.
  instruction = instruction + data_pad(decimal_to_binary(value)) + "000";
  return instruction;
}



string brrrrrt_modulus(int value)
{ // Divides the accumulator by a number.
  string instruction = "01111"; // Decimal = 15.
  instruction = instruction + data_pad(decimal_to_binary(value)) + "000";
  return instruction;
}

string brrrrrt_round()
{ // Rounds the value in the accumulator to the nearest 10th.
  string instruction = "1000000000000000"; // Decimal = 16.
  return instruction;
}
