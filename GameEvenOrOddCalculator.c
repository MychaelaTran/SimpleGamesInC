#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>



// Check even or odd but can do any calculation you want

// Function prototype
bool checkEvenOrOdd(double x);

int main() {
    double x;   //og num stored
    double y;   // num they MAY choose to perfom ops with stored
    char response;  // is yes or no stored
    char calculation;

    // takes og number they want to check if even or odd
    printf("Please enter a number you want to check if even or odd: ");
    scanf("%lf", &x);

    // takes resonse of 'Y' ~ yes or 'N' ~ no
    printf("Would you like to perform calculations on this number? (Y/N): ");
    scanf(" %c", &response);
    
    // uppercase response in case lowercase was input
    response = toupper(response);

    // while the reponse is 'Y', we enter this while loop (bc can perfom more than one op if desired)
    while (response == 'Y') 
    {
        // set a variable validOp to false that is used if false to prompt user to enter valid op if an invalid one was inputted
        bool validOp = false;

        //if the valid op is false(initally is, it enters this while loop)
        while(!validOp)
        {

            // immediatley prompted with which op they want to perform
            printf("Which operation would you like to perform? (+ - x /)?: ");
            scanf(" %c", &calculation);

            // use a switch to compare the diff options that could've been inputted
            switch (calculation) 
            {
                case '+':
                    printf("Which number do you want to add?: ");
                    scanf("%lf", &y);
                    x = x + y;
                    validOp = true;     // if it matches one of the ops, the validOp swithces to true and will no longer enter this while loop
                    break;              //  same for all the operations

                case '-':
                    printf("Which number do you want to subtract?: ");
                    scanf("%lf", &y);
                    x = x - y;
                    validOp = true;
                    break;

                case 'x':
                    printf("Which number do you want to multiply by?: ");
                    scanf("%lf", &y);
                    x = x * y;
                    validOp = true;
                    break;

                case '/':
                    printf("Which number do you want to divide by?: ");
                    scanf("%lf", &y);
                    x = x / y;
                    validOp = true;
                    break;

                default:
                    printf("Please enter one of the specified operations\n");
                    // however if the input matches none of the case statment (opeations), then validOp is not set to true and enters this inner while loop again
                    // ie prompting the user for a specified operation 
            }
        }

        // ask the user if they want to perfom another op, if yes then we enter the outer while loop again and repeat 
        printf("Would you like to perform another operation (Y/N): ");
        scanf(" %c", &response);
        response = toupper(response);
    }

    // now we check if the number is even or odd using a funciton (once reaches here the user has input 'N' for no additional operation to their numebr)
    if (checkEvenOrOdd(x)) {
        printf("%.2lf is even!\n", x);
    } else {
        printf("%.2lf is odd!\n", x);
    }

    return 0;
}

// Function definition
bool checkEvenOrOdd(double x) 
{
    // multiply the double by 100 (since it only has 2 decimal places and make it into an int to be able to use the % operator)
    int multipliedBy10 = (int)(x * 100);

    // if the number % 200 == 0 will only happen if the number has no zeros as decimals and the number is not divisble by 200
    // this makes it so that if the num has non zero decimals, it wont be divisible by any hundred AND
    //if the number has non zero decimals but is odd it wont mod into 200 evenly bc 200 is even, even if the number is a whole number 
    return (multipliedBy10 % 200 == 0);

}
    



