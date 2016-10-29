#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

struct List {
	int value;
	struct List *prev;
	struct List *next;
};

struct List*
append(struct List *tail, int value) {
	struct List *o = (struct List *)calloc(1, sizeof(struct List));
	o->value = value;
	o->prev = NULL;
	o->next = NULL;
	if(tail != NULL) {
		assert(tail->next == NULL);
		tail->next = o;
		o->prev = tail;
	}
	return o;
}

int
main() {
	struct List *head = NULL;
	struct List *tail = NULL;
	for(; !feof(stdin); ) {
		int x = 0;
		if(scanf("%d", &x) <= 0) {
			break;
		}
		tail = append(tail, x);
		if(head == NULL) {
			head = tail;
		}
	}
	for(struct List *c = head; c != NULL; c = c->next) {
		printf("%d ", c->value);
	}
	printf("\n");
	for(struct List *c = tail; c != NULL; c = c->prev) {
		printf("%d ", c->value);
	}
	printf("\n");
	return 0;
}
