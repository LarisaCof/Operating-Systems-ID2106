/* The list here is not updated with each reference (compare LRU)
   We keep an extra flag in the page table entry that keeps track of if the page has been referenced since it was last cleared.
   If the page we are about to evict has the reference flag set it is placed last in the list so it is given a second chance.
   We will use a single linked circular list. 
   We will not unlink a random entry byt only the first entry in the ring.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/* 20% of the pages will have 80% of the references (spatial locality) */

#define HIGH 20
#define FREQ 80
#define SAMPLES 20

typedef struct pte {
 int id;
 int present;
 int referenced; // extra flag implemented
 struct pte *next;
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

/* our clock handle will point to the last entry in the circular list so the entry which is a candidate for eviction will be one entry ahead. */

int simulate(int *seq, pte *table, int refs, int frms, int pgs) {

int hits = 0;
int allocated = 0;
//pte *first = NULL; // LRU
pte *last = NULL;

for(int i = 0; i < refs; i++) {
 int next = seq[i];
 pte *entry = &table[next];

	if(entry->present == 1) {
 	  entry->referenced = 1; // flag referenced
 	  hits++;
 
 	
 	} else { // MISS
  	  if(allocated < frms) {
   	    allocated++;
   	    entry->present = 1; // flag
   
   	/* place entry last, no unlinking! */
   
   	/* first element (no last) */
   	 if(last == NULL) {
   	  entry->next = entry;
   	} else {
   	   entry->next = last->next;
   	   last->next = entry;
   	}
   	
   	last = entry;
   
  } else {
   /* nr of allocated pages is equal to the avaliable nr of frames */
   pte *cand = last->next; 
   
   while(cand->referenced != 0) {
     cand->referenced = 0;
     last = cand;
     cand = cand->next;
   
   }
   cand->present = 0;
   cand->referenced = 0;
   
   entry->present = 1;
   entry->referenced = 0;
  
   /* place entry last*/
   entry->next = cand->next;
   last->next = entry;
   last = entry;
  
  }
 }
}
return hits;

}

