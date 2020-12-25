SHELL := /bin/bash
CC=gcc
CFLAGS= -O0 -g #-fsanitize=address 

.PHONY: clean

without-lock-test:	./src/test/withoutlock/normal-unit-tests.c
	$(CC) $(CFLAGS) $^ -o $@ -lpthread -lcmocka
	./$@
	rm -f ./$@

coarse-grained-lock-test: ./src/test/coarse-grained-lock/coarse-grained-thread-test.c
	$(CC) $(CFLAGS) $^ -o $@ -lpthread -lcmocka
	./$@
	rm -f ./$@

rwlock: ./src/test/rwlock/rwlock-thread-test.c
	$(CC) $(CFLAGS) $^ -o $@ -lpthread -lcmocka
	./$@
	rm -f ./$@

benchmark: 
	echo "Runing rwlock.."
	gcc ./src/test/rwlock-benchmark/10%wrire90%read.c -o 10%wrire90%read -lpthread -g -fsanitize=address
	gcc ./src/test/rwlock-benchmark/40%write60%read.c -o 40%write60%read -lpthread -g -fsanitize=address
	gcc ./src/test/rwlock-benchmark/50%write50%read.c -o 50%write50%read -lpthread -g -fsanitize=address
	gcc ./src/test/rwlock-benchmark/60%write40%read.c -o 60%write40%read -lpthread -g -fsanitize=address
	gcc ./src/test/rwlock-benchmark/90%write10%read.c -o 90%write10%read -lpthread -g -fsanitize=address

	
	time ./10%wrire90%read
	time ./40%write60%read
	time ./50%write50%read
	time ./60%write40%read
	time ./90%write10%read
	
	rm -f ./10%wrire90%read
	rm -f ./10%wrire90%read
	rm -f ./40%write60%read
	rm -f ./50%write50%read
	rm -f ./60%write40%read
	rm -f ./90%write10%read

	gcc ./src/test/coarse-grained-lock-benchmark/10%wrire90%read.c -o 10%wrire90%read -lpthread -g -fsanitize=address
	gcc ./src/test/coarse-grained-lock-benchmark/40%write60%read.c -o 40%write60%read -lpthread -g -fsanitize=address
	gcc ./src/test/coarse-grained-lock-benchmark/50%write50%read.c -o 50%write50%read -lpthread -g -fsanitize=address
	gcc ./src/test/coarse-grained-lock-benchmark/60%write40%read.c -o 60%write40%read -lpthread -g -fsanitize=address
	gcc ./src/test/coarse-grained-lock-benchmark/90%write10%read.c -o 90%write10%read -lpthread -g -fsanitize=address

	
	time ./10%wrire90%read
	time ./40%write60%read
	time ./50%write50%read
	time ./60%write40%read
	time ./90%write10%read
	
	rm -f ./10%wrire90%read
	rm -f ./10%wrire90%read
	rm -f ./40%write60%read
	rm -f ./50%write50%read
	rm -f ./60%write40%read
	rm -f ./90%write10%read

draw:
	gnuplot plot/rwlock-benchmark-plot/plot-setting.p
	gnuplot plot/coarse-grained-benchmark-plot/plot-setting.p
	gnuplot plot/both/plot-setting.p


clean:
	rm -f ./without-lock-test
	rm -f ./coarse-grained-lock-test
	rm -f ./rwlock
	rm -f ./10%wrire90%read
	rm -f ./10%wrire90%read
	rm -f ./40%write60%read
	rm -f ./50%write50%read
	rm -f ./60%write40%read
	rm -f ./90%write10%read