
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STR_LEN 20
#define MAX_ELEM 10
#define HASHSIZE 1000


unsigned int hash_text (char * list) ;
void strong_similar (int hval[MAX_ELEM], int map[MAX_ELEM][MAX_ELEM]) ;
void weak_similar (char list[MAX_ELEM][STR_LEN],int map[MAX_ELEM][MAX_ELEM]) ;

int main()
{
    unsigned int hashed_vals[MAX_ELEM];
    unsigned int same[MAX_ELEM][MAX_ELEM];
    char list[MAX_ELEM][STR_LEN];

    printf("Enter 10 elements:\n");
    int i = 0;
    for(i = 0; i < MAX_ELEM; i++){
        scanf("%[^\n]%*c", list[i]);
    }

    for (int i = 0; i < 10; i++)
        hashed_vals[i] = hash_text(list[i]) ;

    strong_similar (hashed_vals, same) ;

    printf("\nelements with hash values and similarities:\n");
    for (int i = 0; i < 10; i++)
    {
        printf("\n%-20s %5d",list[i],hashed_vals[i]);
        for (int j=0; j<MAX_ELEM;j++)
            if (same[i][j] ==1)
                printf ("%4d",j) ;
    }

    printf ("\n");

    weak_similar (list, same) ;

    printf("\n\nelements with weak similarities:");
    for (int i = 0; i < 10; i++)
    {
        printf("\n%-20s %5d",list[i],hashed_vals[i]);
        for (int j=0; j<MAX_ELEM;j++)
            if (same[i][j] == 2)
                printf ("%4d",j) ;
    }

    printf ("\n");
    return 0;
}


unsigned int hash_text(char* list) {

    unsigned int hash = 0;
    int currentChar;

    while ((currentChar = *list++)) {
        hash = (hash * 36 + currentChar) % 1000;
    }

    return hash;
}

void strong_similar (int hval[MAX_ELEM], int map[MAX_ELEM][MAX_ELEM])
{
    // for each element in names
    for (int i = 0; i < MAX_ELEM; i++) {

        // compare with each other element
        for (int j = 0; j < MAX_ELEM; j++) {

            // if hash values are the same they are similar
            if (i != j) 
            {
                if (hval[i] == hval[j]) {
                    map[i][j] = 1; 
                } else {
                    map[i][j] = 0; 
                }
            }
        }
    }
}


void weak_similar (char list[MAX_ELEM][STR_LEN],int map[MAX_ELEM][MAX_ELEM])
{
    char names[MAX_ELEM][2][STR_LEN];
    unsigned int hashes[MAX_ELEM][2];
    char new_list[MAX_ELEM][STR_LEN];

    // clear the map
    //for (int i = 0; i < MAX_ELEM; i++)
    //    for (int j = 0; j < MAX_ELEM; j++)
    //        map[i][j] = 0;
    
    // copy the original array
    for (int i = 0; i < MAX_ELEM; i++)
        for (int j = 0; j < MAX_ELEM; j++)
            new_list[i][j] = list[i][j];
    
    // for each name-surname pair
    for (int i = 0; i < MAX_ELEM; i++) {

        // get the name as token
        char *token = strtok(new_list[i], " ");
        strcpy(names[i][0], token);

        // then get the surname as token
        token = strtok(NULL, " ");    
        strcpy(names[i][1], token);
    
        // hash both the surname and name
        hashes[i][0] = hash_text(names[i][0]);
        hashes[i][1] = hash_text(names[i][1]);
    }

    // for each element in names
    for (int i = 0; i < MAX_ELEM; i++) {

        // compare with each other element
        for (int j = 0; j < MAX_ELEM; j++) {

            if (i != j) {

                // they are weakly similar if either name or surname is the same
                if (hashes[i][0] == hashes[j][0] || hashes[i][1] == hashes[j][1] 
                || hashes[i][0] == hashes[j][1] || hashes[i][1] == hashes[j][0] ) {
                    
                    map[i][j] = 2; // mark them similar in map

                } else {
                    
                    map[i][j] = 0; // mark them unsimilar in map
                }
            } else {
                map[i][j] = 0;
            }
        }
    }
}


