/* Gaussian elimination without pivoting - Windows version.
 * Compile with "gcc gauss.c -o gauss.exe"
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <math.h>
 #include <time.h>
 #include <windows.h>
 
 /* Program Parameters */
 #define MAXN 2000  /* Max value of N */
 int N;  /* Matrix size */
 
 /* Matrices and vectors */
 volatile float A[MAXN][MAXN], B[MAXN], X[MAXN];
 
 /* Prototype */
 void gauss();  /* The function to perform Gaussian elimination */
 
 /* Returns a seed for srand based on the time */
 unsigned int time_seed() {
     return (unsigned int)time(NULL);
 }
 
 /* Set the program parameters from the command-line arguments */
 void parameters(int argc, char **argv) {
     int seed = 0;
 
     /* Read command-line arguments */
     srand(time_seed());
 
     if (argc == 3) {
         seed = atoi(argv[2]);
         srand(seed);
         printf("Random seed = %i\n", seed);
     }
     if (argc >= 2) {
         N = atoi(argv[1]);
         if (N < 1 || N > MAXN) {
             printf("N = %i is out of range.\n", N);
             exit(0);
         }
     } else {
         printf("Usage: %s <matrix_dimension> [random seed]\n", argv[0]);
         exit(0);
     }
 
     printf("\nMatrix dimension N = %i.\n", N);
 }
 
 /* Initialize A and B (and X to 0.0s) */
 void initialize_inputs() {
     int row, col;
 
     printf("\nInitializing...\n");
     for (col = 0; col < N; col++) {
         for (row = 0; row < N; row++) {
             A[row][col] = (float)rand() / RAND_MAX;
         }
         B[col] = (float)rand() / RAND_MAX;
         X[col] = 0.0;
     }
 }
 
 /* Print input matrices */
 void print_inputs() {
     int row, col;
 
     if (N < 10) {
         printf("\nA =\n\t");
         for (row = 0; row < N; row++) {
             for (col = 0; col < N; col++) {
                 printf("%5.2f%s", A[row][col], (col < N - 1) ? ", " : ";\n\t");
             }
         }
         printf("\nB = [");
         for (col = 0; col < N; col++) {
             printf("%5.2f%s", B[col], (col < N - 1) ? "; " : "]\n");
         }
     }
 }
 
 void print_X() {
     int row;
     if (N < 100) {
         printf("\nX = [");
         for (row = 0; row < N; row++) {
             printf("%5.2f%s", X[row], (row < N - 1) ? "; " : "]\n");
         }
     }
 }
 
 int main(int argc, char **argv) {
     LARGE_INTEGER frequency, start, stop;
     double elapsedTime;
 
     parameters(argc, argv);
     initialize_inputs();
     print_inputs();
 
     printf("\nStarting clock.\n");
     QueryPerformanceFrequency(&frequency);
     QueryPerformanceCounter(&start);
 
     gauss();
 
     QueryPerformanceCounter(&stop);
     printf("Stopped clock.\n");
 
     elapsedTime = (double)(stop.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;
     print_X();
 
     printf("\nElapsed time = %g ms.\n", elapsedTime);
     printf("--------------------------------------------\n");
 
     return 0;
 }
 
 void gauss() {
     int norm, row, col;
     float multiplier;
 
     printf("Computing Serially.\n");
 
     for (norm = 0; norm < N - 1; norm++) {
         for (row = norm + 1; row < N; row++) {
             multiplier = A[row][norm] / A[norm][norm];
             for (col = norm; col < N; col++) {
                 A[row][col] -= A[norm][col] * multiplier;
             }
             B[row] -= B[norm] * multiplier;
         }
     }
 
     for (row = N - 1; row >= 0; row--) {
         X[row] = B[row];
         for (col = N - 1; col > row; col--) {
             X[row] -= A[row][col] * X[col];
         }
         X[row] /= A[row][row];
     }
 }