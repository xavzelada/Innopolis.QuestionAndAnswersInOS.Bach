#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <fcntl.h>

int getCSIZE(int csize) {
    if (csize == CS5) return 5;
    else if (csize == CS6) return 6;
    else if (csize == CS7) return 7;
    else if (csize == CS8) return 8;
}

int getNLDLY(int nldly) {
    if (nldly == NL0) return 0;
    else if (nldly == NL1) return 1;
}

int getVTDLY(int vtdly) {
    if (vtdly == VT0) return 0;
    else if (vtdly == VT1) return 1;
}

int getBSDLY(int bsdly) {
    if (bsdly == BS0) return 0;
    else if (bsdly == BS1) return 1;
}

int getTABDLY(int tabdly) {
    if (tabdly == TAB0) return 0;
    else if (tabdly == TAB1) return 1;
    else if (tabdly == TAB2) return 2;
}

int getCRDLY(int crdly) {
    if (crdly == CR0) return 0;
    else if (crdly == CR1) return 1;
    else if (crdly == CR2) return 2;
    else if (crdly == CR3) return 3;
}

int getSpeed(int B) {
    switch (B) {
        case 0:  return 0;
        case 1:  return 50;
        case 2:  return 75;
        case 3:  return 110;
        case 4:  return 134;
        case 5:  return 150;
        case 6:  return 200;
        case 7:  return 300;
        case 8:  return 600;
        case 9:  return 1200;
        case 10:  return 1800;
        case 11:  return 2400;
        case 12:  return 4800;
        case 13:  return 9600;
        case 14:  return 19200;
        case 15:  return 38400;
        case 16:  return 57600;
        case 17:  return 115200;
        default: return INT_MAX; // does not possible
    }
}

