#include<stdio.h>

void readtext(const char *infile) {
	FILE *in = fopen(infile, "r");
	if(in != NULL) {
		int ch = 0;
		while((ch = fgetc(in)) != EOF) {
			putchar(ch);
		}
		fclose(in);
	}
}
