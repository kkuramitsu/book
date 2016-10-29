#include "mymagic.h"

struct Process {
	int id;
	int remain;
	struct Process *next;
};

void p(int t, struct Process *p) {
	printf("%d ms: ", t);
	for(; p != NULL; p = p->next) {
		printf("P(%d, %d) ", p->id, p->remain);
	}
	printf("\n");
}

#define PMAX 1000
struct Process buf[PMAX] = {0};

int main() {
	struct Process *head = buf;
	struct Process *tail;
	int tmax = 10;
	for(int id = 0; id < PMAX; id++) {
		int t = 0;
		printf("Process %d: ", id+1);
		scanf("%d", &t);
		if(t <= 0) break;
		tmax += t;
		buf[id].id = id+1;
		buf[id].remain = t;
		buf[id].next = &buf[id+1];
		tail = &buf[id];
	}
	tail->next = NULL;
	// start
	int slice = 10;
	for(int t = 0; head != NULL && t < tmax; t++) {
		if(t % 10 == 0) {
			p(t, head);
		}
		head->remain--;
		if(head->remain == 0) {
			head = head->next;
			slice = 10;
		}
		slice--;
		if(slice == 0) {
			if(head->next != NULL) {
				struct Process *de = head;
				head = head->next;
				tail->next = de;
				tail = de;
				tail->next = NULL;
			}
			slice = 10;
		}
	}
	return 0;
}

