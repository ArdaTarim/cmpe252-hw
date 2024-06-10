#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_SKATERS 20

typedef struct
{
    char name[20];
    char surname[20];
    double scores[6];
    double average;

} skater_t;

double calculateAverageScore(const skater_t *skaterp);
int scanSkater(FILE *filep, skater_t *skaterp);
int loadSkaters(skater_t skaters[]);
void printSkater(const skater_t *skaterp);
int findPrintWinner(skater_t skaters[], int numOfSkaters);

int main(void)
{
    skater_t skaters[MAX_SKATERS];

    int numOfSkaters;

    numOfSkaters = loadSkaters(skaters);

    printf("Skaters:\n");
    for (int i = 0; i < numOfSkaters; i++)
        printSkater(&skaters[i]);

    findPrintWinner(skaters, numOfSkaters);

    return 0;
}

double calculateAverageScore(const skater_t *skaterp)
{
    double sum = 0;
    int max = 0;
    int min = 10;
    for (int i = 0; i < 6; i++)
    {
        sum += skaterp->scores[i];
        if (skaterp->scores[i] > max)
        {
            max = skaterp->scores[i];
        }
        if (skaterp->scores[i] < min)
        {
            min = skaterp->scores[i];
        }
    }
    sum = sum - min - max;
    sum = sum / 4.0;
}

int scanSkater(FILE *infile, skater_t *skaterp)
{
    if (fscanf(infile, "%s %s %lf %lf %lf %lf %lf %lf",
        skaterp->name, 
        skaterp->surname,
        skaterp->scores,
        skaterp->scores+1,
        skaterp->scores+2, 
        skaterp->scores+3,
        skaterp->scores+4,
        skaterp->scores+5) == 8)
    {
        skaterp->average = calculateAverageScore(skaterp);
        return 1;
    }

    return 0;
}

int loadSkaters(skater_t skaters[])
{
    char fileName[30];
    printf("Enter the file name to read:\n");
    scanf("%s", fileName);

    printf("Opening %s\n", fileName);
    FILE *file = fopen(fileName, "r");

    printf("Loading complete\n");

    int n = 0;
    while (n < 6 && scanSkater(file, &skaters[n])) {
        n++;
    }
    printf("Closing %s\n", fileName);
    fclose(file);
    return n;
}

void printSkater(const skater_t *skaterp)
{
    printf("%s %s %.2lf\n", skaterp->name, skaterp->surname, skaterp->average);
}

int findPrintWinner(skater_t skaters[], int numOfSkaters)
{
    int maxIdx = 0;
    for (int i = 0; i < numOfSkaters; i++)
    {
        if (skaters[i].average > skaters[maxIdx].average)
            maxIdx = i;
    }

    printf("Winner:\n%s %s %.2lf\n", skaters[maxIdx].name, skaters[maxIdx].surname, skaters[maxIdx].average);
}
