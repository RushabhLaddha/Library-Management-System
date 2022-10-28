#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include "student.c"

typedef struct library
{
    int acc_num;              // Accession Number
    char b_name[60];          // Book Name
    char a_name[60];          // Author Name
    int issue;                // Issued or not
    char genre[20];           // Genre of the book 
}lib;

void new_book();
void delete_book();
void issue_book();
void return_book();
void find_book();
void display_all_books();

int main()
{
    lib b[500];
    int option;                // User input
    
    do
    {
        printf("1. Add New Book\n");
        printf("2. Delete Existing Book\n");
        printf("3. Issue a Book\n");
        printf("4. Return Book\n");
        printf("5. Find a Book\n");
        printf("6. Display all Available Books\n");
        printf("7. Student Related Options\n");
        printf("8. Exit\n");
        printf("\nChoose anyone of the options: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            new_book();
            break;
        
        case 2:
            delete_book();
            break;

        case 3:
            issue_book();
            break;

        case 4:
            return_book();
            break;

        case 5:      
            find_book();        
            break;

        case 6:
            display_all_books();
            break;

        case 7:
            prog();
            break;
        
        case 8:
            return 0;
        
        default:
            printf("Enter Correct option");
            break;
        }
        
    } while (1);
    

    return 0;
}

// Add New Book to the database
void new_book()
{
    lib a;
    FILE *fp;
    fp = fopen("database.csv", "a");

    printf("Enter the Accession Number: ");
    scanf("%d", &a.acc_num);
    fflush(stdin);
    printf("Enter Book Name: ");
    gets(a.b_name);
    fflush(stdin);
    printf("Enter the Author's Name: ");
    gets(a.a_name);
    printf("Enter the Genre of the Book: ");
    gets(a.genre);
    fprintf(fp, "%d,%s,%s,%s,%d\n", a.acc_num, a.b_name, a.a_name, a.genre, a.issue = 0);
    printf("Book Added Successfully!\n");
    fclose(fp);
}

// Delete Particular Book
void delete_book()
{
    FILE *fp, *tp;
    int acc_n;

    fp = fopen("database.csv", "r");
    tp = fopen("temp.csv", "w");

    printf("Enter the Accession Number of the Book You want to delete: ");
    scanf("%d", &acc_n);

    char line[200];
    int access_num, issue = 0;
    char book[60];
    char author[60];
    char *sp;
    bool num_change = false;
    char genre[20];
    while (fgets(line, 200, fp) != NULL)
    {
        sp = strtok(line, ",");
        access_num = atoi(sp);

        sp = strtok(NULL, ",");
        strcpy(book, sp);

        sp = strtok(NULL, ",");
        strcpy(author, sp);

        sp = strtok(NULL, ",");
        strcpy(genre, sp);

        sp = strtok(NULL, ",");
        issue = atoi(sp);

        if (access_num != acc_n)
        {
            if (num_change == true)
            {
                access_num--;
            }
            fprintf(tp, "%d,", access_num);
            fprintf(tp, "%s,", book);
            fprintf(tp, "%s,", author);
            fprintf(tp, "%s,", genre);
            fprintf(tp, "%d\n", issue);
        }
        else if(access_num == acc_n)
        {
            num_change = true;
        }

    }
    
    fclose(fp);
    fclose(tp);

    remove("database.csv");
    rename("temp.csv", "database.csv");

}

