#include <stdio.h>

#define NAUDCENT 4
#define NAUDDOLR 7
#define AUDCENTS (int[NAUDCENT]) {50, 20, 10, 5}
#define AUDDOLRS (int[NAUDDOLR]) {100, 50, 20, 10, 5, 2, 1}

int change_cents_extr(float x)
{
    return (int) (((x - (int) x) * 100) + 0.5);
}

void change_cents_eval(float change, int *denoms, int ndenom)
{
    int n = 0, u = change_cents_extr(change);

    for (int i = 0; i < ndenom; i++)
    {
        n = u / denoms[i], u = u % denoms[i];

        if (n > 0)
        {
            fprintf(stdout, "\tC %3d\t%3d\n", denoms[i], n);
        }
    }
}

int change_dolrs_extr(float x)
{
    return (int) x;
}

void change_dolrs_eval(float change, int *denoms, int ndenom)
{
    int n = 0, u = change_dolrs_extr(change);

    for (int i = 0; i < ndenom; i++)
    {
        n = u / denoms[i], u = u % denoms[i];

        if (n > 0)
        {
            fprintf(stdout, "\t$ %3d\t%3d\n", denoms[i], n);
        }
    }
}

int is_valid_change(float x)
{
    char *ERR01 = "Change may not be negative",
            *ERR02 = "Cents must be a multiple of 5 in range [5,95]";
    int c = change_cents_extr(x), d = change_dolrs_extr(x);

    if (x < 0)
    {
        fprintf(stderr, "ERR-01: Invalid change amount! %s.\n\n", ERR01);
        return 0;
    }
    if (c == 0 && d > 0)
    {
        return 1;
    }
    if (c < 5 || c > 95 || (c % 5) != 0)
    {
        fprintf(stderr, "ERR-02: Invalid change amount! %s.\n\n", ERR02);
        return 0;
    }

    return 1;
}

int main()
{
    float change = 0.f;

    do
    {
        fprintf(stdout, "Change: ");
        if (fscanf(stdin, "%f%*c", &change) != 1)
        {
            return 1;
        }
    }
    while (!is_valid_change(change));

    fprintf(stdout, "\t=============\n");
    fprintf(stdout, "\t DOLRS\tNUM \n");
    fprintf(stdout, "\t=============\n");
    change_dolrs_eval(change, AUDDOLRS, NAUDDOLR);
    fprintf(stdout, "\t-------------\n");

    fprintf(stdout, "\t=============\n");
    fprintf(stdout, "\t CENTS\tNUM \n");
    fprintf(stdout, "\t=============\n");
    change_cents_eval(change, AUDCENTS, NAUDCENT);
    fprintf(stdout, "\t-------------\n");

    return 0;
}