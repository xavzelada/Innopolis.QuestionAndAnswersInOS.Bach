#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

void setSettings(char* modif, char* str,struct termios* temp ){
		if(strcmp(str,"ignbrk")==0){
			if (strcmp(modif,"-")==0){
				temp->c_iflag &=  ~IGNBRK;
			}else{
				temp->c_iflag |= IGNBRK;
			}
		}
		if(strcmp(str,"brkint")==0){
			if (strcmp(modif,"-")==0){
				temp->c_iflag &=  ~BRKINT;
			}else{
				temp->c_iflag |= BRKINT;
			}
		} 
	    if(strcmp(str,"ignpar")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_iflag &=  ~IGNPAR;
   			}else{
   				temp->c_iflag |= IGNPAR;
   			}
   		}
		if(strcmp(str,"parmrk")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_iflag &=  ~PARMRK;
   			}else{
   				temp->c_iflag |= PARMRK;
   			}
   		} 
		if(strcmp(str,"inpck")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_iflag &=  ~INPCK;
   			}else{
   				temp->c_iflag |= INPCK;
   			}
   		}  
		if(strcmp(str,"istrip")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_iflag &=  ~ISTRIP;
   			}else{
   				temp->c_iflag |= ISTRIP;
   			}
   		} 
		if(strcmp(str,"inlcr")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_iflag &=  ~INLCR;
   			}else{
   				temp->c_iflag |= INLCR;
   			}
   		}  
		if(strcmp(str,"igncr")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_iflag &=  ~IGNCR;
   			}else{
   				temp->c_iflag |= IGNCR;
   			}
   		} 
		if(strcmp(str,"icrnl")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_iflag &=  ~ICRNL;
   			}else{
   				temp->c_iflag |= ICRNL;
   			}
   		} 
		if(strcmp(str,"ixon")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_iflag &=  ~IXON;
   			}else{
   				temp->c_iflag |= IXON;
   			}
   		} 
		if(strcmp(str,"ixoff")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_iflag &=  ~IXOFF;
   			}else{
   				temp->c_iflag |= IXOFF;
   			}
   		}  
		if(strcmp(str,"iuclc")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_iflag &=  ~IUCLC;
   			}else{
   				temp->c_iflag |= IUCLC;
   			}
   		}  
		if(strcmp(str,"ixany")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_iflag &=  ~IXANY;
   			}else{
   				temp->c_iflag |= IXANY;
   			}
   		} 
		if(strcmp(str,"imaxbel")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_iflag &=  ~IMAXBEL;
   			}else{
   				temp->c_iflag |= IMAXBEL;
   			}
   		}
		if(strcmp(str,"iutf8")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_iflag &=  ~IUTF8;
   			}else{
   				temp->c_iflag |= IUTF8;
   			}
   		}
		if(strcmp(str,"parenb")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_cflag &=  ~PARENB;
   			}else{
   				temp->c_cflag |= PARENB;
   			}
   		} 
		if(strcmp(str,"parodd")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_cflag &=  ~PARODD;
   			}else{
   				temp->c_cflag |= PARODD;
   			}
   		}  
		if(strcmp(str,"cmspar")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_cflag &=  ~CMSPAR;
   			}else{
   				temp->c_cflag |= CMSPAR;
   			}
   		}  
		if(strcmp(str,"cs5")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_cflag &=  ~CSIZE;
   			}else{
   				temp->c_cflag &=  ~CSIZE;
   				temp->c_cflag |= CS5;
   			}
   		} 
	    if(strcmp(str,"cs6")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_cflag &=  ~CSIZE;
   			}else{
   				temp->c_cflag &=  ~CSIZE;
   				temp->c_cflag |= CS6;
   			}
   		} 
		if(strcmp(str,"cs7")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_cflag &=  ~CSIZE;
   			}else{
   				temp->c_cflag &=  ~CSIZE;
   				temp->c_cflag |= CS7;
   			}
   		} 
		if(strcmp(str,"cs8")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_cflag &=  ~CSIZE;
   			}else{
   				temp->c_cflag &=  ~CSIZE;
   				temp->c_cflag |= CS8;
   			}
   		} 
		if(strcmp(str,"hupcl")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_cflag &=  ~HUPCL;
   			}else{
   				temp->c_cflag |= HUPCL;
   			}
   		} 
		if(strcmp(str,"cstopb")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_cflag &=  ~CSTOPB;
   			}else{
   				temp->c_cflag |= CSTOPB;
   			}
   		}
		if(strcmp(str,"cread")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_cflag &=  ~CREAD;
   			}else{
   				temp->c_cflag |= CREAD;
   			}
   		}
		if(strcmp(str,"clocal")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_cflag &=  ~CLOCAL;
   			}else{
   				temp->c_cflag |= CLOCAL;
   			}
   		} 
		if(strcmp(str,"crtscts")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_cflag &=  ~CRTSCTS;
   			}else{
   				temp->c_cflag |= CRTSCTS;
   			}
   		}
		if(strcmp(str,"opost")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_oflag &=  ~OPOST;
   			}else{
   				temp->c_oflag |= OPOST;
   			}
   		}  
		if(strcmp(str,"olcuc")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_oflag &=  ~OLCUC;
   			}else{
   				temp->c_oflag |= OLCUC;
   			}
   		}
		if(strcmp(str,"ocrnl")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_oflag &=  ~OCRNL;
   			}else{
   				temp->c_oflag |= OCRNL;
   			}
   		} 
		if(strcmp(str,"onlcr")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_oflag &=  ~ONLCR;
   			}else{
   				temp->c_oflag |= ONLCR;
   			}
   		}
		if(strcmp(str,"onocr")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_oflag &=  ~ONOCR;
   			}else{
   				temp->c_oflag |= ONOCR;
   			}
   		}
		if(strcmp(str,"onlret")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_oflag &=  ~ONLRET;
   			}else{
   				temp->c_oflag |= ONLRET;
   			}
   		}
		if(strcmp(str,"ofill")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_oflag &=  ~OFILL;
   			}else{
   				temp->c_oflag |= OFILL;
   			}
   		}
		if(strcmp(str,"ofdel")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_oflag &=  ~OFDEL;
   			}else{
   				temp->c_oflag |= OFDEL;
   			}
   		} 
		if(strcmp(str,"nl0")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_oflag &=  ~NLDLY;
   			}else{
   				temp->c_oflag &=  ~NLDLY;
   				temp->c_oflag |= NL0;
   			}
   		}  
		if(strcmp(str,"nl1")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_oflag &=  ~NLDLY;
   			}else{
   				temp->c_oflag &=  ~NLDLY;
   				temp->c_oflag |= NL1;
   			}
   		}
		if(strcmp(str,"cr0")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_oflag &=  ~CRDLY;
   			}else{
   				temp->c_oflag &=  ~CRDLY;
   				temp->c_oflag |= CR0;
   			}
   		} 
		if(strcmp(str,"cr1")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_oflag &=  ~CRDLY;
   			}else{
   				temp->c_oflag &=  ~CRDLY;
   				temp->c_oflag |= CR1;
   			}
   		} 
		if(strcmp(str,"cr2")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_oflag &=  ~CRDLY;
   			}else{
   				temp->c_oflag &=  ~CRDLY;
   				temp->c_oflag |= CR2;
   			}
   		}  
		if(strcmp(str,"cr3")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_oflag &=  ~CRDLY;
   			}else{
   				temp->c_oflag &=  ~CRDLY;
   				temp->c_oflag |= CR3;
   			}
   		}   
	    if(strcmp(str,"tab0")==0){
  			if (strcmp(modif,"-")==0){
  				temp->c_oflag &=  ~TABDLY;
  			}else{
  				temp->c_oflag &=  ~TABDLY;
  				temp->c_oflag |= TAB0;
  			}
  		}
	    if(strcmp(str, "tab1")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_oflag &=  ~TABDLY;
   			}else{
   				temp->c_oflag &=  ~TABDLY;
   				temp->c_oflag |= TAB1;
   			}
   		} 
	    if(strcmp(str,"tab2")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_oflag &=  ~TABDLY;
   			}else{
   				temp->c_oflag &=  ~TABDLY;
   				temp->c_oflag |= TAB2;
   			}
   		}
	   	if(strcmp(str,"bs0")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_oflag &=  ~BSDLY;
   			}else{
   				temp->c_oflag &=  ~BSDLY;
   				temp->c_oflag |= BS0;
   			}
   		} 
	    if(strcmp(str,"bs1")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_oflag &=  ~BSDLY;
   			}else{
   				temp->c_oflag &=  ~BSDLY;
   				temp->c_oflag |= BS1;
   			}
   		}
	    if(strcmp(str,"vt0")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_oflag &=  ~VTDLY;
   			}else{
   				temp->c_oflag &=  ~VTDLY;
   				temp->c_oflag |= VT0;
   			}
   		}
	    if(strcmp(str,"vt1")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_oflag &=  ~VTDLY;
   			}else{
   				temp->c_oflag &=  ~VTDLY;
   				temp->c_oflag |= VT1;
   			}
   		}
	    if(strcmp(str,"ff0")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_oflag &=  ~FFDLY;
   			}else{
   				temp->c_oflag &=  ~FFDLY;
   				temp->c_oflag |= FF0;
   			}
   		} 
	    if(strcmp(str,"ff1")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_oflag &=  ~FFDLY;
   			}else{
   				temp->c_oflag &=  ~FFDLY;
   				temp->c_oflag |= FF1;
   			}
   		} 
	    if(strcmp(str,"isig")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_lflag &=  ~ISIG;
   			}else{
   				temp->c_lflag |= ISIG;
   			}
   		}
	    if(strcmp(str,"icanon")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_lflag &=  ~ICANON;
   			}else{
   				temp->c_lflag |= ICANON;
   			}
   		}
	    if(strcmp(str,"iexten")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_lflag &=  ~IEXTEN;
   			}else{
   				temp->c_lflag |= IEXTEN;
   			}
   		}
	    if(strcmp(str,"echo")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_lflag &=  ~ECHO;
   			}else{
   				temp->c_lflag |= ECHO;
   			}
   		}
	    if(strcmp(str,"echoe")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_lflag &=  ~ECHOE;
   			}else{
   				temp->c_lflag |= ECHOE;
   			}
   		}
	    if(strcmp(str,"echok")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_lflag &=  ~ECHOK;
   			}else{
   				temp->c_lflag |= ECHOK;
   			}
   		}
	    if(strcmp(str,"echonl")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_lflag &=  ~ECHONL;
   			}else{
   				temp->c_lflag |= ECHONL;
   			}
   		}
	    if(strcmp(str,"noflsh")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_lflag &=  ~NOFLSH;
   			}else{
   				temp->c_lflag |= NOFLSH;
   			}
   		} 
	    if(strcmp(str,"xcase")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_lflag &=  ~XCASE;
   			}else{
   				temp->c_lflag |= XCASE;
   			}
   		}
	    if(strcmp(str,"tostop")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_lflag &=  ~TOSTOP;
   			}else{
   				temp->c_lflag |= TOSTOP;
   			}
   		}
	    if(strcmp(str,"echoprt")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_lflag &=  ~ECHOPRT;
   			}else{
   				temp->c_lflag |= ECHOPRT;
   			}
   		}
	    if(strcmp(str,"echoctl")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_lflag &=  ~ECHOCTL;
   			}else{
   				temp->c_lflag |= ECHOCTL;
   			}
   		} 
	    if(strcmp(str,"echoke")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_lflag &=  ~ECHOKE;
   			}else{
   				temp->c_lflag |= ECHOKE;
   			}
   		}  
	    if(strcmp(str,"flusho")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_lflag &=  ~FLUSHO;
   			}else{
   				temp->c_lflag |= FLUSHO;
   			}
   		} 
	    if(strcmp(str,"extproc")==0){
   			if (strcmp(modif,"-")==0){
   				temp->c_lflag &=  ~EXTPROC;
   			}else{
   				temp->c_lflag |= EXTPROC;
   			}
   		} 
}

