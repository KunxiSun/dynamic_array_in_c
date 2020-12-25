# Output Settings
set terminal png size 800,300
set output 'coarse-grained-benchmark-plot.png'

# Labels, Title and Data
#set key inside bottom right
set xlabel 'Write threads number'
set ylabel 'Time (S)'
set title 'coarse-grained-benchmark-plot'
plot "plot/coarse-grained-benchmark-plot/data.txt" using 1:2 title '' with linespoints