#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>

int check(char* str){
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] < 48 || str[i] > 57) {
            return 0;
        }
    }
    return 1;
}

void getTTY(int fd, char* tty) {
	strcpy(tty, ttyname(fd));
	close(fd);
}

char* getPath(char* s1, char *s2, char* s3) {
	
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    size_t len3 = strlen(s3);                      

    char *result = malloc(len1+len2+len3);

    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2);
    memcpy(result + len1 + len2, s3, len3);

    return result;
}

void getTime(FILE* f, char* time_s){
	unsigned long time, stime;
	for (int i = 0; i < 11; i++)
	   fscanf(f, "%lu", &time);
    fscanf(f, "%lu", &stime);
    time = (int)((double)(time + stime) / sysconf(_SC_CLK_TCK));
    sprintf(time_s, "%02lu:%02lu:%02lu",(time / 3600) % 3600, (time / 60) % 60, time % 60);
}

void getCmd(char *s){
	for (int i = 0; i< strlen(s)-1; i++){
		s[i] = s[i+1];	
	}
	s[strlen(s)-2]='\0';
}

int main(){
    char path[128], cmd[128], tty[128], time[256];
    char * process;
    FILE* f;
    struct dirent* temp;
    int pid;
    char trash;
    DIR* dir = opendir("/proc/");
    int fd = open("/proc/self/fd/0", O_RDONLY);
    
    getTTY(fd,tty);
    
    printf("PID\tTTY\tTIME\t\tCMD\n");
    while ((temp = readdir(dir)) != NULL){
        if (check(temp->d_name)) {
            fd = open(getPath("/proc/", temp->d_name,"/fd/0"), O_RDONLY);
            process = ttyname(fd);
            close(fd);
            if (process != NULL) {
                if (strcmp(tty, process) == 0) {
                    f = fopen(getPath("/proc/", temp->d_name,"/stat"), "r");
                    fscanf(f, "%d%s%c%c%c", &pid, cmd, &trash, &trash, &trash);
                    getTime(f, time);
                    getCmd(cmd);
                    printf("%d\t%s\t%s\t%s\n", pid, tty+5, time, cmd);
                }
            }
        }
    }
}
