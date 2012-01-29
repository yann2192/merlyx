merlyx: merlyx.c cpuinfo.o
	gcc $^ -o $@

cpuinfo.o: cpuinfo.c cpuinfo.h
	gcc -c cpuinfo.c -o $@

clean:
	rm *.o merlyx
