#include <stdio.h>

char *c2s(char c)
{
    switch (c) 
    {
        case ' ':
            return "🔲";
            
        case 'O':
            return "🍑";
            
        case 'X':
            return "🍆";
    }

    return NULL;
}

void print_board(char board[3][3])
{
    // char board[3][3] = {
    //     {' ',' ',' '},
    //     {' ',' ',' '},
    //     {' ',' ',' '}};
    printf("%s|%s|%s\n", c2s(board[0][0]), c2s(board[0][1]), c2s(board[0][2]));
    printf("--------\n");
    printf("%s|%s|%s\n", c2s(board[1][0]), c2s(board[1][1]), c2s(board[1][2]));
    printf("--------\n");
    printf("%s|%s|%s\n", c2s(board[2][0]), c2s(board[2][1]), c2s(board[2][2]));

}

int position_to_coordinates(int position, int *row, int *col)
{
    // switch expression
    switch (position) 
    {
        case 1:
            *row = 2;
            *col = 0;
            break;
        case 2:
            *row = 2;
            *col = 1;
            break;
        case 3:
            *row = 2;
            *col = 2;
            break;
        case 4:
            *row = 1;
            *col = 0;
            break;
        case 5:
            *row = 1;
            *col = 1;
            break;
        case 6:
            *row = 1;
            *col = 2;
            break;
        case 7:
            *row = 0;
            *col = 0;
            break;
        case 8:
            *row = 0;
            *col = 1;
            break;
        case 9:
            *row = 0;
            *col = 2;
            break;
    }

    return 0;
}

int has_winner(char board[3][3])
{
    int sum[8];

    sum[0] = board[0][0] + board[0][1] + board[0][2];
    sum[1] = board[1][0] + board[1][1] + board[1][2];
    sum[2] = board[2][0] + board[2][1] + board[2][2];
    sum[3] = board[0][0] + board[1][0] + board[2][0];
    sum[4] = board[0][1] + board[1][1] + board[2][1]; 
    sum[5] = board[0][2] + board[1][2] + board[2][2];
    sum[6] = board[0][0] + board[1][1] + board[2][2];
    sum[7] = board[2][0] + board[1][1] + board[0][2];
    
    for (int i = 0; i < 8; i++)
    {
        if (sum[i] == 237 || sum[i] == 264)
            return 1;
    }
    /////////////////////////////////////////////////
    //  some aritmetic  problem 
    // int sum_diag_1 = 0;
    // int sum_diag_2 = 0;
    // int colsum = 0;
    // int rowsum = 0;
    //     for (int col = 0; col < 3; col++)
    // {
    //     for (int row = 0; row < 3; row++)
    //     colsum = colsum + board[row][col];
    //     printf("Sum for col %d = %d\n", col, colsum); // debuging line
    // }
    // for (int row = 0; row < 3; row++)
    // {
    //     for (int col = 0; col < 3; col++)
    //     rowsum = rowsum + board[row][col];
    //     printf("Sum for row %d = %d\n", row, rowsum);// debuging line
    // }
    
    // sum_diag_1 = board[0][0] + board[1][1] + board[2][2];
    // printf("sum diagnal 1: %d\n", sum_diag_1);
    // sum_diag_2 = board[2][0] + board[1][1] + board[0][2];
    // printf("sum diagnal 2: %d\n", sum_diag_2);

    // if (rowsum == 237 || colsum == 264 || rowsum == 264 || colsum == 237 || sum_diag_1 == 237 || sum_diag_1 == 264 || sum_diag_2 == 237 || sum_diag_2 == 264)
    //     return 1;
        
    return 0;
}

int full_board(char board[3][3])
{
    int full_sum = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            full_sum += board[i][j];
        }
    }
    if (full_sum == 756 || full_sum == 747)
        return 1;
    // printf("full sum %d", full_sum);
    return 0;
}

int main()
{
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};
    
    int  row_index;
    int  col_index; 
    char player = 'X';
    int  position;
    
    print_board(board);
   
    while(1)
    {
        

        printf("=> player %c enter position\n", player);
        scanf("%d", &position);
        position_to_coordinates(position, &row_index, &col_index);
    
        if (position < 1 || position > 9)
        {
            printf("location %d don't exist, choose number 1 to 9\n", position);
        }
        else if (board[row_index][col_index] == 'O' || board[row_index][col_index] == 'X')
        {
            printf("location %d already taken\n", position);
        }
        else
        {
            board[row_index][col_index] = player;
            print_board(board); 
            
            if (has_winner(board))
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
            if (player == 'O')
                player = 'X';
            else 
                player = 'O';
        }
    }

    return 0;
}
