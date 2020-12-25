# Output Settings
set terminal png size 800,300
set output 'rwlock-and-coarse-grained-plot.png'

# Labels, Title and Data
#set key inside bottom right
set xlabel 'Write threads number'
set ylabel 'Time (S)'
set title 'rwlock-and-coarse-grained-plot'
plot "plot/both/data.txt" using 1:2 title 'coarsegrained' with linespoints, \
"plot/both/data.txt" using 1:3 title 'rw lock' with linespoints