// Issue the Book
void issue_book()
{
    FILE *fp, *tp;
    char line[200];
    char *sp;
    int issue = 0;
    int acc_n;
    int access_num;
    char book[60];
    char author[60];
    char genre[20];

    char book_copy[60];
    int stud_id;

    printf("Enter the Accession Number of the book to be issued: ");
    scanf("%d", &acc_n);

    fflush(stdin);

    printf("Enter the Student ID for the book to be issued: ");
    scanf("%d", &stud_id);

    fflush(stdin);

    fp = fopen("database.csv", "r");
    tp = fopen("temp.csv", "w");


    while (fgets(line, 200, fp) != NULL)
    {
        // Editing database of books
        sp = strtok(line, ",");
        access_num = atoi(sp);

        sp = strtok(NULL, ",");
        strcpy(book, sp);

        sp = strtok(NULL, ",");
        strcpy(author, sp);
        
        sp = strtok(NULL, ",");
        strcpy(genre, sp);

        sp = strtok(NULL,",");
        issue = atoi(sp);

        if (acc_n == access_num)
        {
            strcpy(book_copy, book);

            if (issue == 1)
            {
                printf("Book is already issued\n");

                fclose(fp);
                fclose(tp);
                remove("temp.csv");
                return;
            }
            else if(issue == 0)
            {
                issue = 1;
            }   
        }
        
        fprintf(tp, "%d,", access_num);
        fprintf(tp, "%s,", book);
        fprintf(tp, "%s,", author); 
        fprintf(tp, "%s,", genre);  
        fprintf(tp, "%d\n", issue);
    }

    fclose(fp);
    fclose(tp);

    remove("database.csv");
    rename("temp.csv", "database.csv"); 

    // Student database editing

    fp = fopen("student.csv", "r");
    tp = fopen("temp.csv", "w");

    int std_id;
    char std_name[50];
    int count;
    char book_print[60];


    while (fgets(line, 200, fp) != NULL)
    {
        sp = strtok(line, ",");
        std_id = atoi(sp);

        sp = strtok(NULL, ",");
        strcpy(std_name, sp);

        sp = strtok(NULL, ",");
        count = atoi(sp);

        sp = strtok(NULL, ",");
        strcpy(book_print, sp);

        if (std_id == stud_id)
        {
            count = 1;
            strcpy(book_print, book_copy);
            fprintf(tp, "%d,%s,%d,%s,0\n", std_id, std_name, count, book_print);
            printf("Book Issued successfully!\n");
        }
        else if (count == 1)
        {
            fprintf(tp, "%d,%s,%d,%s,0\n", std_id, std_name, count, book_print);
        }
        else
        {
            fprintf(tp, "%d,%s,%d,,0\n", std_id, std_name, count);
        }
    }
    fclose(fp);
    fclose(tp);

    remove("student.csv");
    rename("temp.csv", "student.csv");
}

// Return Book
void return_book()
{
    FILE *fp, *tp;

    int acc_n;

    printf("Enter the Accession Number of the book to be returned: ");
    scanf("%d", &acc_n);

    fp = fopen("database.csv", "r");
    tp = fopen("temp.csv", "w");

    int acc_num, issue = 0;
    char book[60], author[60];

    char *sp;
    char line[200];
    char genre[20];
    char book_cmp[60];

    while (fgets(line, 200, fp) != NULL)
    {
        sp = strtok(line,",");
        acc_num = atoi(sp);

        sp = strtok(NULL, ",");
        strcpy(book, sp);

        sp = strtok(NULL, ",");
        strcpy(author, sp);

        sp = strtok(NULL, ",");
        strcpy(genre, sp);

        sp = strtok(NULL, ",");
        issue = atoi(sp);

        if (acc_n == acc_num)
        {
            strcpy(book_cmp, book);
            issue = 0;
        }

        fprintf(tp, "%d,%s,%s,%s,%d\n", acc_num, book, author, genre, issue);
    }

    fclose(fp);
    fclose(tp);    

    remove("database.csv");
    rename("temp.csv", "database.csv");

    // Student variables

    int std_id;
    char stud_name[50];
    int count;
    char book_print[60];
    int compare;

    fp = fopen("student.csv", "r");
    tp = fopen("temp.csv", "w");

    while (fgets(line, 200, fp) != NULL)
    {
        sp = strtok(line, ",");
        std_id = atoi(sp);

        sp = strtok(NULL, ",");
        strcpy(stud_name, sp);

        sp = strtok(NULL, ",");
        count = atoi(sp);

        if (count == 1)
        {
            sp = strtok(NULL, ",");
            strcpy(book_print, sp);

            compare = strcmp(book_print, book_cmp);

            if(compare == 0)
            {
                fprintf(tp, "%d,%s,0,,0\n", std_id, stud_name);
                printf("Book Successfully returned\n");
            }
            else
            {
                fprintf(tp, "%d,%s,%d,%s,0\n", std_id, stud_name, count, book_print);
            }
        }
        else
        {
            fprintf(tp, "%d,%s,0,,0\n", std_id, stud_name, count);
        }
        
    }

    fclose(fp);
    fclose(tp);

    remove("student.csv");
    rename("temp.csv", "student.csv");

}

