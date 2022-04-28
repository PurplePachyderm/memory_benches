CC=gcc
CFLAGS=-O0

cpu: cpu_bandwidth_rw cpu_bandwidth_r cpu_bandwidth_w cpu_latency

gpu: gpu_bandwidth_rw gpu_latency gpu_bandwidth_transfers gpu_latency_internal


# CPU
cpu_bandwidth_rw: src/cpu_bandwidth_rw.c
	$(CC) $(CFLAGS) -o cpu_bandwidth_rw src/cpu_bandwidth_rw.c

cpu_bandwidth_r: src/cpu_bandwidth_r.c
	$(CC) $(CFLAGS) -o cpu_bandwidth_r src/cpu_bandwidth_r.c

cpu_bandwidth_w: src/cpu_bandwidth_w.c
	$(CC) $(CFLAGS) -o cpu_bandwidth_w src/cpu_bandwidth_w.c

cpu_latency: src/cpu_latency.c
	$(CC) $(CFLAGS) -o cpu_latency src/cpu_latency.c


# GPU
gpu_bandwidth_rw: src/gpu_bandwidth_rw.c
	$(CC) $(CFLAGS) -o gpu_bandwidth_rw src/gpu_bandwidth_rw.c

gpu_latency: src/gpu_latency.c
	$(CC) $(CFLAGS) -o gpu_latency src/gpu_latency.c

gpu_bandwidth_transfers: src/gpu_bandwidth_transfers.c
	$(CC) $(CFLAGS) -o gpu_bandwidth_transfers src/gpu_bandwidth_transfers.c

gpu_latency_internal: src/gpu_latency_internal.c
	$(CC) $(CFLAGS) -o gpu_latency_internal src/gpu_latency_internal.c

# Phony
clean:
	rm cpu_bandwidth_rw cpu_bandwidth_r cpu_bandwidth_w cpu_latency gpu_bandwidth_rw gpu_latency gpu_bandwidth_transfers gpu_latency_internal
