#include <fstream>
#include <string.h>
#include <stdio.h>
#include <vector>

int main(int argv, char** argc)
{

    std::ifstream inputFile("Day4Input.txt");

    int x;
    char comma;
    std::string bingo_numbers_string;
    std::vector<int> bingo_numbers;
    std::vector<int> bingo_boards;

    while(inputFile >> x)
    {
        bingo_numbers.push_back(x);
        inputFile >> comma;
        if(comma != ',') break;
    }
    inputFile.seekg(0);

    //workaround to ignore first line
    std::getline(inputFile, bingo_numbers_string);

    while(inputFile >> x)
    {   
        bingo_boards.push_back(x);
    }

    bool seen_zero = false;
    bool winner = false;
    int winning_no = -1;
    int winning_board = -1;

    int no_of_boards = bingo_boards.size()/25;

    //[0:24] [25:49] [50:74] [75:99] + 24
    //  0  1  2  3  4
    //  5  6  7  8  9
    // 10 11 12 13 14 
    // 15 16 17 18 19
    // 20 21 22 23 24 
    // whenever ticking a winning number, check if others are ticked on the board (line and column)
    for(int i = 0; i < bingo_numbers.size() && !winner; ++i)
    {
        for(int j = 0; j < no_of_boards && !winner; ++j) //go per board
        {
            int board_pos = j * 25;
            int index = board_pos;
            int board_end = (j+1) * 25; 
            while(index < board_end) //loop over the board
            {
                if(bingo_boards[index] == bingo_numbers[i]) //got a number
                {
                    printf("Found match for %d in board no %d\n", bingo_numbers[i], j);
                    if(!seen_zero)
                        seen_zero = bingo_numbers[i] == 0 ? true : false;
                    if(bingo_boards[index] > 0)
                    {
                        bingo_boards[index] = bingo_boards[index] * -1; //mark it as seen
                    }
                    //check line and column for a winning board
                    bool winner_line = true;
                    int line = (index - board_pos)/5;
                    int line_start = board_pos + line * 5;
                    for(line = line_start; line < line_start + 5; ++line)
                    {
                        if(bingo_boards[line] > 0 || (bingo_boards[line] == 0 && !seen_zero))
                        {
                            winner_line = false;
                            break;
                        }
                    }
                    bool winner_column = true;
                    int column = index % 5;
                    int column_start = board_pos + column;
                    for(column = column_start; column < (column_start + 24); column += 5)
                    {
                        if(bingo_boards[line] > 0 || (bingo_boards[line] == 0 && !seen_zero))
                        {
                            winner_column = false;
                            break;
                        }
                    }
                    if(winner_line || winner_column)
                    {
                        winner = true;
                        winning_no = bingo_numbers[i];
                        winning_board = j;
                        break;
                    }
                }
                ++index;
            }
        }
    }

    int sum = 0;
    int winning_board_start_pos = winning_board * 25;
    for(int i = winning_board_start_pos ; i <= (winning_board_start_pos + 24); ++i)
    {
        // printf(" sum += %d\n", bingo_boards[i]);
        if(bingo_boards[i] > 0)
        {
            // printf(" sum += %d", bingo_boards[i]);
            sum += bingo_boards[i];
        }
    }

    printf("sum %d\n", sum);
    printf("Winning number is %d\n", sum * winning_no);
    return 0;
}