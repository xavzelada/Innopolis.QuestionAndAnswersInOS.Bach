#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/fs.h>
#include <fcntl.h>

void getSuperblock(char *path) {
    struct super_block *s_block
    char temp[1024];
    int fd = open(path, O_RDONLY);
    read(fd, temp, 1024 * sizeof(char));
    read(fd, &s_block, sizeof(struct super_block));
    close(fd);
}

int main(int argc, char **argv) {
    long beginning_partition[1000], end_partition[1000];
    struct ext2_super_block superblock;
    int block_size = 512, beginning_index, count = 0;
    int fd;

    disk = fopen(argv[2], "r");
    while (getline(&line, &len, disk) != -1) {
        beginning_index = 0;
        for (int i = 0; i < 3; i++) {
            if (line[i] == ' ') {
                beginning_index = i + 1;
                break;
            }
            ind[i] = line[i];
        }

        beginning_partition[count] = line + beginning_index;
        strcpy(path, argv[1]);
        strcat(path, ind);

        getSuperblock(path);

        end_partition[count] = superblock.s_blocks_count * block_size - beginning_partition[count];

        count++;
    }

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (i != j && beginning_partition[i] >= beginning_partition[j]) {
                if (beginning_partition[j] >= end_partition[i] || end_partition[i] <= end_partition[j]) {
                    printf("overlap");
                    return 0;
                }
            }
        }
    }

    printf("no overlap");
    return 0;
}