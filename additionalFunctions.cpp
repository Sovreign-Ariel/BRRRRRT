#include <iostream>
using namespace std;

int main()
{
    return 0;
}

void multiplication(int value, int& reg[], int indx)
{
    //what if the updated bits needed for the new value in reg[0] > the max allowed bit value?
    //I don't know if what I'm trying to say about the index is correct here.
    if(indx <= 256/*?*/)
        reg[0] = reg[0] * value;
    else
        cout << "Number too large for brrrrt translation\n\n";
        exit(0);
}

void division(int value, int& reg[], int indx)
{
    if(value != 0)
        reg[0] = reg[0] / value;
    else
        cout << "Error...\nDivision by 0\n\n";
        exit(0);
}

void modulus(int value, int& reg[], int indx)
{
    int quotient = reg[0] / value;

    if((value * quotient) == reg[0])
        reg[0] = quotient;
    else
        reg[0] = reg[0] - (value * quotient);
}

void brrrrrt_round(int& reg[], int indx)
{
    int remainder = reg[0] % 10;

    if(remainder >= 5)
        reg[0] = 10 - remainder;
    else
        reg[0] = reg[0] / 10;
}
