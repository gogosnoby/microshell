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
// zmiana
int main()
{
    while(true) 
    {
        char command[10];
        char currentpath[1024];
        getcwd(currentpath, sizeof(currentpath));
        printf(KGRN "[%s] $ " RESET, currentpath);
        fgets(command, sizeof command, stdin);
        if(strcmp(command,"help\n")==0)
        {
            printf(KRED "\n===MicroShell===\nAutor: Oskar Winiarski\n" RESET);
            printf(KRED "\nObslugiwane komendy :\nhelp\nexit\n\n" RESET);
        }
        else if(strcmp(command,"exit\n")==0)
            exit(0);

        else if(strcmp(command,"cat\n")==0)
        {
            char plik[100];
            scanf("%s", plik);
            char buffer[BUFFER_SIZE];
            int fd_in, num;

            fd_in = open(plik, O_RDONLY);

            while ((num = read(fd_in, &buffer, BUFFER_SIZE)) > 0)
            {
                write(STDOUT_FILENO, &buffer, num);
            }

            close(fd_in);
        }
        else if(strcmp(command,"pwd\n")==0)
        {
            char path[1024];
            getcwd(path, sizeof(path));
            printf("%s\n", path);
        }
    }

    return 0;
}
