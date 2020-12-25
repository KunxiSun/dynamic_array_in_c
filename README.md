
# Instruction
I implemented **three** versions of dynamic array, they are:
* Dynamic array without lock (src/src/withoutlock/dynamic-array.c)
* Dynamic array with coarse grained lock (src/src/coarse-grained-lock/dynamic-array.c)
* Dynamic array with rw lock (src/src/rwlock/dynamic-array.c)

# HOW TO RUN MY tests
* Run the tests for dynamic array without lock

        make without-lock-test

* Run the tests for dynamic array with coarse grained lock

        make coarse-grained-lock-test

* Run the tests for dynamic array with rw lock

        make rwlock

* Run the benchmark for rwlock and coarse grained lock 
    Note: it is very very slow, because it iterates 5000 times in each thread

        make benchmark

* Generate the gunplot for both benchmark in root path:

        make draw

* To clean complied files, run:

        make clean