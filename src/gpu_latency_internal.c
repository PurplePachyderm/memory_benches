#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include<time.h>

// Read/write bench
double latency_bench(size_t N, int nWarmups, int nRepets){
	if(nWarmups < 0) {
		fprintf(stderr,"Error: expected value >= 0 for nWarmups (got %d)\n", nWarmups);
		exit(1);
	}
	if(nRepets <= 0) {
		fprintf(stderr,"Error: expected value > 0 for nRepets (got %d)\n", nRepets);
		exit(1);
	}
	clock_t start, end;

	int32_t * p = (int32_t*) malloc(N * sizeof(int));
	int32_t * q = (int32_t*) malloc(N * sizeof(int));

	// Generate permutations :
	// Initialize p
	for(size_t i=0; i<N; i++) {
		p[i] = i;
	}
	//Shuffle p
	for (int i=0; i<N-1; i++) {
		size_t j = i + rand() / (RAND_MAX / (N - i) + 1);
		int32_t t = p[j];
		p[j] = p[i];
		p[i] = t;
	}
	// Ensure permutation contains a single cycle
	int kinit = p[N - 1];
	for (size_t i = 0; i < N; i++) {
		kinit = q[kinit] = p[i];
	}

	int32_t * k = (int32_t*) malloc(sizeof(int32_t));
	*k = kinit;

	#pragma omp target enter data map(to:q[0:N], k[0:1])
	{
	// Warmups
	for(int t=0; t<nWarmups; t++) {
		for(size_t i=0; i<N; i++) {
			k = &(q[*k]);
		}
	}

	// Measures
	// (access all arrays elements w/ pointer chasing)
	start = clock();
	for(int t=0; t<nRepets; t++) {
		for(size_t i=0; i<N; i++) {
			k = &(q[*k]);
		}
	}
	end = clock();

	}

	free(p);
	free(q);

	return (double) (end - start) / CLOCKS_PER_SEC * 1000. / nRepets;
};



int main(int argc, char *argv[]) {
	// Args management
	if(argc != 4) {
		fprintf(stderr,"Error: expected exactly 3 arguments (see usage_below)\n./cpu_bandwith_rw [N] [nWarmups] [nRepets]\n");
		exit(1);
	}
	size_t N = atol(argv[1]);
	int nWarmups = atol(argv[2]);
	int nRepets = atol(argv[3]);

	// Run test
	double time = latency_bench(N, nWarmups, nRepets);
	double latency = (double) time / N * 1000000.;

	// Output results
	printf("*** Latency GPU benchmark (internal) ***\n");
	printf("N=%ld, nWarmups=%d, nRepets=%d\n\n", N, nWarmups, nRepets);

	printf("Time taken        : %lf ms\n", time);
	printf("Latency           : %lf ns\n\n", latency);

	FILE * fp = fopen("tmp.txt", "w");
	fprintf(fp, "%lf\n", latency);
	fclose(fp);

	return latency;
}