int getBaud(int temp){
		if(temp == 15) return 38400;
		if(temp == 14) return 19200; 
		if(temp == 13) return 9600;
		if(temp == 12) return 4800;
		if(temp == 11) return 2400;
		if(temp == 10) return 1800; 
		if(temp == 9) return 1200; 
		if(temp == 8) return 600; 
		if(temp == 7) return 300;
		if(temp == 6) return 200; 
		if(temp == 5) return 150; 
		if(temp == 4) return 134; 
		if(temp == 3) return 110;
		if(temp == 2) return 75;
		if(temp == 1) return 50; 
		if(temp == 0) return 0; 
}

char check(int flag, int value){
	if((flag&value)==0){
		return '-';
	}else{
		return ' ';
	}
}

int getCSIZE(int csize){
	if (csize == CS5){
		return 5;
	}else if (csize == CS6){
		return 6;
	}else if (csize == CS7){
			return 7;
	}else if (csize == CS8){
			return 8;
    }
	
}

int getCRDLY(int crdly){
	if (crdly == CR0){
		return 0;
	}else if (crdly == CR1){
		return 1;
	}else if (crdly == CR2){
			return 2;
	}else if ( crdly == CR3){
			return 3;
    }
	
}

int getTABDLY(int tabdly){
	if (tabdly == TAB0){
		return 0;
	}else if (tabdly == TAB1){
		return 1;
	}else if (tabdly == TAB2){
			return 2;
	}	
}

