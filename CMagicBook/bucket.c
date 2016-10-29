#include"mymagic.h"

#define A  5
#define B  3
#define C  4

struct buckets {
	const char *action;
	int a;
	int b;
};

bool search(int a, int b, int depth, int maxdepth, int visited[])
{
	if(a == C || b == C) {
		return true;
	}
	if(a < 0 || a > A || b < 0 || b > B) {
		return false;
	}
	if(depth == maxdepth) {
		return false;
	}
	int h = a * (B+1) + b;
	assert(h < (A+1) * (B+1));
	if(visited[h] == 1) {
		return false;
	}
	visited[h] = 1;

	int moveAB = (B-b) > a ? a : (B-b);
	int moveBA = (A-a) > b ? b : (A-a);
	struct buckets path[6] = {
		{"Fill A", A, b},
		{"Fill B", a, B},
		{"Move A to B", a-moveAB, b+moveAB},
		{"Move B to A", a+moveBA, b-moveBA},
		{"Drop A", 0, b},
        	{"Drop B", a, 0},
	};
	for(int i = 0; i < 6; i++) {
		if(search(path[i].a, path[i].b, depth+1, maxdepth, visited)) {
			printf("#%d %s (%d,%d) => (%d, %d)\n", depth+1, path[i].action, a, b, path[i].a, path[i].b);
			return true;
		}
	}
	return false;
}

struct path {
    const char *action;
    int a;
    int b;
    struct *parent;
    struct *next;
};

struct *path newpath(const char *action, int a, int b, struct path *parent, struct path *tail)
{
    struct path *p = (struct path)calloc(sizeof(struct path), 1);
    p->action = action;
    p->a = a;
    p->b = b;
    p->parent = parent;
    p->next = NULL;
    if(tail != NULL) {
        tail->next = p;
    }
    return p;
}

struct path* findpath(int a, int b, struct path *parent, int visited[])
{
    int h = a * (B+1) + b;
    assert(h < (A+1) * (B+1));
    if(visited[h] == 1) {
        return NULL;
    }
    visited[h] = 1;
    int moveAB = (B-b) > a ? a : (B-b);
    int moveBA = (A-a) > b ? b : (A-a);
    struct path *head = newpath("Fill A", A, b, parent, NULL);
    struct path *tail = head;
    tail = newpath("Fill B", a, B, parent, tail);
    tail = newpath("Move A to B", a-moveAB, b+moveAB, parent, tail);
    tail = newpath("Move B to A", a+moveBA, b-moveBA, parent, tail);
    tail = newpath("Drop A", 0, b, parent, tail);
    tail = newpath("Drop B", a, 0, , parent, tail);
    return head;
}

void merge(struct path *p, struct path *n)
{
    for(;p->next != NULL; p = p->next);
    p->next = n;
}

bool bsearch(int a, int b, int visited[])
{
    struct path *p = findpath(a, b, NULL, visited);
    for(; p != NULL; p = p->next) {
        if(p->a == C || p->b == C) {
            break;
        }
        if(p->a <0 || p->a > A || p->b < 0 || p->b > B) {
            continue;
        }
        merge(p, findpath(p->a, p->b, p, visited));
    }
    if(p != NULL) {
        for(; p != NULL; p = p->parent) {
            printf("%s => (%d, %d)\n", p->action, p->a, p->b);
        }
        return true;
    }
    return false;
}


int main() 
{
	int visited[(A+1)*(B+1)] = {0};
	for(int maxdepth = 2; maxdepth < A*B; maxdepth++) {
		memset(visited, 0, sizeof(visited)); 
		if(search(0, 0, 0, maxdepth, visited)) {
			break;
		}
	}
	return 0;
}
