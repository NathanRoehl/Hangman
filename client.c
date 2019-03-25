//Nathan Roehl
//client program
//homework 8

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <string.h>

#include "shared.h"

void draw1();
void draw2();
void draw3();
void draw4();
void draw5();
void draw6();
void winner(char* word);
int replay();

int main(){

int repeat = 0;
while(repeat == 0)
{
int strlength = 0;

int s2 = socket(AF_UNIX, SOCK_STREAM, 0);
char buffer[BIGBUFF];
if(connect(s2, &serverSocket, sLength) == - 1){
printf("error in connection.\n");
exit(1);
} else {
read(s2,buffer,BIGBUFF);
}
close(s2);

char* word = strdup(strtok(buffer,"+"));
char* hint = strdup(strtok(NULL,"\0"));

int wordLen = strlen(word);
char hidden[wordLen];

word[wordLen] = '\0';		//null terminate word
hidden[wordLen] = '\0';		//null terminate hidden word

int found = 0;			//used to exit while loop
int qmCount = 0;		//used to count number of question marks
int guessWrong = 0;		//keeps track of number of incorrect guesses
char guessed[64];		//holds all guessed values
int correct = 0;		//tells if a correct answer was given
int totalGuess = 0;		//keeps track of number of guesses
int contains = 0;		//checks if letter was already tried

int i = 0;
for(i = 0; i < wordLen; i++){
//fill hidden array with question marks
//increment qmCount to keep track of total question marks
if(word[i] != ' '){
hidden[i] = '?';
qmCount++;
} else {
hidden[i] = ' ';
}
}

printf("\nHint: %s\n", hint);
char buff[128];
char c = NULL;

//start of game, if int found == anything but zero either
//user won or lost the game and program will end.
while(found == 0){
fflush(stdin);

printf("Common Phrase\n");
printf("--------------------------------\n");
printf("%s\n",hidden);
printf("\n<------------------------------>");
printf("\nEnter a single character guess: ");

//makes sure to only get single character from user
while(1){
int i = 0;

//read input from user
fflush(stdin);
while((c = getchar()) != '\n'){
	buff[i++] = c;
}
buff[i] = '\0';

if(strlen(buff) != 1) {
printf("Enter a single character guess: ");
continue;
}

contains = 0;
for(i = 0; i < totalGuess; i++){
	if(buff[0] == guessed[i]){
	printf("You have already tried the letter \"%c\".\n", buff[0]);
	printf("Enter a single character guess: ");
	contains = 1;
	}
}
if(contains == 0){
guessed[totalGuess] = buff[0];
totalGuess++;
break;
}

} //end of while loop to read guess

//correct meant to tell if guess was in the word
correct = 0;
for(i = 0; i < wordLen; i++){
	if(buff[0] == word[i] && hidden[i] == '?') {
		hidden[i] = word[i];
		qmCount--;
		correct = 1;
	 }
}


//if correct is zero means incorrect guess
//draws a picture depending on how many incorrect guesses
if(correct == 0){
printf("Incorrect quess.\n");

guessWrong++;

if(guessWrong == 1){
draw1();
} else if(guessWrong == 2){
draw2();
} else if(guessWrong == 3){
draw3();
} else if(guessWrong == 4){
draw4();
} else if(guessWrong == 5){
draw5();
} else if(guessWrong == 6){
draw6();
found = 1;
}
} else if( qmCount != 0){
printf("\nCorrect guess! Letter \"%c\" is in the answer.\n\n",buff[0]);

}

if(guessWrong >= 0 && guessWrong < 6){

printf("Previous guesses:");
for(i = 0; i < totalGuess; i++){
printf(" %c",guessed[i]);
}
printf("\n");
int x = 6-guessWrong;

if(x>1){
printf("You have %d incorrect guesses left.\n",x);
} else {
printf("You have %d incorrect guess left.\n",x);
}
printf("<------------------------------>\n\n");
}

//check if any question marks left
//if not they guessed the correct answer
if(qmCount == 0){
found = 1;

}

}//end of outer while loop and game

if(qmCount == 0){
printf("\nWooHoo! You solved it.\n");
winner(word);
repeat = replay();
} else {
printf("\nI'm sorry but you lost.\n");
printf("The answer was: %s\n",word);
repeat = replay();
}

free(word);
free(hint);
}//end of out while loop

printf("Thanks for playing. Goodbye.\n");
return 0;
}//end of main

int replay(){

printf("Would you like to play again?\n");
printf("Enter 'y' to keep playing.\n");
char c;
scanf("%c",&c);

int value = 0;
if(c != 'y'){
value = 1;
}
fflush(stdin);
fflush(stdout);
return value;
}

void draw1(){
printf("\n");
printf("  ____________ \n");
printf("      |     |  \n");
printf("     [ ]    |  \n");
printf("            |  \n");
printf("            |  \n");
printf("            |  \n");
printf("            |  \n");
printf("____________|__\n\n");
}

void draw2(){
printf("\n");
printf("  ____________ \n");
printf("      |     |  \n");
printf("     [ ]    |  \n");
printf("      |     |  \n");
printf("      |     |  \n");
printf("            |  \n");
printf("            |  \n");
printf("____________|__\n\n");

}

void draw3(){
printf("\n");
printf("  ____________ \n");
printf("      |     |  \n");
printf("     [ ]    |  \n");
printf("     /|     |  \n");
printf("      |     |  \n");
printf("            |  \n");
printf("            |  \n");
printf("____________|__\n\n");

}
void draw4(){
printf("\n");
printf("  ____________ \n");
printf("      |     |  \n");
printf("     [ ]    |  \n");
printf("     /|\\    |  \n");
printf("      |     |  \n");
printf("            |  \n");
printf("            |  \n");
printf("____________|__\n\n");

}
void draw5(){
printf("\n");
printf("  ____________ \n");
printf("      |     |  \n");
printf("     [ ]    |  \n");
printf("     /|\\    |  \n");
printf("      |     |  \n");
printf("     /      |  \n");
printf("            |  \n");
printf("____________|__\n\n");

}

void draw6(){
printf("\n");
printf("  ____________ \n");
printf("      |     |  \n");
printf("     [ ]    |  \n");
printf("     /|\\    |  \n");
printf("      |     |  \n");
printf("     / \\    |  \n");
printf("            |  \n");
printf("____________|__\n\n");

}

void winner(char * word){
printf("                          ___  __   \n");
printf("\\        / | |\\  | |\\  | |    |__| |\n");
printf(" \\  /\\  /  | | \\ | | \\ | |-   |\\   |\n");
printf("  \\/  \\/   | |  \\| |  \\| |___ | \\  o\n");
printf("\n");

printf("Answer was: %s\n\n",word);

}

