#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>

int check_digits(char* str){
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] < 48 || str[i] > 57) {
            return 0;
        }
    }
    return 1;
}

int main(){
    char* proc = "/proc/";
    char* fd_path = "/fd/0";
    char path[128], cmd[128];
    DIR* dir = opendir(proc);
    FILE* file;
    struct dirent* dir_ent;
    int fd = open("/proc/self/fd/0", O_RDONLY), pid;
    char tty[128], * tty_process;
    strcpy(tty, ttyname(fd));
    close(fd);
    
    printf("\tPID\tTTY\tCMD\n");
    while ((dir_ent = readdir(dir)) != NULL){
        if (check_digits(dir_ent->d_name)) {
            strcpy(path, proc);
            strcat(path, dir_ent->d_name);
            strcat(path, fd_path);
            fd = open(path, O_RDONLY);
            tty_process = ttyname(fd);
            close(fd);
            if (tty_process != NULL) {
                if (strcmp(tty, tty_process) == 0) {
                    strcpy(path, proc);
                    strcat(path, dir_ent->d_name);
                    strcat(path, "/stat");
                    file = fopen(path, "r");
                    fscanf(file, "%d %s", &pid, cmd);
                    printf("\t%d\t%s\t%s\n", pid, tty+5, cmd);
                }
            }
        }
    }
}