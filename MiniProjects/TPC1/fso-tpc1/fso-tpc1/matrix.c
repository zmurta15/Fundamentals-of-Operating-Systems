
#include "matrix.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


matrix* new_mat(unsigned nrows, unsigned ncols) {

	matrix* mat = (matrix*) malloc(sizeof(matrix));
	mat->data = (int**) malloc(sizeof(int*) * nrows);
    mat->ncols = ncols;
    mat->nrows = nrows;

	for (int i = 0; i < nrows; i++) 
		mat->data[i] =  (int*) malloc(sizeof(int) * ncols);

	return mat;
}

void fill_mat(matrix* mat) {

    for (int i = 0; i < mat->nrows; i++)
        for (int j = 0; j < mat->ncols; j++)
            mat->data[i][j] = i * mat->ncols + j;
}


void fill_mat_random(matrix* mat) {

	for (int i = 0; i < mat->nrows; i++) 
		for (int j = 0; j < mat->ncols; j++) 
			mat->data[i][j] = rand() % 10000;
}

void fill_mat_value(matrix* mat, int value) {

    for (int i = 0; i < mat->nrows; i++)
        for (int j = 0; j < mat->ncols; j++)
            mat->data[i][j] = value;
}


matrix* submat(const matrix* mat, const unsigned range[2]) {

    matrix* result = (matrix*) malloc(sizeof(matrix));
    result->data = &mat->data[range[0]];
    result->ncols = mat->ncols;
    result->nrows = range[1] - range[0];

    return result;
}


void print_mat(const matrix* mat) {

    printf ("matrix %ux%u:\n", mat->nrows, mat->ncols);
	for (int i = 0; i < mat->nrows; i++) {
		for (int j = 0; j < mat->ncols; j++) 
			printf("%d ", mat->data[i][j]);
		printf ("\n");
	}
}

matrix* mat_mul(const matrix* mat1, const matrix* mat2) {

	matrix* result = new_mat(mat1->nrows, mat2->ncols);

	for (int i = 0; i < result->nrows; i++) {
        for (int j = 0; j < result->ncols; j++) {
            int sum = 0;
            for (int k = 0; k < mat1->ncols; k++)
                sum = sum + mat1->data[i][k] * mat2->data[k][j];

            result->data[i][j] = sum;
        }
    }

	return result;	
}

void free_mat(matrix* mat) {

    for (int i = 0; i < mat->nrows; i++)
        free(mat->data[i]);
    free(mat);
}



