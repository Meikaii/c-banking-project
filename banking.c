#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int i, j, menuExit;

void menu();
void newAcc();
void edit();
void transact();
void erase();
void checkDetails();
void closeBnk();
double interest(double time, double principle, double rate);

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
    long adhaar;
    char *address;
    char *accType;
    long phoneNumber;
    double amt;
    struct date dob;
    struct date deposit;
    struct date withdraw;
} add,update,check,rem,transaction;

int main()
{
    char userPass[50];
    char pass[50] = "1234567890";
    int i = 0;
    printf("Enter password to login: ");
    scanf("%s", userPass);

    if(strcmp(userPass, pass) == 0)
    {
        printf("\n\n Welcome... \n\n");
        printf("LOADING...\n");
        system("cls");
        menu();
    }
    else
    {
        printf("\n\n Wrong PASSWORD. \n\n");
        printf("\n TERMINATING NOW... \n");
        return 1;
    }

    return 0;
}

double interest(double time, double principle, double rate)
{
    double SI;
    
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
    while(fscanf(fptr,"%d %s %d/%d/%d %d %s %d %d %s %lf %d/%d/%d\n",&add.accNo, add.name, &add.dob.day, &add.dob.month, &add.dob.year, &add.age, add.address, &add.adhaar, &add.phoneNumber, add.accType, &add.amt, &add.deposit.day, &add.deposit.month, &add.deposit.year)!=EOF)
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
    scanf("%ld", &add.adhaar);
    printf("Enter your phone number: ");
    scanf("%ld", &add.phoneNumber);
    
    if(strlen(add.phoneNumber) < 10 || strlen(add.phoneNumber) > 10)
    {
        printf("Please enter a valid phone number!: ");
        scanf("%ld", &add.phoneNumber);
    }

    printf("Enter the amount you want to deposit: ");
    scanf("%lf", &add.amt);
    printf("Type of account:\n\t>>Current\n\t>>Saving");
    scanf("\n");
    scanf("%[^\n]%*c", add.accType);

        fprintf(fptr,"%d %s %d/%d/%d %d %s %ld %ld %s %lf %d/%d/%d\n",add.accNo,add.name,add.dob.day,add.dob.month,add.dob.year,add.age,add.address,add.adhaar,add.phoneNumber,add.accType,add.amt,add.deposit.day,add.deposit.month,add.deposit.year);

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

void edit()
{
    int ch;
    int test = 0;

    FILE *oldRec, *newRec;

    oldRec = fopen("record.dat", "r");
    newRec = fopen("new.dat", "w");

    printf("Enter the account number to proceed making changes: ");
    scanf("%d", &update.accNo);
    while(fscanf(oldRec,"%d %s %d/%d/%d %d %s %ld %ld %s %lf %d/%d/%d",&add.accNo,add.name,&add.dob.day,&add.dob.month,&add.dob.year,&add.age,add.address, &add.adhaar,&add.phoneNumber,add.accType,&add.amt,&add.deposit.day,&add.deposit.month,&add.deposit.year)!=EOF)
    {
        if(add.accNo == update.accNo)
        {
            test = 1;
            printf("Which one of the following do you want to update/make changes?\n");
            printf("1. Address\n");
            printf("2. Phone Number\n");
            printf("Enter your choice: ");
            scanf("%d", &ch);

            if (ch == 1)
            {
                printf("Enter your new address: ");
                scanf("\n");
                scanf("%[^\n]%*c", update.address);
                fprintf(newRec,"%d %s %d/%d/%d %d %s %ld %ld %s %lf %d/%d/%d",add.accNo,add.name,add.dob.day, add.dob.month, add.dob.year, add.age, update.address, add.adhaar, add.phoneNumber,add.accType, add.amt, add.deposit.day, add.deposit.month, add.deposit.year);
                printf("\n...\n");
                printf("Changes saved successfully.\n");
            }
            else if (ch == 2)
            {
                printf("Enter your new phone number: ");
                scanf("%d", &update.phoneNumber);
                if(strlen(update.phoneNumber) < 10 || strlen(update.phoneNumber) > 10)
                {
                    printf("Please enter a valid phone number: ");
                    scanf("%d", &update.phoneNumber);
                }
                fprintf(newRec,"%d %s %d/%d/%d %d %s %ld %ld %s %lf %d/%d/%d", add.accNo,add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.adhaar, update.phoneNumber,add.accType, add.amt, add.deposit.day, add.deposit.month, add.deposit.year);
                printf("\n...\n");
                printf("Changes saved successfully.\n");
            }
        }
        else
        {
            fprintf(newRec,"%d %s %d/%d/%d %d %s %ld %ld %s %lf %d/%d/%d", add.accNo,add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.adhaar, add.phoneNumber,add.accType, add.amt, add.deposit.day, add.deposit.month, add.deposit.year);
        }
    }
    fclose(oldRec);
    fclose(newRec);
    remove("record.dat");
    rename("new.dat", "record.dat");

    if (test != 1)
    {
        printf("Record not found!..\n");
        printf("Press 0 to try again.\nPress 1 to return to main menu.\nPress 2 to exit.\n");
        printf("Enter your choice: ");
        scanf("%d", &menuExit);
        
        if (menuExit == 0)
        {
            edit();
        }
        else if (menuExit == 1)
        {
            menu();
        }
        else if (menuExit == 2)
        {
            closeBnk();
        }
        else
        {
            printf("Invalid input. Teminating. \n");
            exit(1);
        }
    }
    else
    {
        printf("Press 1 to return to main menu\nPress 0 to exit.");
        printf("Enter your choice: ");
        scanf("%d", &menuExit);

        if (menuExit == 0)
        {
            closeBnk();
        } 
        else if (menuExit == 1)
        {
            menu();
        }
        else
        {
            printf("Invalid input. Teminating. \n");
            exit(1);
        }
    }
}

void transact()
{
    int ch;
    int test = 0;

    FILE *oldRec, *newRec;

    oldRec = fopen("record.dat", "r");
    newRec = fopen("new.dat", "w");

    printf("Enter the account number of the customer: ");
    scanf("%d", &transaction.accNo);

    while(fscanf(oldRec,"%d %s %d/%d/%d %d %s %ld %ld %s %lf %d/%d/%d",&add.accNo,add.name,&add.dob.day,&add.dob.month,&add.dob.year,&add.age,add.address, &add.adhaar,&add.phoneNumber,add.accType,&add.amt,&add.deposit.day,&add.deposit.month,&add.deposit.year)!=EOF)
    {
        if(add.accNo == transaction.accNo)
        {
            test = 1;
            printf("Press 1 to Deposit.\nPress 2 to Withdraw.");
            printf("Enter your choice: ");
            printf("%d", &ch);

            if (ch == 1)
            {
                printf("Enter the amount you want to deposit: $");
                scanf("%lf", &transaction.amt);
                add.amt += transaction.amt;
                fprintf(newRec,"%d %s %d/%d/%d %d %s %ld %ld %s %lf %d/%d/%d", add.accNo,add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.adhaar, add.phoneNumber,add.accType, add.amt, add.deposit.day, add.deposit.month, add.deposit.year);
                printf("\n Deposited successfully! \n");
            }
            else if (ch == 2)
            {
                printf("Enter the amount you want to withdraw: $");
                scanf("%lf", &transaction.amt);
                add.amt -= transaction.amt;
                fprintf(newRec,"%d %s %d/%d/%d %d %s %ld %ld %s %lf %d/%d/%d", add.accNo,add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.adhaar, add.phoneNumber,add.accType, add.amt, add.deposit.day, add.deposit.month, add.deposit.year);
                printf("\n Withdrawn successfully! \n");
            }
        }
        else
        {
            fprintf(newRec,"%d %s %d/%d/%d %d %s %ld %ld %s %lf %d/%d/%d", add.accNo,add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.adhaar, add.phoneNumber,add.accType, add.amt, add.deposit.day, add.deposit.month, add.deposit.year);
        }
    }
    fclose(oldRec);
    fclose(newRec);
    remove("record.dat");
    rename("new.dat", "record.dat");

    if (test != 1)
    {
        printf("Record not found!..\n");
        printf("Press 0 to try again.\nPress 1 to return to main menu.\nPress 2 to exit.\n");
        printf("Enter your choice: ");
        scanf("%d", &menuExit);
        
        if (menuExit == 0)
        {
            transact();
        }
        else if (menuExit == 1)
        {
            menu();
        }
        else if (menuExit == 2)
        {
            closeBnk();
        }
        else
        {
            printf("Invalid input. Teminating. \n");
            exit(1);
        }
    }
    else
    {
        printf("Press 1 to return to main menu\nPress 0 to exit.");
        printf("Enter your choice: ");
        scanf("%d", &menuExit);

        if (menuExit == 0)
        {
            closeBnk();
        } 
        else if (menuExit == 1)
        {
            menu();
        }
        else
        {
            printf("Invalid input. Teminating. \n");
            exit(1);
        }
    }
}

void erase()
{
    FILE *oldRec, *newRec;
    int test = 0;
    
    oldRec = fopen("record.dat", "r");
    newRec = fopen("new.dat", "w");

    printf("Enter the account number you want to delete: ");
    scanf("%d", &rem.accNo);
    while(fscanf(oldRec,"%d %s %d/%d/%d %d %s %ld %ld %s %lf %d/%d/%d",&add.accNo,add.name,&add.dob.day,&add.dob.month,&add.dob.year,&add.age,add.address, &add.adhaar,&add.phoneNumber,add.accType,&add.amt,&add.deposit.day,&add.deposit.month,&add.deposit.year)!=EOF)
    {
        if(add.accNo != rem.accNo)
        {
            fprintf(newRec, "%d %s %d/%d/%d %d %s %ld %ld %s %lf %d/%d/%d", add.accNo,add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.adhaar, add.phoneNumber,add.accType, add.amt, add.deposit.day, add.deposit.month, add.deposit.year);
        }
        else
        {
            test++;
            printf("\n\nRecord deleted successfully.\n\n");
        }
    }
    fclose(newRec);
    fclose(oldRec);
    remove("record.dat");
    rename("new.dat", "record.dat");

    if (test != 1)
    {
        printf("Record not found!..\n");
        printf("Press 0 to try again.\nPress 1 to return to main menu.\nPress 2 to exit.\n");
        printf("Enter your choice: ");
        scanf("%d", &menuExit);
        
        if (menuExit == 0)
        {
            erase();
        }
        else if (menuExit == 1)
        {
            menu();
        }
        else if (menuExit == 2)
        {
            closeBnk();
        }
        else
        {
            printf("Invalid input. Teminating. \n");
            exit(1);
        }
    }
    else
    {
        printf("Press 1 to return to main menu\nPress 0 to exit.");
        printf("Enter your choice: ");
        scanf("%d", &menuExit);

        if (menuExit == 0)
        {
            closeBnk();
        } 
        else if (menuExit == 1)
        {
            menu();
        }
        else
        {
            printf("Invalid input. Teminating. \n");
            exit(1);
        }
    }
}

void checkDetails()
{
    FILE *ptr;
    int test = 0;
    int ch;
    double time, rate, principle;

    ptr = fopen("record.dat", "r");
    printf("Check by: \n1. Account Number. \n2. Name.\n");
    printf("Enter your choice: ");
    scanf("%d", &ch);

    if(ch == 1)
    {
        printf("Enter the Account number: ");
        scanf("%d", &check.accNo);

        while(fscanf(ptr, "%d %s %d/%d/%d %d %s %ld %ld %s %lf %d/%d/%d",&add.accNo,add.name,&add.dob.day,&add.dob.month,&add.dob.year,&add.age,add.address, &add.adhaar,&add.phoneNumber,add.accType,&add.amt,&add.deposit.day,&add.deposit.month,&add.deposit.year)!=EOF)
        {
            if(add.accNo == check.accNo)
            {
                test++;

                printf("Account Number: %d \nName: %s \nDOB: %d/%d/%d \nAge: %d \nAddress: %s \nAdhaar Number: %d \nPhone Number: %d \nAccount Type: %s \nAmount Deposited: $%.2lf \nDate of Deposit: %d/%d/%d \n\n", add.accNo,add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.adhaar, add.phoneNumber,add.accType, add.amt, add.deposit.day, add.deposit.month, add.deposit.year);
                if(strcmpi(add.accType, "savings") == 0)
                {
                    time = (1.0/12.0);
                    rate = 8;
                    double inter = interest(time, add.amt, rate);
                    printf("\n\nInterest every month on %d: %.2lf", add.deposit.day, inter);
                }
                else if(strcmpi(add.accType, "current") == 0)
                {
                    printf("\n\n You will not receive any interest. \n\n");
                }
            }
        }
    }
    fclose(ptr);
    if (test != 1)
    {
        printf("Record not found!..\n");
        printf("Press 0 to try again.\nPress 1 to return to main menu.\nPress 2 to exit.\n");
        printf("Enter your choice: ");
        scanf("%d", &menuExit);
        
        if (menuExit == 0)
        {
            checkDetails();
        }
        else if (menuExit == 1)
        {
            menu();
        }
        else if (menuExit == 2)
        {
            closeBnk();
        }
        else
        {
            printf("Invalid input. Teminating. \n");
            exit(1);
        }
    }
    else
    {
        printf("Press 1 to return to main menu\nPress 0 to exit.");
        printf("Enter your choice: ");
        scanf("%d", &menuExit);

        if (menuExit == 0)
        {
            closeBnk();
        } 
        else if (menuExit == 1)
        {
            menu();
        }
        else
        {
            printf("Invalid input. Teminating. \n");
            exit(1);
        }
    }
}

void closeBnk()
{
    printf("\n\n\n ...CLOSING... \n\n\n");
}
