#! /usr/bin/gnuplot
#
# purpose:
#        generate data reduction graphs for the multi-threaded list project
#
# input: lab2_list.csv
#       1. test name
#       2. # threads
#       3. # iterations per thread
#       4. # lists
#       5. # operations performed (threads x iterations x (ins + lookup + delete))
#       6. run time (ns)
#       7. run time per operation (ns)
#
# output:
#       lab2_list-1.png ... cost per operation vs threads and iterations
#       lab2_list-2.png ... threads and iterations that run (un-protected) w/o failure
#       lab2_list-3.png ... threads and iterations that run (protected) w/o failure
#       lab2_list-4.png ... cost per operation vs number of threads
#
# Note:
#       Managing data is simplified by keeping all of the results in a single
#       file.  But this means that the individual graphing commands have to
#       grep to select only the data they want.
#
#       Early in your implementation, you will not have data for all of the
#       tests, and the later sections may generate errors for missing data.
#


# general plot parameters
set terminal png
set datafile separator ","

# how many threads/iterations we can run without failure (w/o yielding)
set title "List-1: Spin locks vs Mutexes Throughput by Thread Count"
set xlabel "Threads"
set logscale x 2
set xrange [0.75:30]
set ylabel "Cost per Operation (ns)"
unset yrange
set logscale y 10
set output 'lab2b_1.png'

plot \
     "< grep -e 'list-none-m,[0-9]*,1000,1,' lab2b_list.csv" using ($2):(1000000000/($7)) \
        title 'list w/mutex' with linespoints lc rgb 'blue', \
     "< grep -e 'list-none-s,[0-9]*,1000,1,' lab2b_list.csv" using ($2):(1000000000/($7)) \
        title 'list w/spin-lock' with linespoints lc rgb 'green'

# how many threads/iterations we can run without failure (w/o yielding)
set title "List-2: Mutex Wait Time for Locking"
set xlabel "Threads"
set logscale x 2
set xrange [0.75:30]
set ylabel "Time (ns)"
set logscale y 10
unset yrange
set output 'lab2b_2.png'

plot \
     "< grep -e 'list-none-m,[0-9]*,1000,1,' lab2b_list.csv" using ($2):($8) \
        title 'Average wait-for-lock' with linespoints lc rgb 'blue', \
     "< grep -e 'list-none-m,[0-9]*,1000,1,' lab2b_list.csv" using ($2):($7) \
        title 'Average time per operation' with linespoints lc rgb 'red'


set title "List-3: Threads vs Iterations that run without failure"
set xlabel "Threads"
set logscale x 2
set xrange [0.75:]
set ylabel "Successful Iterations"
set logscale y 10
set output 'lab2b_3.png'
# note that unsuccessful runs should have produced no output
plot \
     "< grep 'list-id-none,[0-9]*,[0-9]*,4,' lab2b_list.csv" using ($2):($3) \
        title 'Unprotected' with points lc rgb 'green', \
     "< grep 'list-id-m,[0-9]*,[0-9]*,4,' lab2b_list.csv" using ($2):($3) \
        title 'Mutex Locks' with points lc rgb 'red', \
     "< grep 'list-id-s,[0-9]*,[0-9]*,4,' lab2b_list.csv" using ($2):($3) \
        title 'Spin Locks' with points lc rgb 'blue'


set title "List-4: Mutex Throughput vs Threads with List #s"
set xlabel "Threads"
set logscale x 2
set xrange [0.75:15]
set ylabel "Cost per Operation (ns)"
set logscale y 10
set output 'lab2b_4.png'

plot \
     "< grep -e 'list-none-m,[0-9]*,1000,1,' lab2b_list.csv" using ($2):(1000000000/($7)) \
        title '1 list' with linespoints lc rgb 'blue', \
     "< grep -e 'list-none-m,[0-9]*,1000,4,' lab2b_list.csv" using ($2):(1000000000/($7)) \
        title '4 list' with linespoints lc rgb 'violet', \
     "< grep -e 'list-none-m,[0-9]*,1000,8,' lab2b_list.csv" using ($2):(1000000000/($7)) \
        title '8 list' with linespoints lc rgb 'green', \
     "< grep -e 'list-none-m,[0-9]*,1000,16,' lab2b_list.csv" using ($2):(1000000000/($7)) \
        title '16 list' with linespoints lc rgb 'red'

set title "List-5: Spinlock Throughput vs Threads with List #s"
set xlabel "Threads"
set logscale x 2
set xrange [0.75:15]
set ylabel "Cost per Operation (ns)"
set logscale y 10
set output 'lab2b_5.png'

plot \
     "< grep -e 'list-none-s,[0-9]*,1000,1,' lab2b_list.csv" using ($2):(1000000000/($7)) \
        title '1 list' with linespoints lc rgb 'blue', \
     "< grep -e 'list-none-s,[0-9]*,1000,4,' lab2b_list.csv" using ($2):(1000000000/($7)) \
        title '4 list' with linespoints lc rgb 'violet', \
     "< grep -e 'list-none-s,[0-9]*,1000,8,' lab2b_list.csv" using ($2):(1000000000/($7)) \
        title '8 list' with linespoints lc rgb 'green', \
     "< grep -e 'list-none-s,[0-9]*,1000,16,' lab2b_list.csv" using ($2):(1000000000/($7)) \
        title '16 list' with linespoints lc rgb 'red'




	



