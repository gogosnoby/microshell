#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

#define BUFFER_SIZE 1024
#define _XOPEN_SOURCE 500

int getlogin_r(char *name, size_t namesize);

int main()
{
    while(true)
    {
        char command[100];
        char currentpath[1024];
        char login[1024];
        char *maincommand;
        char separator[] = " ";


        getlogin_r(login, 1024);
        printf(KBLU "%s:" RESET, login);
        getcwd(currentpath, sizeof(currentpath));
        printf(KGRN "[%s] $ " RESET, currentpath);

        fgets(command, 100, stdin);
        if(command[strlen(command)-1=='\n'] && strlen(command)!=1)
            command[strlen(command)-1]=0;
        else
            continue;
        char temp[strlen(command)];
        strcpy(temp,command);
        maincommand=strtok(temp, separator);


        if(strcmp(maincommand,"help")==0)
        {
            if(strlen(command)==strlen(maincommand))
            {
                printf(KRED "\n===MicroShell===\nAutor: Oskar Winiarski\n" RESET);
                printf(KRED "\nObslugiwane komendy :\nhelp\nexit\n\n" RESET);
            }
            else if(strlen(command)!=strlen(maincommand))
                printf("Wrong argument for command %s.\n", maincommand);
        }
        else if(strcmp(maincommand,"exit")==0)
        {
            if(strlen(command)==strlen(maincommand))
            {
                exit(0);
            }
            else if(strlen(command)!=strlen(maincommand))
                printf("Wrong argument for command %s.\n", maincommand);
        }
        else if(strcmp(maincommand,"cd")==0)
        {
            char dotdot[2]="..";
            maincommand=strtok(NULL,separator);
            if(maincommand!=NULL)
            {
                while(maincommand!=NULL)
                {
                    if(strcmp(maincommand,dotdot)==0)
                    {
                        chdir("..");
                        break;
                    }
                    else
                    {
                        if(chdir(maincommand)==-1)
                            printf("No such directory.\n");
                        else
                            chdir(maincommand);
                    }

                    maincommand=strtok(NULL,separator);
                }
            }
            else
            {
                printf("domowy\n");
            }
        }
        else if(strcmp(maincommand,"cat")==0)
        {
            char *plik;
            plik=strtok(NULL,separator);
            maincommand=strtok(NULL,separator);
            if(maincommand==NULL)
            {
                printf("%s git\n", plik);
            }
        }
        else if(strcmp(maincommand,"pwd")==0)
        {
            char path[1024];
            getcwd(path, sizeof(path));
            printf("%s\n", path);
        }
        else
            printf("command %s not found.\n", maincommand);
    }

    return 0;
}
