 stack.c 
 This program has a buffer overflow vulnerability. 
 Our task is to exploit this vulnerability 
#include stdlib.h
#include stdio.h
#include string.h

unsigned long get_sp(void) {
	__asm__(movl %esp,%eax);
}


int bof(char str){
	char buffer[18];
	printf(Address of str is %pn, (void)&str);
	printf(%pn, (void)get_sp());
	 The following statement has a buffer overflow problem 
	strcpy(buffer, str);
	return 1;
}
int main(int argc, char argv){
	char str[517];
	FILE badfile;
	badfile = fopen(badfile, r);
	fread(str, sizeof(char), 517, badfile);
	bof(str);
	printf(Returned Properlyn);
	return 1;
}