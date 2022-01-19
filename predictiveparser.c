#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int v, t;
char *V, *T;
char VPmap[30][100][100]; // array of productions of each non terminal
int VPcnt[30] = {0};      // count of productions in each non terminal
char input[100];
char inputLength = 0;
int ip = 0;
int hasEpsilon[30] = {0};

char firstOfV[30][100];
char followOfV[30][100];
int firstVisited[30] = {0}, followVisited[30] = {0};

char ptable[100][100][100]; // 2d array of strings

void removeDup(char *str, int removeEps)
{
    char newStr[100] = "";
    int len = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        int f = 0;
        for (int j = 0; j < len; j++)
        {
            if (newStr[j] == str[i])
                f = 1;
        }
        if (f == 0 && removeEps == 0)
        {
            newStr[len] = str[i];
            len++;
        }
        else if (f == 0 && removeEps == 1 && str[i] != '#')
        {
            newStr[len] = str[i];
            len++;
        }
    }
    newStr[len] = '\0';
    strcpy(str, newStr);
}

char *first(char V)
{
    int index = V - 65;
    if (firstVisited[index] == 0)
    {

        int count = VPcnt[index]; // number of productions of V(current nonterminal)
        if (hasEpsilon[index])
        {
            int len = strlen(firstOfV[index]);
            firstOfV[index][len] = '#';
            firstOfV[index][len + 1] = '\0';
        }

        for (int p = 0; p < count; p++)
        {
            char prod[100];
            strcpy(prod, VPmap[index][p]);

            for (int j = 0; j < strlen(prod); j++)
            {

                if (65 <= prod[j] && prod[j] <= 90) // prod[j] is nonterminal
                {
                    char catFirst[100];
                    strcpy(catFirst, first(prod[j]));

                    int eps = 0;
                    for (int k = 0; k < strlen(catFirst); k++)
                    {
                        if (catFirst[k] == '#')
                        {
                            eps = 1;
                            break;
                        }
                    }

                    if (eps == 0)
                        strcat(firstOfV[index], catFirst);
                    else
                        continue;
                }
                else if (prod[j] == '#')
                    continue;
                else
                {
                    int len = strlen(firstOfV[index]);
                    firstOfV[index][len] = prod[j];
                    firstOfV[index][len + 1] = '\0';
                    break; // production end
                }
            }
        }
    }

    firstVisited[index] = 1;

    removeDup(firstOfV[index], 0);
    return firstOfV[index];
}

int change = 1;
void follow(char V)
{
    int index = V - 65;
    int count = VPcnt[index]; // number of productions of V(current nonterminal)

    for (int p = 0; p < count; p++)
    {
        char prod[100];
        strcpy(prod, VPmap[index][p]);

        for (int j = 0; j < strlen(prod); j++)
        {
            if (65 <= prod[j] && prod[j] <= 90) // prod[j] is nonterminal
            {
                char catFirst[100];
                strcpy(catFirst, followOfV[prod[j] - 65]);

                // if(j+1==strlen(prod))
                //     strcpy(catFirst,followOfV[index]);

                char compStr[100];
                strcpy(compStr, catFirst); // string to compare

                int eps = 0;
                for (int k = j + 1; k < strlen(prod); k++)
                {
                    int found = 0;
                    eps = 0;
                    if (65 <= prod[k] && prod[k] <= 90) // prod[k] is nonterminal
                    {
                        char ftmp[100];
                        strcpy(ftmp, firstOfV[prod[k] - 65]);

                        for (int k = 0; k < strlen(ftmp); k++)
                        {
                            if (ftmp[k] == '#')
                            {
                                eps = 1;
                                break;
                            }
                        }

                        strcat(catFirst, ftmp);
                    }
                    else if (prod[k] == '#')
                        continue;
                    else
                    {
                        int len = strlen(catFirst);
                        catFirst[len] = prod[k];
                        catFirst[len + 1] = '\0';
                        break; // first calculated
                    }
                    if (eps)
                        continue;
                    else
                        break;
                }

                if (strcmp(catFirst, compStr) == 0 || eps == 1)
                {
                    // printf("\n\t%c->%s : Adding follow of %c to %c",V,prod,V,prod[j]);
                    strcat(catFirst, followOfV[index]); // A->BC if C->epsilon then follow of B contains follow of A
                }

                removeDup(catFirst, 1); // 1 to remove #

                // printf("\n\tfollow of %c : %s\n",prod[j],catFirst);

                // printf("\t%c follow : %s\n",prod[j],catFirst);
                strcpy(followOfV[prod[j] - 65], catFirst);

                if (strcmp(catFirst, compStr) != 0)
                    change = 1;
            }
            else
                continue;
        }
    }
}

