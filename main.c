#include <stdio.h>
#include <stdlib.h>

//Book implementation
struct Book{
    char title[60];//Title of book
    char author[50];//Name of author
    int year;//Year of publishing
    float book_rate;//Book rate

    struct Book *nextbook;//Pointer to next book
};

//Customer implementation
typedef struct s{
    char name[50];//Name of customer
    int age;//Age of customer
    float customer_rate;//Customer rate

    struct s *nextcustomer;//Pointer to next customer
} customer;

struct Book *first_book = NULL; //First book pointer
customer *first_customer = NULL; //First customer pointer

//Print menu in console
void PrintMenu(){
    printf("Commands: 1 - Show books\n");
    printf("          2 - Add book\n");
    printf("          3 - Update book\n");
    printf("          4 - Remove book\n");
    printf("          5 - Show customers\n");
    printf("          6 - Add customer\n");
    printf("          7 - Update customer\n");
    printf("          8 - Remove customer\n");
    printf("          9 - Exit\n");
    printf("Enter command: ");
}

//Free input buffer (for using fgets without bugs)
void FreeBuffer(){
    int c;
    do{
        c = getchar();
    }while(c != EOF && c != '\n');
}

//Print string
void PrintString(char *str, int N){
    for (int i = 0; i < N; i++)
        if (str[i] != '\0' && str[i] != '\n')
            printf("%c", str[i]);
        else
            break;
}

//Compare strings
int CompareStrings(char *str1, char *str2, int N1, int N2){
    int N = 0;

    if (N1 < N2)
        N = N1;
    else
        N = N2;

    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0' && i < N){
        if (str1[i] != str2[i])
            return 0;

        i++;
    }

    return 1;
}

//Add book to collection by title, author, book rate and year
void AddBook(){
    struct Book *new_book = first_book;
    struct Book *last_book = NULL;

    //Search of last book
    while (new_book != NULL){
        last_book = new_book;
        new_book = new_book->nextbook;
    }

    new_book = malloc(sizeof(struct Book));//Memory allocation for new book

    if (last_book != NULL)
        last_book->nextbook = new_book;//Last book contains pointer to next one
    else
        first_book = new_book;//Or new book is first one

    FreeBuffer();//Necessary command
    printf("Title: ");
    fgets(new_book->title, 60, stdin);//Initialize title of book

    printf("Author: ");
    fgets(new_book->author, 50, stdin);//Initialize author of book

    printf("Year: ");
    scanf("%d", &(new_book->year));//Initialize year of book

    printf("Book rate: ");
    scanf("%f", &(new_book->book_rate));//Initialize rate of book

    new_book->nextbook = NULL;//Pointer to next book is null because next book does not exist

    printf("Book has been added.\n");
};

//Show all books
void ShowBooks(){
    struct Book *current_book = first_book;

    //Print books until pointer to new one is not empty
    while (current_book != NULL){
        printf("Title: ");
        PrintString(current_book->title, sizeof(current_book->title));
        printf(", Author: ");
        PrintString(current_book->author, sizeof(current_book->author));
        printf(", Year: ");
        printf("%d, Rate: %f\n", current_book->year, current_book->book_rate);

        current_book = current_book->nextbook;
    }

    //If collection of book is empty
    if (first_book != NULL)
        printf("End of list.\n");
    else
        printf("Empty list.\n");
}

//Update book given the title
void UpdateBook(){
    FreeBuffer();//Necessary command
    char title[60];//Title of necessary book

    printf("Enter title of the book: ");
    fgets(title, 60, stdin);//User enters title

    struct Book *current_book = first_book;

    //Search book until they are not over or coincidence is not found
    while (current_book != NULL){
        if (CompareStrings(current_book->title, title, 60, 60))
            break;

        current_book = current_book->nextbook;
    }

    if (current_book != NULL){//If book is found
        printf("Book is found.\n");
        int command = 0;//Pointer of current command
        while (command != 5){//Loop for action
            printf("You can change: 1 - Update title\n");
            printf("                2 - Update author\n");
            printf("                3 - Update year\n");
            printf("                4 - Update book rate\n");
            printf("                5 - Exit\n");
            printf("Enter command: ");
            scanf("%d", &command);
            FreeBuffer();

            switch (command){
            case 1:{
                printf("New title: ");
                fgets(current_book->title, 60, stdin);//Rename book
                break;
            }

            case 2:{
                printf("New author: ");
                fgets(current_book->author, 60, stdin);//Change author of book
                break;
            }

            case 3:{
                printf("New year: ");
                scanf("%d", &(current_book->year));//Change year of book
                break;
            }

            case 4:{
                printf("New book rate: ");
                scanf("%f", &(current_book->book_rate));//Change book rate
                break;
            }

            case 5:
                printf("Enter to menu.\n");//Entering to main menu
                break;

            default:
                printf("Command not found.\n");//If command is not found
                break;
            }
        }
    }
    else
        printf("Book is not found\n");
}

//Remove book from collection by title
void RemoveBook(){
    FreeBuffer();//Necessary command
    char title[60];//Title of necessary book

    printf("Enter title of the book: ");
    fgets(title, 60, stdin);//User enters title

    struct Book *current_book = first_book;
    struct Book *previous_book = first_book;

    //Search book until they are not over or coincidence is not found
    while (current_book != NULL){
        if (CompareStrings(current_book->title, title, 60, 60))
            break;

        previous_book = current_book;
        current_book = current_book->nextbook;
    }

    if (current_book != NULL){//If book is found
        previous_book->nextbook = current_book->nextbook;//Previous book must contain new pointer to other book

        //free(current_book->title);
        //free(current_book->author);
        free(current_book);//Free memory for removable book

        if (first_book == current_book && current_book->nextbook == NULL)
            first_book = NULL;//If removable book is last
        else if (first_book == current_book && current_book->nextbook != NULL){
            first_book = current_book->nextbook;//If removable book is first in list of ones
        }

        printf("Book has been removed\n");
    }
    else
        printf("Book is not found\n");
}

