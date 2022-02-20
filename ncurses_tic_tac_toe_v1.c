#include <curses.h>
#include <stdio.h>
#include <unistd.h>

void show_buffer_at(char *buffer, int x, int y)
{
    move(x, y);
    addstr(buffer);
    clrtoeol();
}

void print_board(char *buffer, size_t max_size, char board[3][3])
{
    snprintf(buffer, max_size, "%c|%c|%c\n", (board[0][0]), (board[0][1]), (board[0][2]));
    show_buffer_at(buffer, 0, 0);

    snprintf(buffer, max_size, "-----\n");
    show_buffer_at(buffer, 1, 0);

    snprintf(buffer, max_size, "%c|%c|%c\n", (board[1][0]), (board[1][1]), (board[1][2]));
    show_buffer_at(buffer, 2, 0);

    snprintf(buffer, max_size, "-----\n");
    show_buffer_at(buffer, 3, 0);

    snprintf(buffer, max_size, "%c|%c|%c\n", (board[2][0]), (board[2][1]), (board[2][2]));
    show_buffer_at(buffer, 4, 0);

    move(0, 0); // cursor posstion
}

int is_within_boundary(int x, int y)
{
    if (x > 4 || y > 4)
        return 0;
    else
        return 1;
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
    return 0;
}

int swap_player(char player)
{
    if (player == 'O')
        player = 'X';
    else 
        player = 'O';

    return player;
}

int main()
{
    initscr();
    cbreak();
    noecho();

    // Enables keypad mode. This makes mouse events getting reported as
    // KEY_MOUSE, instead as of random letters.
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);

    char buffer[512];
    size_t max_size = sizeof(buffer);
    char player = 'X';
    int x, y;
   
    char board[3][3] = {
        {' ',' ',' '},
        {' ',' ',' '},
        {' ',' ',' '}};
    print_board(buffer, max_size, board);
   
    while (1) {
        curs_set(0); //0 hides cursor, 1 shows cursor
        int c = wgetch(stdscr);
        char buffer[512];
        size_t max_size = sizeof(buffer);
        
        if (c == KEY_MOUSE) 
        {
            MEVENT event;
            if (getmouse(&event) == OK) 
            {
                if ((event.bstate & BUTTON1_PRESSED) || (event.bstate & BUTTON1_CLICKED)) 
                {
                    // snprintf(buffer, max_size, "Mouse clicked at row=%d, column=%d bstate=0x%x",
                    //          event.y, event.x, event.bstate);
                    if (is_within_boundary(event.x, event.y))
                    {
                        x = event.y / 2;
                        y = event.x / 2;
                        if (board[x][y] == ' ')
                        {
                            board[x][y] = player;
                            print_board(buffer, max_size, board);
                            
                            if (full_board(board) || has_winner(board))
                                break;
                              
                            player = swap_player(player);                                              
                        }
                    }
                }
            } 
        } 
    }

    if (has_winner(board))
        snprintf(buffer, max_size, "the Winner of the Game is %c press enter to exit game", player);
    else
        snprintf(buffer, max_size, "the board is full: the game is draw, press enter to exit game");
    show_buffer_at(buffer, 5, 0);
    
    wgetch(stdscr);
    wgetch(stdscr);
    endwin();
    return 0;
}
