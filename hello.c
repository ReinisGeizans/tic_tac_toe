#include <stdio.h>

void print_board(char board[])
{
    printf("%c|%c|%c\n-----\n", board[0], board[1], board[2]);
    printf("%c|%c|%c\n-----\n", board[3], board[4], board[5]);
    printf("%c|%c|%c\n\n", board[6], board[7], board[8]);
}

// int has_winner(char board[])
// {
//     return  ((board[0] == 'o'|| board[0] == 'x') && board[0] == board [1] && board[0] == board [2]) ||
//             ((board[3] == 'o'|| board[3] == 'x') && board[3] == board [4] && board[3] == board [5]) ||
//             ((board[6] == 'o'|| board[6] == 'x') && board[6] == board [7] && board[6] == board [8]) ||
//             ((board[0] == 'o'|| board[0] == 'x') && board[0] == board [3] && board[0] == board [6]) ||
//             ((board[1] == 'o'|| board[1] == 'x') && board[1] == board [4] && board[1] == board [7]) ||
//             ((board[2] == 'o'|| board[2] == 'x') && board[2] == board [5] && board[2] == board [8]) ||
//             ((board[0] == 'o'|| board[0] == 'x') && board[0] == board [4] && board[0] == board [8]) ||
//             ((board[2] == 'o'|| board[2] == 'x') && board[2] == board [4] && board[2] == board [6]);
// }

int has_winner_2(char board[])
{
    int sum[8];

    for (int i = 0; i < 3; i++)
        sum[i] = board[i * 3] + board[1 + i * 3] + board[2 + i * 3];

    for (int i = 3; i < 6; i++)
        sum[i] = board[i - 3] + board[i] + board[i + 3];

    sum[6] = board[0] + board[4] + board[8];
    sum[7] = board[2] + board[4] + board[6];

    for (int i = 0; i < 8; i++)
    {
        if (sum[i] == 333 || sum[i] == 360)
            return 1;
    }
    
    return 0;
}

int full_board(char board[])
{
    int full_sum = 0;

    for (int i = 0; i < 9; i++)
    {
        full_sum = full_sum + board[i];
    }

    if (full_sum == 1035 || full_sum == 1044)
        return 1;
    
    return 0;
}
 
int main()
{
    // board
    char board[9];
    char player = 'o';
    int position;
    
    for (int i = 0; i < 9; i++)
    {
        board[i] = ' ';
    }
    
    print_board(board);

    while (1)
    {
        printf("=> player %c enter position\n", player);
        scanf("%d", &position);

        // boundary
        if (position > 8) 
        {
            printf("location %d don't exist, choose number 0 to 8\n", position);
        } 
        else if(board[position] == 'o' || board[position] == 'x') // check if player has taken position
        {
            printf("location %d already taken\n", position);
        }
        else
        {
            board[position] = player;
        
            print_board(board);


            if (has_winner_2(board))
            {
                printf("player %c has won\n", player);
                break;
            }

            if (full_board(board))
            {
                printf("board is full, no winners\n");
                break;
            }

            // switch player
            if (player == 'o')
                player = 'x';
            else 
                player = 'o';
        }
    }

    return 0;
}
