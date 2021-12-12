#include <fstream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <cmath>

int main(int argv, char** argc)
{

    std::ifstream inputFile("Day5Input.txt");

    int i = 0;
    char c;
    bool added = false;
    std::vector<int> points;

    inputFile.seekg(0, std::ios::end);
    size_t length = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);
    char buffer[length];

    inputFile.read(buffer, length);

    int number = 0;
    while(i <= length)
    {
        if(buffer[i] >= '0' && buffer[i] <= '9')
        {
            number = number * 10 + (buffer[i] - '0');
            added = false;
        }
        else //non numeric char, save number and reset
        {
            if(!added)
            {
                points.push_back(number);
                number = 0;
                added = true;
            }
        }
        ++i;
    }

    //finding max x and max y
    int max_x = 0; 
    int max_y = 0;
    for(int i = 0; i < points.size(); ++i)
    {
        if(i % 2 == 0)
        {
            max_x = max_x > points[i] ? max_x : points[i];
        }
        else 
        {
            max_y = max_y > points[i] ? max_y : points[i];
        }
    }

    std::vector<std::vector<int> > space;
    space.reserve(max_x+1);
    for(int i = 0; i <= max_x; ++i)
    {
        space[i].resize(max_y+1);
        std::fill(space[i].begin(), space[i].end(), 0);
    }

    int x = 0; int y = 0;
    int miny = 0; int minx = 0;
    int maxy = 0; int maxx = 0;

    for(int i= 0; i <= (points.size()-4); i += 4)
    {
        printf("looking at : %d %d %d %d \n", points[i], points[i+1], points[i+2], points[i+3]);
        if(points[i] == points[i+2]) //x matches
        {
            y = points[i];
            minx = points[i+1] < points[i+3] ? points[i+1] : points[i+3];
            maxx = points[i+1] > points[i+3] ? points[i+1] : points[i+3];
            for(int x = minx; x <= maxx; ++x)
            {
                ++space[x][y];
                printf("line: adding space[%d][%d] with val: %d \n", x, y, space[x][y]);
            }
        }
        else if(points[i+1] == points[i+3]) //y matches
        {
            x = points[i+1];
            miny = points[i] < points[i+2] ? points[i] : points[i+2];
            maxy = points[i] > points[i+2] ? points[i] : points[i+2];
            for(int y = miny; y <= maxy; ++y)
            {
                ++space[x][y];
            }
        }
        //[part 2]
        else if(std::abs(points[i+1] - points[i+3]) == std::abs(points[i] - points[i+2]))
        {
            minx = points[i+1] < points[i+3] ? points[i+1] : points[i+3];
            miny = points[i] < points[i+2] ? points[i] : points[i+2];
            x = points[i+1];
            y = points[i];
            int diff = std::abs(points[i+1] - points[i+3]);
            while(diff >= 0)
            {
                ++space[x][y];
                x += points[i+1] < points[i+3] ? 1 : -1;
                y += points[i] < points[i+2] ? 1 : -1;
                --diff;
            }
        }
    }

    int count = 0;
    for(int i = 0; i <= max_x; ++i)
    {
        for(int j = 0; j <= max_y; ++j)
        {
            printf("%d ", space[i][j]);
            if(space[i][j] > 1)
            {
                ++count;
            }
        }
        printf("\n");
    }

    printf("CounT %d\n", count);

    return 0;
}

