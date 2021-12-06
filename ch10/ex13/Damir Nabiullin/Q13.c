#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <fcntl.h>

struct termios settings;
struct winsize wins;
int baud[16] = {0,  50,  75,  110,  134,  150,  200,  300,  600,  1200,  1800,  2400,  4800,  9600,  19200,  38400};

void update(char sign,  char* cmd) {
    if (strcmp(cmd,  "ignbrk") == 0) {
        if (sign == '-') {
            settings.c_iflag &=  ~IGNBRK;
        } else {
            settings.c_iflag |= IGNBRK;
        }
    }
    if (strcmp(cmd,  "brkint") == 0) {
        if (sign == '-') {
            settings.c_iflag &=  ~BRKINT;
        } else {
            settings.c_iflag |= BRKINT;
        }
    } 
    if (strcmp(cmd,  "ignpar") == 0) {
        if (sign == '-') {
            settings.c_iflag &=  ~IGNPAR;
        } else {
            settings.c_iflag |= IGNPAR;
        }
    }
    if (strcmp(cmd,  "parmrk") == 0) {
        if (sign == '-') {
            settings.c_iflag &=  ~PARMRK;
        } else {
            settings.c_iflag |= PARMRK;
        }
    } 
    if (strcmp(cmd,  "inpck") == 0) {
        if (sign == '-') {
            settings.c_iflag &=  ~INPCK;
        } else {
            settings.c_iflag |= INPCK;
        }
    }  
    if (strcmp(cmd,  "istrip") == 0) {
        if (sign == '-') {
            settings.c_iflag &=  ~ISTRIP;
        } else {
            settings.c_iflag |= ISTRIP;
        }
    } 
    if (strcmp(cmd,  "inlcr") == 0) {
        if (sign == '-') {
            settings.c_iflag &=  ~INLCR;
        } else {
            settings.c_iflag |= INLCR;
        }
    }  
    if (strcmp(cmd,  "igncr") == 0) {
        if (sign == '-') {
            settings.c_iflag &=  ~IGNCR;
        } else {
            settings.c_iflag |= IGNCR;
        }
    } 
    if (strcmp(cmd,  "icrnl") == 0) {
        if (sign == '-') {
            settings.c_iflag &=  ~ICRNL;
        } else {
            settings.c_iflag |= ICRNL;
        }
    } 
    if (strcmp(cmd,  "ixon") == 0) {
        if (sign == '-') {
            settings.c_iflag &=  ~IXON;
        } else {
            settings.c_iflag |= IXON;
        }
    } 
    if (strcmp(cmd,  "ixoff") == 0) {
        if (sign == '-') {
            settings.c_iflag &=  ~IXOFF;
        } else {
            settings.c_iflag |= IXOFF;
        }
    }  
    if (strcmp(cmd,  "iuclc") == 0) {
        if (sign == '-') {
            settings.c_iflag &=  ~IUCLC;
        } else {
            settings.c_iflag |= IUCLC;
        }
    }  
    if (strcmp(cmd,  "ixany") == 0) {
        if (sign == '-') {
            settings.c_iflag &=  ~IXANY;
        } else {
            settings.c_iflag |= IXANY;
        }
    } 
    if (strcmp(cmd,  "imaxbel") == 0) {
        if (sign == '-') {
            settings.c_iflag &=  ~IMAXBEL;
        } else {
            settings.c_iflag |= IMAXBEL;
        }
    }
    if (strcmp(cmd,  "iutf8") == 0) {
        if (sign == '-') {
            settings.c_iflag &=  ~IUTF8;
        } else {
            settings.c_iflag |= IUTF8;
        }
    }
    if (strcmp(cmd,  "parenb") == 0) {
        if (sign == '-') {
            settings.c_cflag &=  ~PARENB;
        } else {
            settings.c_cflag |= PARENB;
        }
    } 
    if (strcmp(cmd,  "parodd") == 0) {
        if (sign == '-') {
            settings.c_cflag &=  ~PARODD;
        } else {
            settings.c_cflag |= PARODD;
        }
    }  
    if (strcmp(cmd,  "cmspar") == 0) {
        if (sign == '-') {
            settings.c_cflag &=  ~CMSPAR;
        } else {
            settings.c_cflag |= CMSPAR;
        }
    }  
    if (strcmp(cmd,  "cs5") == 0) {
        if (sign == '-') {
            settings.c_cflag &=  ~CSIZE;
        } else {
            settings.c_cflag &=  ~CSIZE;
            settings.c_cflag |= CS5;
        }
    } 
    if (strcmp(cmd,  "cs6") == 0) {
        if (sign == '-') {
            settings.c_cflag &=  ~CSIZE;
        } else {
            settings.c_cflag &=  ~CSIZE;
            settings.c_cflag |= CS6;
        }
    } 
    if (strcmp(cmd,  "cs7") == 0) {
        if (sign == '-') {
            settings.c_cflag &=  ~CSIZE;
        } else {
            settings.c_cflag &=  ~CSIZE;
            settings.c_cflag |= CS7;
        }
    } 
    if (strcmp(cmd,  "cs8") == 0) {
        if (sign == '-') {
            settings.c_cflag &=  ~CSIZE;
        } else {
            settings.c_cflag &=  ~CSIZE;
            settings.c_cflag |= CS8;
        }
    } 
    if (strcmp(cmd,  "hupcl") == 0) {
        if (sign == '-') {
            settings.c_cflag &=  ~HUPCL;
        } else {
            settings.c_cflag |= HUPCL;
        }
    } 
    if (strcmp(cmd,  "cstopb") == 0) {
        if (sign == '-') {
            settings.c_cflag &=  ~CSTOPB;
        } else {
            settings.c_cflag |= CSTOPB;
        }
    }
    if (strcmp(cmd,  "cread") == 0) {
        if (sign == '-') {
            settings.c_cflag &=  ~CREAD;
        } else {
            settings.c_cflag |= CREAD;
        }
    }
    if (strcmp(cmd,  "clocal") == 0) {
        if (sign == '-') {
            settings.c_cflag &=  ~CLOCAL;
        } else {
            settings.c_cflag |= CLOCAL;
        }
    } 
    if (strcmp(cmd,  "crtscts") == 0) {
        if (sign == '-') {
            settings.c_cflag &=  ~CRTSCTS;
        } else {
            settings.c_cflag |= CRTSCTS;
        }
    }
    if (strcmp(cmd,  "opost") == 0) {
        if (sign == '-') {
            settings.c_oflag &=  ~OPOST;
        } else {
            settings.c_oflag |= OPOST;
        }
    }  
    if (strcmp(cmd,  "olcuc") == 0) {
        if (sign == '-') {
            settings.c_oflag &=  ~OLCUC;
        } else {
            settings.c_oflag |= OLCUC;
        }
    }
    if (strcmp(cmd,  "ocrnl") == 0) {
        if (sign == '-') {
            settings.c_oflag &=  ~OCRNL;
        } else {
            settings.c_oflag |= OCRNL;
        }
    } 
    if (strcmp(cmd,  "onlcr") == 0) {
        if (sign == '-') {
            settings.c_oflag &=  ~ONLCR;
        } else {
            settings.c_oflag |= ONLCR;
        }
    }
    if (strcmp(cmd,  "onocr") == 0) {
        if (sign == '-') {
            settings.c_oflag &=  ~ONOCR;
        } else {
            settings.c_oflag |= ONOCR;
        }
    }
    if (strcmp(cmd,  "onlret") == 0) {
        if (sign == '-') {
            settings.c_oflag &=  ~ONLRET;
        } else {
            settings.c_oflag |= ONLRET;
        }
    }
    if (strcmp(cmd,  "ofill") == 0) {
        if (sign == '-') {
            settings.c_oflag &=  ~OFILL;
        } else {
            settings.c_oflag |= OFILL;
        }
    }
    if (strcmp(cmd,  "ofdel") == 0) {
        if (sign == '-') {
            settings.c_oflag &=  ~OFDEL;
        } else {
            settings.c_oflag |= OFDEL;
        }
    } 
    if (strcmp(cmd,  "nl0") == 0) {
        if (sign == '-') {
            settings.c_oflag &=  ~NLDLY;
        } else {
            settings.c_oflag &=  ~NLDLY;
            settings.c_oflag |= NL0;
        }
    }  
    if (strcmp(cmd,  "nl1") == 0) {
        if (sign == '-') {
            settings.c_oflag &=  ~NLDLY;
        } else {
            settings.c_oflag &=  ~NLDLY;
            settings.c_oflag |= NL1;
        }
    }
    if (strcmp(cmd,  "cr0") == 0) {
        if (sign == '-') {
            settings.c_oflag &=  ~CRDLY;
        } else {
            settings.c_oflag &=  ~CRDLY;
            settings.c_oflag |= CR0;
        }
    } 
    if (strcmp(cmd,  "cr1") == 0) {
        if (sign == '-') {
            settings.c_oflag &=  ~CRDLY;
        } else {
            settings.c_oflag &=  ~CRDLY;
            settings.c_oflag |= CR1;
        }
    } 
    if (strcmp(cmd,  "cr2") == 0) {
        if (sign == '-') {
            settings.c_oflag &=  ~CRDLY;
        } else {
            settings.c_oflag &=  ~CRDLY;
            settings.c_oflag |= CR2;
        }
    }  
    if (strcmp(cmd,  "cr3") == 0) {
        if (sign == '-') {
            settings.c_oflag &=  ~CRDLY;
        } else {
            settings.c_oflag &=  ~CRDLY;
            settings.c_oflag |= CR3;
        }
    }   
    if (strcmp(cmd,  "tab0") == 0) {
        if (sign == '-') {
            settings.c_oflag &=  ~TABDLY;
        } else {
            settings.c_oflag &=  ~TABDLY;
            settings.c_oflag |= TAB0;
        }
    }
    if (strcmp(cmd,   "tab1") == 0) {
        if (sign == '-') {
            settings.c_oflag &=  ~TABDLY;
        } else {
            settings.c_oflag &=  ~TABDLY;
            settings.c_oflag |= TAB1;
        }
    } 
    if (strcmp(cmd,  "tab2") == 0) {
        if (sign == '-') {
            settings.c_oflag &=  ~TABDLY;
        } else {
            settings.c_oflag &=  ~TABDLY;
            settings.c_oflag |= TAB2;
        }
    }
    if (strcmp(cmd,  "bs0") == 0) {
        if (sign == '-') {
            settings.c_oflag &=  ~BSDLY;
        } else {
            settings.c_oflag &=  ~BSDLY;
            settings.c_oflag |= BS0;
        }
    } 
    if (strcmp(cmd,  "bs1") == 0) {
        if (sign == '-') {
            settings.c_oflag &=  ~BSDLY;
        } else {
            settings.c_oflag &=  ~BSDLY;
            settings.c_oflag |= BS1;
        }
    }
    if (strcmp(cmd,  "vt0") == 0) {
        if (sign == '-') {
            settings.c_oflag &=  ~VTDLY;
        } else {
            settings.c_oflag &=  ~VTDLY;
            settings.c_oflag |= VT0;
        }
    }
    if (strcmp(cmd,  "vt1") == 0) {
        if (sign == '-') {
            settings.c_oflag &=  ~VTDLY;
        } else {
            settings.c_oflag &=  ~VTDLY;
            settings.c_oflag |= VT1;
        }
    }
    if (strcmp(cmd,  "ff0") == 0) {
        if (sign == '-') {
            settings.c_oflag &=  ~FFDLY;
        } else {
            settings.c_oflag &=  ~FFDLY;
            settings.c_oflag |= FF0;
        }
    } 
    if (strcmp(cmd,  "ff1") == 0) {
        if (sign == '-') {
            settings.c_oflag &=  ~FFDLY;
        } else {
            settings.c_oflag &=  ~FFDLY;
            settings.c_oflag |= FF1;
        }
    } 
    if (strcmp(cmd,  "isig") == 0) {
        if (sign == '-') {
            settings.c_lflag &=  ~ISIG;
        } else {
            settings.c_lflag |= ISIG;
        }
    }
    if (strcmp(cmd,  "icanon") == 0) {
        if (sign == '-') {
            settings.c_lflag &=  ~ICANON;
        } else {
            settings.c_lflag |= ICANON;
        }
    }
    if (strcmp(cmd,  "iexten") == 0) {
        if (sign == '-') {
            settings.c_lflag &=  ~IEXTEN;
        } else {
            settings.c_lflag |= IEXTEN;
        }
    }
    if (strcmp(cmd,  "echo") == 0) {
        if (sign == '-') {
            settings.c_lflag &=  ~ECHO;
        } else {
            settings.c_lflag |= ECHO;
        }
    }
    if (strcmp(cmd,  "echoe") == 0) {
        if (sign == '-') {
            settings.c_lflag &=  ~ECHOE;
        } else {
            settings.c_lflag |= ECHOE;
        }
    }
    if (strcmp(cmd,  "echok") == 0) {
        if (sign == '-') {
            settings.c_lflag &=  ~ECHOK;
        } else {
            settings.c_lflag |= ECHOK;
        }
    }
    if (strcmp(cmd,  "echonl") == 0) {
        if (sign == '-') {
            settings.c_lflag &=  ~ECHONL;
        } else {
            settings.c_lflag |= ECHONL;
        }
    }
    if (strcmp(cmd,  "noflsh") == 0) {
        if (sign == '-') {
            settings.c_lflag &=  ~NOFLSH;
        } else {
            settings.c_lflag |= NOFLSH;
        }
    } 
    if (strcmp(cmd,  "xcase") == 0) {
        if (sign == '-') {
            settings.c_lflag &=  ~XCASE;
        } else {
            settings.c_lflag |= XCASE;
        }
    }
    if (strcmp(cmd,  "tostop") == 0) {
        if (sign == '-') {
            settings.c_lflag &=  ~TOSTOP;
        } else {
            settings.c_lflag |= TOSTOP;
        }
    }
    if (strcmp(cmd,  "echoprt") == 0) {
        if (sign == '-') {
            settings.c_lflag &=  ~ECHOPRT;
        } else {
            settings.c_lflag |= ECHOPRT;
        }
    }
    if (strcmp(cmd,  "echoctl") == 0) {
        if (sign == '-') {
            settings.c_lflag &=  ~ECHOCTL;
        } else {
            settings.c_lflag |= ECHOCTL;
        }
    } 
    if (strcmp(cmd,  "echoke") == 0) {
        if (sign == '-') {
            settings.c_lflag &=  ~ECHOKE;
        } else {
            settings.c_lflag |= ECHOKE;
        }
    }  
    if (strcmp(cmd,  "flusho") == 0) {
        if (sign == '-') {
            settings.c_lflag &=  ~FLUSHO;
        } else {
            settings.c_lflag |= FLUSHO;
        }
    } 
    if (strcmp(cmd,  "extproc") == 0) {
        if (sign == '-') {
            settings.c_lflag &=  ~EXTPROC;
        } else {
            settings.c_lflag |= EXTPROC;
        }
    }
}

