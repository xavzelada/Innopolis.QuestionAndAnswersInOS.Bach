#include <stdio.h>
#include "unistd.h"
#include "sys/wait.h"
#include "string.h"

int main(void) {
    int id;
    char *command, *filename, *parameters[128], input[128];
    while (1) {
        fgets(input,128,stdin);
        if (input[0]=='\n') //check empty input ('\n')
            continue; //if we face it, then start new loop
        // Now we break our input string on words
        char *token;
        token = strtok(input," ");
        id=0;
        while(token!=NULL){
            parameters[id]=token;
            token = strtok(NULL," ");
            id++;
        }
        parameters[id-1][strlen(parameters[id-1])-1]='\0';//removing '\n' from the last word
        parameters[id]=NULL;
        //our command lies in first word that we receive after separation of input string
        command=parameters[0];
        int idOfSpecialOutput=-1;
        for (int i=0; i<id; i++) {
            if (strcmp(parameters[i],">>")==0) {
                idOfSpecialOutput=i;
                break;
            }
        }
        filename=NULL;
        if (idOfSpecialOutput!=-1)
            filename=parameters[idOfSpecialOutput+1];

        int amper =0;
        if (strcmp(parameters[id-1],"&")==0) {
            amper=1;
            parameters[id-1]=NULL;
            id--;
        }
        if (idOfSpecialOutput!=-1) {
            parameters[idOfSpecialOutput]=NULL;
            id=idOfSpecialOutput;
        }
        //check on existence of command, since case with string numerous spaces might happen.
        if (strcmp(command,"")!=0) {
            if (strcmp(command,"exit")==0)//exit command for terminating a process
                break;
            if (fork()!=0) {
                if (amper==0)//we won't wait a child process if it works in background.
                    wait (NULL);//wait for child
            } else {
                if (filename!=NULL)
                    freopen(filename, "a", stdout);
                if (execvp(command, parameters) < 0) {
                    //if there is something wrong with command or parameters we'll receive error
                    printf("Error");
                }
            }
        }
    }
}
