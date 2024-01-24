#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h> 
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"


// defined for loops
int i;
//defined for loops
int j;
// # of rows
const int rows = 6;
// # of cols
const int cols = 7;
// size of board
char board[rows][cols];
// winner
char winner = ' ';
// bool to determmine if use wants to play or npot(used in questionPlay funciton)
bool play;
// var that is used to determinen inital play print stamtnet
int playNumber = 1;

//this function displays the board ie prints it on the screen
void displayBoard();
// this clears the board (adds spcaes where needed for future placement )
void clearBoard();
// this function takes input for the users move
void playerMove();
// this functions plays a move for comouter
void computerMove();
//this functions checks if the board is full or not and a move is availabel
bool checkSpaces();
// this functin checks if there is a winner after each move
char checkWinner();
// function that prints would u like to play(used multiple tiems)
bool questionPlay(int playNumber);
// function that prints winner message
void winnerMessage(char winner);
bool playerCloseWin(int row, int col);
bool checkWinInput(int row, int col);


int main()
{
    srand(time(NULL));
    printf("**************************\n");
    printf("Welcome to Connect Four!!\n");
    printf("**************************\n");
    // we see if they wanna play (will return a true or false var)
    // etner in the 1 bc it is the first time we are asking to play 
    play = questionPlay(1);
    while(play)
    {

        char response = ' ';
        clearBoard();
        
        // if there are free spaces and there is no winner
        while(checkSpaces() == true && winner == ' ')
        {
            displayBoard();

            playerMove();
            winner = checkWinner();
            if(winner != ' ')
                break;
            


            computerMove();
            winner = checkWinner();
            if(winner != ' ')
                break;
          
            
          
            
        }
        displayBoard();

        //exit this while loop when there is either a winner or no free spces

        // pass the winner to the winenrMEssage function to print the winenr
        winnerMessage(winner);
        winner = ' ';
        play = questionPlay(2);
        
    }
    
        printf("Thanks for coming!\n");
    
    return 0;
}

void winnerMessage(char winner)
{
    // if there is no winner, then winner would = ' ', else the check winenr func would have changed the value
        if(winner == ' ')
        {
            // print draw and ask if they wann aplay 
            // passing in 2 into the questionPlay function beause this is second time we are asking to play
            printf("It's a Draw!\n");
            questionPlay(2);
        }
        else if(winner == 'o')
        {
            // if winner is 'o' that means use won!
            printf("You Won!!! SLAY YAYAYA\n");
            
        }
        else
        // last case is the computetr won, user lsot
        {
            printf("You LOST LOSER!!!!!\n");
        
        }
}

bool questionPlay(int playNumber)
{
    // set validPlayAgain to true so we iterate through while loop once to ask 
    bool validPlayAgain = true;
    // char that takes in user input of Y or N
    char playResponse;

    // if first time playing the game, the function takes in int playNumber 
    // and if it's one, the main function passes in 1 for the first time, 
    // and if one we ask if they'd like to play
    if (playNumber == 1)
    {
        printf("Would you like to play?(Y/N): ");
    }
    // if the main func passes in 2 to this function that means we are asking if they wanna play again or not
    else
    {
        printf("Would you like to play again?(Y/N): ");
    }

    // we enter this while loop
    while (validPlayAgain)
    {
        // take in their response of yes or no
        scanf(" %c", &playResponse);
        // uppercase it 
        playResponse = toupper(playResponse);
        // compare their answers
        switch (playResponse)
        {
            // if enter a y then we know their answer was valid 
            // so we set it now to false to not enter this again
            // return true bc they wanna play again 
            case 'Y':
                validPlayAgain = false;
                return true;

            // same reasoning as yes but we return false bc they don't wanna play
            case 'N':
                validPlayAgain = false;
                return false;

            // if yes or no was not input we ask them to input proper one 
            // and validPlayAgain is not switched to false, therefore, we enter this loop again
            default:
                printf("Please enter a valid answer(Y/N): ");
        }
    }

}


void clearBoard()
{
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            board[i][j] = ' ';
            // each element will be empty space, effectivle clearing it 
        }
    }
}


