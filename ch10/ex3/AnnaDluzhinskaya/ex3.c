#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/fs.h>
#include <sys/ioctl.h>

struct super_block {
    __le32  s_inodes_count;     
    __le32  s_blocks_count;
};

int getDiskSize(char * s){
	int temp;
	int fd = open(s, O_RDONLY);
    ioctl(fd, BLKGETSIZE64, &temp);
    close(fd);
    temp = temp/512;
    return temp;
}

void getIndex(char *s1, char *s2){
	int j = 0;
    for (int i = 0; i < 3; i++) {
        if (s1[i] == ' ') {
            j = i + 1;
            break;
        }
        s2[i] = s1[i];
    }	
}

void getPath(char *s1, char *s2, char *s){
    strcpy(s, s1);
    strcat(s, s2);
}

void getSuperBlock(char *path, struct super_block *s_block){
    char trash[1024];
    int fd = open(path, O_RDONLY);
    read(fd, trash, 1024*sizeof(char));
    read(fd, &s_block, sizeof(struct super_block));
    close(fd);
}

int main(int argc, char **argv){
	struct super_block s_block;
	FILE * d_file;
	int k;
    char index[3], path[128];
    unsigned long d_size;
    long long first[20], last[20];
    char num[32];
    char * line;
    size_t l;

    k = 0;
    d_size = getDiskSize(argv[1]);

    d_file = fopen(argv[2], "r");
    while (getline(&line, &l, d_file) != -1) {
        getIndex(line,index);
        
        strcpy(num, line+strlen(index)+2);
        first[k] = atoll(num);
        
        getPath(argv[1], argv[1], path);
        
        getSuperBlock(path, &s_block);
        
        last[k] = last[k] + (long long)s_block.s_blocks_count*4096/512 - 1;
        count++;
    }

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            if (i != j) {
                if ((first[i] <= last[j]&&first[i] >= first[j])||(last[i] >= first[j] && last[i] <= first[j])) {
                    printf("overlaping!");
                    return -1;
                }
            }
        }
    }
}