void configure(char *configs, char *str, struct termios *term) {
    if (strcmp(str, "brkint") == 0) {
        if (strcmp(configs, "-") == 0) term->c_iflag &= ~BRKINT;
        else term->c_iflag |= BRKINT;
    }

    if (strcmp(str, "iutf8") == 0) {
        if (strcmp(configs, "-") == 0) term->c_iflag &= ~IUTF8;
        else term->c_iflag |= IUTF8;
    }

    if (strcmp(str, "ignbrk") == 0) {
        if (strcmp(configs, "-") == 0) term->c_iflag &= ~IGNBRK;
        else term->c_iflag |= IGNBRK;
    }

    if (strcmp(str, "clocal") == 0) {
        if (strcmp(configs, "-") == 0) term->c_cflag &= ~CLOCAL;
        else term->c_cflag |= CLOCAL;
    }

    if (strcmp(str, "ignpar") == 0) {
        if (strcmp(configs, "-") == 0) term->c_iflag &= ~IGNPAR;
        else term->c_iflag |= IGNPAR;
    }

    if (strcmp(str, "cread") == 0) {
        if (strcmp(configs, "-") == 0) term->c_cflag &= ~CREAD;
        else term->c_cflag |= CREAD;
    }

    if (strcmp(str, "echok") == 0) {
        if (strcmp(configs, "-") == 0) term->c_lflag &= ~ECHOK;
        else term->c_lflag |= ECHOK;
    }

    if (strcmp(str, "ixon") == 0) {
        if (strcmp(configs, "-") == 0) term->c_iflag &= ~IXON;
        else term->c_iflag |= IXON;
    }

    if (strcmp(str, "parodd") == 0) {
        if (strcmp(configs, "-") == 0) term->c_cflag &= ~PARODD;
        else term->c_cflag |= PARODD;
    }

    if (strcmp(str, "ixoff") == 0) {
        if (strcmp(configs, "-") == 0) term->c_iflag &= ~IXOFF;
        else term->c_iflag |= IXOFF;
    }

    if (strcmp(str, "imaxbel") == 0) {
        if (strcmp(configs, "-") == 0) term->c_iflag &= ~IMAXBEL;
        else term->c_iflag |= IMAXBEL;
    }

    if (strcmp(str, "parenb") == 0) {
        if (strcmp(configs, "-") == 0) term->c_cflag &= ~PARENB;
        else term->c_cflag |= PARENB;
    }

    if (strcmp(str, "echoctl") == 0) {
        if (strcmp(configs, "-") == 0) term->c_lflag &= ~ECHOCTL;
        else term->c_lflag |= ECHOCTL;
    }

    if (strcmp(str, "echoprt") == 0) {
        if (strcmp(configs, "-") == 0) term->c_lflag &= ~ECHOPRT;
        else term->c_lflag |= ECHOPRT;
    }

    if (strcmp(str, "echo") == 0) {
        if (strcmp(configs, "-") == 0) term->c_lflag &= ~ECHO;
        else term->c_lflag |= ECHO;
    }

    if (strcmp(str, "echoe") == 0) {
        if (strcmp(configs, "-") == 0) term->c_lflag &= ~ECHOE;
        else term->c_lflag |= ECHOE;
    }

    if (strcmp(str, "cs7") == 0) {
        if (strcmp(configs, "-") == 0) term->c_cflag &= ~CSIZE;
        else {
            term->c_cflag &= ~CSIZE;
            term->c_cflag |= CS7;
        }
    }

    if (strcmp(str, "cs6") == 0) {
        if (strcmp(configs, "-") == 0) term->c_cflag &= ~CSIZE;
        else {
            term->c_cflag &= ~CSIZE;
            term->c_cflag |= CS6;
        }
    }

    if (strcmp(str, "nl0") == 0) {
        if (strcmp(configs, "-") == 0) term->c_oflag &= ~NLDLY;
        else {
            term->c_oflag &= ~NLDLY;
            term->c_oflag |= NL0;
        }
    }

    if (strcmp(str, "vt0") == 0) {
        if (strcmp(configs, "-") == 0) term->c_oflag &= ~VTDLY;
        else {
            term->c_oflag &= ~VTDLY;
            term->c_oflag |= VT0;
        }
    }

    if (strcmp(str, "nl1") == 0) {
        if (strcmp(configs, "-") == 0) term->c_oflag &= ~NLDLY;
        else {
            term->c_oflag &= ~NLDLY;
            term->c_oflag |= NL1;
        }
    }

    if (strcmp(str, "cs5") == 0) {
        if (strcmp(configs, "-") == 0) term->c_cflag &= ~CSIZE;
        else {
            term->c_cflag &= ~CSIZE;
            term->c_cflag |= CS5;
        }
    }

    if (strcmp(str, "bs1") == 0) {
        if (strcmp(configs, "-") == 0) term->c_oflag &= ~BSDLY;
        else {
            term->c_oflag &= ~BSDLY;
            term->c_oflag |= BS1;
        }
    }

    if (strcmp(str, "tab1") == 0) {
        if (strcmp(configs, "-") == 0) term->c_oflag &= ~TABDLY;
        else {
            term->c_oflag &= ~TABDLY;
            term->c_oflag |= TAB1;
        }
    }

    if (strcmp(str, "tab0") == 0) {
        if (strcmp(configs, "-") == 0) term->c_oflag &= ~TABDLY;
        else {
            term->c_oflag &= ~TABDLY;
            term->c_oflag |= TAB0;
        }
    }

    if (strcmp(str, "bs0") == 0) {
        if (strcmp(configs, "-") == 0) term->c_oflag &= ~BSDLY;
        else {
            term->c_oflag &= ~BSDLY;
            term->c_oflag |= BS0;
        }
    }

    if (strcmp(str, "tab2") == 0) {
        if (strcmp(configs, "-") == 0) term->c_oflag &= ~TABDLY;
        else {
            term->c_oflag &= ~TABDLY;
            term->c_oflag |= TAB2;
        }
    }

    if (strcmp(str, "vt1") == 0) {
        if (strcmp(configs, "-") == 0) term->c_oflag &= ~VTDLY;
        else {
            term->c_oflag &= ~VTDLY;
            term->c_oflag |= VT1;
        }
    }

    if (strcmp(str, "cr2") == 0) {
        if (strcmp(configs, "-") == 0) term->c_oflag &= ~CRDLY;
        else {
            term->c_oflag &= ~CRDLY;
            term->c_oflag |= CR2;
        }
    }

    if (strcmp(str, "cr1") == 0) {
        if (strcmp(configs, "-") == 0) term->c_oflag &= ~CRDLY;
        else {
            term->c_oflag &= ~CRDLY;
            term->c_oflag |= CR1;
        }
    }

    if (strcmp(str, "cr0") == 0) {
        if (strcmp(configs, "-") == 0) term->c_oflag &= ~CRDLY;
        else {
            term->c_oflag &= ~CRDLY;
            term->c_oflag |= CR0;
        }
    }

    if (strcmp(str, "cs8") == 0) {
        if (strcmp(configs, "-") == 0) term->c_cflag &= ~CSIZE;
        else {
            term->c_cflag &= ~CSIZE;
            term->c_cflag |= CS8;
        }
    }

    if (strcmp(str, "cr3") == 0) {
        if (strcmp(configs, "-") == 0) term->c_oflag &= ~CRDLY;
        else {
            term->c_oflag &= ~CRDLY;
            term->c_oflag |= CR3;
        }
    }
}

