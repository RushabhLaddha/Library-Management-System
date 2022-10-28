#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

void new_stud();
void del_stud();
void display();
void prog();

// int main()
// {
//     prog();
// }

void prog()
{
    int choice;

    do
    {
        printf("1. Add New Student Profile\n");
        printf("2. Delete Exisiting student Profile\n");
        printf("3. Display all students\n");
        printf("4. Exit\n");
        printf("Select your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
            new_stud();
            break;

            case 2:
            del_stud();
            break;

            case 3:
            display();
            break;

            case 4:
                return;
        
            default:
            printf("Enter correct option\n");
            break;
        }        
    } while (choice);
}

void new_stud()
{
    int std_id;
    char std_name[50];

    printf("Enter the Student ID: ");
    scanf("%d", &std_id);

    fflush(stdin);

    printf("Enter Name of the Student: ");
    gets(std_name);

    FILE *fp;

    fp = fopen("student.csv", "a");

    fprintf(fp, "%d,%s,0,,0\n", std_id, std_name);

    printf("Student Profile Added Successfully!\n");

    fclose(fp);

}

void del_stud()
{
    int std_in_id;

    printf("Enter the Student ID to delete: ");
    scanf("%d", &std_in_id);

    fflush(stdin);

    FILE *fp, *tp;

    fp = fopen("student.csv", "r");
    tp = fopen("temp2.csv", "w");

    int stud_id;
    char stud_name[50];
    int count;
    char book[50];

    char line[200];
    char *sp;

    while (fgets(line, 200, fp) != NULL)
    {
        sp = strtok(line, ",");
        stud_id = atoi(sp);

        sp = strtok(NULL, ",");
        strcpy(stud_name, sp);

        sp = strtok(NULL, ",");
        count = atoi(sp);

        if (std_in_id != stud_id)
        {
            if (count == 1)
            {
                sp = strtok(NULL, ",");
                strcpy(book, sp);

                fprintf(tp, "%d,%s,%d,%s,0\n", stud_id, stud_name, count, book);
            }

            if (count == 0)
            {
                fprintf(tp, "%d,%s,0,,0\n", stud_id, stud_name);
            }
            

        }
        else if (std_in_id == stud_id)
        {
            printf("Student Profile Deleted Successfully\n");
        }
        
    }

    fclose(fp);
    fclose(tp);

    remove("student.csv");
    rename("temp2.csv", "student.csv");
}

void display()
{
    FILE *fp;
    char line[200];
    fp = fopen("student.csv", "r");
    char *sp;
    int std_id;
    char std_name[50];
    int count;
    char book[60];

    while (fgets(line, 200, fp) != NULL)
    {
        sp = strtok(line, ",");
        std_id = atoi(sp);
        sp = strtok(NULL, ",");
        strcpy(std_name, sp);
        sp = strtok(NULL, ",");
        count = atoi(sp);

        if (count == 1)
        {
            sp = strtok(book, sp);
            printf("%d\t%s\t%s\n", std_id, std_name, book);
        }
        else if (count == 0)
        {
            printf("%d\t%s\tNo Book Issued Yet\n", std_id, std_name);
        }
    }

    fclose(fp);
    
}