int getNLDLY(int nldly){
	if (nldly == NL0){
		return 0;
	}else if (nldly == NL1){
		return 1;
	}
	
}

int getBSDLY(int bsdly){
	if (bsdly == BS0){
		return 0;
	}else if (bsdly == BS1){
		return 1;
	}
	
}

int getVTDLY(int vtdly){
	if (vtdly == VT0){
		return 0;
	}else if (vtdly == VT1){
		return 1;
	}
	
}

int getFFDLY(int ffdly){
	if (ffdly == FF0){
		return 0;
	}else if (ffdly == FF1){
		return 1;
	}
	
}

void printIFlagSettings (struct termios temp){
	 printf("%cignbrk %cbrkint %cignpar %cparmrk %cinpck %cistrip %cinlcr %cigncr %cicrnl %cixon %cixoff %ciuclc %cixany %cimaxbel %ciutf8\n", check(temp.c_iflag,IGNBRK),check(temp.c_iflag,BRKINT),check(temp.c_iflag,IGNPAR), check(temp.c_iflag,PARMRK),check(temp.c_iflag,INPCK),check(temp.c_iflag,ISTRIP),check(temp.c_iflag,INLCR),check(temp.c_iflag,IGNCR),check(temp.c_iflag,ICRNL),check(temp.c_iflag,IXON),check(temp.c_iflag,IXOFF),check(temp.c_iflag,IUCLC),check(temp.c_iflag,IXANY),check(temp.c_iflag,IMAXBEL),check(temp.c_iflag,IUTF8));
}

