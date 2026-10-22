#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int roll_no;
    char name[20];
    float marks;
} Student;

int main(void) {
    Student *ptr;
    Student *temp;
    Student *topper;
    int n, i, add;
    float total = 0.0f;
    char choice;

    printf("Enter number of students: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of students.\n");
        return 1;
    }

    /* Dynamically allocate memory */
    ptr = malloc(n * sizeof(Student));

    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    /* Read student records */
    for (i = 0; i < n; i++) {
        printf("Enter roll, name, marks: ");
        if (scanf("%d %19s %f",
                  &(ptr + i)->roll_no,
                  (ptr + i)->name,
                  &(ptr + i)->marks) != 3) {
            printf("Invalid input.\n");
            free(ptr);
            return 1;
        }
    }

    /* Calculate average and find topper */
    topper = ptr;
    total = 0.0f;

    for (i = 0; i < n; i++) {
        total += (ptr + i)->marks;

        if ((ptr + i)->marks > topper->marks) {
            topper = ptr + i;
        }
    }

    printf("\nAverage marks: %.2f\n", total / n);
    printf("Topper: %s (Roll %d, Marks %.2f)\n",
           topper->name, topper->roll_no, topper->marks);

    /* Ask whether to add two more students */
    printf("\nAdd 2 more students? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        add = 2;

        /* Use a temporary pointer for realloc */
        temp = realloc(ptr, (n + add) * sizeof(Student));

        if (temp == NULL) {
            printf("Memory reallocation failed.\n");
            free(ptr);
            return 1;
        }

        ptr = temp;

        /* Read the two additional records */
        for (i = n; i < n + add; i++) {
            printf("Enter roll, name, marks: ");
            if (scanf("%d %19s %f",
                      &(ptr + i)->roll_no,
                      (ptr + i)->name,
                      &(ptr + i)->marks) != 3) {
                printf("Invalid input.\n");
                free(ptr);
                return 1;
            }
        }

        n += add;
        total = 0.0f;
        topper = ptr;

        /* Recalculate using all student records */
        for (i = 0; i < n; i++) {
            total += (ptr + i)->marks;

            if ((ptr + i)->marks > topper->marks) {
                topper = ptr + i;
            }
        }

        printf("Updated average marks: %.2f\n", total / n);
        printf("Topper: %s (Roll %d, Marks %.2f)\n",
               topper->name, topper->roll_no, topper->marks);
    }

    /* Release allocated memory */
    free(ptr);
    ptr = NULL;

    return 0;
}
