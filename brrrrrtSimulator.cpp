#include <map>
#include <fstream>
using namespace std;

int binaryToDecimal(string bin);

int main()
{
    string instruction;
    string opcode;
    
    ifstream fin("brrrrrtMnemonicFile.txt");
    
    if(fin.fail())
    {
        cout << "Error\n\n";
        
        exit(0);
    }

    map<string, int> reg_map;
    
    reg_map["00001"] = 0; // store
    reg_map["00010"] = 0; // load
    reg_map["00011"] = 0; // hault
    reg_map["00100"] = 0; // clear
    reg_map["00101"] = 0; // input
    reg_map["00110"] = 0; // output
    reg_map["00111"] = 0; // jump
    reg_map["01000"] = 0; // skip
    reg_map["01001"] = 0; // add
    reg_map["01010"] = 0; // subtract
    reg_map["01011"] = 0; // multiply
    reg_map["01100"] = 0; // divide
    reg_map["01101"] = 0; // modulus
    reg_map["01110"] = 0; // ceiling
    reg_map["01111"] = 0; // floor
    reg_map["10000"] = 0; // round
    
    while(!fin.eof())
    {
        fin >> instruction;
        opcode = instruction.substr(0, 5);
        if(opcode == "00001") // store
        {
            string n = instruction.substr(5, 6);
            int val = binaryToDecimal(bin);
            string regis = instruction.substr(11, 3);
            reg_map[regis] = val;
     
        }
        //else if(opcode == 00010) // load
        //else if(opcode == 00011) // hault
        //else if(opcode == 00100) // clear
        //else if(opcode == 00101) // input
        else if(opcode == "00110") // output
        {
            string regis = instruction.substr(5, 3);
            cout << reg_map[regis] << endl;
        }
        //else if(opcode == 00111) // jump
        //else if(opcode == 01000) // skip
        else if(opcode == "01001") // add
        {
            string regisA = instruction.substr(4,3);
            string regisB = instruction.substr(7,3);
            string regisC = instruction.substr(10,3);
            int sum_result = reg_map[regisA] + reg_map[regisB];
            reg_map[regisC] = sum_result;
      // need more here (and to fix)
        }
        //else if(opcode == 01010) // subtract
        //else if(opcode == 01011) // multiply
        //else if(opcode == 01100) // divide
        //else if(opcode == 01101) // modulus
        //else if(opcode == 01110) // ceiling
        //else if(opcode == 01111) // floor
        //else if(opcode == 10000) // round
        
    }
    fin.close();
    return 0;
}

int binaryToDecimal(string bin)
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

