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

struct ext2_super_block {
    __le32  s_inodes_count;     /* Inodes count */
    __le32  s_blocks_count;     /* Blocks count */
    __le32  s_r_blocks_count;   /* Reserved blocks count */
    __le32  s_free_blocks_count;    /* Free blocks count */
    __le32  s_free_inodes_count;    /* Free inodes count */
    __le32  s_first_data_block; /* First Data Block */
    __le32  s_log_block_size;   /* Block size */
    __le32  s_log_frag_size;    /* Fragment size */
    __le32  s_blocks_per_group; /* # Blocks per group */
    __le32  s_frags_per_group;  /* # Fragments per group */
    __le32  s_inodes_per_group; /* # Inodes per group */
    __le32  s_mtime;        /* Mount time */
    __le32  s_wtime;        /* Write time */
    __le16  s_mnt_count;        /* Mount count */
    __le16  s_max_mnt_count;    /* Maximal mount count */
    __le16  s_magic;        /* Magic signature */
    __le16  s_state;        /* File system state */
    __le16  s_errors;       /* Behaviour when detecting errors */
    __le16  s_minor_rev_level;  /* minor revis#include <stdio.h>
#include <stdlib.h>ion level */
    __le32  s_lastcheck;        /* time of last check */
    __le32  s_checkinterval;    /* max. time between checks */
    __le32  s_creator_os;       /* OS */
    __le32  s_rev_level;        /* Revision level */
    __le16  s_def_resuid;       /* Default uid for reserved blocks */
    __le16  s_def_resgid;       /* Default gid for reserved blocks */
    /*
    * These fields are for EXT2_DYNAMIC_REV superblocks only.
    *
    * Note: the difference between the compatible feature set and
    * the incompatible feature set is that if there is a bit set
    * in the incompatible feature set that the kernel doesn't
    * know about, it should refuse to mount the filesystem.
    * 
    * e2fsck's requirements are more strict; if it doesn't know
    * about a feature in either the compatible or incompatible
    * feature set, it must abort and not try to meddle with
    * things it doesn't understand...
    */
    __le32  s_first_ino;        /* First non-reserved inode */
    __le16   s_inode_size;      /* size of inode structure */
    __le16  s_block_group_nr;   /* block group # of this superblock */
    __le32  s_feature_compat;   /* compatible feature set */
    __le32  s_feature_incompat;     /* incompatible feature set */
    __le32  s_feature_ro_compat;    /* readonly-compatible feature set */
    __u8    s_uuid[16];     /* 128-bit uuid for volume */
    char    s_volume_name[16];  /* volume name */
    char    s_last_mounted[64];     /* directory where last mounted */
    __le32  s_algorithm_usage_bitmap; /* For compression */
    /*
    * Performance hints.  Directory preallocation should only
    * happen if the EXT2_COMPAT_PREALLOC flag is on.
    */
    __u8    s_prealloc_blocks;  /* Nr of blocks to try to preallocate*/
    __u8    s_prealloc_dir_blocks;  /* Nr to preallocate for dirs */
    __u16   s_padding1;
    /*
    * Journaling support valid if EXT3_FEATURE_COMPAT_HAS_JOURNAL set.
    */
    __u8    s_journal_uuid[16]; /* uuid of journal superblock */
    __u32   s_journal_inum;     /* inode number of journal file */
    __u32   s_journal_dev;      /* device number of journal file */
    __u32   s_last_orphan;      /* start of list of inodes to delete */
    __u32   s_hash_seed[4];     /* HTREE hash seed */
    __u8    s_def_hash_version; /* Default hash version to use */
    __u8    s_reserved_char_pad;
    __u16   s_reserved_word_pad;
    __le32  s_default_mount_opts;
    __le32  s_first_meta_bg;    /* First metablock block group */
    __u32   s_reserved[190];    /* Padding to the end of the block */
};


/*
    Example of execution: 
    sudo ./ex3 /dev/sda ./descriptor
*/
int main(int argc, char **argv){
	FILE *descriptor_file;
    struct ext2_super_block sp;
	int block_size_for_ext4 = 4096, block_size_default = 512, count = 0, j = 0;
    char ind[3], path[128];
    unsigned long disk_size;
    long long starts[20], ends[20], start, end;
    char boot[1024], num[32];

    char * line = NULL;
    size_t len = 0;

    int fd = open(argv[1], O_RDONLY);
    ioctl(fd, BLKGETSIZE64, &disk_size);
    close(fd);
    disk_size = disk_size/block_size_default;

    descriptor_file = fopen(argv[2], "r");
    while (getline(&line, &len, descriptor_file) != -1) {
        j = 0;
        for (int i = 0; i < 3; i++) {
            if (line[i] == ' ') {
                j = i + 1;
                break;
            }
            ind[i] = line[i];
        }
        strcpy(num, line+j);
        starts[count] = atoll(num);
        strcpy(path, argv[1]);
        strcat(path, ind);
        fd = open(path, O_RDONLY);
        read(fd, boot, 1024*sizeof(char));
        read(fd, &sp, sizeof(struct ext2_super_block));
        close(fd);
        ends[count] = starts[count] + (long long)sp.s_blocks_count*block_size_for_ext4/block_size_default - 1;
        count++;
    }

    for (int i = 0; i < count; i++) {
        for (j = 0; j < count; j++) {
            if (i != j) {
                if (starts[i] >= starts[j] && starts[i] <= ends[j]) {
                    printf("OVERLAPING");
                    return 0;
                }
                if (ends[i] >= starts[j] && ends[i] <= ends[j]) {
                    printf("OVERLAPING");
                    return 0;
                }
                if (ends[i] > disk_size) {
                    printf("INCORRECT BLOCK LENGTH");
                    return 0;
                }
            }
        }
    }
    printf("NO OVERLAPING");
}