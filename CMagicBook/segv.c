#include"mymagic.h"

char* upper(char str[]) {
	int size = strlen(str);
	for(int i = 0; i < size; i++) {
		if(islower(str[i])) {
			str[i] = toupper(str[i]);
		}
	}
	return NULL;
}

int main()
{
	char msg[20] = {'h', 'i', '\0'};
	printf("%s\n", upper(msg));
	printf("%s\n", upper("hello,world"));
	return 0;
}

