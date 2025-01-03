#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*xcmp_t)(void *lhs, int lsz, void *rhs, int rsz);

void xmsort(void *mem, int *sizes, int nelts, xcmp_t cmp);

int compare(void *lhs, int lsz, void *rhs, int rsz) {
  int *ilhs = (int *)lhs;
  int *irhs = (int *)rhs;
  return (*ilhs - *irhs);
}

void printmem(void *mem, int *sizes, int nelts) {
  int i;
  int *imem = (int *) mem;
  for (i = 0; i < nelts; ++i) {
    printf("%d ", *imem);
    imem += sizes[i] / sizeof(int); 
  }
  printf("\n");
}

int main() {
  int res, n, i, nextsz, totalsz;
  int *sizes;
  int *mem, *pos;

  assert(sizeof(int) == 4);

  res = scanf("%d", &n);
  assert(res == 1);
  assert(n > 0);

  sizes = (int *) calloc(n, sizeof(int));
  assert(sizes != NULL);

  // for tests we are setting sizes to 4, 8 or 12
  // but using only first 4

  totalsz = 0;
  nextsz = 0;
  for (i = 0; i < n; ++i) {
    nextsz = (nextsz + 4) % 8; // 0 -> 4 -> 8
    sizes[i] = nextsz + 4;
    totalsz += sizes[i];
  }

  mem = (int *) calloc(totalsz / sizeof(int), sizeof(int));
  assert(mem != NULL);
  pos = mem;

  for (i = 0; i < n; ++i) {
    int elt;
    res = scanf("%d", &elt);
    assert(res == 1);
    *pos = elt;
    pos += sizes[i] / sizeof(int);
  }

#ifdef VISUALIZE
  // print array before sort
  printmem(mem, sizes, n);
#endif

  xmsort(mem, sizes, n, compare);

  printmem(mem, sizes, n);

  free(mem);
  free(sizes);
}

void xmsort(void *mem, int *sizes, int nelts, xcmp_t cmp){
    int totalsz;
    int * cumulsizes;

    int * from;
    int * to;
    int * tmp;

    int i;
    int step;
    int start1, end1, start2, end2;
    int ind1, ind2;
	int indexto;
    
    cumulsizes = (int*)calloc(nelts, sizeof(int));
    if (cumulsizes == NULL) {
        abort();
    }

    totalsz = 0;
    for (i = 0; i < nelts; ++i) {
        cumulsizes[i] = totalsz;
        totalsz += sizes[i];
    }

    from = (int*)calloc(nelts, sizeof(int));
    if (from==NULL) {
        free(cumulsizes);
        abort();
    }
    for (i = 0; i < nelts; ++i) {
        from[i] = i;
    }

    to = (int*)calloc(nelts, sizeof(int));
    if (to == NULL) {
        free(cumulsizes);
        free(from);
        abort();
    }
   
    for (step = 1; step < nelts; step *= 2) {
		indexto = 0;
		for (i = 0; i < nelts; i += 2 * step) {
			start1 = i; 
            end1 = start1 + step; 
            end1 = (end1 < nelts) ? end1 : nelts;
			start2 = end1;  
            end2 = start2 + step;   
            end2 = (end2 < nelts) ? end2 : nelts;
			while (start1 < end1 && start2 < end2) {
                ind1 = from[start1];
                ind2 = from[start2];
                if (cmp((char*)mem + cumulsizes[ind1], sizes[ind1], (char*)mem + cumulsizes[ind2], sizes[ind2]) < 0){
                    to[indexto++] = ind1;
                    ++start1;
                } else {
                    to[indexto++] = ind2;
                    ++start2;
                }
			}
			while (start1 < end1) to[indexto++] = from[start1++];
			while (start2 < end2) to[indexto++] = from[start2++];
		}
        // swap(from, to)
		tmp = from;
        from = to;
        to = tmp;
	}


	// Copy from mem to tmpmem at right order
    char* tmpmem = (char*)calloc(totalsz, sizeof(char));
    start1 = 0;
    for(i=0; i < nelts; ++i){
        ind1 = from[i];
        memcpy(tmpmem + start1, (char*)mem + cumulsizes[ind1], sizes[ind1]);
        start1 += sizes[ind1];
    }

    memcpy(mem, tmpmem, totalsz);
    free(tmpmem);

    for (i = 0; i < nelts; ++i) {
        to[i] = sizes[from[i]];
    }
    memcpy(sizes, to, nelts*sizeof(int));

    free(to);
    free(from);
	free(cumulsizes);
}