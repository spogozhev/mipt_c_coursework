#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int nlz(unsigned x){
    int n;
    if (x==0) return 32;
    n = 1;
    if((x>>16)==0) { n = n + 16; x = x<<16;}
    if((x>>24)==0) { n = n + 8;  x = x<<8;}
    if((x>>28)==0) { n = n + 4;  x = x<<4;}    
    if((x>>30)==0) { n = n + 2;  x = x<<2;}    
    n= n - (x>>31);
    return n;
}

int ntz(unsigned x){
    int n;
    if (x==0) return 32;
    n = 1;
    if((x & 0x0000FFFF) == 0) { n = n + 16; x = x>>16;}
    if((x & 0x000000FF) == 0) { n = n + 8;  x = x>>8; }
    if((x & 0x0000000F) == 0) { n = n + 4;  x = x>>4; }    
    if((x & 0x00000003) == 0) { n = n + 2;  x = x>>2; }    
    return n - (x & 1);
}

int main() {
    unsigned N = 0;
    int lsb = 0;
    int msb = 0;
    int res;

    res = scanf("%u", &N);
    assert(res == 1);
    msb = nlz(N);
    if (msb==32){
        printf("NO");
    } else {
        msb = 31-msb;
        lsb = ntz(N);
        printf("%d %d", msb, lsb);
    }

    return 0;
}

