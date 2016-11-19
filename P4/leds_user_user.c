#include <stdio.h>
#include <fcntl.h>
#include <unistd.h> 

void showPunto(int fd){
	write(fd,"0",1);
	usleep(500000);
	write(fd,"1",1);
	usleep(500000);
}

void showRalla(int fd){
	write(fd,"0",1);
	usleep(500000);
	write(fd,"2",1);
	usleep(500000);
}

void showEspacio(int fd){
	write(fd,"0",1);
	usleep(1000000);
}

void showMorseFrom(char mander, int fd){
	switch(mander){
		case 'a':
		case 'A':
			showPunto(fd);			showRalla(fd);
			break;
		case 'b':
		case 'B':
			showRalla(fd);			showPunto(fd);
			showPunto(fd);			showPunto(fd);
			break;
		case 'c':
		case 'C':
			showRalla(fd);			showPunto(fd);
			showRalla(fd);			showPunto(fd);
			break;
		case 'd':
		case 'D':
			showRalla(fd);			showPunto(fd);
			showPunto(fd);
			break;
		case 'e':
		case 'E':
			showPunto(fd);
			break;
		case 'f':
		case 'F':
			showPunto(fd);			showPunto(fd);
			showRalla(fd);			showPunto(fd);
			break;
		case 'g':
		case 'G':
			showRalla(fd);			showRalla(fd);
			showPunto(fd);
			break;
		case 'h':
		case 'H':
			showPunto(fd);			showPunto(fd);
			showPunto(fd);			showPunto(fd);
			break;
		case 'i':
		case 'I':
			showPunto(fd);			showPunto(fd);
			break;
		case 'j':
		case 'J':
			showPunto(fd);			showRalla(fd);
			showRalla(fd);			showRalla(fd);
			break;
		case 'k':
		case 'K':
			showRalla(fd);			showPunto(fd);
			showRalla(fd);
			break;
		case 'l':
		case 'L':
			showPunto(fd);			showRalla(fd);
			showPunto(fd);			showPunto(fd);
			break;
		case 'm':
		case 'M':
			showRalla(fd);			showRalla(fd);
			break;
		case 'n':
		case 'N':
			showRalla(fd);			showPunto(fd);
			break;
		case 'o':
		case 'O':
			showRalla(fd);			showRalla(fd);
			showRalla(fd);
			break;
		case 'p':
		case 'P':
			showRalla(fd);
			showPunto(fd);			showRalla(fd);
			showRalla(fd);			showPunto(fd);
			break;
		case 'q':
		case 'Q':
			showRalla(fd);			showRalla(fd);
			showPunto(fd);			showRalla(fd);
			break;
		case 'r':
		case 'R':
			showPunto(fd);			showRalla(fd);
			showPunto(fd);
			break;
		case 's':
		case 'S':
			showPunto(fd);			showPunto(fd);
			showPunto(fd);
			break;
		case 't':
		case 'T':
			showRalla(fd);
			break;
		case 'u':
		case 'U':
			showPunto(fd);			showPunto(fd);
			showRalla(fd);
			break;
		case 'v':
		case 'V':
			showPunto(fd);			showPunto(fd);
			showPunto(fd);			showRalla(fd);
			break;
		case 'w':
		case 'W':
			showPunto(fd);			showRalla(fd);
			showRalla(fd);
			break;
		case 'x':
		case 'X':
			showRalla(fd);			showPunto(fd);
			showPunto(fd);			showRalla(fd);
			break;
		case 'y':
		case 'Y':
			showRalla(fd);			showPunto(fd);
			showRalla(fd);			showRalla(fd);
			break;
		case 'z':
		case 'Z':
			showRalla(fd);			showRalla(fd);
			showPunto(fd);			showPunto(fd);
			break;
		case '1':
			showPunto(fd);			showRalla(fd);
			showRalla(fd);			showRalla(fd);
			showRalla(fd);
			break;
		case '2':
			showPunto(fd);			showPunto(fd);
			showRalla(fd);			showRalla(fd);
			showRalla(fd);
			break;
		case '3':
			showPunto(fd);			showPunto(fd);
			showPunto(fd);			showRalla(fd);
			showRalla(fd);
			break;
		case '4':
			showPunto(fd);			showPunto(fd);
			showPunto(fd);			showPunto(fd);
			showRalla(fd);
			break;
		case '5':
			showPunto(fd);			showPunto(fd);
			showPunto(fd);			showPunto(fd);
			showPunto(fd);
			break;
		case '6':
			showRalla(fd);			showPunto(fd);
			showPunto(fd);			showPunto(fd);
			showPunto(fd);
			break;
		case '7':
			showRalla(fd);			showRalla(fd);
			showPunto(fd);			showPunto(fd);
			showPunto(fd);
			break;
		case '8':
			showRalla(fd);			showRalla(fd);
			showRalla(fd);			showPunto(fd);
			showPunto(fd);
			break;
		case '9':
			showRalla(fd);			showRalla(fd);
			showRalla(fd);			showRalla(fd);
			showPunto(fd);
			break;
		case '0':
			showRalla(fd);			showRalla(fd);
			showRalla(fd);			showRalla(fd);
			showRalla(fd);
			break;
		default:
			break;
	}
	showEspacio(fd);
}

int main(){
	int i=0;
	char input[128];
	int fd=open("/dev/led", O_WRONLY);
	printf("Dame cadena: ");
	scanf("%s", input);
	while(i<128 && input[i]!='\n'){
		showMorseFrom(input[i],fd);
		i++;
	}
	close(fd);
	return 0;
}









