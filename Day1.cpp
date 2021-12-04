#include <stdio.h>
#include <fstream>

int main(int argv, char** argc)
{
    std::ifstream inputFile("Day1Input.txt");

    int total = 0;
    int val1 =0, val2 = 0, val3 = 0; 
    
    inputFile >> val1 >> val2 >> val3;

    int window1 = val1 + val2 + val3;
    int window2 = 0;

    val1 = val2; 
    val2 = val3;

    while (inputFile >> val3) 
    {
        window2 = val1 + val2 + val3;
        if(window2 > window1) ++total;
        val1 = val2;
        val2 = val3;
        window1 = window2;
    }

    inputFile.close();

    printf("Times increased: %d\n", total);

    return 0;
}