int getCSIZE(int csize) {
	if (csize == CS5) {
		return 5;
	} else if (csize == CS6) {
		return 6;
	} else if (csize == CS7) {
        return 7;
	} else if (csize == CS8) {
        return 8;
    }
}

int getCRDLY(int crdly) {
	if (crdly == CR0) {
		return 0;
	} else if (crdly == CR1) {
		return 1;
	} else if (crdly == CR2) {
        return 2;
	} else if ( crdly == CR3) {
        return 3;
    }
}

int getTABDLY(int tabdly) {
	if (tabdly == TAB0) {
		return 0;
	} else if (tabdly == TAB1) {
		return 1;
	} else if (tabdly == TAB2) {
        return 2;
	}	
}

void print_settings(int fd) {
	if (tcgetattr(fd,  &settings) == 0) {
    	printf("speed %d baud\nrow = %d\ncolumn = %d\nline = %d\n",  
            baud[settings.c_ispeed], 
            wins.ws_row,  
            wins.ws_col,  
            settings.c_line
        );
    	printf("%cparenb %cparodd %ccmspar cs%d %chupcl %ccstopb %ccread %cclocal %ccrtscts\n",  
            settings.c_cflag & PARENB == 0 ? '-' : ' ', 
            settings.c_cflag & PARODD == 0 ? '-' : ' ',
            settings.c_cflag & CMSPAR == 0 ? '-' : ' ',
            getCSIZE(settings.c_cflag&CSIZE),  
            settings.c_cflag & HUPCL == 0 ? '-' : ' ',
            settings.c_cflag & CSTOPB == 0 ? '-' : ' ',
            settings.c_cflag & CREAD == 0 ? '-' : ' ',
            settings.c_cflag & CLOCAL == 0 ? '-' : ' ',
            settings.c_cflag & CRTSCTS == 0 ? '-' : ' '
        );
        printf("%cignbrk %cbrkint %cignpar %cparmrk %cinpck %cistrip %cinlcr %cigncr %cicrnl %cixon %cixoff %ciuclc %cixany %cimaxbel %ciutf8\n",  
            settings.c_iflag & IGNBRK == 0 ? '-' : ' ', 
            settings.c_iflag & BRKINT == 0 ? '-' : ' ', 
            settings.c_iflag & IGNPAR == 0 ? '-' : ' ', 
            settings.c_iflag & PARMRK == 0 ? '-' : ' ', 
            settings.c_iflag & INPCK == 0 ? '-' : ' ', 
            settings.c_iflag & ISTRIP == 0 ? '-' : ' ', 
            settings.c_iflag & INLCR == 0 ? '-' : ' ', 
            settings.c_iflag & IGNCR == 0 ? '-' : ' ',
            settings.c_iflag & ICRNL == 0 ? '-' : ' ',
            settings.c_iflag & IXON == 0 ? '-' : ' ',
            settings.c_iflag & IXOFF == 0 ? '-' : ' ',
            settings.c_iflag & IUCLC == 0 ? '-' : ' ',
            settings.c_iflag & IXANY == 0 ? '-' : ' ',
            settings.c_iflag & IMAXBEL == 0 ? '-' : ' ',
            settings.c_iflag & IUTF8 == 0 ? '-' : ' '
        );
        printf("%copost %colcuc %cocrnl %conlcr %conocr %conlret %cofill %cofdel nl%d cr%d tab%d bs%d vt%d ff%d\n",
            settings.c_oflag & OPOST == 0 ? '-' : ' ',
            settings.c_oflag & OLCUC == 0 ? '-' : ' ',
            settings.c_oflag & OCRNL == 0 ? '-' : ' ',
            settings.c_oflag & ONLCR == 0 ? '-' : ' ',
            settings.c_oflag & ONOCR == 0 ? '-' : ' ',
            settings.c_oflag & ONLRET == 0 ? '-' : ' ',
            settings.c_oflag & OFILL == 0 ? '-' : ' ',
            settings.c_oflag & OFDEL == 0 ? '-' : ' ',
            settings.c_oflag & NLDLY == NL0 ? 0 : 1,
            getCRDLY(settings.c_oflag&CRDLY),  
            getTABDLY(settings.c_oflag&TABDLY), 
            settings.c_oflag & BSDLY == BS0 ? 0 : 1,
            settings.c_oflag & VTDLY == VT0 ? 0 : 1,
            settings.c_oflag & FFDLY == FF0 ? 0 : 1
        );
        printf("%cisig %cicanon %ciexten %cecho %cechoe %cechok %cechonl %cnoflsh %cxcase %ctostop %cechoprt %cechoctl %cechoke %cflusho %cextproc\n",  
            settings.c_lflag & ISIG == 0 ? '-' : ' ',
            settings.c_lflag & ICANON == 0 ? '-' : ' ',
            settings.c_lflag & IEXTEN == 0 ? '-' : ' ',
            settings.c_lflag & ECHO == 0 ? '-' : ' ',
            settings.c_lflag & ECHOE == 0 ? '-' : ' ',
            settings.c_lflag & ECHOK == 0 ? '-' : ' ',
            settings.c_lflag & ECHONL == 0 ? '-' : ' ',
            settings.c_lflag & NOFLSH == 0 ? '-' : ' ',
            settings.c_lflag & XCASE == 0 ? '-' : ' ',
            settings.c_lflag & TOSTOP == 0 ? '-' : ' ',
            settings.c_lflag & ECHOPRT == 0 ? '-' : ' ',
            settings.c_lflag & ECHOCTL == 0 ? '-' : ' ',
            settings.c_lflag & ECHOKE == 0 ? '-' : ' ',
            settings.c_lflag & FLUSHO == 0 ? '-' : ' ',
            settings.c_lflag & EXTPROC == 0 ? '-' : ' '
        );
    } else {
    	printf("Invalid file descriptor");
    }
}

