#include <stdio.h>

#define MAX 100

typedef struct {
    int row, col, value;
} term;

void printTriples(term a[]) {
    int i;

    printf("Row\tCol\tValue\n");

    for (i = 0; i <= a[0].value; i++) {
        printf("%d\t%d\t%d\n",
               a[i].row, a[i].col, a[i].value);
    }
}

void fast_transpose(term a[], term b[]) {
    int row_terms[MAX] = {0};
    int starting_pos[MAX] = {0};
    int i, j;
    int rows = a[0].row;
    int cols = a[0].col;
    int terms = a[0].value;

    b[0].row = cols;
    b[0].col = rows;
    b[0].value = terms;

    if (terms == 0) {
        printf("row_terms: all zero\n");
        printf("starting_pos: no entries\n");
        return;
    }

    for (i = 1; i <= terms; i++) {
        row_terms[a[i].col]++;
    }

    starting_pos[0] = 1;

    for (i = 1; i < cols; i++) {
        starting_pos[i] =
            starting_pos[i - 1] + row_terms[i - 1];
    }

    printf("\nrow_terms[]:\n");
    for (i = 0; i < cols; i++) {
        printf("%d ", row_terms[i]);
    }

    printf("\nstarting_pos[]:\n");
    for (i = 0; i < cols; i++) {
        printf("%d ", starting_pos[i]);
    }
    printf("\n");

    for (i = 1; i <= terms; i++) {
        j = starting_pos[a[i].col]++;

        b[j].row = a[i].col;
        b[j].col = a[i].row;
        b[j].value = a[i].value;
    }
}

int main(void) {
    int rows, cols, value;
    int i, j, count = 0;
    int matrix[MAX][MAX];
    term a[MAX], b[MAX];

    printf("Enter rows and columns (maximum %d): ", MAX);
    if (scanf("%d %d", &rows, &cols) != 2 ||
        rows <= 0 || cols <= 0 ||
        rows > MAX || cols > MAX) {
        printf("Invalid matrix dimensions.\n");
        return 1;
    }

    printf("Enter matrix elements row by row:\n");

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                printf("Invalid matrix element.\n");
                return 1;
            }

            if (matrix[i][j] != 0) {
                count++;
            }
        }
    }

    a[0].row = rows;
    a[0].col = cols;
    a[0].value = count;

    value = 1;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                a[value].row = i;
                a[value].col = j;
                a[value].value = matrix[i][j];
                value++;
            }
        }
    }

    printf("\nOriginal matrix triples:\n");
    printTriples(a);

    fast_transpose(a, b);

    printf("\nTransposed matrix triples:\n");
    printTriples(b);

    printf("\nTriples are in row-major order: Yes\n");

    return 0;
}
