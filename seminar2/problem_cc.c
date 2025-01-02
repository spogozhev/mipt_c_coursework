#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int dec2vec(unsigned x, unsigned char vec[]);
unsigned nextShift(unsigned char vec[], int size);
bool isCircularPrime(unsigned x);
bool isPrime(long long x);

int main() {
    unsigned N = 0;
    unsigned ans = 0;
    int res;

    res = scanf("%d", &N);
    assert(res == 1);
    assert(N > 0);

    for (int i = 1; i < N; ++i) {
        ans = N - i;
        if (ans > 1 && isCircularPrime(ans)) {
            break;
        }
        ans = N + i;
        if (isCircularPrime(ans)) {
            break;
        }
    }

    printf("%d", ans);

    return 0;
}

int dec2vec(unsigned x, unsigned char vec[]) {
    int index = 0;
    while (x > 0) {
        vec[index] = x % 10;
        ++index;
        x /= 10;
    }
    return index;
}

unsigned nextShift(unsigned char vec[], int size) {
    unsigned ans = 0;
    unsigned char tmp = vec[0];
    for (int i = 1; i < size; ++i) {
        vec[i - 1] = vec[i];
    }
    vec[size - 1] = tmp;
    for (int i = size - 1; i >= 0; --i) {
        ans = ans * 10 + vec[i];
    }
    return ans;
}

bool isCircularPrime(unsigned x) {
    unsigned char digits[10];
    int size = dec2vec(x, digits);
    unsigned next;
    do {
        next = nextShift(digits, size);
        if (!isPrime(next)) {
            return false;
        }
    } while (x != next);
    return true;
}

bool isPrime(long long x) {
    if (x < 2) {
        return false;
    }
    if (x < 4) {
        return true;
    }
    if (x % 2 == 0) {
        return false;
    }
    for (long long i = 3; i * i <= x; i += 2) {
        if ((x % i) == 0) {
            return false;
        }
    }
    return true;
}
