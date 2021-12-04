#include <fstream>
#include <string.h>
#include <stdio.h>

int main (int argv, char** argc)
{
    std::ifstream inputFile("Day2Input.txt");

    int depth = 0, position = 0, aim = 0;
    int temp = 0;
    std::string command;

    while(inputFile >> command)
    {
        inputFile >> temp;

        if(command.compare("forward") == 0) 
        {
            position += temp;
            depth += (aim * temp);
        }
        if(command.compare("up") == 0) aim -= temp;
        if(command.compare("down") == 0) aim += temp;
    }

    inputFile.close();

    printf("Total is %d\n", depth*position);
    return 0;
}