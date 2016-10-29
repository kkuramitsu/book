#include"mymagic.h"
#include<setjmp.h>

typedef int (*opfunc)(int, int);

int add(int x, int y)
{
	return x+y;
}

int sub(int x, int y)
{
	return x-y;
}

int mul(int x, int y)
{
	return x*y;
}

jmp_buf jbuf;

int _div(int x, int y)
{
	if(y == 0) {
		longjmp(jbuf, 1);
	}
	return x/y;
}

int mod(int x, int y)
{
	if(y == 0) {
		longjmp(jbuf, 1);
	}
	return x%y;
}

#define OP 5
static opfunc opset[OP] = {
	add, sub, mul, _div, mod
};
static int opcharset[OP] = {
	'+', '-', '*', '/', '%'
};

static int opc(opfunc f) {
	for(int i = 0; i< OP; i++) {
		if(opset[i] == f) {
			return opcharset[i];
		}
	}
	return '?';
}

typedef int (*exprfunc)(int *, opfunc *);

int left(int d[], opfunc op[])
{
	return op[2](op[1](op[0](d[0],d[1]),d[2]),d[3]);
}

int leftmid(int d[], opfunc op[])
{
	return op[2](op[0](d[0], op[1](d[1], d[2])),d[3]);
}

int mid(int d[], opfunc op[])
{
	return op[1](op[0](d[0], d[1]),op[2](d[2], d[3]));
}

int midright(int d[], opfunc op[])
{
	return op[0](d[0],op[2](op[1](d[1],d[2]),d[3]));
}

int right(int d[], opfunc op[])
{
	return op[0](d[0], op[1](d[1], op[2](d[2], d[3])));
}

#define EXPR 5
static exprfunc exprset[EXPR] = {
	left, leftmid, mid, midright, right
};

static const char* exprfmt[EXPR] = {
	"((%d %c %d) %c %d) %c %d\n",
	"(%d %c (%d %c %d)) %c %d\n",
	"((%d %c %d) %c (%d %c %d)\n",
	"%d %c ((%d %c %d) %c %d)\n",
	"%d %c (%d %c (%d %c %d))\n"
};

void p(int expr, int d[], opfunc op[])
{
	printf(exprfmt[expr], d[0], opc(op[0]), d[1], opc(op[1]), d[2], opc(op[2]), d[3]); 
}

void check(int d[], opfunc op[]) {
	for(int i = 0; i < EXPR; i++) {
		if( setjmp( jbuf ) == 0 ) {
			if(exprset[i](d, op) == 10) {
				p(i, d, op);
			}
		}
	}
}

void shuffle(int d[]) {
	opfunc op[3] = {NULL};
	for(int i = 0; i < OP; i++) {
		for(int j = 0; j < OP; j++) {
			for(int k = 0; k < OP; k++) {
				op[0] = opset[i];
				op[1] = opset[j];
				op[2] = opset[k];
				check(d, op);
			}
		}
	}
}

void swap(int a[], int l, int r) {
        int tmp = a[l];
        a[l] = a[r];
        a[r] = tmp;
}

void perm(int d[], int len, int loc)
{
        if(loc + 1 == len) {
                shuffle(d);
                return;
        }
        perm(d, len, loc+1);
        for(int i = loc + 1; i < len; i++) {
                swap(d, loc, i);
                perm(d, len, loc+1);
                swap(d, loc, i);
        }
}

int main()
{
	int n = 0;
	scanf("%d", &n);
	int d[4] = {
		(n / 1000) % 10,
		(n / 100) % 10,
		(n / 10) % 10,
		n % 10,
	};
	perm(d, 4, 0);
}
