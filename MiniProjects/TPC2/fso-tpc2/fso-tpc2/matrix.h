#ifndef MATRIX_H
#define MATRIX_H


struct mat {
    int** data; // the values in the matrix
    unsigned nrows; // the number of columns
    unsigned ncols; // the number of rows
};

typedef struct mat matrix;

/**
 * A matrix with size nrows x ncols
 */
matrix* new_mat(unsigned nrows, unsigned ncols);

/**
 * Free matrix
 */
void free_mat(matrix* mat);

/**
 * Fill matrix with values from 0 to size-1
 */
void fill_mat(matrix* mat);

/**
 * Fill matrix with random values
 */
void fill_mat_random(matrix* mat);

/**
 * Fill all positions of the matrix with a given value
 */
void fill_mat_value(matrix* mat, int value);


/**
 * Obtain a submatrix of matrix 'mat' from row range[0] to row range[1].
 * For instance, for a matrix 'mat' od size 10x8, a submatrix for range {3, 6}
 * returns a matrix of size 3x8 with rows 3, 4 and 5 of the original matrix
 */
matrix* submat(const matrix* mat, const unsigned range[2]);

/**
 * Prints the matrix to the stndard output
 */
void print_mat(const matrix* mat);

/**
 * Returns a matrix that is the multiplication of mat1 per mat2
 */
matrix* mat_mul(const matrix* mat1, const matrix* mat2);


#endif // MATRIX_H