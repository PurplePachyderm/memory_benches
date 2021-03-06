#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
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

	int32_t * array = (int32_t*) malloc(N * sizeof(int));
	int32_t * copy = (int32_t*) malloc(N * sizeof(int));

	#pragma omp target enter data map(to:array[0:N], copy[0:N])
	{
	// Warmups
	for(int t=0; t<nWarmups; t++) {
		#pragma omp target teams distribute parallel for simd
		for(size_t i=0; i<N; i++) {
			copy[i] = array[i];
		}
	}

	// Measures
	start = clock();
	for(int t=0; t<nRepets; t++) {
		#pragma omp target teams distribute parallel for simd
		for (size_t i = 0; i<N; i++) {
			copy[i] = array[i];
		}
	}
	end = clock();

	}

	free(array);
	free(copy);

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
	double time = rw_bench(N, nWarmups, nRepets);
	double accessesPerSecond = (double) N / time * 1000.;

	// Output results
	printf("*** Read/write GPU benchmark (internal bandwidth over all SMs) ***\n");
	printf("N=%ld, nWarmups=%d, nRepets=%d\n\n", N, nWarmups, nRepets);

	printf("Time taken        : %lf ms\n", time);
	printf("Accesses per sec. : %lf\n\n", accessesPerSecond);

	FILE * fp = fopen("tmp.txt", "w");
	fprintf(fp, "%lf\n", accessesPerSecond);
	fclose(fp);

	return accessesPerSecond;
}
