#include <stdio.h>
#include <stdlib.h>

typedef enum {
    FULL_TIME,
    CONTRACT
} EmployeeType;

typedef struct {
    char name[20];
    int emp_id;
    EmployeeType type;

    union {
        float salary;

        struct {
            float hourly_rate;
            int hours_worked;
        } contract_info;

    } pay;
} Employee;

int main(void) {
    int n, i;
    float total_bill = 0.0f;
    Employee *emp;

    printf("Enter number of employees: ");

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of employees.\n");
        return 1;
    }

    emp = malloc((size_t)n * sizeof(Employee));

    if (emp == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("\nEnter name and employee ID: ");
        scanf("%19s %d", (emp + i)->name,
              &(emp + i)->emp_id);

        printf("Enter type (1 = Full-time, 2 = Contract): ");
        if (scanf("%d", &n) != 1) {
            free(emp);
            return 1;
        }

        if (n == 1) {
            (emp + i)->type = FULL_TIME;

            printf("Enter monthly salary: ");
            scanf("%f", &(emp + i)->pay.salary);
        } else if (n == 2) {
            (emp + i)->type = CONTRACT;

            printf("Enter hourly rate and hours worked: ");
            scanf("%f %d",
                  &(emp + i)->pay.contract_info.hourly_rate,
                  &(emp + i)->pay.contract_info.hours_worked);
        } else {
            printf("Invalid employee type.\n");
            free(emp);
            return 1;
        }
    }

    printf("\n----- EMPLOYEE PAYSLIPS -----\n");

    for (i = 0; i < n; i++) {
        float salary;

        printf("\nName: %s\n", (emp + i)->name);
        printf("Employee ID: %d\n", (emp + i)->emp_id);

        if ((emp + i)->type == FULL_TIME) {
            salary = (emp + i)->pay.salary;
            printf("Employee Type: Full-time\n");
        } else {
            salary =
                (emp + i)->pay.contract_info.hourly_rate *
                (emp + i)->pay.contract_info.hours_worked;

            printf("Employee Type: Contract\n");
        }

        printf("Total Pay: %.2f\n", salary);
        total_bill += salary;
    }

    printf("\nTotal Salary Bill: %.2f\n", total_bill);

    free(emp);
    return 0;
}