int findIndexOfT(char c)
{
    for (int i = 0; i < t + 1; i++)
    {
        if (T[i] == c)
            return i;
    }
    return 0;
}

int findIndexOfV(char c)
{
    for (int i = 0; i < v; i++)
    {
        if (V[i] == c)
            return i;
    }
    return 0;
}

void createPtable(char V1, int vIndex)
{
    int index = V1 - 65;
    int count = VPcnt[index];

    for (int i = 0; i < count; i++)
    {
        char prod[100];
        strcpy(prod, VPmap[index][i]);
        char catFirst[100];
        int eps = 0;

        strcpy(catFirst, "");

        // fidning first of prod
        for (int j = 0; j < strlen(prod); j++)
        {
            char ftmp[100];
            strcpy(ftmp, "");

            if (65 <= prod[j] && prod[j] <= 90) // prod[j] is nonterminal
            {
                strcpy(ftmp, firstOfV[prod[j] - 65]);

                for (int k = 0; k < strlen(ftmp); k++)
                {
                    if (ftmp[k] == '#')
                    {
                        eps = 1;
                        break;
                    }
                }

                strcat(catFirst, ftmp);

                if (eps == 0)
                    break;
                else
                    continue;
            }
            else if (prod[j] == '#')
            {
                strcat(catFirst, "#");
                eps = 1;
                continue;
            }
            else
            {
                int len = strlen(catFirst);
                catFirst[len] = prod[j];
                catFirst[len + 1] = '\0';
                break; // production end
            }
        }

        removeDup(catFirst, 0); // 1 to remove epsilon

        for (int j = 0; j < strlen(catFirst); j++)
        {
            int tIndex = findIndexOfT(catFirst[j]);
            strcpy(ptable[vIndex][tIndex], prod);
        }

        if (eps == 1)
        {
            char foll[100];
            strcpy(foll, followOfV[V1 - 65]);

            for (int j = 0; j < strlen(foll); j++)
            {
                int tIndex = findIndexOfT(foll[j]);
                strcpy(ptable[vIndex][tIndex], prod);
            }
        }
    }
}

void parseInput(char w[], char start)
{
    char stack[100];
    int top = -1;
    int ip = 0;
    int error = 0;

    top++;
    stack[top] = '$';
    top++;
    stack[top] = start;

    char x = stack[top];
    printf("Matched\t\tStack\t\tInput\t\tAction");
    printf("\n-----------------------------------------------------------------\n");
    while (x != '$')
    {
        char a = w[ip];

        for (int i = 0; i < ip; i++)
            printf("%c", w[i]);
        printf("\t\t");

        for (int i = 0; i <= top; i++)
            printf("%c", stack[i]);
        printf("\t\t");

        for (int i = ip; i < strlen(w); i++)
            printf("%c", w[i]);
        printf("\t\t");

        if (x == a)
        {
            top--;
            ip++;
            printf("match %c", a);
        }
        else if (x < 65 && x > 90)
        {
            error = 1;
            break;
        }
        else if (strcmp(ptable[findIndexOfV(x)][findIndexOfT(a)], "") == 0)
        {
            error = 1;
            break;
        }
        else
        {
            char prod[100];
            strcpy(prod, ptable[findIndexOfV(x)][findIndexOfT(a)]);
            printf("output %c -> %s", x, prod);
            top--;
            for (int i = strlen(prod) - 1; i >= 0; i--)
            {
                if (prod[i] != '#')
                {
                    top++;
                    stack[top] = prod[i];
                }
            }
        }
        printf("\n");

        x = stack[top];
    }

    if (error == 0)
        printf("\nSuccessfully parsed\n");
    else
        printf("\nParsing Error\n");
}

