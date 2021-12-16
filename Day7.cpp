#include <fstream>
#include <iostream>
#include <vector>
#include <cmath> 
#include <algorithm>

int main(int argv, char** argc)
{

    std::ifstream inputFile("Day7Input.txt");
    float pos; 
    char c;
    std::vector<float> x_positions;
    int max = 0;

    while(inputFile >> pos)
    {
        x_positions.push_back(pos);
        max = max > pos? max : pos;
        inputFile >> c;
    }

    int sum = 0;
    float count = 0;

    for(int i = 0; i < x_positions.size(); ++i)
    {
        sum += x_positions[i];
        ++count;
    }

    std::sort(x_positions.begin(), x_positions.end());
    int median = x_positions[x_positions.size()/2];

    int fuel_p1 = 0;
    for(int i = 0; i < x_positions.size(); ++i)
    {
        fuel_p1 += std::abs(x_positions[i] - median); 
    }
    printf("Fuel needed for part 1: %d\n", fuel_p1);

    int mean = std::floor(sum/x_positions.size());
    int fuel_p2 = 0;

    for(int i = 0; i < x_positions.size(); ++i)
    {
        int distance = std::abs(x_positions[i] - mean);
        // printf("Distance of position %f from mean %f: %f\n", x_positions[i], mean, distance);

        for(int j = 0; j <= distance; ++j)
        {
            fuel_p2 += j;
        }
    }
    printf("Fuel needed for part 2 %d\n", fuel_p2);

    inputFile.close();

    return 0;
}