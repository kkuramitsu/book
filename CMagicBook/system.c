#include "mymagic.h"

#define START "open"

int main(void)
{
	char url[BUFSIZ];
	char cmd[BUFSIZ + sizeof(START)+1];
	printf("URL: ");
	fgets(url, BUFSIZ, stdin);
	snprintf(cmd, BUFSIZ, "%s %s", START, url); 
	printf("invoking %s\n", cmd);
	system(cmd);
	return 0;
}

