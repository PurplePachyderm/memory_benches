#include <stdio.h>
#include <stdlib.h>
#include<time.h>

// Read/write bench
double rw_bench(size_t N, int nWarmups, int nRepets){
	if(nWarmups < 0) {
		fprintf(stderr,"Error: expected value >= 0 for nWarmups (got %d)\n", nWarmups);
		exit(1);
	}
	if(nRepets <= 0) {
		fprintf(stderr,"Error: expected value > 0 for nRepets (got %d)\n", nRepets);
		exit(1);
	}
	clock_t start, end;

	int array[N];
	int acc;

	// Warmups
	for(int t=0; t<nWarmups; t++) {
		for(size_t i=0; i<N; i++) {
			acc += array[i];
		}
	}

	// Measures
	start = clock();
	for(int t=0; t<nRepets; t++) {
		for (int i = 0; i < N; i++) {
			acc += array[i];
		}
	}
	end = clock();

	return (double) (end - start) / CLOCKS_PER_SEC * 1000.;
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
	double time = rw_bench(N, nWarmups, nRepets);

	// Output results
	printf("*** Read CPU benchmark ***\n");
	printf("N=%ld, nWarmups=%d, nRepets=%d\n\n", N, nWarmups, nRepets);

	printf("Time taken : %lf ms\n", time);

	return time;
}
