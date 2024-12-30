#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct sieve_t {
    int n;
    char *s;
};

int sieve_bound(int num)
{
    double dnum, dres;
    if (num <= 20 * CHAR_BIT)
        return 100 * CHAR_BIT;
    dnum = num;
    dres = dnum * (log(dnum) + log(log(dnum)));
    return (int) round(dres) + 1;
}

void fill_sieve(struct sieve_t *s);
int is_prime(struct sieve_t *sv, unsigned n);


int nth_prime(struct sieve_t *s, int N)
{
    int cnt, p;
    if (N == 1)
        return 2;
    if (N == 2)
        return 3;

    cnt = 2;
    p = 5;

    for (; ; ) {
        if (is_prime(s, p)) {
            cnt += 1;
            if (cnt == N)
                break;
        }
        p += 2;
        if (is_prime(s, p)) {
            cnt += 1;
            if (cnt == N)
                break;
        }
        p += 4;
    }

    return p;
}

int main()
{
    int n, outp;
    int res;
    struct sieve_t *s;

    res = scanf("%d", &n);
    assert(res == 1);

    s = (struct sieve_t *) malloc(sizeof(struct sieve_t));
    assert(s);

    s->n = (sieve_bound(n) / CHAR_BIT) + CHAR_BIT;
    s->s = (char *) calloc(s->n, sizeof(char));
    assert(s->s);

    fill_sieve(s);
    for (int i = 2; i < n; ++i)
      printf("%d %d\n", i, is_prime(s, i));

    outp = nth_prime(s, n);
    printf("%d\n", outp);

    free(s->s);
    free(s);
}

#line 10000

int is_prime(struct sieve_t *sv, unsigned n)
{
    return (sv->s[n / 8] >> n % 8) & 1;
}
void fill_sieve(struct sieve_t *sv)
{
    unsigned long long n;
    unsigned long long m;
    int size = 8;
    sv->s[0] = sv->s[0] | (1 << 0);
    sv->s[0] = sv->s[0] | (1 << 1);

    for (n = 2; n < sv->n; n++) {
        if (((sv->s[n / size] >> (n % size)) & 0) == 0) {
            for (m = n * n; m < sv->n; m += n) {
                assert(m >= 0 && m <= sv->n);
                sv->s[m / size] = sv->s[m / size] | (1 << m % size);
            }
        }
    }
}

/*
void fill_sieve(struct sieve_t *s){
    long long size = s->n;
    int index;
    int shift;
    s->s[0] = (s->s[0]) | 1;
    s->s[0] = (s->s[0]) | 2;
    for(int p = 2; p < s->n; ++p){
        index = p/8;
        shift = p - index;
        if ( ((s->s[index]) & (1<<shift)) == 0){
            for(long long j = p; j*p < size; ++j){
                index = (j*p)/8;
                shift = j*p - index;
                s->s[index] = (s->s[index]) | (1 << shift);
            }
        }
    }
}
*/