//Add customer to collection by name, age and customer rate
void AddCustomer(){
    customer *new_customer = first_customer;
    customer *last_customer = NULL;

    //Search of last CUSTOMER
    while (new_customer != NULL){
        last_customer = new_customer;
        new_customer = new_customer->nextcustomer;
    }

    new_customer = malloc(sizeof(customer));//Memory allocation for new customer

    if (last_customer != NULL)
        last_customer->nextcustomer = new_customer;//Last customer contains pointer to next one
    else
        first_customer = new_customer;//Or new customer is first one

    FreeBuffer();//Necessary command
    printf("Name: ");
    fgets(new_customer->name, 50, stdin);//Set name of customer

    printf("Age: ");
    scanf("%d", &(new_customer->age));//Set age of customer

    printf("Customer rate: ");
    scanf("%f", &(new_customer->customer_rate));//Set customer rate

    new_customer->nextcustomer = NULL;//Next customer does not exist yet

    printf("Customer has been added.\n");
}

//Show all customers
void ShowCustomers(){
    customer *current_customer = first_customer;

    //Print customers until pointer to new one is not empty
    while (current_customer != NULL){
        printf("Name: ");
        PrintString(current_customer->name, sizeof(current_customer->name));
        printf(", Age: ");
        printf("%d, Rate: %f\n", current_customer->age, current_customer->customer_rate);

        current_customer = current_customer->nextcustomer;
    }

    //If collection of customers is empty
    if (first_customer != NULL)
        printf("End of list.\n");
    else
        printf("Empty list.\n");
}

//Update customer given the name
void UpdateCustomer(){
    FreeBuffer();//Necessary command
    char name[60];//Name of necessary customer

    printf("Enter name of the customer: ");
    fgets(name, 60, stdin);//User enters name

    customer *current_customer = first_customer;

    //Search customer until they are not over or coincidence is not found
    while (current_customer != NULL){
        if (CompareStrings(current_customer->name, name, sizeof(current_customer->name), sizeof(name)))
            break;

        current_customer = current_customer->nextcustomer;
    }

    if (current_customer != NULL){//If book is found
        printf("Customer is found.\n");
        int command = 0;//Pointer to current command
        while (command != 4){
            printf("You can change: 1 - Update name\n");
            printf("                2 - Update age\n");
            printf("                3 - Update customer rate\n");
            printf("                4 - Exit\n");
            printf("Enter command: ");
            scanf("%d", &command);
            FreeBuffer();

            switch (command){
            case 1:{
                printf("New name: ");
                fgets(current_customer->name, 60, stdin);//Change name of customer
                break;
            }

            case 2:{
                printf("New age: ");
                scanf("%d", &(current_customer->age));//Change age of customer
                break;
            }

            case 3:{
                printf("New customer rate: ");
                scanf("%f", &(current_customer->customer_rate));//Change rate of customer
                break;
            }

            case 4:
                printf("Enter to menu.\n");//Entering to main menu
                break;

            default:
                printf("Command not found.\n");//If command is not found
                break;
            }
        }
    }
    else
        printf("Customer is not found\n");//Customer is not found
}

//Remove customer from collection by name
void RemoveCustomer(){
    FreeBuffer();//Necessary command
    char name[60];//Name of necessary customer

    printf("Enter name of the customer: ");
    fgets(name, 60, stdin);//User enters name

    customer *current_customer = first_customer;
    customer *previous_customer = first_customer;

    //Search customer until they are not over or coincidence is not found
    while (current_customer != NULL){
        if (CompareStrings(current_customer->name, name, sizeof(current_customer->name), sizeof(name)))
            break;

        previous_customer = current_customer;
        current_customer = current_customer->nextcustomer;
    }

    if (current_customer != NULL){//If customer is found
        previous_customer->nextcustomer = current_customer->nextcustomer;//Previous customer must contain new pointer to other customer

        //free(current_book->title);
        //free(current_book->author);
        free(current_customer);

        if (first_customer == current_customer && current_customer->nextcustomer == NULL)
            first_customer = NULL;//If removable customer is last
        else if (first_customer == current_customer && current_customer->nextcustomer != NULL){
            first_customer = current_customer->nextcustomer;//If removable customer is first in list of ones
        }

        printf("Customer has been removed\n");
    }
    else
        printf("Customer is not found\n");//If customer is not found
}

int main()
{
    auto int command = 0;//Command pointer

    //main loop
    while (command != 9){
        PrintMenu();
        scanf("%d", &command); //Get current command

        switch (command){
        case 1:{//Show books
            ShowBooks();
            break;
        }

        case 2:{//Add book
            AddBook();
            break;
        }

        case 3:{//Update book
            UpdateBook();
            break;
        }

        case 4:{//Remove book
            RemoveBook();
            break;
        }

        case 5:{//Show customers
            ShowCustomers();
            break;
        }

        case 6:{//Add customer
            AddCustomer();
            break;
        }

        case 7:{//Update customer
            UpdateCustomer();
            break;
        }

        case 8:{//Remove customer
            RemoveCustomer();
            break;
        }

        case 9://Command for termination process
            printf("End of session.\n");
            break;

        default://If command is not found
            printf("Command is not found.\n");
            break;
        }
    }

    return 0;
}
