
#include <stdio.h>
#define SIZE 1000

void readInput(int arr[], int *nPtr);
void swap(int *xPtr, int *yPtr);
void printNumbers(const int arr[], int n);

void readInput(int arr[], int *nPtr)
{
    printf("Enter the number of elements: \n");
    scanf("%d", nPtr);

    printf("Enter %d elements: \n", *nPtr);
    
    for (int i = 0; i < *nPtr; i++) {
        scanf("%d", &arr[i]);
    }

}

void swap(int *xPtr, int *yPtr)
{
    int temp = *xPtr;
    *xPtr = *yPtr;
    *yPtr = temp;
}

void printNumbers(const int arr[], int n)
{
    printf("Array elements: ");
    for (size_t i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int arr[SIZE];
    int n;

    readInput(arr, &n);

    printNumbers(arr, n);

    int idx1 = 0;
    int idx2 = 0;

    printf("Enter the first index to be swapped:\n");
    scanf("%d", &idx1);

    printf("Enter the second index to be swapped:\n");
    scanf("%d", &idx2);

    swap(&arr[idx1], &arr[idx2]);

    printNumbers(arr, n);

    return 0;
}