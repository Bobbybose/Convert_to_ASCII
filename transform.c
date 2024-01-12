//Compiler Directives
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//Given: Current position in input line, current char being looked at, input line data, output line array, position in output line array
//Returns: None
//Purpose: Deals with strings that are in the input
void stringInput(int *position, char *currChar, char inputLine[], char outputData[], int *positionOutput){
    //Move up a spot in input line
    *position+=1;
    //Set currChar to new spot we're looking at
    currChar = &(inputLine[*position]);

    //Until the end of the string is reached
    while(*currChar != '"'){
        //Add the current char to the output
        outputData[*positionOutput] = inputLine[*position];
        //Move up a spot in the output array
        *positionOutput += 1; 

        //Move up a spot in input line
        *position+=1;
        //Set currChar to new spot we're looking at
        currChar = &(inputLine[*position]);
    }

    //Move up a spot in input line
    *position+=1;
}//stringInput


//Given: Current position in input line, current char being looked at, input line data, output line array, position in output line array
//Returns: None
//Purpose: Deals with hex numbers that are in the input
void hexInput(int *position, char *currChar, char inputLine[], char outputData[], int *positionOutput){
    //Current value of the current hex character
    int currValue;

    //Set curr char to the first digit of the hex value
    currChar = &(inputLine[(*position+2)]);

    //Second digit of the hex value
    char third = inputLine[*position+3];

    //Making sure the first hex value is in the appropriate range (0-9 and A-F or a-f)
    if( (*currChar > 47 && *currChar < 58) || (*currChar > 64 && *currChar < 71) || (*currChar > 96 && *currChar < 103)){
        //Making sure the second hex value is in the appropriate range (0-9 and A-F or a-f)
        if( (third > 47 && third < 58) || (third > 64 && third < 71) || (third > 96 && third < 103)){
            //Converting the hex value to ASCII
            sscanf(currChar, "%x", &currValue);

            //Add the ASCII value to the output
            outputData[*positionOutput] = currValue;
            //Move up a spot in the output array
            *positionOutput += 1; 

            //Moving up four spots in the input line (Hex value is four long 0xZz)    
            *position += 4;

            //Finished so returning
            return;
        }
    }

    //Informing the user that the hex value is invalid
    printf("Malformed Token: %c%c%c%c\n", inputLine[*position], inputLine[*position+1], *currChar, third );
    //Exiting the program
    exit(0);
}//hexInput


//Given: Current position in input line, current char being looked at, input line data, output line array, position in output line array
//Returns: 0 if number is in range, otherwise the number itself.
//Purpose: Deals with decimal numbers that are in the input
int decimalInput(int *position, char *currChar, char inputLine[], char outputData[], int *positionOutput){
    //Converting the current number to an int
    int number = atoi(currChar);
    
    //Going to be used for the ASCII equivalent
    char equivalent;
    
    //If the number is only one digit long
    if(number<10){
        //Move up a spot in the input array
        *position += 1;
    }

    //If the number is two digits long
    else if(number<100){
        //Move up two spots in the input array
        *position += 2;
    }

    //If the number is three digits long and in range
    else if(number<255){
        //Move up three spots in the input array
        *position += 3;
    }

    //Number is not in range
    else{
        return number;
    }

    //Converting the number to it's ASCII equivalent
    equivalent = number;

    //Add the ASCII value to the output
    outputData[*positionOutput] = equivalent;
    //Move up one spot in the input line
    *positionOutput += 1; 

    //Returning 0 if value was valid.
    return 0;
}//decimalInput


//Given: Output line array and position in output line array
//Returns: None
//Purpose: Prints the output to the standard output
void printOutput(char outputData[], int positionOutput){
    //For loop
    int i;

    //Looping through the output array
    for(i=0; i< positionOutput; i++){
        //Printing the current character
        printf("%c", outputData[i]);
    }

    //Printing a new line at the end
    printf("\n");
}//printOutput


//Given: Numbers of arguments and what they are
//Returns: None
//Purpose: Main program of the file
int main(int argc, char** argv){

    //Used for each input line
    char line[1024];
    //Length of the input
    int lengthOfLine;
    //Current character in the input being looked at
    char *currentChar;
    //Index value of input array being looked at right now
    int positionInLine = 0;

    //Used to store output
    char output[1024];
    //Where in the output we are (Also length of output)
    int positionInOutput = 0;

    //Used to inform whether decimal value is in range
    int status = 0;

    //Until the user is done inputing
    while(fgets(line, 1024, stdin) != NULL){

        //Setting the length of current line, not counting the newline at end
        lengthOfLine = strlen(line) -1; 

        //Starting at the beginning of the input line
        positionInLine = 0;

        //Keeps running. Break statements in loop control end
        while(1==1){

            //Find the first index of the line that isn't a space.
            while(( positionInLine < lengthOfLine) && (line[positionInLine] == ' ') ){
                positionInLine++;
            }
        
            //If there are only empty spaces in the line
            if(positionInLine>=lengthOfLine){
                break;
            }
            
            //Setting what the current character being looked at is
            currentChar = &(line[positionInLine]);
            
            //If the current character is the start of a string
            if(line[positionInLine] == '"'){
                //Call stringInput()
                stringInput(&positionInLine, currentChar, line, output, &positionInOutput);
            }

            //If the current character is a comment
            else if(*currentChar == '/' && line[positionInLine+1] == '/'){
                //Exit loop
                break;
            }
            
            //If the current character is a hex value
            else if(*currentChar == '0' && (line[positionInLine+1] == 'x' || line[positionInLine+1] == 'X') ){
                //Call hexInput()
                hexInput(&positionInLine, currentChar, line, output, &positionInOutput);
            }

            //If the current character is a decimal
            else if(*currentChar >= '0' && *currentChar <= '9'){
                //Call decimalInput(). Status becomes 0 if number is in range, otherwise it becomes the number's value
                status = decimalInput(&positionInLine, currentChar, line, output, &positionInOutput);
                //If the number was not in range
                if(status != 0 ){
                    //Informed the user the number was not in range
                    printf("Malformed Token: %d\n", status);
                    //Exit program
                    exit(0);
                }
            }

            //The current character is not a valid input
            else{
                //Inform the user the current character is not valid
                printf("Malformed Token: %c\n", *currentChar);
                //Exit program
                exit(0);
            }
        }

        


    }//while()

    //Print out the output
    printOutput(output, positionInOutput);

}//main()

