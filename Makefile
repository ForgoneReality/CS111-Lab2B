#NAME: Cao Xu
#EMAIL: cxcharlie@gmail.com
#ID: 704551688

default:
	gcc -g -Wall -Wextra -pthread SortedList.c lab2_list.c -o lab2_list

tests: default lab2b_list.csv

lab2b_list.csv:
	./lab2_list --iterations=1000 --sync=m --threads=1 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=m --threads=2 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=m --threads=4 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=m --threads=8 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=m --threads=12 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=m --threads=16 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=m --threads=24 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=s --threads=1 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=s --threads=2 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=s --threads=4 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=s --threads=8 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=s --threads=12 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=s --threads=16 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=s --threads=24 >> lab2b_list.csv
#PNG 3
	./lab2_list --yield=id --lists=4 --threads=1 --iterations=1 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --threads=1 --iterations=2 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --threads=1 --iterations=4 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --threads=1 --iterations=8 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --threads=1 --iterations=16 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=4 --iterations=1 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=4 --iterations=2 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=4 --iterations=4 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=4 --iterations=8 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=4 --iterations=16 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=8 --iterations=1 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=8 --iterations=2 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=8 --iterations=4 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=8 --iterations=8 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=8 --iterations=16 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=12 --iterations=1 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=12 --iterations=2 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=12 --iterations=4 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=12 --iterations=8 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=12 --iterations=16 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=16 --iterations=1 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=16 --iterations=2 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=16 --iterations=4 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=16 --iterations=8 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=16 --iterations=16 >> lab2b_list.csv

	./lab2_list --yield=id --lists=4 --sync=s --threads=1 --iterations=10 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=s --threads=1 --iterations=20 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=s --threads=1 --iterations=40 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=s --threads=1 --iterations=80 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=s --threads=4 --iterations=10 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=s --threads=4 --iterations=20 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=s --threads=4 --iterations=40 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=s --threads=4 --iterations=80 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=s --threads=8 --iterations=10 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=s --threads=8 --iterations=20 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=s --threads=8 --iterations=40 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=s --threads=8 --iterations=80 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=s --threads=12 --iterations=10 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=s --threads=12 --iterations=20 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=s --threads=12 --iterations=40 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=s --threads=12 --iterations=80 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=s --threads=16 --iterations=10 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=s --threads=16 --iterations=20 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=s --threads=16 --iterations=40 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=s --threads=16 --iterations=80 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=m --threads=1 --iterations=10 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=m --threads=1 --iterations=20 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=m --threads=1 --iterations=40 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=m --threads=1 --iterations=80 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=m --threads=4 --iterations=10 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=m --threads=4 --iterations=20 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=m --threads=4 --iterations=40 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=m --threads=4 --iterations=80 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=m --threads=8 --iterations=10 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=m --threads=8 --iterations=20 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=m --threads=8 --iterations=40 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=m --threads=8 --iterations=80 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=m --threads=12 --iterations=10 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=m --threads=12 --iterations=20 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=m --threads=12 --iterations=40 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=m --threads=12 --iterations=80 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=m --threads=16 --iterations=10 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=m --threads=16 --iterations=20 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=m --threads=16 --iterations=40 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --sync=m --threads=16 --iterations=80 >> lab2b_list.csv

#png 4/5
	./lab2_list --iterations=1000 --sync=m --lists=4 --threads=1 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=m --lists=4 --threads=2 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=m --lists=4 --threads=4 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=m --lists=4 --threads=8 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=m --lists=4 --threads=12 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=m --lists=8 --threads=1 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=m --lists=8 --threads=2 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=m --lists=8 --threads=4 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=m --lists=8 --threads=8 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=m --lists=8 --threads=12 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=m --lists=16 --threads=1 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=m --lists=16 --threads=2 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=m --lists=16 --threads=4 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=m --lists=16 --threads=8 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=m --lists=16 --threads=12 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=s --lists=4 --threads=1 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=s --lists=4 --threads=2 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=s --lists=4 --threads=4 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=s --lists=4 --threads=8 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=s --lists=4 --threads=12 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=s --lists=8 --threads=1 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=s --lists=8 --threads=2 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=s --lists=8 --threads=4 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=s --lists=8 --threads=8 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=s --lists=8 --threads=12 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=s --lists=16 --threads=1 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=s --lists=16 --threads=2 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=s --lists=16 --threads=4 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=s --lists=16 --threads=8 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=s --lists=16 --threads=12 >> lab2b_list.csv



profile:
	LD_PRELOAD=/usr/lib64/libprofiler.so CPUPROFILE=./raw.gperf ./lab2_list --threads=12 --iterations=1000 --sync=s
	pprof ./lab2_list ./raw.gperf > profile.out
	pprof --list=thread_worker ./lab2_list ./raw.gperf >> profile.out
	rm -f ./raw.gperf

graphs: tests
	gnuplot lab2b.gp
dist: graphs profile 
	tar -czvf lab2b-704551688.tar.gz SortedList.c SortedList.h lab2_list.c profile.out lab2b_list.csv lab2b_1.png lab2b_2.png lab2b_3.png lab2b_4.png lab2b_5.png README lab2b.gp Makefile

clean:
	rm -f lab2b-704551688.tar.gz lab2_list