void displayBoard()
{

//The YELLOW is defined that contains the ANSI escape code for yellow text. 
//After printing the character, RESET is used to reset the text color to the default.

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            // Check the value in each box on the board
            if (board[i][j] == 'o')
                printf(YELLOW " %c " RESET, board[i][j]);  
            else if (board[i][j] == 'x')
                printf(RED " %c " RESET, board[i][j]);     // Print red 'x'
            else
                printf(" %c ", board[i][j]);

            // we do this because we want the | to only be printed in the middle not edge so when j = 6 is no tless than 7-1(6) so we dont print at end 
            //and it ensured we print | at each row bc it is independent of the row just column 
            if (j < cols - 1)
                printf("|");
        }

        // we do tbis bc we want row seperators on the middle not end to make the board rowless on the edge
        // by doing this it ownr print one of these on the last one 
        //since ut prrints the inner for loop first we dont print a first row on top either 
        if (i < rows - 1)
            printf("\n---|---|---|---|---|---|---\n");
    }
    printf("\n");
}

void computerMove()
{
    bool compValidWin = true;
    bool compValidRand = true;
    bool playerWin = true;

    // Check for a winning move
    for (int compCol = 0; compCol < cols && compValidWin; compCol++)
    {
        for (int i = rows - 1; i >= 0; i--)
        {
            if (board[i][compCol] == ' ')
            {
                if (checkWinInput(i, compCol))
                {
                    board[i][compCol] = 'x';
                    compValidWin = false;
                    compValidRand = false;
                    playerWin = false;
                    return;
                }
                break;
            }

        }
    }

    // Block the player from winning
    for (int compCol = 0; compCol < cols && playerWin; compCol++)
    {
        for (int i = rows - 1; i > 0; i--)
        {
            if (board[i][compCol] == ' ')
            {
                if (playerCloseWin(i, compCol))
                {
                    board[i][compCol] = 'x';
                    compValidWin = false;
                    compValidRand = false;
                    playerWin = false;  // Set playerWin to true if a blocking move is made
                    return;
                }
                break;
            }

        }
    }

    // If no winning move or blocking move, make a random move
    while (compValidRand)
    {
        int compCol = rand() % cols;
        for (int i = rows - 1; i >= 0; i--)
        {
            if (board[i][compCol] == ' ')
            {
                board[i][compCol] = 'x';
                compValidRand = false;
                break;
            }
        }
    }
}




void playerMove()
{
    char cPlay;
    int isInt = 0;
    int playerCol;
    int playerRow = 5;

    // this var used to validate if valid move or not
    bool valid = true;

    do {
        printf("\nPlease enter a column to drop your piece (1-7): ");
        bool validCol = true;

        do
        {
            // this isInt will be equal to the amount of numbers scanned ie 1   
            scanf(" %c%*c", &cPlay);
            printf("\n");
            
            if(isalpha(cPlay))
            {
                printf("Please enter a number not a letter: ");
                valid = false;
            }
            else
            {

                playerCol = cPlay - '0';
                // if the user inputs a column number out of range, it will not be a valid move and print that 
                if(playerCol > 7 || playerCol < 1)
                {
                    
                    printf("Please enter a valid move (cols 1-7): ");
                    valid = false;
                }
                
                // check if the spot is already taken
                else
                {
                    // Check if the column is full
                    for (int i = rows - 1; i >= 0; i--)
                    {
                        if (board[i][playerCol - 1] == ' ')
                        {
                            board[i][playerCol - 1] = 'o';
                            validCol = false;
                            break;
                        }
                    }

                    if (validCol)
                    {
                        printf("This column is full, please choose another column: ");
                    }
                }
            } 
        }while (validCol);

        valid = false;  // Set valid to false outside the inner loop

    } while (valid);
}

