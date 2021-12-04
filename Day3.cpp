#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

char countBits(std::vector<std::string> bits_arr, int position)
{
    int count_ones = std::count_if(bits_arr.begin(),
                                bits_arr.end(),
                                [&] (const std::string& elem) {
                                    return (elem[position] == '1');
                                });
    int count_zeroes = bits_arr.size() - count_ones;
    return (count_ones >= count_zeroes) ?  '1' :  '0';
}

int main (int argv, char** argc)
{
    std::ifstream inputFile("Day3Input.txt");
    std::string bits;

    int ones [12] = {};
    int zeroes [12] = {};
    std::vector<std::string> oxygen_ratings;
    std::vector<std::string> co2_ratings;

    uint gamma = 0, epsilon = 0;
    uint oxygen_gen_rating = 0, co2_scrubber_rating = 0;

    //reading the file
    while(inputFile >> bits)
    {   
        oxygen_ratings.push_back(bits);
        co2_ratings.push_back(bits);
    }

    // first part
    for(int j = 0; j < oxygen_ratings.size(); ++j)
    {
        for(int i = 0; i < 12; ++i)
        {
            if(oxygen_ratings[j][i] == '1') ++ones[i];
            else ++zeroes[i]; 
        }
    }
    int j = 11;
    for(int i = 0; i < 12; ++i)
    {
        if(ones[i] > zeroes[i])
            gamma |= 1UL << j;
        else 
            epsilon |= 1UL << j;
        j--;
    }
    printf("Total is %d\n", gamma * epsilon);

    //second part
    char to_keep_oxygen = ones[0] >= zeroes[0]? '1' : '0';
    char to_keep_co2 = zeroes[0] <= ones[0]? '0' : '1';

    for(int i = 0; i < 12; ++i)
    {
        oxygen_ratings.erase(
            std::remove_if(oxygen_ratings.begin(), 
                           oxygen_ratings.end(),
                           [&] (const std::string& rating) {
                            return (rating[i] != to_keep_oxygen && oxygen_ratings.size() > 1);
                            }
                        ),
                        oxygen_ratings.end());
        
        co2_ratings.erase(
            std::remove_if(co2_ratings.begin(), 
                           co2_ratings.end(),
                           [&] (const std::string& rating) {
                            return (rating[i] != to_keep_co2 && co2_ratings.size() > 1);
                        }
                    ),
                    co2_ratings.end());
        if(i == 11) break;
        to_keep_oxygen = countBits(oxygen_ratings, i+1);
        to_keep_co2 = countBits(co2_ratings, i+1) == '1'? '0' : '1';
    }

    j = 11;
    for(int i = 0; i < 12; ++i)
    {
        if(oxygen_ratings[0][i] == '1')
            oxygen_gen_rating |= 1UL << j;
        if(co2_ratings[0][i] == '1')
            co2_scrubber_rating |= 1UL << j;
        j--;
    }

    printf("life support rating :%d\n", oxygen_gen_rating * co2_scrubber_rating);

    inputFile.close();

    return 0;
}