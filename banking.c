#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int i, j, menuExit;

void menu();
void newAcc();
void edit();
void transact();
void erase();
void showDetails();
void closeBnk();
float interest(float time, float principle, float rate);

struct date
{
    int day;
    int month;
    int year;
};

struct
{
    char *name;
    int age;
    int accNo;
    int adhaar;
    char *address;
    char *accType;
    int phoneNumber;
    float amt;
    struct date dob;
    struct date deposit;
    struct date withdraw;
} add,update,check,remove,transaction;

int main()
{
    menu();

    return 0;
}

float interest(float time, float principle, float rate)
{
    float SI;
    
    SI = (principle * time * rate)/100;
    return SI;
}

void menu()
{
    int ch;
    while(1)
    {
        printf("\t BANKING MENU \n");
        printf("******* MAIN MENU *******\n\n");
        printf("1. Create a new account.\n");
        printf("2. Update information of existing account.\n");
        printf("3. For Transactions.\n");
        printf("4. Check details of existing account.\n");
        printf("5. Remove existing account.\n");
        printf("6. Exit.\n");
        printf("\n\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        
        switch (ch)
        {
            case 1: newAcc();
                break;
            case 2: edit();
                break;
            case 3: transact();
                break;
            case 4: showDetails();
                break;
            case 5: erase();
                break;
            case 6: printf("Thank you for using the program.\n");
                break;
            default:
                printf("Invalid Statement. Program terminating now.\n");
                exit(1);
        }
    }
}

void newAcc()
{
    int ch;
    FILE *fptr;

    fptr = fopen("record.dat", "a+");

    system("cls");
    printf("****** Welcome to XYZ Bank! *******\n\n");
    printf("Enter today's date (DD/MM/YYYY): ");
    scanf("%d/%d/%d", &add.deposit.day, &add.deposit.month, &add.deposit.year);
    printf("Enter your Account number: ");
    scanf("%d", &check.accNo);
    while(fscanf(fptr,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",&add.accNo,add.name,&add.dob.day,&add.dob.month,&add.dob.year,&add.age,add.address,add.adhaar,&add.phoneNumber,add.accType,&add.amt,&add.deposit.day,&add.deposit.month,&add.deposit.year)!=EOF)
    {
        if(check.accNo == add.accNo)
        {
            printf("Account already exists!\n");
            newAcc(); 
        }
    }
    add.accNo = check.accNo;
    printf("Please Enter Your Name: ");
    scanf("\n");
    scanf("%[^\n]%*c", add.name);
    printf("Enter your date of birth (DD/MM/YYYY): ");
    scanf("%d/%d/%d", &add.dob.day, &add.dob.month, &add.dob.year);
    printf("Enter your age: ");
    scanf("%d", &add.age);
    printf("Enter your address: ");
    scanf("\n");
    scanf("%[^\n]%*c", add.address);
    printf("Enter your Adhaar number: ");
    scanf("%d", &add.adhaar);
    printf("Enter your phone number: ");
    scanf("%d", &add.phoneNumber);
    
    if(strlen(add.phoneNumber) < 10 || strlen(add.phoneNumber) > 10)
    {
        printf("Please enter a valid phone number!: ");
        scanf("%d", &add.phoneNumber);
    }

    printf("Enter the amount you want to deposit: ");
    scanf("%f", &add.amt);
    printf("Type of account:\n\t>>Current\n\t>>Saving");
    scanf("\n");
    scanf("%[^\n\%*c", add.accType);

        fprintf(fptr,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.accNo,add.name,add.dob.day,add.dob.month,add.dob.year,add.age,add.address,add.adhaar,add.phoneNumber,add.accType,add.amt,add.deposit.day,add.deposit.month,add.deposit.year);

    fclose(fptr);
    
    printf("\nAccount created successfully!\n");
    printf("Press 1 to return to main menu or 0 to exit: ");
    scanf("%d",&menuExit);
    
    if(menuExit == 0)
    {
        closeBnk();
    }
    else if(menuExit == 1)
    {
        menu();
    }
    else
    {
        printf("INVALID INPUT. TERMINATING... \n");
    }
}