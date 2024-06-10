#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct Participant
{
    char full_name[50];
    char name[25];
    char surname[25];
    float duration;
};

void str_tolower(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}
void read_file(FILE *file_ptr, struct Participant participants[], int *participant_arr_size)
{
    char file_line[100];
    int first_line_skipped = 0;
    while (fgets(file_line, 100, file_ptr) != NULL)
    {
        // skipping the first line
        if (!first_line_skipped)
        {
            first_line_skipped = 1;
            continue;
        }

        // tokenizing the string
        char *file_token;
        char *full_name;
        char *duration_str = NULL;
        float duration_float = 0;

        // getting the full name
        file_token = strtok(file_line, ",");
        full_name = file_token;

        // getting the duration
        while (file_token != NULL)
        {
            duration_str = file_token;
            file_token = strtok(NULL, ",");
        }

        if (duration_str != NULL)
        {
            duration_float = atof(duration_str);
        }
        // printf("full name is: %s\nduration: %.1f\n", full_name, duration_float); // debug line

        // adding them to struct array
        strcpy(participants[*participant_arr_size].full_name, full_name);
        participants[*participant_arr_size].duration = duration_float;
        (*participant_arr_size)++;
    }
}

void remove_duplicates(struct Participant participants[], int *participant_arr_size)
{
    // for each element in array
    for (int i = 0; i < *participant_arr_size - 1; i++)
    {
        // compare with each element
        for (int j = i + 1; j < *participant_arr_size;)
        {
            // convert to lower case
            char full_name_lower1[50];
            strcpy(full_name_lower1, participants[i].full_name);
            str_tolower(full_name_lower1);

            char full_name_lower2[50];
            strcpy(full_name_lower2, participants[j].full_name);
            str_tolower(full_name_lower2);

            // compare the strings
            if (strcmp(full_name_lower1, full_name_lower2) == 0)
            {
                // adding the duration
                participants[i].duration += participants[j].duration;
                // shift the elements of the array
                for (int k = j; k < *participant_arr_size - 1; k++)
                {
                    strcpy(participants[k].full_name, participants[k + 1].full_name);
                    participants[k].duration = participants[k + 1].duration;
                }
                // decrease the size of array
                (*participant_arr_size)--;
            }
            else
            {
                // move to next element
                j++;
            }
        }
    }
}

void split_name_surname(struct Participant participants[], int participant_arr_size)
{
    for (int i = 0; i < participant_arr_size; i++)
    {
        char full_name[50];
        strcpy(full_name, participants[i].full_name);

        int no_spaces = 0;
        char *c = full_name;
        while (*c)
        {
            if (*c == ' ')
            {
                no_spaces++;
            }
            c++;
        }

        char *token = strtok(full_name, " ");
        strcpy(participants[i].name, token);

        // if there are more than 1 name
        if (no_spaces > 0) {
            strcat(participants[i].name, " ");
            for (int j = 1; j < no_spaces; j++) {
                token = strtok(NULL, " ");
                strcat(participants[i].name, token);
                strcat(participants[i].name, " ");
            }

            // surname
            token = strtok(NULL, " ");
            strcpy(participants[i].surname, token);
        }
    }
}

void bubble_sort_str(struct Participant participants[], int participant_arr_size)
{
    for (int i = 0; i < participant_arr_size - 1; i++)
    {
        for (int j = 0; j < participant_arr_size - i - 1; j++)
        {
            char surname_lower[25];
            strcpy(surname_lower, participants[j].surname);
            str_tolower(surname_lower);

            char surname_lower2[25];
            strcpy(surname_lower2, participants[j + 1].surname);
            str_tolower(surname_lower2);

            char name_lower[25];
            strcpy(name_lower, participants[j].name);
            str_tolower(name_lower);

            char name_lower2[25];
            strcpy(name_lower2, participants[j + 1].name);
            str_tolower(name_lower2);

            if (strcmp(surname_lower, surname_lower2) > 0)
            {
                // swap
                struct Participant temp = participants[j];
                participants[j] = participants[j + 1];
                participants[j + 1] = temp;
            }

            else if (strcmp(surname_lower, surname_lower2) == 0)
            {
                if (strcmp(name_lower, name_lower2) > 0)
                {
                    // swap
                    struct Participant temp = participants[j];
                    participants[j] = participants[j + 1];
                    participants[j + 1] = temp;
                }
            }
        }
    }
}

int main()
{
    char input_line[30];
    char *input_token;

    char *file_name;
    float min_duration_float = 0;
    int is_sorted = 0;

    // participant array
    struct Participant participants[500];
    int participant_arr_size = 0;

    // get the input line from the user
    fgets(input_line, 30, stdin);
    if (input_line[strlen(input_line) - 1] == '\n')
    {
        input_line[strlen(input_line) - 1] = '\0';
    }

    // tokenize the input
    // get the file name
    input_token = strtok(input_line, " ");
    file_name = input_token;

    // get the min duration convert to float
    input_token = strtok(NULL, " ");
    char *min_duration_str = input_token;
    min_duration_float = atof(min_duration_str);

    // get the sort parameter convert to int
    input_token = strtok(NULL, " ");
    char *sort_output = input_token;
    if (strcmp("sorted\0", sort_output) == 0)
    {
        is_sorted = 1;
    }

    // open the file
    FILE *file_ptr = fopen(file_name, "r");
    if (file_ptr == NULL)
    {
        printf("File error.\n");
        return 1;
    }

    // read the file line by line adding participants to the array
    read_file(file_ptr, participants, &participant_arr_size);

    // remove the duplicate entries and calculate total duration
    remove_duplicates(participants, &participant_arr_size);

    // split the full_name into name and surname for each participant
    split_name_surname(participants, participant_arr_size);

    // sort the array if parameter is_sorted is 1
    if (is_sorted)
        bubble_sort_str(participants, participant_arr_size);

    // print the result
    for (int i = 0; i < participant_arr_size; i++)
    {
        if (participants[i].duration >= min_duration_float)
        {
            printf("%s %s %.2f\n", participants[i].surname, participants[i].name, participants[i].duration);
        }
    }

    // close the file
    fclose(file_ptr);
    return 0;
}