int main(int argc,  char **argv) {
    int fd = STDOUT_FILENO;
    char cmd[32],  start_string[2],  start_char;
    ioctl(STDOUT_FILENO,  TIOCGWINSZ,  &wins);
    int flag = 0;
    
    if (argc==1) {
        if (tcgetattr(fd,  &settings) == 0) {
            print_settings(fd);
        }
    } else if (argc == 2) {
     	if (strcmp(argv[1], "-a") == 0) {
            print_settings(fd);
            return 0;
     	}
        printf("Invalid argument");
    } else {
        if (strcmp(argv[1], "-F") == 0) {
            fd = open(argv[2],  O_RDWR | O_NOCTTY | O_NONBLOCK);
            if (fd == -1) {
                printf("Invalid file descriptor");
                return 0;
            } 
            if (strcmp(argv[3], "-a") == 0) {
                print_settings(fd);
                return 0;
            }
        }
        if (tcgetattr(fd,  &settings) == 0) {
            for(int i = 1; i < argc; i++) {
                start_char = argv[i][0];
                if (start_char == '-') {
                    memcpy(cmd,  &argv[i][1],  strlen(argv[i])-1);
                } else {
                    memcpy(cmd,  &argv[i][0],  strlen(argv[i]));
                }
                update(start_char,  cmd);							
            }
            tcsetattr(fd,  TCSAFLUSH,  &settings);	
        } else {
            printf("Invalid file descriptor");
        }
    }
}
