//
// Created by lkapi on 05.03.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cuda_runtime.h>

#define MATRIX_SIZE 8192

__global__ void matrix_multiply(float *matrix1, float *matrix2, float *result, int size)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < size && col < size){
        float sum = 0;
        for(int i=0; i<size; i++){
            sum += matrix1[row*size + i] * matrix2[i*size + col];
        }
        result[row*size + col] = sum;
    }
}

int main() {
    // Set up output file
    FILE *fp;
    fp = fopen("log.txt", "w");

    // Generate random matrices
    srand(time(NULL));
    float *matrix1 = (float *) malloc(MATRIX_SIZE * MATRIX_SIZE * sizeof(float));
    float *matrix2 = (float *) malloc(MATRIX_SIZE * MATRIX_SIZE * sizeof(float));
    float *result = (float *) malloc(MATRIX_SIZE * MATRIX_SIZE * sizeof(float));

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrix1[i * MATRIX_SIZE + j] = (float) rand() / RAND_MAX;
            matrix2[i * MATRIX_SIZE + j] = (float) rand() / RAND_MAX;
            result[i * MATRIX_SIZE + j] = 0;
        }
    }

    // Perform matrix multiplication on GPU
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    float *d_matrix1, *d_matrix2, *d_result;
    cudaMalloc(&d_matrix1, MATRIX_SIZE * MATRIX_SIZE * sizeof(float));
    cudaMalloc(&d_matrix2, MATRIX_SIZE * MATRIX_SIZE * sizeof(float));
    cudaMalloc(&d_result, MATRIX_SIZE * MATRIX_SIZE * sizeof(float));

    cudaMemcpy(d_matrix1, matrix1, MATRIX_SIZE * MATRIX_SIZE * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_matrix2, matrix2, MATRIX_SIZE * MATRIX_SIZE * sizeof(float), cudaMemcpyHostToDevice);

    dim3
    threadsPerBlock(32, 32);
    dim3
    numBlocks(ceil((float) MATRIX_SIZE / threadsPerBlock.x), ceil((float) MATRIX_SIZE / threadsPerBlock.y));

    cudaEventRecord(start);
    matrix_multiply<<<numBlocks, threadsPerBlock>>>(d_matrix1, d_matrix2, d_result, MATRIX_SIZE);
    cudaEventRecord(stop);

    cudaMemcpy(result, d_result, MATRIX_SIZE * MATRIX_SIZE * sizeof(float), cudaMemcpyDeviceToHost);

    cudaEventSynchronize(stop);
    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    // Write results to file
    fprintf(fp, "Matrix multiplication on GPU took %f milliseconds\n", milliseconds);
    fclose(fp);

    // Write results to high result file
    FILE *fp_high;
    fp_high = fopen("result.high", "w");

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            fprintf(fp_high, "%f ", result[i * MATRIX_SIZE + j]);
        }
        fprintf(fp_high, "\n");
    }

    fclose(fp_high);

}