// make this function check for the input of the row and col from the pc if teh plahyer
// is one away from winning and if so block it
// do this by checking the block below and above and to the left and right and diagnols
bool playerCloseWin(int row, int col)
{
    // the general jist of this is to see if the count of 'o's is three then the player can win
    // count is 3 in the diff directions 
    // Horizontal Check
    int adjCount = 0;

    //LeftCount
    for (int x = col - 1; x >= 0; x--) //we loop through the cols with the input row(to check orizontal)
    // we move the cols to the right 
    {
        if (board[row][x] == 'o')
        {
            adjCount++;
        }
        else
        {
            break;
        }
    }

    //RightCount
    for (int x = col + 1; x < cols; x++) // now we checl the cols to the left (add this count to a counter to see if it'll eual 3)
    {
        if (board[row][x] == 'o')
        {
            adjCount++;
        }
        else
        {
            break;
        }
    }

    if (adjCount >= 3) // if the ocunt is greater or equal to 3 then we return true, the player can win next move
    {
        return true;
    }

    //Vertical Check
    int verticalCount = 0; // the count is initialized to 0 
    for (int x = row - 1; x >= 0; x--) // we set the row ewaul to the input row and check down 
    {
        if (board[x][col] == 'o') // if there is an o then we add one to the count
        {
            verticalCount++;
        }
        else
        {
            break;
        }
    }

    if (verticalCount >= 3) //if there are more tan 3 'o's in a row then we retur true and play the move inputted by pc
    {
        return true;
    }

    //Diagonal up right check
    int diagCount = 0;
    for (int step = 1, x = 1; col + step < cols && row - step >= 0; step++) // we start step (going up or down) at 1 
    // if the input col + step is under cols need to be true (dont wanna go off board) 
    // if in put row - step is greater than 0 needs to be true (not go off the board)
    
    {
        if (board[row - step][col + step] == 'o') //if the row we're checking minus the step (row ) and the col+ step for cols 
        // is 0 ie we went one up and one right if its an o we add one to daig count
        {
            diagCount++;
        }
        else
        {
            break;
        }
    }

    for (int step = 1, x = 1; col - step >= 0 && row + step < rows; step++) //same idea here but we go opposite direction
    //ie we go one row down (row+step) and one row left (col-stepo)
    // check this if it equals o
    {
        if (board[row + step][col - step] == 'o')
        {
            diagCount++;
        }
        else
        {
            break;
        }
    }

    if (diagCount >= 3) // count greater or equal to 3 we reutn true they can win here
    {
        return true;
    }

    diagCount = 0; 

    //Diagonal down right check
    for (int step = 1, x = 1; col + step < cols && row + step <= rows; step++)
    {
        if (board[row + step][col + step] == 'o')
        {
            diagCount++;
        }
        else
        {
            break;
        }
    }

    for (int step = 1, x = 1; col - step >= 0 && row - step >= 0; step++) //same idea here but checking diagonal down right (opposite of one aobve)
    {
        if (board[row - step][col - step] == 'o')
        {
            diagCount++;
        }
        else
        {
            break;
        }
    }

    if (diagCount >= 3) 
    {
        return true;
    }

    return false;

}


bool checkSpaces()
{
    for(i = 0; i < rows; i++ )
    {
        for(j = 0; j < cols; j++)
        {
            // if there is any tile that has a free space, then we return true immedialy
            if(board[i][j] == ' ')
            {
                return true;
            }
        }
    }
    // no free spaces were foujd
    return false;
}

bool checkWinInput(int row, int col)
{
    board[row][col] = 'x';
    if (checkWinner() != ' ')
    {
        return true;

    }
    else{
        board[row][col] = ' ';
        return false;
    }

}

char checkWinner()
{
    //HORIZONTALLY CHECK
    for(i = 0; i < rows; i++)
    {
        // cols- 3 bc dont wanna go off the board
        for(j = 0; j < cols -3; j++)
        {
            // if the board is not empty at i,j and i,j is equal to 4 in a row then TRUE!!
            if(board[i][j] != ' ' 
            && board[i][j] == board[i][j+1]
            && board[i][j] == board[i][j+2]
            && board[i][j] == board[i][j+3])
            {
                return board[i][j];   
            }
        }
    }

    //Vertical Check
    //rows-3 bc dont wanna go off the board
    for(i = 0; i < rows-3; i++)
    {
        for(j = 0; j < cols; j++)
        {
            // if the board is not empty at i,j and i,j is equal to 4 in a row then TRUE!!
            if(board[i][j] != ' ' 
            && board[i][j] == board[i+1][j]
            && board[i][j] == board[i+2][j]
            && board[i][j] == board[i+3][j])
            {
                return board[i][j];   
            }
        }
    }

    // diagonal right check
    for(i = 0; i < rows-3; i++)
        {
            for(j = 0; j < cols -3; j++)
            {
                // if the board is not empty at i,j and i,j is equal to 4 in a row then TRUE!!
                if(board[i][j] != ' ' 
                && board[i][j] == board[i+1][j+1]
                && board[i][j] == board[i+2][j+2]
                && board[i][j] == board[i+3][j+3])
                {
                    return board[i][j];   
                }
            }
        }
    
    //diagonal left check
    for(i = 0; i < rows-3; i++)
    {
        for(j = 0; j < cols -3; j++)
        {
            // if the board is not empty at i,j and i,j is equal to 4 in a row then TRUE!!
            if(board[i][j] != ' ' 
            && board[i][j] == board[i+1][j-1]
            && board[i][j] == board[i+2][j-2]
            && board[i][j] == board[i+3][j-3])
            {
                return board[i][j];   
            }
        }
    }

    //no winner yet
    return ' ';
}




*/