void printOFlagSettings (struct termios temp){
	printf("%copost %colcuc %cocrnl %conlcr %conocr %conlret %cofill %cofdel nl%d cr%d tab%d bs%d vt%d ff%d\n", check(temp.c_oflag,OPOST), check(temp.c_oflag,OLCUC), check(temp.c_oflag,OCRNL),check(temp.c_oflag,ONLCR),check(temp.c_oflag,ONOCR), check(temp.c_oflag,ONLRET), check(temp.c_oflag,OFILL), check(temp.c_oflag,OFDEL), getNLDLY(temp.c_oflag&NLDLY),  getCRDLY(temp.c_oflag&CRDLY), getTABDLY(temp.c_oflag&TABDLY),getBSDLY(temp.c_oflag&BSDLY), getVTDLY(temp.c_oflag&VTDLY), getFFDLY(temp.c_oflag&FFDLY));
}

void printCFlagSettings (struct termios temp){
	printf("%cparenb %cparodd %ccmspar cs%d %chupcl %ccstopb %ccread %cclocal %ccrtscts\n", check(temp.c_cflag,PARENB),check(temp.c_cflag,PARODD), check(temp.c_cflag,CMSPAR),getCSIZE(temp.c_cflag&CSIZE), check(temp.c_cflag,HUPCL),check(temp.c_cflag,CSTOPB),check(temp.c_cflag,CREAD),check(temp.c_cflag,CLOCAL),check(temp.c_cflag,CRTSCTS));	
}

void printLFlagSettings (struct termios temp){
	printf("%cisig %cicanon %ciexten %cecho %cechoe %cechok %cechonl %cnoflsh %cxcase %ctostop %cechoprt %cechoctl %cechoke %cflusho %cextproc\n", check(temp.c_lflag,ISIG),check(temp.c_lflag,ICANON),check(temp.c_lflag,IEXTEN),check(temp.c_lflag,ECHO),check(temp.c_lflag,ECHOE),check(temp.c_lflag,ECHOK),check(temp.c_lflag,ECHONL),check(temp.c_lflag,NOFLSH),check(temp.c_lflag,XCASE), check(temp.c_lflag,TOSTOP), check(temp.c_lflag,ECHOPRT), check(temp.c_lflag,ECHOCTL),check(temp.c_lflag,ECHOKE), check(temp.c_lflag,FLUSHO),check(temp.c_lflag,EXTPROC));
}


