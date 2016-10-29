#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<ctype.h>
#include<stdbool.h>
#include<stdint.h>
#include<float.h>
#include<math.h>
#include<string.h>
#include<assert.h>
#include<time.h>
#include<sys/time.h>

#define MAX(x, y)  (x) > (y) ? (x) : (y)
#define MIN(x, y)  (x) < (y) ? (x) : (y)

#define P(x) \
	fprintf(stderr, "(%d) %s = (long)%ld (double)%f (addr)%p\n", __LINE__, #x, (long)(x), (double)(x), (void*)((intptr_t)x)); 

static double gettime()
{
	struct timeval tv = {0};
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0);
}

// 

#define KMAGIC 0xDeadBeef

typedef void (*Kcleanup)(void *);

typedef struct Kheader {
        size_t magic;
        const char *type;
	size_t refc;
	Kcleanup  cleanup;
} Kheader;

static void * Kmalloc(size_t size, const char *type, Kcleanup cleanup)
{
        Kheader *h = (Kheader *)malloc(sizeof(Kheader) + size);
        bzero(h, sizeof(Kheader) + size);
        h[0].magic = KMAGIC;
        h[0].type = type;
	h[0].refc = 0;
	h[0].cleanup = cleanup;
        return (void*)(&h[1]);
}

#define Knew(T) (T *)Kmalloc(sizeof(T), #T, NULL)
#define Knew2(T, C) (T *)Kmalloc(sizeof(T), #T, C);

static const char *Kname(void *ptr)
{
        Kheader *h = (Kheader*)ptr;
        assert(h[-1].magic == KMAGIC);
        return h[-1].type;
}

static bool Kis(void *ptr, const char *type)
{
        const char *t = Kname(ptr);
        return t == type || strcmp(t, type) == 0;
}

static void Kinc(void *value)
{
	if(value == NULL) {
		return ;
	}
        Kheader *h = (Kheader *)value;
        assert(h[-1].magic == KMAGIC);
	h[-1].refc += 1;
}

static void Kdec(void *value)
{
	if(value == NULL) {
		return ;
	}
	Kheader *h = (Kheader *)value;
        assert(h[-1].magic == KMAGIC);
        h[-1].refc -= 1;
	if(h[-1].refc == 0) {
		if(h[-1].cleanup != NULL) {
                        h[-1].cleanup(value);
                }
		free(h - 1);
        }
}