char isFlag(int flag, int value) {
    if ((flag & value) == 0) return '-';
    else return ' ';
}

void currentSettings(struct termios term) {
    printf("CSIZE%d %cCREAD %cCLOCAL %cPARENB %cPARODD\n",
           isFlag(term.c_cflag, PARENB), getCSIZE(term.c_cflag & CSIZE), isFlag(term.c_cflag, CREAD),
           isFlag(term.c_cflag, CLOCAL), isFlag(term.c_cflag, PARODD));
}

void localSettings(struct termios term) {
    printf("%cECHO %cECHOE %cECHOK %cECHOCTL %cECHOPRT\n", isFlag(term.c_lflag, ECHO), isFlag(term.c_lflag, ECHOE),
           isFlag(term.c_lflag, ECHOK), isFlag(term.c_lflag, ECHOCTL), isFlag(term.c_lflag, ECHOPRT));
}

void inputSettings(struct termios term) {
    printf("%c%cIXON %cIXOFF %cIUTF8 IGNBRK %cIGNPAR\n", isFlag(term.c_iflag, IXON), isFlag(term.c_iflag, IXOFF),
           isFlag(term.c_iflag, IUTF8), isFlag(term.c_iflag, IGNBRK), isFlag(term.c_iflag, IGNPAR));
}

void outputSettings(struct termios term) {
    printf("NLDLY%d CRDLY%d TABDLY%d BSDLY%d VTDLY%d\n",
           getNLDLY(term.c_oflag & NLDLY), getCRDLY(term.c_oflag & CRDLY), getTABDLY(term.c_oflag & TABDLY),
           getBSDLY(term.c_oflag & BSDLY), getVTDLY(term.c_oflag & VTDLY));
}

void humanReadable() {
    struct termios term;
    currentSettings(term);
    localSettings(term);
    inputSettings(term);
    outputSettings(term);
}

void sttyReadable() {
    struct termios term;
    printf("%x:", term.c_cflag);
    printf("%x:", term.c_lflag);
    printf("%x:", term.c_iflag);
    printf("%x:", term.c_oflag);
}

void setAttributes(char command1[], char command2[], char **argv) {
    struct termios term;

    for (int i = 0; i < argc; i++) {
        if (i >= 3) {
            command2[0] = argv[i][0];
            size_t len = strlen(argv[i]);

            if (strcmp(command2, "-") == 0) {
                memcpy(command1, &argv[i][1], len - 1);
            } else {
                memcpy(command1, &argv[i][0], len);
            }

            configure(command2, command1, &term);
        }
    }

    tcsetattr(descriptor, TCSAFLUSH, &term);
}

int main(int argc, char **argv) {
    char *device;

    char command1[1000];
    char command2[2];

    struct winsize size;
    struct termios term;

    int descriptor = STDOUT_FILENO;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

    if (argc == 1) {
        if (tcgetattr(descriptor, &term) == 0) {
            printf("speed = %d; line = %d; %cBRKINT; %cIMAXBEL; %cIUTF8\n", getSpeed(term.c_ispeed), term.c_line),
                    isFlag(term.c_iflag, BRKINT), isFlag(term.c_iflag, IMAXBEL), isFlag(term.c_iflag, IUTF8);
        }
    } else if (argc == 2) {
        if (strcmp(argv[1], "-a") == 0) {
            humanReadable();
        } else if (strcmp(argv[1], "-g") == 0) {
            sttyReadable();
        }
    } else if (argc >= 3) {
        if (strcmp(argv[1], "-F") == 0) {
            device = argv[2];
            descriptor = open(device, O_NOCTTY | O_RDWR | O_NONBLOCK);

            if (strcmp(argv[3], "-a") == 0) {
                humanReadable();
            } else if (strcmp(argv[3], "-g") == 0) {
                sttyReadable();
            } else {
                setAttributes(command1, command2, argv);
            }
        } else if (tcgetattr(descriptor, &term) == 0) {
            setAttributes(command1, command2, argv);
        }
    }

    return 0;
}
