#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>

unsigned long getTime(FILE* f, char* time_s){
    unsigned long time, stime;
    for (int i = 0; i < 11; i++)
        fscanf(f, "%lu", &time);
    fscanf(f, "%lu", &stime);

    time = (int)((double)(time + stime) / sysconf(_SC_CLK_TCK));
    sprintf(time_s, "%02lu:%02lu:%02lu",(time / 3600) % 3600, (time / 60) % 60, time % 60);
}

int main(int argc, char** argv){
    DIR *dirp = opendir("/proc");

    int descriptor_var, descriptor = open("/proc/self/fd/0", O_RDONLY);
    char *tty = malloc(sizeof(char) * 1000);
    sprintf(tty, "%s", ttyname(descriptor));
    printf("%s %s %s %s\n", "CMD", "PID", "TTY", "TIME");

    struct dirent *dp;
    int isDigits;
    FILE* file;
    char *tty_var;
    char *time = malloc(sizeof(char) * 1000);
    char *cmd = malloc(sizeof(char) * 1000);
    char *path = malloc(sizeof(char) * 1000);
    char *temp = malloc(sizeof(char) * 1000)
    int i;
    while ((dp = readdir(dirp)) != NULL) {
        isDigits = 1;
        for (i = 0; dp->d_name[i]; ++i)
            if (!isdigit(dp->d_name[i])) {
                isDigits = 0;
                break;
            }

        if (isDigits) {
            sprintf(path, "/proc/%s/fd/0", dp->d_name);
            descriptor_var = open(path, O_RDONLY);
            tty_var = ttyname(descriptor_var);

            if (tty_var && strcmp(tty_var, tty) == 0) {
                sprintf(path, "/proc/%s/stat", dp->d_name);
                file = fopen(path, "r");
                fscanf(file, "%d%s%s%s%s", &i, cmd, &temp, &temp, &temp);
                printf("%s %s %s %lu\n", cmd, dp->d_name, tty_var, getTime(file, time));
                fclose(file);
            }
            close(descriptor_var);
        }
    }
    close(descriptor);
    return 0;
}