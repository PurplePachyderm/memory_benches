CC=gcc
CFLAGS=-O2

all: cpu_bandwith_rw cpu_bandwith_r cpu_bandwith_w cpu_latency


cpu_bandwith_rw: src/cpu_bandwidth_rw.c
	$(CC) $(CFLAGS) -o cpu_bandwith_rw src/cpu_bandwidth_rw.c

cpu_bandwith_r: src/cpu_bandwidth_r.c
	$(CC) $(CFLAGS) -o cpu_bandwith_r src/cpu_bandwidth_r.c

cpu_bandwith_w: src/cpu_bandwidth_w.c
	$(CC) $(CFLAGS) -o cpu_bandwith_w src/cpu_bandwidth_w.c

cpu_latency: src/cpu_latency.c
	$(CC) $(CFLAGS) -o cpu_latency src/cpu_latency.c