void printSettingsReadable(int fd, struct winsize w){
	struct termios temp;
	if (tcgetattr(fd, &temp) == 0){
    	printf("speed %d baud; row = %d; column = %d; line = %d;\n",getBaud(temp.c_ispeed),w.ws_row, w.ws_col, temp.c_line);
    	printf("intr = ^C; quit = ^/; erase = ^?; kill = ^U; eof = ^D; eol = <undef>; eol2 = <undef>; swtch = <undef>; start = ^Q; stop = ^S; susp = ^Z; rprnt = ^R; werase = ^W; lnext = ^V; discard = ^O; min = 1; time = 0;\n");
    	printCFlagSettings(temp);
    	printIFlagSettings(temp);
    	printOFlagSettings(temp);
    	printLFlagSettings(temp);
    }else{
    	printf("stty: invalid file descriptor\n");
    }
	
}

void printSettingsMashine(int fd){
	struct termios temp;
	if (tcgetattr(fd, &temp) == 0){
		printf("%x:", temp.c_iflag);
		printf("%x:", temp.c_oflag);
		printf("%x:", temp.c_cflag);
		printf("%x:", temp.c_lflag);
		for (int i = 0; i< NCCS-1;i++){
			printf("%x:", temp.c_cc[i]);
    	}
		printf("%x\n", temp.c_cc[NCCS-1]);
	}	
}


int main(int argc, char **argv) {

    struct termios settings;
    int fd = STDOUT_FILENO;
    char* device;
    char* temp2;
    char temp[32];
    char temp_c[2];
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int flag = 0;
    
    if (argc==1){
    	if (tcgetattr(fd, &settings) == 0){
    	  printf("speed %d baud; line = %d;\n",getBaud(settings.c_ispeed), settings.c_line);
    	  printf("%cbrkint %cimaxbel %ciutf8\n",check(settings.c_iflag,BRKINT),check(settings.c_iflag,IMAXBEL),check(settings.c_iflag,IUTF8));
    	}else{
    	  printf("stty: invalid file descriptor\n");
    	  return -1;
    	}
    }else if(argc==2){
     	if(strcmp(argv[1],"-a")==0){
	   		 printSettingsReadable(fd, w);
     	}else if(strcmp(argv[1],"-g")==0){
     		printSettingsMashine(fd);
     	}else if(strcmp(argv[1],"-F")==0){
     	        printf("stty: invalid argument ‘-F’ ");
     	        return -1;
        }
    }else if(argc > 2){
        if (strcmp(argv[1],"-F")==0){
          device = argv[2];
          fd = open(device, O_RDWR | O_NOCTTY | O_NONBLOCK);
          if (fd == -1){
            printf( "failed to open port\n" );
            return -1;
          } 
          if (strcmp(argv[3],"-a")==0){
            printSettingsReadable(fd, w);
          }else if (strcmp(argv[3],"-g")==0){
            printSettingsMashine(fd);
          }else{
            if (tcgetattr(fd, &settings) == 0){
              for(int i = 3; i < argc; i++){
                temp_c[0] = argv[i][0];
                if (strcmp(temp_c,"-")==0){
                  memcpy(temp, &argv[i][1], strlen(argv[i])-1);
                }else{
                  memcpy(temp, &argv[i][0], strlen(argv[i]));
                }
                setSettings(temp_c, temp ,&settings);							
              }
              tcsetattr(fd, TCSAFLUSH, &settings);	
            }else{
                printf("stty: invalid file descriptor\n");
                return -1;
            }	
          }
        }else{
          if (tcgetattr(fd, &settings) == 0){
              for(int i = 1; i < argc; i++){
                temp_c[0] = argv[i][0];
                if (strcmp(temp_c,"-")==0){
                  memcpy(temp, &argv[i][1], strlen(argv[i])-1);
                }else{
                  memcpy(temp, &argv[i][0], strlen(argv[i]));
                }
                setSettings(temp_c, temp ,&settings);							
              }
              tcsetattr(fd, TCSAFLUSH, &settings);	
            }else{
                printf("stty: invalid file descriptor\n");
                return -1;
            }	
        }
    }
}
