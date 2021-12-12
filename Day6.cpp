#include <fstream>
#include <stdio.h>
#include <vector>

int main(int argv, char** argc)
{

    std::ifstream inputFile("Day6Input.txt");
    int x; char c;
    std::vector<int> fish;

    while(inputFile >> x)
    {
        fish.push_back(x);
        inputFile >> c;
    }

    long long fish_days[9] = {0};

    for(int i = 0; i < fish.size(); ++i)
    {
        ++fish_days[fish[i]]; 
    }

    long long reset_fish = 0, new_fish = 0;
    for(int i = 0; i < 256; ++i)
    {
        reset_fish = 0;
        new_fish = 0;
        if(fish_days[0] > 0) //all those fish are giving birth
        {
            reset_fish = fish_days[0];
            new_fish = fish_days[0];
            fish_days[0] = 0;
        }
        for(int j = 1; j <= 8; ++j)
        {
            fish_days[j-1] = fish_days[j];
        }
        fish_days[6] += reset_fish;
        fish_days[8] = new_fish;
    }

    long long total_fish = 0;
    for(int i = 0; i <=8; ++i)
    {
        total_fish += fish_days[i];
    }

    // for(int i = 0; i < 9; ++i)
    // {
    //     printf("%llu \n", fish_days[i]);
    // }

    printf("total fish after 80 days: %llu\n", total_fish);

    return 0;
}