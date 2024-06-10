#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;          // book id
    char name[20];   // book name
    char author[20]; // author of book
    int quantity;    // quantity of book
    int rackno;      // rack no of the book
} bookData;

void showRecords();
int updateRecord(int id, int diff);
int deleteRecord(int id);

int main()
{
    int id;
    int diff;

    printf("\nBooks:\n");
    showRecords();

    printf("\nEnter id of the book to be updated:\n");
    scanf("%d", &id);
    printf("\nHow many books will be added(+) or removed(-):\n");
    scanf("%d", &diff);

    if (updateRecord(id, diff) == 0)
        printf("There is no book with id %d\n", id);

    printf("\nBooks:\n");
    showRecords();

    printf("\nEnter id of the book to be deleted:\n");
    scanf("%d", &id);

    if (deleteRecord(id) == 0)
        printf("There is no book with id %d\n", id);

    printf("\nBooks:\n");
    showRecords();

    return 0;
}

void printBook(bookData record)
{
    printf("id: %d\n", record.id);
    printf("name: %s\n", record.name);
    printf("author: %s\n", record.author);
    printf("quantity: %d\n", record.quantity);
    printf("rackno: %d\n", record.rackno);
}

// It shows and lists all records in the binary file.
void showRecords()
{
    // open the file with “rb”
    FILE *file = fopen("library.bin", "rb");

    if (file == NULL)
        printf("No file error");

    while (!feof(file))
    {
        bookData record;
        fread(&record, sizeof(bookData), 1, file);
        if (record.id != 0)
            printBook(record);
    }

    fclose(file);
}

// adding the number diff to the quantity of the book  If there is a book record
// with the given id, the new quantity of the book is written to library.bin
// and the function returns 1; otherwise, it returns 0.
int updateRecord(int id, int diff)
{
    // open the file with “rb+”
    FILE *file = fopen("library.bin", "rb+");

    if (file == NULL)
        printf("No file error");

    while (!feof(file))
    {
        bookData record;
        fread(&record, sizeof(bookData), 1, file);
        if (record.id == id) {
            record.quantity += diff;
            fseek(file, -sizeof(bookData), SEEK_CUR);
            fwrite(&record, sizeof(bookData), 1, file);
            fclose(file);
            return  1;
        }
    }
    
    fclose(file);
    return 0;
}

// removes the book with the given id from binary file (library.bin) by setting
// its fields to {0, "", "", 0, 0}. If the given id is found in the binary file, the book record will be removed from the
// binary file and the function returns 1; otherwise, it returns 0.
int deleteRecord(int id)
{
    // open the file with “rb+”
    FILE *file = fopen("library.bin", "rb+");

    if (file == NULL)
        printf("No file error");

    while (!feof(file))
    {
        bookData record;
        fread(&record, sizeof(bookData), 1, file);
        if (record.id == id) {
            record.id = 0;
            record.name[0] = '\0';
            record.author[0] = '\0';
            record.rackno = 0;
            record.quantity = 0;
            fseek(file, -sizeof(bookData), SEEK_CUR);
            fwrite(&record, sizeof(bookData), 1, file);
            fclose(file);
            return  1;
        }
    }
    
    fclose(file);
    return 0;
}
