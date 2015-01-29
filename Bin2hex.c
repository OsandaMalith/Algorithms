#include <stdio.h>
#define BITS 8

/*
 * https://github.com/OsandaMalith
 */
 
char binary[BITS];

short toHex(char *binary) {
	size_t i;
	short MASK, hex = 0;
	for (i = 0; i < BITS; i++) {
		hex <<= 1;
		switch (*(binary+i)){
			case '1':MASK = 1; break;
			case '0':MASK = 0; break;
			default: puts("Not binary");
		}	
		hex |= MASK;
	} return hex;
}

int main (void) { 
	size_t i;
	puts("\t\t\t****_Binary to Hex Converter_****");
	puts("\t\t\t  2015 (c) Osanda M. Jayathissa")	
	;fputs("\nEnter an 8-bit binary number: ",stdout);
	for (i = 0; i < BITS; i++) binary[i] = getchar();
	printf ("Hex value = %x\n",toHex(&binary));
	return 0;
}
