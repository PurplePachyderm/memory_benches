CC=gcc
CFLAGS=-O2

all: cpu_bandwith_rw


cpu_bandwith_rw: src/cpu_bandwidth_rw.c
	$(CC) $(CFLAGS) -o cpu_bandwith_rw src/cpu_bandwidth_rw.c
