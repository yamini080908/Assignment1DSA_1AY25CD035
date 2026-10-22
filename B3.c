#include <stdio.h>

typedef struct {
    int degree;
    float coef[101];
} polynomial;

polynomial readPolynomial(void) {
    polynomial p;
    int i;

    do {
        printf("Enter degree (0 to 100): ");
        scanf("%d", &p.degree);

        if (p.degree < 0 || p.degree > 100) {
            printf("Invalid degree.\n");
        }
    } while (p.degree < 0 || p.degree > 100);

    printf("Enter coefficients from x^%d to x^0:\n",
           p.degree);

    for (i = 0; i <= p.degree; i++) {
        scanf("%f", &p.coef[i]);
    }

    return p;
}

polynomial add(polynomial a, polynomial b) {
    polynomial result;
    int i, exponent;
    int max_degree = a.degree > b.degree
                     ? a.degree : b.degree;

    result.degree = max_degree;

    for (i = 0; i <= max_degree; i++) {
        exponent = max_degree - i;

        float ca = 0.0f;
        float cb = 0.0f;

        if (exponent <= a.degree) {
            ca = a.coef[a.degree - exponent];
        }

        if (exponent <= b.degree) {
            cb = b.coef[b.degree - exponent];
        }

        result.coef[i] = ca + cb;
    }

    while (result.degree > 0 &&
           result.coef[0] == 0.0f) {
        for (i = 0; i < result.degree; i++) {
            result.coef[i] = result.coef[i + 1];
        }
        result.degree--;
    }

    return result;
}

void display(polynomial p) {
    int i, exponent;
    int printed = 0;

    for (i = 0; i <= p.degree; i++) {
        float c = p.coef[i];
        exponent = p.degree - i;

        if (c == 0.0f) {
            continue;
        }

        if (printed) {
            printf(c < 0 ? " - " : " + ");
        } else if (c < 0) {
            printf("-");
        }

        float abs_c = c < 0 ? -c : c;

        if (exponent == 0) {
            printf("%g", abs_c);
        } else {
            if (abs_c != 1.0f) {
                printf("%g", abs_c);
            }

            printf("x");

            if (exponent > 1) {
                printf("^%d", exponent);
            }
        }

        printed = 1;
    }

    if (!printed) {
        printf("0");
    }

    printf("\n");
}

int main(void) {
    polynomial a, b, result;

    printf("Enter first polynomial:\n");
    a = readPolynomial();

    printf("Enter second polynomial:\n");
    b = readPolynomial();

    result = add(a, b);

    printf("First polynomial: ");
    display(a);

    printf("Second polynomial: ");
    display(b);

    printf("Sum: ");
    display(result);

    return 0;
}
