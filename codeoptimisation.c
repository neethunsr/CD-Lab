#include <stdio.h>
#include <string.h>

#define MAX_STRLEN 20
#define MAX_LINES 20

typedef struct
{
    char l, r[MAX_STRLEN];
} line;

void main()
{
    int n;
    line op[MAX_LINES], pr[MAX_LINES];
    printf("Number of lines: ");
    scanf("%d", &n);
    printf("Enter the lines.\n");
    for (int i = 0; i < n; i++)
        scanf(" %c %s", &op[i].l, op[i].r);
    printf("\n");

    printf("Intermediate Code\n");
    for (int i = 0; i < n; i++)
        printf("%c=%s\n", op[i].l, op[i].r);
    printf("\n");

    int z = 0;
    for (int i = 0; i < n - 1; i++)
    {
        char temp = op[i].l;
        for (int j = 0; j < n; j++)
        {
            char *pos = strchr(op[j].r, temp);
            if (pos != NULL)
            {
                pr[z].l = op[i].l;
                strcpy(pr[z].r, op[i].r);
                z++;
            }
        }
    }
    pr[z].l = op[n - 1].l;
    strcpy(pr[z].r, op[n - 1].r);
    z++;
    printf("After Dead Code Elimination.\n");
    for (int k = 0; k < z; k++)
        printf("%ct=%s\n", pr[k].l, pr[k].r);
    printf("\n");

    for (int m = 0; m < z; m++)
    {
        char *temp = pr[m].r;
        for (int j = m + 1; j < z; j++)
        {
            char *pos = strstr(temp, pr[j].r);
            if (pos != NULL)
            {
                char t = pr[j].l;
                pr[j].l = pr[m].l;
                for (int i = 0; i < z; i++)
                {
                    char *l = strchr(pr[i].r, t);
                    if (l != NULL)
                        pr[i].r[l - pr[i].r] = pr[m].l;
                }
            }
        }
    }
    printf("Eliminate Common Expression\n");
    for (int i = 0; i < z; i++)
        printf("%c=%s\n", pr[i].l, pr[i].r);
    printf("\n");

    for (int i = 0; i < z; i++)
    {
        for (int j = i + 1; j < z; j++)
        {
            int q = strcmp(pr[i].r, pr[j].r);
            if ((pr[i].l == pr[j].l) && !q)
            {
                pr[i].l = '\0';
                strcpy(pr[i].r, "\0");
            }
        }
    }
    printf("Optimized Code\n");
    for (int i = 0; i < z; i++)
        if (pr[i].l)
            printf("%c=%s\n", pr[i].l, pr[i].r);
}