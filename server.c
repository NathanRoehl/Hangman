//Nathan Roehl
//server program
//homework 8

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>

#include "shared.h"

void ctrlc();

int main(int argc, char * argv[]){

Answer* answers[64] = {NULL};

int counter = 0;
FILE* fin = fopen("phrases.txt","r");
if(fin == NULL){
printf("Could not open file.\n");
exit(1);
}

char buff[BIGBUFF];
Answer* tmp = NULL;;
int i = 0;
//int len = 0;

while(fgets(buff,BIGBUFF,fin) != NULL){
tmp = (Answer*)malloc(sizeof(Answer));
char* token = strtok(buff,":");
tmp->answer = strdup(token);
token = strtok(NULL, "\0");
tmp->hint = strdup(token);
answers[i] = tmp;
i++;
counter++;
}

fclose(fin);

//for loop to print answers with hints 
/*i = 0;
while(answers[i]){
printf("%s, %s\n",answers[i]->answer, answers[i]->hint);
i++;
}*/

/////////////////////end of reading from file to create array of struct answers

printf("Welcome to my server. Hit ctrl c to exit program.\n");
struct sigaction endProgram;
struct sigaction original;

void ctrlc(){
printf("\nExiting server.  Goodbye.\n");
unlink("server1");
int i = 0;
while(answers[i]){
free(answers[i]->answer);
free(answers[i]->hint);
answers[i] = NULL;
i++;
}
sigaction(SIGINT, &original, NULL);
exit(0);
}

endProgram.sa_handler = ctrlc;
endProgram.sa_flags = 0;

sigaction(SIGINT, &endProgram, &original);



///////////////////////////////////////////////////////////////end of sigaction

int s0 = socket(AF_UNIX, SOCK_STREAM, 0);
if(s0==-1) {return -1;}

if(bind(s0,&serverSocket, sLength)==-1){return -1;}//bind to server1

int s1;

if(listen(s0,1) == -1)
{
printf("Listen failed.\n");
return -1;
}
char socketBuff[BIGBUFF];

int index = 0;

//while loop to infinitely listen
while(1){

if((s1 = accept(s0,&serverSocket, &sLength)) != -1){

//old tests
//printf("Connection made.\n"); //for debugging
//int len1 = strlen(answers[index]->answer);
//len1 += strlen(answers[index]->hint);
//len1 += 2;

strcpy(socketBuff,answers[index]->answer);
strcat(socketBuff,"+");
strcat(socketBuff,answers[index]->hint);
//printf("String:%s\n",socketBuff); //for debugging

write(s1,socketBuff,BIGBUFF);
index++;

if(index == counter){
index = 0;
}
}

} //end of while loop

return 0;
}


