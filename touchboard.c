#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <fcntl.h>
#include <unistd.h>
char inp(char x,char type){
	char i;
	char*y;
	char len;
	if(!type){
		y="qwertyuiop";
	}
	else if(type==1){
		y="asdfghjkl";
	}
	else if(type==2){
		y="zxcvbnm";
	}
	len=strlen(y);
	for(i=0;i<len;i++){
		if(x==(y[i])){
			return 1;
		}
	}
	return 0;
}
char pos(char x){
	char i;
	char*y;
	char len;
	if(inp(x,0)){
		y="qwertyuiop";
	}
	else if(inp(x,1)){
		y="asdfghjkl";
	}
	else{
		y="zxcvbnm";
	}
	len=strlen(y);
	for(i=0;i<len;i++){
		if(x==(y[i])){
			return i;
		}
	}
}
char cl(char l,char c){
	char x=0;
	if(l>5){
		x=90;
	}
	else if(l>3){
		x=30;
	}
	if(x){
		x+=c;
	}
	return x;
}
char lr(char*y,char i,char s){
	if(!i){
		return y[("qwertyuiop"[s])-97];
	}
	else if(i==1){
		return y[("asdfghjkl"[s])-97];
	}
	else if(i==2){
		return y[("zxcvbnm"[s])-97];
	}
}
char clr(char x){
	char l=0;
	if((x&15)>3){
		l=90;
	}
	else if(x&15){
		l=30;
	}
	if(l){
		l+=x>>4;
	}
	return l;
}
int main(int argc,char**argv){
	if(argc>1){
		if(argv[1][0]==("-"[0])){
			if(argv[1][1]==("h"[0])){
				printf("Start programm without flags to start.\n");
				printf("Press buttons without caps.\n");
				printf("Press esc to exit.\n\n");
				printf("Edit ~/.config/touchboard.conf to change colour.\n");
				printf("How to edit? Type letter in down register and ");
				printf("next symbol must be number from 1 to 6 (Unix colours).\n");
				printf("Typing 0 or 7 does not make sense.\n");
				printf("-h - help.\n-o - khm.\n");
				return 0;
			}
			else if(argv[1][1]==("o"[0])){
				printf("Made by olly    \\(\\___/ ~ \\___/).\n");
				return 0;
			}
			else{
				fprintf(stderr,"input error\n");
				return 1;
			}
		}
		else{
			fprintf(stderr,"input error\n");
			return 1;
		}
	}
	setlocale(LC_ALL,"");
	struct termios t;
	struct termios x;
	long long i;
	char s=1;
	long long fi;
	char*y=malloc(26);
	char*z=malloc(6144);
	char***l=malloc(24);
	l[0]=malloc(80);
	for(i=0;i<10;i++){
		l[0][i]=calloc(6,1);
	}
	l[1]=malloc(72);
	l[1][0]=calloc(6,1);
	l[1][8]=calloc(6,1);
	for(i=1;i<8;i++){
		l[1][i]=calloc(5,1);
	}
	l[2]=malloc(56);
	for(i=0;i<7;i++){
		l[2][i]=calloc(6,1);
	}
	char*fs=malloc(1024);
	long long len;
	int o;
	char c;
	const char*h=getenv("HOME");
	char*sf=malloc(1024);
	snprintf(sf,256,"%s/.config/touchboard.conf",h);
	FILE*f=fopen(sf,"r");
	for(i=0;i<26;i++){
		y[i]=s;
		s++;
		if(s==7){
			s=1;
		}
	}
	if(f){
		while(fgets(fs,1024,f)){
			len=strlen(fs);
			for(i=0;i<len;i++){
				if((96<fs[i])&&((fs[i])<123)){
					y[(fs[i])-97]=fs[i+1]-48;
				}
				else{
					if((64<(fs[i]))&&((fs[i])<91)){
						y[(fs[i])-65]=fs[i+1]-48;
					}
				}
			}
		}
		fclose(f);
	}
	tcgetattr(0,&x);
	t.c_lflag&=~10;
	tcsetattr(0,2,&t);
	o=fcntl(0,3,0);
	fcntl(0,4,o|2048);
	setvbuf(stdout,z,0,6144);
	while(1){
		for(i=0;i<10;i++){
			l[0][i][0]--;
			if(l[0][i][0]<0){
				l[0][i][0]=0;
			}
			for(fi=1;fi<6;fi++){
				if((l[0][i][fi]&15)>0){
					l[0][i][fi]--;
				}
				else{
					l[0][i][fi]=0;
				}
			}
		}
		for(fi=1;fi<6;fi++){
			if((l[1][0][fi]&15)>0){
				l[1][0][fi]--;
			}
			else{
				l[1][0][fi]=0;
			}
		}
		for(i=0;i<9;i++){
			l[1][i][0]--;
			if(l[1][i][0]<0){
				l[1][i][0]=0;
			}
			if((i>0)&&(i<8)){
				for(fi=1;fi<5;fi++){
	                                if((l[1][i][fi]&15)>0){
	                                        l[1][i][fi]--;
	                                }
	                                else{
	                                        l[1][i][fi]=0;
	                                }
	                        }
			}
		}
		for(fi=1;fi<6;fi++){
                        if((l[1][8][fi]&15)>0){
                                l[1][8][fi]--;
                        }
                        else{
                                l[1][8][fi]=0;
                        }
                }
		for(i=0;i<7;i++){
			l[2][i][0]--;
			if(l[2][i][0]<0){
				l[2][i][0]=0;
			}
			for(fi=1;fi<6;fi++){
                                if((l[2][i][fi]&15)>0){
                                        l[2][i][fi]--;
                                }
                                else{
                                        l[2][i][fi]=0;
                                }
                        }
		}
		for(i=0;i<10;i++){
			if((l[0][i][2]&15)>3){
				l[0][i][5]++;
				if(l[0][i][5]){
					l[0][i][5]=6;
				}
				l[0][i][5]|=((l[0][i][2])>>4)<<4;
			}
			for(fi=1;fi<5;fi++){
				if(l[0][i][0]>3){
					l[0][i][fi]++;
					if(l[0][i][fi]>>4){
						l[0][i][fi]=6;
					}
					l[0][i][fi]|=(lr(y,0,i))<<4;
				}
			}
		}
		for(i=0;i<9;i++){
			if((!i)||(i==8)){
				if((l[1][i][2]&15)>3){
					l[1][i][5]++;
					if(l[1][i][5]){
						l[1][i][5]=6;
					}
					l[1][i][5]|=((l[1][i][2])>>4)<<4;
				}
			}
                        for(fi=1;fi<5;fi++){
                                if(l[1][i][0]>3){
                                        l[1][i][fi]++;
                                        if(l[1][i][fi]>>4){
						l[1][i][fi]=6;
					}
                                        l[1][i][fi]|=(lr(y,1,i))<<4;
                                }
                        }
		}
                for(i=0;i<7;i++){
                        if((l[2][i][2]&15)>3){
                                l[2][i][5]++;
                                if(l[2][i][5]){
                                        l[2][i][5]=6;
                                }
                                l[2][i][5]|=((l[2][i][2])>>4)<<4;
                        }
                        for(fi=1;fi<5;fi++){
                                if(l[2][i][0]>3){
                                        l[2][i][fi]++;
                                        if(l[2][i][fi]>>4){
                                                l[2][i][fi]=6;
                                        }
                                        l[2][i][fi]|=(lr(y,2,i))<<4;
                                }
                        }
                }
		for(i=0;i<2;i++){
	                c=0;
	                read(0,&c,1);
			if(c==27){
				tcsetattr(0,2,&x);
                                fcntl(0,4,o);
                                printf("\033[H\033[J");
                                fflush(stdout);
                                return 0;
			}
			if((96<c)&&(c<123)){
				if(inp(c,0)){
					l[0][pos(c)][0]=6;
				}
				else if(inp(c,1)){
					l[1][pos(c)][0]=6;
				}
				else{
					l[2][pos(c)][0]=6;
				}
			}
		}
		printf("\033[H\033[J\n\n\n");
//        ╭────────────────────────────────────────────────────────────────────────╮
		printf("        \033[%dm╭────────\033[0m",clr(l[0][0][5]));
		for(i=1;i<9;i++){
			printf("\033[%dm───────\033[0m",clr(l[0][i][5]));
		}
		printf("\033[%dm────────╮\033[0m",clr(l[0][9][5]));
//        │ ╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮ │
		printf("\n\r        \033[%dm│ \033[0m",clr(l[0][0][5]));
		for(i=0;i<10;i++){
                        printf("\033[%dm╭─────╮\033[0m",clr(l[0][i][2]));
                }
                printf("\033[%dm │\033[0m",clr(l[0][9][5]));
//        │ │  Q  ││  W  ││  E  ││  R  ││  T  ││  Y  ││  U  ││  I  ││  O  ││  P  │ │
		printf("\n\r        \033[%dm│ \033[0m",clr(l[0][0][5]));
		for(i=0;i<10;i++){
                        printf("\033[%dm│  \033[0m",clr(l[0][i][3]));
			printf("\033[%dm%c\033[0m",cl(l[0][i][0],lr(y,0,i)),"QWERTYUIOP"[i]);
			printf("\033[%dm  │\033[0m",clr(l[0][i][1]));
                }
		printf("\033[%dm │\033[0m",clr(l[0][9][5]));
//        │ │     ││     ││     ││     ││     ││     ││     ││     ││     ││     │ │
		printf("\n\r        \033[%dm│ \033[0m",clr(l[0][0][5]));
		for(i=0;i<10;i++){
			printf("\033[%dm│   \033[0m",clr(l[0][i][3]));
			printf("\033[%dm  │\033[0m",clr(l[0][i][1]));
		}
		printf("\033[%dm │\033[0m",clr(l[0][9][5]));
//      │ ╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯ │
		printf("\n\r        \033[%dm│ \033[0m",clr(l[0][0][5]));
		for(i=0;i<10;i++){
			printf("\033[%dm╰─────╯\033[0m",clr(l[0][i][4]));
		}
		printf("\033[%dm │\033[0m",clr(l[0][9][5]));
//        ╰──╮ ╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮ ╭───╯
		printf("\n\r        \033[%dm╰──╮ \033[0m",clr(l[0][0][5]));
		for(i=0;i<9;i++){
			printf("\033[%dm╭─────╮\033[0m",clr(l[1][i][2]));
		}
		printf("\033[%dm ╭───╯\033[0m",clr(l[0][9][5]));
//           │ │  A  ││  S  ││  D  ││  F  ││  G  ││  H  ││  J  ││  K  ││  L  │ │
		printf("\n\r           \033[%dm│ \033[0m",clr(l[1][0][5]));
		for(i=0;i<9;i++){
			printf("\033[%dm│  \033[0m",clr(l[1][i][3]));
			printf("\033[%dm%c\033[0m",cl(l[1][i][0],lr(y,1,i)),"ASDFGHJKL"[i]);
			printf("\033[%dm  │\033[0m",clr(l[1][i][1]));
		}
		printf("\033[%dm │\033[0m",clr(l[1][8][5]));
//           │ │     ││     ││     ││     ││     ││     ││     ││     ││     │ │
		printf("\n\r           \033[%dm│ \033[0m",clr(l[1][0][5]));
                for(i=0;i<9;i++){
			printf("\033[%dm│   \033[0m",clr(l[1][i][3]));
                        printf("\033[%dm  │\033[0m",clr(l[1][i][1]));
                }
                printf("\033[%dm │\033[0m",clr(l[1][8][5]));
//           │ ╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯ │
		printf("\n\r           \033[%dm│ \033[0m",clr(l[1][0][5]));
                for(i=0;i<9;i++){
                        printf("\033[%dm╰─────╯\033[0m",clr(l[1][i][4]));
                }
                printf("\033[%dm │\033[0m",clr(l[1][8][5]));
//           ╰───╮ ╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮ ╭─────────╯
		printf("\n\r           \033[%dm╰───╮ \033[0m",clr(l[1][0][5]));
                for(i=0;i<7;i++){
                        printf("\033[%dm╭─────╮\033[0m",clr(l[2][i][2]));
                }
                printf("\033[%dm ╭─────────╯\033[0m",clr(l[1][8][5]));
//               │ │  Z  ││  X  ││  C  ││  V  ││  B  ││  N  ││  M  │ │
		printf("\n\r               \033[%dm│ \033[0m",clr(l[2][0][5]));
                for(i=0;i<7;i++){
                        printf("\033[%dm│  \033[0m",clr(l[2][i][3]));
                        printf("\033[%dm%c\033[0m",cl(l[2][i][0],lr(y,2,i)),"ZXCVBNM"[i]);
                        printf("\033[%dm  │\033[0m",clr(l[2][i][1]));
                }
		printf("\033[%dm │\033[0m",clr(l[2][6][5]));
//               │ │     ││     ││     ││     ││     ││     ││     │ │
		printf("\n\r               \033[%dm│ \033[0m",clr(l[2][0][5]));
                for(i=0;i<7;i++){
                        printf("\033[%dm│   \033[0m",clr(l[2][i][3]));
                        printf("\033[%dm  │\033[0m",clr(l[2][i][1]));
                }
                printf("\033[%dm │\033[0m",clr(l[2][6][5]));
//               │ ╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯ │
                printf("\n\r               \033[%dm│ \033[0m",clr(l[2][0][5]));
                for(i=0;i<7;i++){
                        printf("\033[%dm╰─────╯\033[0m",clr(l[2][i][4]));
                }
                printf("\033[%dm │\033[0m",clr(l[2][6][5]));
//               ╰───────────────────────────────────────────────────╯
		printf("\n\r               \033[%dm╰─\033[0m",clr(l[2][0][5]));
		for(i=0;i<7;i++){
                        printf("\033[%dm───────\033[0m",clr(l[2][i][5]));
                }
		printf("\033[%dm─╯\033[0m",clr(l[2][6][5]));
		fflush(stdout);
		usleep(50000);
	}
}
/*



        ╭────────────────────────────────────────────────────────────────────────╮
        │ ╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮ │
        │ │  Q  ││  W  ││  E  ││  R  ││  T  ││  Y  ││  U  ││  I  ││  O  ││  P  │ │
        │ │     ││     ││     ││     ││     ││     ││     ││     ││     ││     │ │
        │ ╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯ │
        ╰──╮ ╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮ ╭───╯
           │ │  A  ││  S  ││  D  ││  F  ││  G  ││  H  ││  J  ││  K  ││  L  │ │
           │ │     ││     ││     ││     ││     ││     ││     ││     ││     │ │
           │ ╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯ │
           ╰───╮ ╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮╭─────╮ ╭─────────╯
               │ │  Z  ││  X  ││  C  ││  V  ││  B  ││  N  ││  M  │ │
               │ │     ││     ││     ││     ││     ││     ││     │ │
               │ ╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯╰─────╯ │
               ╰───────────────────────────────────────────────────╯


*/
