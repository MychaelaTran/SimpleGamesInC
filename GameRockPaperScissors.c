#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

char play;

char checkWinner(char player, char cp);
char computerMove();

int main()
{
    bool anotherGame = false;
    bool draw = false;
    
        
        // define variable for player's chosen move
        char chosen;
        // define variable for when there is a winner
        bool winner = false;

        printf("**********************************\n");
        printf("Welcome to Rock Paper Scissors!\n");
        printf("**********************************\n");

        // assign this so we can make if default case then it'll do loop again
        bool askAgain = true;
        // put in while loop for default case
        while (askAgain == true)
        {
            
            printf("Would you like to play (Y/N)?: ");

            // Consume whitespace characters, including newline, else infinite loop
            // for default case cause it won't be y or n it'll be new line char
            scanf(" %c", &play);
            play = toupper(play);

            switch (play)
            {
            case 'Y':
                printf("Great! Let's get started!\n");
                askAgain = false;
                break;

            case 'N':
                printf("Okay, thanks for coming!\n");
                askAgain = false;
                return 0;

            default:
                printf("Please enter a valid answer (Y/N)\n");
            }
        }
        do{ 
        while (winner == false)
        {
            bool valid = true;

            while(valid == true)
            {
                // get input from player
                printf("Please choose either rock, paper or scissors (R, P or S): ");
                scanf(" %c", &chosen);
                chosen = toupper(chosen);

                switch (chosen)
                {
                case 'R':
                case 'P':
                case 'S':
                    valid = false;
                    break;

                default:
                    printf("Please choose a valid move!\n");
                }
            
            }

                // get a move from computer
                char cpMove = computerMove();
                switch(cpMove)
                {
                    case 'R':
                    printf("The computer has choosen Rock...\n");
                    break; 

                    case 'S':
                    printf("The computer has choosen Scissors...\n");
                    break;

                    case 'P':
                    printf("The computer has choosen Paper...\n");
                    break;
                }

                // Call the checkWinner function and pass the player's move and computer's move
                char result = checkWinner(chosen, cpMove);
                bool validInputAgain = false;
                switch(result)
                {
                    case 'P':
                    winner = true;
                    printf("You won!!! YAYAYA SLAY!!\n");
                    break; 

                    case 'C':
                    winner = true;
                    printf("YOu lost LOSERRRRR!!!!\n");
                    break;



                    case 'D':
                    printf("It is a draw! Please input another move!\n");
                    askAgain = false;
                    validInputAgain = true;
                    break;
                    //fisodjsojfvodskjfps
                }

            char playAgain;
            
            while(validInputAgain == false)
            {
                //check if they wanna play again 
                
                printf("Would you like to play again? (Y/N): ");
                scanf(" %c", &playAgain);
                playAgain = toupper(playAgain);
                
                
                switch(playAgain)
                {
                    // if yes we reset all teh valyes to default and anotheGame to be true bc its all in a do loop rn 
                    case 'Y':
                    anotherGame = true;
                    validInputAgain = true;
                    winner = false;
                    valid = true;
                    break;

                    // if no it breaks and exits
                    case 'N':
                    printf("Thanks for playing, come again!\n");
                    anotherGame = false;
                    return 0;

                    default: 
                    printf("Please enter a valid (Y/N). \n");
                    valid = false;
                }
            }
            


        }

        
    }while (anotherGame == true);

    return 0;
}

char checkWinner(char player, char cp)
{
    switch(player)
    {
        case 'R':
        switch(cp)
        {
            
            case 'R':
            // D stands for draws and rteuns this info back to main fucnton to work with 
            return 'D';
         

            case 'S':
            // return player has won 
            return 'P';
          

            case 'P':
            // returns that the cp has won
            return 'C';
          
        }

        case 'P':
        switch(cp)
        {
            
            case 'R':
            // D stands for draws and rteuns this info back to main fucnton to work with 
            return 'P';

            case 'S':
            // return player has won 
            return 'C';

            case 'P':
            return 'D';
        }

        case 'S':
        switch(cp)
        {
            
            case 'R':
            // D stands for draws and rteuns this info back to main fucnton to work with 
            return 'C';

            case 'S':
            // return player has won 
            return 'D';

            case 'P':
            return 'P';
        }
        
    }
}

char computerMove()
{
    // seed time
    srand(time(0));
    // define variable for index of move
    int indexOfMove;
    // create array of characters of which moves cp can play
    char moves[3] = {'R', 'P', 'S'};
    // define var for cp moves
    char cpMove;
    // the index of move can be 0-2 because three different moves
    indexOfMove = rand() % 3;

    // Obtain the move the Cp will do
    cpMove = moves[indexOfMove];

    // return cp moves
    return cpMove;
}
