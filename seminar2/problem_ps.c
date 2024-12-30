#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct sieve_t {
    int n;
    char *s;
};

int sieve_bound(int num)
{
    double dnum, dres;
    if (num <= 20)
        return 100;
    dnum = num;
    dres = dnum * (log(dnum) + log(log(dnum)));
    return (int) round(dres);
}

void fill_sieve(struct sieve_t *s);
int nth_prime(struct sieve_t *s, int N);
void print_sieve(struct sieve_t *s);

int main()
{
    int n, outp;
    int res;
    struct sieve_t *s;

    res = scanf("%d", &n);
    assert(res == 1);
    s = (struct sieve_t *) malloc(sizeof(struct sieve_t));
    s->n = sieve_bound(n);
    s->s = (char *) calloc(s->n, sizeof(char));
    fill_sieve(s);
    //print_sieve(s);
    outp = nth_prime(s, n);
    printf("%d\n", outp);

    free(s->s);
    free(s);
}

#line 10000

void fill_sieve(struct sieve_t *s){
    long long size = s->n;
    s->s[0] = 1;
    s->s[1] = 1;
    for(int p = 2; p < s->n; ++p){
        if (s->s[p]==0){
            for(long long j = p; j*p < size; ++j){
                s->s[j*p] = 1;
            }
        }
    }
}

int nth_prime(struct sieve_t *s, int N){
    int index = 2;
    while (N>1){
        do {
            ++index;
        } while((index < s->n) && (s->s[index])!=0);
        if (index >= s->n) printf("ups\n");
        --N;
    }
    return index;
}

void print_sieve(struct sieve_t *s){
    for(int i=2; i<s->n; ++i){
        printf("%d ", s->s[i]);
    }
}