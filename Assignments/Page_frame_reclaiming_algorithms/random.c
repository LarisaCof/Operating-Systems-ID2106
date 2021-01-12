#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/* 20% of the pages will have 80% of the references (spatial locality) */

#define HIGH 20
#define FREQ 80
#define SAMPLES 20

typedef struct pte {
 int present;
} pte;


void init(int *sequence, int refs, int pages) {

int high = (int)(pages*((float)HIGH/100));

 for(int i = 0; i < refs; i++) {
  if(rand()%100 < FREQ) {
   /* the frequently case */
   sequence[i] = rand() % high;
   } else {
    /* the less frequent case */
    sequence[i] = high + rand()%(pages - high);
  }
 }
}

int main(int argc, char *argv[]) {
  
 /* could be command line arguments */
 int refs = 100000;
 int pages = 100;
 
 /* allocate memory for the page table */
 //pte table[PAGES];
 pte *table = (pte *)malloc(pages*sizeof(pte));
 
 int *sequence = (int*)malloc(refs*sizeof(int));
 
 init(sequence, refs, pages);
 
 
 /* a small experiment to show that it works */
 /*
 for(int i = 1; i < refs; i++) {
  printf(", %d", sequence[i]);
 }*/
 
 printf("# This is a benchmark of random replacement\n");
 printf("# %d page references\n", refs);
 printf("# %d pages \n", pages);
 printf("#\n#\n#frames\tratio\n");
 
 /* frames is the size of the memory in frames */
 int frames;
 
 int incr = pages/SAMPLES;
 
 for(frames = incr; frames <= pages; frames += incr) {
 
 /* clear page tables entries */
 clear_page_table(table, pages);
 
 int hits = simulate(sequence, table, refs, frames, pages);
 
 float ratio = (float)hits/refs;
 
 printf("%d\t%.2f\n", frames, ratio);
 
 } 
 
 printf("\n");
 
 return 0;

}

void clear_page_table(pte *page_table, int pages) {
for(int i = 0; i < pages; i++) {
 page_table[i].present = 0;
 }
}

int simulate(int *seq, pte *table, int refs, int frms, int pgs) {

int hits = 0;
int allocated = 0;

int i;

for(i = 0; i < refs; i++) {
int next = seq[i];
pte *entry = &table[next];

if(entry->present == 1) {
 hits++;
 } else {
  if(allocated < frms) {
   allocated++;
   entry->present = 1; // mark as being in memory
  } else {
   /* nr of allocated pages is equal to the avaliable nr of frames */
   pte *evict; 
   /* need to evict a page, selected by random (not efficient) */
   do {
    int rnd = rand()%pgs;
    evict = &table[rnd];
   } while(evict->present != 1);
   
   evict->present = 0;
   entry->present = 1;
  }
 }
}
return hits;

}