// Find particular book from the database using Accession Number or Book Name
void find_book()
{ 
    FILE *fp;

    int access_num;
    char book[60];
    char author[60];
    int issue;
    int choice;
    fp = fopen("database.csv", "r");
    
    char *sp;
    char line[200];

    int acc_n;
    char book_name[60];
    
    int compare;
    char genre[20];
    char genre_input[20];

    printf("How you want to find the book?\n");
    printf("1. Through Accession Number\n");
    printf("2. Through Book Name\n");
    printf("3. Through Genre\nYour choice: ");
    scanf("%d", &choice);

    fflush(stdin);

    if (choice == 1)
    {
        printf("Enter the Accession Number: ");
        scanf("%d", &acc_n);

        fflush(stdin);

        while (fgets(line, 200, fp) != NULL)
        {
            sp = strtok(line, ",");
            access_num = atoi(sp);

            if (access_num == acc_n)
            {
                printf("Access Number: %d\n", access_num);

                sp = strtok(NULL, ",");
                strcpy(book, sp);
                printf("Book Name: %s\n", book);

                sp = strtok(NULL, ",");
                strcpy(author, sp);
                printf("Author Name: %s\n", author);

                sp = strtok(NULL, ",");
                strcpy(genre, sp);
                printf("Genre: %s\n", genre);

                sp = strtok(NULL, ",");
                issue = atoi(sp);

                if (issue == 0)
                {
                    printf("Book is available\n\n");
                }
                else if(issue == 1)
                {
                    printf("Book is not available\n\n");
                }
            }
        }

        fclose(fp);
    }
    else if(choice == 2)
    {

        printf("Enter the Book Name: ");
        gets(book_name);

        while (fgets(line, 200, fp) != NULL)
        {
            sp = strtok(line, ",");
            access_num = atoi(sp);
            
            sp = strtok(NULL, ",");
            strcpy(book, sp);

            compare = strcmp(book, book_name);

            if (compare == 0)
            {
                sp = strtok(NULL, ",");
                strcpy(author, sp);

                sp = strtok(NULL, ",");
                strcpy(genre, sp);

                sp = strtok(NULL, ",");
                issue = atoi(sp);

                

                printf("Accession Number: %d\n", access_num);
                printf("Book Name: %s\n", book);
                printf("Author's Name: %s\n", author);
                printf("Genre: %s\n", genre);
                if (issue == 0)
                {
                    printf("Book is available\n\n");
                }
                else if(issue == 1)
                {
                    printf("Book is not available\n\n");
                }
            }
        }
        fclose(fp);
    }
    else if(choice == 3)
    {
        printf("Enter the Genre: ");
        gets(genre_input);

        while (fgets(line, 200, fp) != NULL)
        {
            sp = strtok(line, ",");
            access_num = atoi(sp);

            sp = strtok(NULL, ",");
            strcpy(book, sp);

            sp = strtok(NULL, ",");
            strcpy(author, sp);

            sp = strtok(NULL, ",");
            strcpy(genre, sp);

            sp = strtok(NULL, ",");
            issue = atoi(sp);

            

            compare = strcmp(genre, genre_input);

            if (compare == 0)
            {
                printf("%-10d %-60s %-60s", access_num, book, author);
                if (issue == 0)
                {
                    printf("Available\n");
                }
                else if(issue == 1)
                {
                    printf("Not available\n");
                }                
            }
        }

        fclose(fp);
    }

    else
    {
        if (choice == 1)
        {
            printf("Please enter correct Accession Number");
        }
        else if (choice == 2)
        {
            printf("Please enter correct Book Name");
        }
        else if(choice == 3)
        {
            printf("Enter correct genre");
        }
        fclose(fp);
    }
}

// Display all available books from the database
void display_all_books()
{
    FILE *fp;
    lib a;
    int access_num;
    char book[60];
    char author[60];
    char line[300];
    bool issue;
    char *sp;
    char genre[20];
    
    fp = fopen("database.csv", "r");

    printf("Following are the Books available for issuing\n");

    while (fgets(line, 300, fp) != NULL)
    {
        sp = strtok(line, ",");
        access_num = atoi(sp);
        
        sp = strtok(NULL, ",");
        strcpy(book, sp);
        
        sp = strtok(NULL, ",");
        strcpy(author, sp);

        sp = strtok(NULL, ",");
        strcpy(genre, sp);

        sp = strtok(NULL, ",");
        issue = atoi(sp);

        if (issue == 0)
        {
            printf("%-10d", access_num);
            printf("%-40s", book);
            printf("%-40s", author);
            printf("%-20s\n", genre);
        }
    }
    fclose(fp);
}
