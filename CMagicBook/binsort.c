#include "mymagic.h"

struct student {
	const char *name;
	int score;
	int rank;
};

struct student data[3] = {
	{"naruto", 400}, {"sasuke, 880}, {"sakura", 720}
};

int compare(struct student *s, struct student *e)
{
	s->score - e->score;
}

int
main() {
	qsort(data, n, sizeof(struct student), compare); 
	return 0;
}
