#include "mymagic.h"

int match(const char s[], const char t[])
{
	int slen = strlen(s);
	int tlen = strlen(t);
	for(int i = 0; i <= slen - tlen; i++) {
		bool found = true;
		for(int j = 0; j < tlen; j++) {
			if(s[i+j] != t[j]) {
				found = false;
				break;
			}
		}
		if(found) {
			return i;
		}
	}
	return -1;
}

int match2(const char s[], const char t[]) {
	int slen = strlen(s);
	int tlen = strlen(t);
	for(int i = 0; i <= slen - tlen; i++) {
		if(memcmp(s+i, t, tlen) == 0) {
			return i;
		}
	}
	return -1;
}

int match_strstr(const char s[], const char t[])
{
	const char * p = strstr(s, t);
	return (p == NULL) ? -1 : p - s;
}

#define REHASH(a, b, h) ((((h) - (a)*d) << 1) + (b))

int match_kr(const char y[], const char x[])
{
	int m = strlen(y), n = strlen(x);
	int d=1, hx, hy, i, j;

   	/* Preprocessing */
   	/* computes d = 2^(m-1) with the left-shift operator */
   	for (int i = 1; i < m; ++i) {
      		d = (d<<1);
	}

   	for (hy = hx = i = 0; i < m; ++i) {
      		hx = ((hx<<1) + x[i]);
      		hy = ((hy<<1) + y[i]);
   	}

   	/* Searching */
   	j = 0;
   	while (j <= n-m) {
      		if (hx == hy && memcmp(x, y + j, m) == 0) {
        		return j;
		}
      		hy = REHASH(y[j], y[j + m], hy);
      		++j;
   	}
	return -1;
}

// -------

#define ALPHABET_LEN 255
#define NOT_FOUND patlen
#define max(a, b) ((a < b) ? b : a)

// delta1 table: delta1[c] contains the distance between the last
// character of pat and the rightmost occurence of c in pat.
// If c does not occur in pat, then delta1[c] = patlen.
// If c is at string[i] and c != pat[patlen-1], we can
// safely shift i over by delta1[c], which is the minimum distance
// needed to shift pat forward to get string[i] lined up 
// with some character in pat.
// this algorithm runs in alphabet_len+patlen time.

void make_delta1(int *delta1, uint8_t *pat, int32_t patlen) {
    int i;
    for (i=0; i < ALPHABET_LEN; i++) {
        delta1[i] = NOT_FOUND;
    }
    for (i=0; i < patlen-1; i++) {
        delta1[pat[i]] = patlen-1 - i;
    }
}

// true if the suffix of word starting from word[pos] is a prefix 
// of word
int is_prefix(uint8_t *word, int wordlen, int pos) {
    int i;
    int suffixlen = wordlen - pos;
    // could also use the strncmp() library function here
    for (i = 0; i < suffixlen; i++) {
        if (word[i] != word[pos+i]) {
            return 0;
        }
    }
    return 1;
}

// length of the longest suffix of word ending on word[pos].
// suffix_length("dddbcabc", 8, 4) = 2
int suffix_length(uint8_t *word, int wordlen, int pos) {
    int i;
    // increment suffix length i to the first mismatch or beginning
    // of the word
    for (i = 0; (word[pos-i] == word[wordlen-1-i]) && (i < pos); i++);
    return i;
}

// delta2 table: given a mismatch at pat[pos], we want to align 
// with the next possible full match could be based on what we
// know about pat[pos+1] to pat[patlen-1].
//
// In case 1:
// pat[pos+1] to pat[patlen-1] does not occur elsewhere in pat,
// the next plausible match starts at or after the mismatch.
// If, within the substring pat[pos+1 .. patlen-1], lies a prefix
// of pat, the next plausible match is here (if there are multiple
// prefixes in the substring, pick the longest). Otherwise, the
// next plausible match starts past the character aligned with 
// pat[patlen-1].
// 
// In case 2:
// pat[pos+1] to pat[patlen-1] does occur elsewhere in pat. The
// mismatch tells us that we are not looking at the end of a match.
// We may, however, be looking at the middle of a match.
// 
// The first loop, which takes care of case 1, is analogous to
// the KMP table, adapted for a 'backwards' scan order with the
// additional restriction that the substrings it considers as 
// potential prefixes are all suffixes. In the worst case scenario
// pat consists of the same letter repeated, so every suffix is
// a prefix. This loop alone is not sufficient, however:
// Suppose that pat is "ABYXCDEYX", and text is ".....ABYXCDEYX".
// We will match X, Y, and find B != E. There is no prefix of pat
// in the suffix "YX", so the first loop tells us to skip forward
// by 9 characters.
// Although superficially similar to the KMP table, the KMP table
// relies on information about the beginning of the partial match
// that the BM algorithm does not have.
//
// The second loop addresses case 2. Since suffix_length may not be
// unique, we want to take the minimum value, which will tell us
// how far away the closest potential match is.
void make_delta2(int *delta2, uint8_t *pat, int32_t patlen) {
    int p;
    int last_prefix_index = patlen-1;

    // first loop
    for (p=patlen-1; p>=0; p--) {
        if (is_prefix(pat, patlen, p+1)) {
            last_prefix_index = p+1;
        }
        delta2[p] = last_prefix_index + (patlen-1 - p);
    }

    // second loop
    for (p=0; p < patlen-1; p++) {
        int slen = suffix_length(pat, patlen, p);
        if (pat[p - slen] != pat[patlen-1 - slen]) {
            delta2[patlen-1 - slen] = patlen-1 - p + slen;
        }
    }
}

uint8_t* boyer_moore (uint8_t *string, uint32_t stringlen, uint8_t *pat, uint32_t patlen) {
    int i;
    int delta1[ALPHABET_LEN];
    int *delta2 = malloc(patlen * sizeof(int));
    make_delta1(delta1, pat, patlen);
    make_delta2(delta2, pat, patlen);

    i = patlen-1;
    while (i < stringlen) {
        int j = patlen-1;
        while (j >= 0 && (string[i] == pat[j])) {
            --i;
            --j;
        }
        if (j < 0) {
            free(delta2);
            return (string + i+1);
        }

        i += max(delta1[string[i]], delta2[j]);
    }
    free(delta2);
    return NULL;
}

int match_bm(const char s[], const char t[]) {
	char *p = (char*)boyer_moore((uint8_t*)s, strlen(s), (uint8_t*)t, strlen(t));
	return p == NULL ? -1 : p - s;
}

// -------

#define N 1000000
char text[N+2]={0};
char pat[N+2]={0};

void init(int m, int n) {
	assert(m <= N);
	assert(n <= N);
	for(int i = 0; i < N; i++) {
		text[i] = 'a';
		pat[i] = 'a';
	}
	text[m]='b';
	text[m+1]= 0;
	pat[n] = 'b';
	pat[n+1] = 0;
}


int main()
{
	init(100000, 15);
	double s = gettime();
	printf("match  %d %f[ms]\n", match(text, pat), gettime() - s);
	s = gettime();
	printf("memcmp %d %f[ms]\n", match2(text, pat), gettime() - s);
	s = gettime();
	printf("strstr %d %f[ms]\n", match_strstr(text, pat), gettime() - s);
	s = gettime();
	printf("bm     %d %f[ms]\n", match_bm(text, pat), gettime() - s);
	//s = gettime();
	//printf("kr    %d %f[ms]\n", match_kr(text, pat), gettime() - s); 
	return 0;
}

