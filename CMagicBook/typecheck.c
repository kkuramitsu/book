#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<assert.h>

#define MAGIC 0xDeadBeef

struct header {
	size_t magic;
	const char *type;
};

void * _tmalloc(size_t size, const char *type)
{
	struct header *h = (struct header *)malloc(sizeof(struct header) + size);
	bzero(h, sizeof(struct header) + size);
	h[0].magic = MAGIC;
	h[0].type = type;
	return (void*)(&h[1]);
}

const char *tname(void *ptr)
{
	struct header *h = (struct header*)ptr;
	assert(h[-1].magic == MAGIC);
	return h[-1].type;
}

bool _instanceof(void *ptr, const char *type)
{
	const char *t = tname(ptr);
	return t == type || strcmp(t, type) == 0;
}

void tfree(void *ptr)
{
	struct header *h = (struct header *)ptr;
	assert(h[-1].magic == MAGIC);
	free(h - 1);
}

struct point {
	int x, y;
};

struct list {
	int value;
	struct List *next;
};

#define tmalloc(T) (T *)_tmalloc(sizeof(T), #T)
#define instanceof(p, T) _instanceof(p, #T)

struct Shape {
	double (*area)(void *);
};

struct Triangle {
	struct Shape super;
	double width;
	double height;
};

struct Circle {
	struct Shape super;
	double radius;
};

double Triangle_area(struct Triangle *this)
{
	return this->width * this->height / 2.0;
}

double Circle_area(struct Circle *this)
{
	return 3.14159 * this->radius * this->radius;
}

void poly()
{
	struct Triangle *t = tmalloc(struct Triangle);
	t->height = 18.0;
	t->width = 18.0;
	t->super.area = Triangle_area;
	struct Circle *c = tmalloc(struct Circle);
	c->radius = 9.0;
	c->super.area = Circle_area;
	printf("Circle: %f\n", c->super.area(c));
	printf("Triangle: %f\n", t->super.area(t));
}

int main() {
	struct point *p = tmalloc(struct point);
	printf("Type name: %s\n", tname(p));
	printf("Is struct point?: %d\n", instanceof(p, struct point));
	printf("Is struct list?: %d\n", instanceof(p, struct list));
	tfree(p);
	poly();
	return 0;
}

