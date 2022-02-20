#include <curses.h>
#include <stdio.h>
 
// char *c2s(char c)
// {
//     switch (c) 
//     {
//         case ' ':
//             return "🔲";
            
//         case 'O':
//             return "🍑";
            
//         case 'X':
//             return "🍆";
//     }

//     return NULL;
// }

void print_board(char *buffer, size_t max_size, char board[3][3])
{
    // char board[3][3] = {
    //     {'00','02','04'},
    //     {' ',' ',' '},
    //     {' ',' ',' '}};
    // move(0, 0); // cursor posstion
    // snprintf(buffer, max_size, "%c|%c|%c\n------\n%c|%c|%c\n------\n%c|%c|%c\n", 
    //          board[0][0], board[0][1], board[0][2], 
    //          board[1][0], board[1][1], board[1][2], 
    //          board[2][0], board[2][1], board[2][2]);
    // move(10, 0);
    // snprintf(buffer, max_size, "%s|%s|%s\n", c2s(board[0][0]), c2s(board[0][1]), c2s(board[0][2]));
    // move(10, 1);
    // snprintf(buffer, max_size, "--------\n");
    // move(10, 2);
    // snprintf(buffer, max_size, "%s|%s|%s\n", c2s(board[1][0]), c2s(board[1][1]), c2s(board[1][2]));
    // move(10,3);
    // snprintf(buffer, max_size, "--------\n");
    // move(10, 4);
    // snprintf(buffer, max_size, "%s|%s|%s\n", c2s(board[2][0]), c2s(board[2][1]), c2s(board[2][2]));

    move(0, 0); // cursor position  move(0, 10) = move(Y, X) positions Y is first X is second 
        snprintf(buffer, max_size, "%c|%c|%c\n", (board[0][0]), (board[0][1]), (board[0][2]));
        addstr(buffer);
        clrtoeol();
    move(1, 0);
        snprintf(buffer, max_size, "-----\n");
        addstr(buffer);
        clrtoeol();
    move(2, 0);
        snprintf(buffer, max_size, "%c|%c|%c\n", (board[1][0]), (board[1][1]), (board[1][2]));
        addstr(buffer);
        clrtoeol();
    move(3, 0);
        snprintf(buffer, max_size, "-----\n");
        addstr(buffer);
        clrtoeol();
    move(4, 0);
        snprintf(buffer, max_size, "%c|%c|%c\n", (board[2][0]), (board[2][1]), (board[2][2]));
        addstr(buffer);
        clrtoeol();
    move(0, 0); // cursor posstion
}

int is_within_boundary(int x, int y)
{
    if (x > 4 || y > 4)
        return 0;
    else
        return 1;
}

void game_announcement_text(char *buffer, size_t max_size, char feedback[100])
{
    move(5, 0);
    snprintf(buffer, max_size, "%s", feedback);
    addstr(buffer);
    clrtoeol();
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
    char feedback[100] = "game announcment text";
    int x, y;
   
    char board[3][3] = {
        {' ',' ',' '},
        {' ',' ',' '},
        {' ',' ',' '}};
    game_announcement_text(buffer, max_size,feedback);
    print_board(buffer, max_size, board);
   
    while (1) {
        curs_set(0); //0 hides cursor, 1 shows cursor
        int c = wgetch(stdscr);
       
        // if (c == '\n')
        //   break;
 
        char buffer[512];
        size_t max_size = sizeof(buffer);
        if (c == ERR)
        {
            snprintf(buffer, max_size, "Nothing happened.");
        } 
        else if (c == KEY_MOUSE) 
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

                            //game_announcement_text(buffer, max_size, game_update);
                            if (full_board(board))
                            {
                                snprintf(buffer, max_size, "Board is Full: No winners, relaunch the game");
                                break;
                            }

                            if (has_winner(board))
                            {
                                
                                break;                                 
                            }
                            
                            

                            if (player == 'O')
                                player = 'X';
                            else 
                                player = 'O';                                                 

                        }
                    }
                }
                
            } 
            else 
            {
                snprintf(buffer, max_size, "Got bad mouse event.");
            }
        } 
        else 
        {
            snprintf(buffer, max_size, "Pressed key %d (%s)", c, keyname(c));
        }
    }
    
                                 move(5,0);
                                snprintf(buffer, max_size, "the Winner of the Game is %c press enter to exit game", player);
                                addstr(buffer);
                                clrtoeol();
                                wgetch(stdscr);

    endwin();
    return 0;
}
