set terminal png
set output "tlb.png"

set title "TLB benchmark, 4KiByte pages, 10 Gi operations"

set key right center

set xlabel "number of pages"
set ylabel "time in s"

# use log scale if we use dounling of number of pages
set logscal x 2

plot "tlb4K.dat" u 1:2 w linespoints title "page size 4K bytes", \
     "tlb64.dat" u 1:2 w linespoints title "page size 64 bytes", \
"tlb.dat" u 1:2 w linespoints title "page size 16"