int main()
{

    printf("Enter the number of non-terminals : ");
    scanf("%d", &v);

    printf("Enter the number of terminals : ");
    scanf("%d", &t);

    V = (char *)malloc(v * sizeof(char));
    T = (char *)malloc(t * sizeof(char));

    printf("Enter the non-terminals : ");
    for (int i = 0; i < v; i++)
        scanf(" %c", &V[i]);

    printf("Enter the terminals : ");
    for (int i = 0; i < t; i++)
        scanf(" %c", &T[i]);
    T[t] = '$';

    int p;
    printf("Enter the number of productions : ");
    scanf(" %d", &p);

    char *leftSide = (char *)malloc(p * sizeof(char));
    char rightSide[p][100];

    printf("Enter the productions (\"#\" for epsilon) : \n");
    printf("\nProduction\tLeft-side\tRight-side\n");
    printf("--------------------------------------------\n");
    for (int i = 0; i < p; i++)
    {
        printf("P%d \t   :\t", i + 1);
        scanf(" %c", &leftSide[i]);
        scanf(" %s", rightSide[i]);

        if (strcmp(rightSide[i], "#") == 0)
            hasEpsilon[leftSide[i] - 65] = 1;

        int cnt = VPcnt[leftSide[i] - 65];
        strcpy(VPmap[leftSide[i] - 65][cnt], rightSide[i]);
        VPcnt[leftSide[i] - 65]++;
    }

    printf("\nProductions : \n");

    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < VPcnt[V[i] - 65]; j++)
        {
            printf("%c -> %s\n", V[i], VPmap[V[i] - 65][j]);
        }
    }
    printf("\n");

    for (int i = 0; i < 30; i++)
    {
        strcpy(followOfV[i], "");
        strcpy(firstOfV[i], "");
    }

    char start;
    printf("Enter the start symbol : ");
    scanf(" %c", &start);

    printf("\n\nFirst : \n");
    for (int i = 0; i < v; i++)
    {
        printf("%c : %s\n", V[i], first(V[i]));
    }

    followOfV[start - 65][0] = '$';
    followOfV[start - 65][1] = '\0';

    while (change)
    {
        change = 0;
        for (int i = 0; i < v; i++)
        {
            follow(V[i]);
        }
    }

    printf("\nFollow :\n");
    for (int i = 0; i < v; i++)
    {
        printf("%c : %s\n", V[i], followOfV[V[i] - 65]);
    }

    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < t + 1; j++)
        {
            strcpy(ptable[i][j], "");
        }
    }

    for (int i = 0; i < v; i++)
    {
        createPtable(V[i], i);
    }

    printf("\nParsing Table:\n");
    for (int i = 0; i < t + 1; i++)
    {
        if (T[i] != '#')
            printf("\t%c", T[i]);
    }
    printf("\n-------------------------------------------------------\n");
    for (int i = 0; i < v; i++)
    {
        printf("%c : ", V[i]);
        for (int j = 0; j < t + 1; j++)
        {
            if (T[j] != '#')
            {
                if (strcmp(ptable[i][j], "") != 0)
                    printf("\t%c->%s", V[i], ptable[i][j]);
                else
                    printf("\t");
            }
        }
        printf("\n");
    }
    char w[100];
    printf("\nEnter the input String :");
    scanf(" %s", w);

    parseInput(w, start);
    return 0;
}