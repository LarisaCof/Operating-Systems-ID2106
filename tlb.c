#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define PAGES (16) // set maximum nr of pages
#define REFS (1024*1024)

int main (int argc, char *argv[]) {

clock_t c_start, c_stop;

printf("#pages\t proc\t sum\n");

/* in order to facilitate the comparison of numbers, we make the same number of references in each test. We therefore set up a loop in a loop where the inner loop will access the number of pages in the test and the outer loop is adjusted to make the total number of refereences the same */

for (int pages = 1; pages <= PAGES; pages+=1) {

int loops = REFS / pages;

c_start = clock();

long sum = 0;

/* takes more time to run the outer loop 1 M times and inner loop once, than the outer loop 500 K times and inner loop twice. This is expected since there is an overhead in preparing for the inner loop and jumping out of the loop. The more time we spend inside the loop, the less the overhead will make a difference. */

 for(int l = 0; l < loops; l++){
  for (int p = 0; p < pages; p++) {
   /* dummy operation */
   sum++;
  }
 }
 
 c_stop = clock();
 
 {
  double proc;
  proc = ((double)(c_stop - c_start))/CLOCKS_PER_SEC;
  printf("%d\t %.12f\t %ld\n", pages, proc, sum);
 }
}
 return 0;

}

/* Optimization / Looking at the generated assembly */
// gcc -o tlb-reg.s -S tlb.c /*this is the regular version*/
// filled with references using the base stack pointer, -16(%rbp)

// gcc -o tlb-opt.s -S -O tlb.c /* this is the optimized version */
// references to different registers, %ebx, %edx 






