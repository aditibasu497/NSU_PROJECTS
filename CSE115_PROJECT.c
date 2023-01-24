#include<stdio.h>
#include<time.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<conio.h>
#define MAX_YEAR 9999
#define MIN_YEAR 1900
#define MAX_SIZE_USER_NAME 50
#define MAX_SIZE_PASSWORD 50
//for personal info
#define MAX_NAME 50
#define MAX_ADDRESS 100
#define MAX_PHONE_NUMBER 50
#define BLOOD_TYPE 10
#define NATIONALITY 50
#define EMAIL 50
#define INSTITUTE_NAME 50
#define MAX_SIZE_USER_NAME 50
#define MAX_SIZE_PASSWORD 50
#define FILE_NAME "info.bin"
#define FILE_HEADER_SIZE sizeof(fileheader)
//structure to store data
typedef struct
{
    int yyyy;
    int mm;
    int dd;
    int new_day;
    int new_month;
    int new_year;
}date;
 typedef struct
{
    unsigned int serial_number;
    int acc_delete;
    char name[MAX_NAME];
    int age;
    char address[MAX_ADDRESS];
    char phone[MAX_PHONE_NUMBER];
    char blood_type[BLOOD_TYPE];
    char nationality[NATIONALITY];
    char email[EMAIL];
    char institution[INSTITUTE_NAME];
    int choice;
    date vaccination_date;   /*for the updated date */
    date second_vaccination_date;
}personal_info;
typedef struct
{
    char username[MAX_SIZE_USER_NAME];
    char password[MAX_SIZE_PASSWORD];
}fileheader;



void  printMessageCenter(const char *message)  /*This function prints the message in the middle of the head massage.
                                                                                     I have passed the message in this function as per the operation.*/
{
    int length=0;
    int pos=0;
    //calculate the spaces need to printf
    length=(78-strlen(message))/2;
    printf ("\t\t\t");
    for (pos=0; pos<length; pos++)
    {
        //printf space
        printf (" ");
    }
    printf ("%s", message);
}
void HEADMESSAGE(const char *message)  //It prints the message on the top of the console and prints the message as per operation.
{
    system("cls");
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############          Vaccination Manaegment System            ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printMessageCenter(message);
    printf("\n\t\t\t----------------------------------------------------------------------------");
}
void welcomeMessage()  /*This function displays the first welcomes screen of the
                               “Welcome to Vaccination Management system” and asks the user to press any key to access the library application*/
{
    printf("\n\n\n\n\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                 WELCOME                   =");
    printf("\n\t\t\t        =                   TO                      =");
    printf("\n\t\t\t        =              VACCINATION                  =");
    printf("\n\t\t\t        =               MANAGEMENT                  =");
    printf("\n\t\t\t        =                 SYSTEM                    =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf ("\t\t\t Group 3:\n");
    printf ("\t\t\t Ananna Saha(2211861042)\n");
    printf ("\t\t\t Ambia Ferdous Mimin(2211881642)\n");
    printf ("\t\t\t Aditi Basu(2212067042)\n");
    printf("\n\n\n\t\t\t Enter any key to continue.....");
    getch();

}

int valid_name(const char *validname)   /*checks the validity of the name input, name can only contain
                                                                    alphabets and spaces, returns 1 if the condition is false*/
{
    int valid_name=1;
    int length=0;
    int index=0;
    length=strlen(validname);
    for (index=0; index<length; index++)
    {
        if(!(isalpha(validname[index]))&& (validname[index]!='\n') && (validname[index]!=' '))
        {
            valid_name=0;
            break;
        }
    }
    return valid_name;
}
int valid_email_address(const char *validemail)   /*checks if the given email address is valid or not, email can
                                                                                  contain uppercase letters and spaces, returns 1 if condition is false*/
{
    int valid_email=1;
    int length=0;
    int index=0;
    length=strlen(validemail);
    for (index=0; index<length; index++)
    {
        if (isupper(validemail[index]))
        {
            valid_email=0;
            break;
        }
    }
    return valid_email;
}
int valid_phone_number(const char *validnumber)   /*Checks the validity of the phone number provided by the user
                                                                                        , phone numbers can only contain numbers and no space in between*/
{
    int valid_number=1;
    int length=0;
    int index=0;
    length=strlen(validnumber);
    for (index=0; index<length; index++)
    {
        if (!(isdigit(validnumber[index])) && (validnumber[index]!='\n'))
        {
            valid_number=0;
            break;
        }
    }
    return valid_number;
}


int check_leap_year(int year)    //Check if the provided year is a leap year or not
{
    return (((year%4==0) &&(year%100!=0)) || (year%400==0)); //returns 1 if data is valid
}
int valid_date(date *validDate)   //Checks the validity of the user provided  date
{
    if (validDate->yyyy> MAX_YEAR || validDate->yyyy<MIN_YEAR)
        return 0;
    if (validDate->mm<1 || validDate->mm>12)
        return 0;
    if (validDate->dd<1 || validDate->dd>31)
        return 0;
    if (validDate->mm==2)
    {
        if (check_leap_year(validDate-> yyyy))
           {
                return (validDate->dd <=29);
           }
            else
               {
                    return (validDate->dd <=28);
               }

    }
    if (validDate->mm=4 || validDate->mm==6 || validDate->mm==9 || validDate->mm==11)
        {
            return (validDate->dd<=30);
        }
    return 1;
}

//add personal infos
void add_personal_info(void)     /* This function opens the binary file in append mode and writes the name and the other personal
                                                        details(provided by the user) and stores them*/
{
    int days;
    personal_info add_personal_info={0};
    FILE *fp=NULL;
    int status=0;
    fp=fopen(FILE_NAME, "ab+");
    if (fp==NULL)
    {
        printf ("\n\t\tFile is not opened\n");
        exit(1);
    }
    HEADMESSAGE("REGISTER YOUR ACCOUT");
    printf ("\n\n\t\tEnter your details below: \n");
    printf ("\n\t\tSerial no: ");
    fflush(stdin);
    scanf ("%u", &add_personal_info.serial_number);
    do
    {
        printf ("\t\tName: ");
        fflush(stdin);
        fgets(add_personal_info.name, MAX_NAME, stdin);
        status=valid_name(add_personal_info.name);
        if (!status)
        {
            printf ("\n\t\tName contain Invalid character, please enter again");

        }
    }while(!status);
    printf  ("\t\tAge: ");
    scanf ("%d", & add_personal_info.age);
    printf ("\t\tGender:");
    printf ("\n\t\t 1.Male");
    printf ("\n\t\t 2.Female");
    printf (" \n");
    scanf ("%d", & add_personal_info.choice);
    fflush(stdin);
    printf ("\t\tAddress: ");
    fflush(stdin);
    scanf ("%s", add_personal_info.address);
    do
    {
        printf ("\t\tPhone number: ");
        fflush(stdin);
        fgets(add_personal_info.phone, MAX_PHONE_NUMBER, stdin);
        status=valid_phone_number(add_personal_info.phone);
        if (!status)
        {
            printf ("\n\t\tPhone number contain invalid character, please enter again");
        }
    }while(!status);
    do
    {
    printf ("\t\tEmail address: ");
    fflush(stdin);
    fgets(add_personal_info.email, EMAIL, stdin);
    status=valid_email_address(add_personal_info.email);
    if (!status)
    {
        printf ("\n\t\tEmail address contains invalid character, please try again");
    }
    }while(!status);
    printf ("\t\tBlood type: ");
    fflush(stdin);
    scanf ("%s", add_personal_info.blood_type);
    do
    {
        printf ("\t\tNationality: ");
        fflush(stdin);
        fgets(add_personal_info.nationality, NATIONALITY, stdin);
        status=valid_name(add_personal_info.nationality);
        if (!status)
        {
            printf ("\n\t\tNationality contains invalid character, please enter again");
        }
    }while(!status);

    do
    {
        printf ("\t\tInstitution Name: ");
        fflush(stdin);
        fgets(add_personal_info.institution, INSTITUTE_NAME, stdin);
        status=valid_name(add_personal_info.institution);
         if (!status)
        {
            printf ("\n\t\tInstitution name contains invalid character, please enter again");
        }
    }while(!status);

    do
    {
        printf ("\t\tEnter date in format(day/month/year): ");
        scanf ("%d/%d/%d", & add_personal_info.vaccination_date.dd, &add_personal_info.vaccination_date.mm, &add_personal_info.vaccination_date.yyyy);
        status=valid_date(& add_personal_info.vaccination_date);
        if (!status)
        {
            printf ("\n\t\tPlease enter a valid date");
        }
    }while(!status);
    //conditions for adding 30 days with the previously given date by the user
    if ((add_personal_info.vaccination_date.dd==30)  &&(add_personal_info.vaccination_date.mm==1) &&!(add_personal_info.vaccination_date.yyyy%4==0) &&(add_personal_info.vaccination_date.yyyy%100!=0)||(add_personal_info.vaccination_date.yyyy==0))
    {
        add_personal_info.second_vaccination_date.new_day=1;
         add_personal_info.second_vaccination_date.new_month=3;
          add_personal_info.second_vaccination_date.new_year= add_personal_info.vaccination_date.yyyy;
        }
    else if (( add_personal_info.vaccination_date.dd==31) &&add_personal_info.vaccination_date.mm==1 && !(add_personal_info.vaccination_date.yyyy%4==0) &&(add_personal_info.vaccination_date.yyyy%100!=0) ||(add_personal_info.vaccination_date.yyyy%400==0))
    {
        add_personal_info.second_vaccination_date.new_day=2;
        add_personal_info.second_vaccination_date.new_month=3;
        add_personal_info.second_vaccination_date.new_year= add_personal_info.vaccination_date.yyyy;

    }
    else if ( add_personal_info.vaccination_date.dd==31 &&  add_personal_info.vaccination_date.mm==1 && ( add_personal_info.vaccination_date.yyyy%4==0) && ( add_personal_info.vaccination_date.yyyy%100!=0)||( add_personal_info.vaccination_date.yyyy%400==0))
    {
        add_personal_info.second_vaccination_date.new_day=1;
        add_personal_info.second_vaccination_date.new_month=3;
        add_personal_info.second_vaccination_date.new_year= add_personal_info.vaccination_date.yyyy;


    }
    else if (add_personal_info.vaccination_date.mm==1 ||add_personal_info.vaccination_date.mm==3||add_personal_info.vaccination_date.mm==5||add_personal_info.vaccination_date.mm==7||add_personal_info.vaccination_date.mm==8||add_personal_info.vaccination_date.mm==10)
    {
        add_personal_info.second_vaccination_date.new_day= add_personal_info.vaccination_date.dd-1;
         add_personal_info.second_vaccination_date.new_month=add_personal_info.vaccination_date.mm+1;
          add_personal_info.second_vaccination_date.new_year= add_personal_info.vaccination_date.yyyy;
    }
    else if (add_personal_info.vaccination_date.mm==4 ||add_personal_info.vaccination_date.mm==6||add_personal_info.vaccination_date.mm==9||add_personal_info.vaccination_date.mm==11)
    {
        add_personal_info.second_vaccination_date.new_day= add_personal_info.vaccination_date.dd;
         add_personal_info.second_vaccination_date.new_month=add_personal_info.vaccination_date.mm+1;
          add_personal_info.second_vaccination_date.new_year= add_personal_info.vaccination_date.yyyy;
    }
    else if (add_personal_info.vaccination_date.mm==2 &&!(add_personal_info.vaccination_date.yyyy%4==0)&&(add_personal_info.vaccination_date.yyyy%100!=0)||(add_personal_info.vaccination_date.yyyy%400==0))
    {
        add_personal_info.second_vaccination_date.new_day=add_personal_info.vaccination_date.dd+2;
        add_personal_info.second_vaccination_date.new_month=add_personal_info.vaccination_date.mm+1;
        add_personal_info.second_vaccination_date.new_year= add_personal_info.vaccination_date.yyyy;

    }
    else if (add_personal_info.vaccination_date.mm==12)
    {
        add_personal_info.second_vaccination_date.new_day=add_personal_info.vaccination_date.dd-1;
        add_personal_info.second_vaccination_date.new_month=1;
        add_personal_info.second_vaccination_date.new_year= add_personal_info.vaccination_date.yyyy+1;

    }
    else if (add_personal_info.vaccination_date.mm==2 && ((add_personal_info.vaccination_date.yyyy%4==0) &&(add_personal_info.vaccination_date.yyyy%100!=0) ||(add_personal_info.vaccination_date.yyyy%400==0)))
    {
          add_personal_info.second_vaccination_date.new_day=add_personal_info.vaccination_date.dd+1;
          add_personal_info.second_vaccination_date.new_month=add_personal_info.vaccination_date.mm+1;
          add_personal_info.second_vaccination_date.new_year= add_personal_info.vaccination_date.yyyy;

    }

    else
    {
        add_personal_info.second_vaccination_date.new_day=add_personal_info.vaccination_date.dd;
         add_personal_info.second_vaccination_date.new_month=add_personal_info.vaccination_date.mm+1;
          add_personal_info.second_vaccination_date.new_year= add_personal_info.vaccination_date.yyyy;

    }
    printf ("\t\tYour next date of vaccination is %d/%d/%d", add_personal_info.second_vaccination_date.new_day,add_personal_info.second_vaccination_date.new_month, add_personal_info.second_vaccination_date.new_year);
  //conditions for taking vaccines according to age
     if (10<=add_personal_info.age && add_personal_info.age<=18)
        printf ("\n\t\tVaccine name: Pfizer");
       else if (19<=add_personal_info.age && add_personal_info.age <=30)
        printf("\n\t\tVaccine name: Moderna");
       else if (31<=add_personal_info.age &&add_personal_info.age <=40)
        printf ("\n\t\tVaccine name: Astra-zeneca");
        else if (41<=add_personal_info.age &&add_personal_info.age <=50)
        printf ("\n\t\tVaccine name:Sinopharm");
       else if (51<=add_personal_info.age &&add_personal_info.age <=60)
        printf ("\n\t\tVaccine name:Sputnik V");
       else if (61<=add_personal_info.age &&add_personal_info.age <=70)
        printf ("\n\t\tVaccine name: Sinovac");
       else
        printf ("\n\t\tCovaxin");
    fwrite(&add_personal_info, sizeof (add_personal_info), 1, fp);


    fclose(fp);


}
//search data
void search_data(void)  /* This function opens the binary file in reading mode and asks the user to enter the  name which wants to search.
                                                   If the name is not previously registered in the list, it shows the message find in records.*/
{
    int found=0;

    char name[MAX_NAME]={0};
    personal_info add_personal_info={0};
    FILE *fp=NULL;
    int status=0;
    fp=fopen(FILE_NAME, "rb");
    if (fp==NULL)
    {
        printf ("file not found\n");
        exit(1);
    }
    HEADMESSAGE("SEARCH YOUR ACCOUNT INFORMATION");

   printf ("\n\n\t\tEnter your name to search: ");
   fflush(stdin);
   fgets(name,MAX_NAME , stdin);
   while(fread(&add_personal_info, sizeof (add_personal_info), 1, fp))
   {

       if (!strcmp(add_personal_info.name, name))
       {
           found=1;
           break;

       }
}
   if (found)
   {
       printf ("\t\tSerial no: %u\n", add_personal_info.serial_number);
       printf ("\t\tName:%s\n", add_personal_info.name);
       printf ("\t\tAge:%d\n", add_personal_info.age);

       printf ("\t\tPhone: %s\n", add_personal_info.phone);
       printf ("\t\tBlood type:%s\n", add_personal_info.blood_type);
       switch(add_personal_info.choice)
       {
       case 1:
        printf ("\t\tGender: Male\n");
        break;
       case 2:
        printf ("\t\tGender: Female\n");
        break;
       default:
        printf ("\n\t\tInvalid input, try again");
       }
        printf ("\t\tAddress: %s\n", add_personal_info.address);
        printf ("\t\tPhone: %s\n", add_personal_info.phone);
        printf ("\t\tEmail: %s\n", add_personal_info.email);
        printf ("\t\tBlood Type:%s\n",add_personal_info.blood_type);
        printf ("\t\tNationality:%s\n", add_personal_info.nationality);
       printf ("\t\tInstitution: %s\n", add_personal_info.institution);
       printf ("\t\tFirst dose of vaccination date: %d/%d/%d\n", add_personal_info.vaccination_date.dd,add_personal_info.vaccination_date.mm,add_personal_info.vaccination_date.yyyy);
       printf ("\t\tSecond dose of vaccination date: %d/%d/%d\n", add_personal_info.second_vaccination_date.new_day, add_personal_info.second_vaccination_date.new_month, add_personal_info.second_vaccination_date.new_year);
       if (10<=add_personal_info.age && add_personal_info.age<=18)
        printf ("\t\tVaccine name: Pfizer\n");
       else if (19<=add_personal_info.age && add_personal_info.age <=30)
        printf("\t\tVaccine name: Moderna\n");
       else if (31<=add_personal_info.age &&add_personal_info.age <=40)
        printf ("\t\tVaccine name: Astra-zeneca\n");
        else if (41<=add_personal_info.age &&add_personal_info.age <=50)
        printf ("\t\tVaccine name:Sinopharm\n");
       else if (51<=add_personal_info.age &&add_personal_info.age <=60)
        printf ("\t\tVaccine name:Sputnik V\n");
       else if (61<=add_personal_info.age &&add_personal_info.age <=70)
        printf ("\t\tVaccine name: Sinovac\n");
       else
        printf ("\t\tVaccine name: Covaxin\n");
   }
   else
   {
       printf ("\n No  record");
   }
   fclose (fp);

   printf ("\n\t\tPress any key to return to main menu");
   getchar();

}


void view_account_info()    /* It opens the file in reading mode and read and display all the stored personal details
                                          . If there is no records available in the records, then it displays the message record is empty.*/
{
    int found = 0;
    char name[MAX_NAME] = {0};
    personal_info add_personal_info = {0};
    FILE *fp = NULL;
    int status = 0;
    unsigned int count = 1;
    HEADMESSAGE("VIEW ALL DETAILS AT ONE LIST");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("Facing issue while reading file\n");
        exit(1);
    }
    while (fread (&add_personal_info, sizeof(add_personal_info), 1, fp))
    {
        printf("\t\t\tNumber: %d\n",count);
        printf("\t\t\tSerial number: %u\n",add_personal_info.serial_number);
        printf("\t\t\tName: %s\n",add_personal_info.name);
        printf("\t\t\tAge: %d\n",add_personal_info.age);
        printf ("\t\t\tAdress: %s\n", add_personal_info.address);
        printf ("\t\t\tPhone no:%s\n",add_personal_info.phone);
        printf ("\t\t\t E-mail:%s\n", add_personal_info.email);
        printf ("\t\t\t Blood Type:%s\n", add_personal_info.blood_type);
        printf ("\t\t\tNationality:%s\n",add_personal_info.nationality);
        printf ("\t\t\tInstitution Name:%s\n", add_personal_info.institution);
        printf ("\t\t\tFirst dose of Vaccination date: %d/%d/%d\n", add_personal_info.vaccination_date.dd,add_personal_info.vaccination_date.mm,add_personal_info.vaccination_date.yyyy);
        printf ("\t\t\tSecond dose of vaccination date: %d/%d/%d\n", add_personal_info.second_vaccination_date.new_day, add_personal_info.second_vaccination_date.new_month, add_personal_info.second_vaccination_date.new_year);
        found = 1;
        ++count;
    }
    fclose(fp);
    if(!found)
    {
        printf("\n\t\t\tNo Record");
    }
    printf("\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}
void delete_account()    /* This function asks the serial number from the user to delete.
                                       In this function, I am creating a temporary binary file and copy all the data from the existing file
                                        In the last renamed the temporary bin file with an existing binary file.*/
{
    int found = 0;
    int deleteaccount = 0;
    fileheader fileHeaderInfo = {0};
    char name[MAX_NAME] = {0};
    personal_info add_personal_info = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    int status = 0;
    HEADMESSAGE("Delete Your Account");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","wb");
    if(tmpFp == NULL)
    {
        fclose(fp);
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, tmpFp);
printf("\n\t\t\tEnter Serial no to delete:");
    scanf("%d",&deleteaccount);
    while (fread (&add_personal_info, sizeof(add_personal_info), 1, fp))
    {
        if(add_personal_info.serial_number != deleteaccount)
        {
            fwrite(&add_personal_info,sizeof(add_personal_info), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    (found)? printf("\n\t\t\tRecord deleted successfully....."):printf("\n\t\t\tRecord not found");
    fclose(fp);
    fclose(tmpFp);
    remove(FILE_NAME);
    rename("temp.bin",FILE_NAME);
}
void update_password(void)     /*This function opens the file in rb+ mode (reading and writing). It asks the user for the new username and password.
                                                       After taking the password and username it closes the application.
                                                        Now user can use the application with a new password and username.*/
{
    fileheader fileHeaderInfo = {0};
    FILE *fp = NULL;
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    HEADMESSAGE("Update Credential");
    fp = fopen(FILE_NAME,"rb+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    if (fseek(fp,0,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        exit(1);
    }
    printf("\n\n\t\t\tNew Username:");
    fflush(stdin);
    fgets(userName,MAX_SIZE_USER_NAME,stdin);
 printf("\n\n\t\t\tNew Password:");
    fflush(stdin);
    fgets(password,MAX_SIZE_PASSWORD,stdin);
    strncpy(fileHeaderInfo.username,userName,sizeof(userName));
    strncpy(fileHeaderInfo.password,password,sizeof(password));
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    printf("\n\t\t\tYour Password has been changed successfully");
    printf("\n\t\t\tRe-enter your new password again to confirm:");
    fflush(stdin);
    getchar();
    exit(1);
}
void menu()    /*This function displays the main menu and asks the user to select the option.
                          If the user selects 0, then the application will close.*/
{
    int choice = 0;
    do
    {
        HEADMESSAGE("Main Menu");
        printf("\n\n\n\t\t\t1.Account Registration");
        printf("\n\t\t\t2.Search Account");
        printf("\n\t\t\t3.View Account Info");
        printf("\n\t\t\t4.Delete Account");
        printf("\n\t\t\t5.Change Password");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            add_personal_info();
            break;
        case 2:
            search_data();
            break;
        case 3:
            view_account_info();
            break;
        case 4:
            delete_account();

            break;
        case 5:
            update_password();
            break;
            case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }                                            //Switch Ended
    }
    while(choice!=0);                                        //Loop Ended
}
void login()  //this function takes input of the username and passsword and matches them with the default password
{
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    int L=0;
    fileheader fileHeaderInfo = {0};
    FILE *fp = NULL;
    HEADMESSAGE("Login");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    do
    {
        printf("\n\n\n\t\t\t\tUsername:");
        fgets(userName,MAX_SIZE_USER_NAME,stdin);
printf("\n\t\t\t\tPassword:");
        fgets(password,MAX_SIZE_PASSWORD,stdin);
        if((!strcmp(userName,fileHeaderInfo.username)) && (!strcmp(password,fileHeaderInfo.password)))
        {
            menu();
        }
        else
        {
            printf("\t\t\t\tLogin Failed Enter Again Username & Password\n\n");
            L++;
        }
    }
    while(L<=3);
    if(L>3)
    {
        HEADMESSAGE("Login Failed");
        printf("\t\t\t\tSorry,Unknown User.");
        getch();
        system("cls");
    }
}

int isFileExists(const char *path)   /*This function verifies that a file has been created or not.
                                                       If the file exists, the function return 1 otherwise returns 0.*/
{
    // Try to open file
    FILE *fp = fopen(path, "rb");
    int status = 0;
    // If file does not exists
    if (fp != NULL)
    {
        status = 1;
        // File exists hence close file
        fclose(fp);
    }
    return status;
}
void init()     /*This function creates the file if not exist and copies the
                    default password (“password”) in file header structure.*/
{
    FILE *fp = NULL;
    int status = 0;
    const char defaultUsername[] ="password\n";
    const char defaultPassword[] ="password\n";
    fileheader fileHeaderInfo = {0};
    status = isFileExists(FILE_NAME);
    if(!status)
    {
        //create the binary file
        fp = fopen(FILE_NAME,"wb");
        if(fp != NULL)
        {
            //Copy default password
            strncpy(fileHeaderInfo.password,defaultPassword,sizeof(defaultPassword));
            strncpy(fileHeaderInfo.username,defaultUsername,sizeof(defaultUsername));
            fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
            fclose(fp);
        }
    }
}
int main(void)     //the main function
{
    init();
    welcomeMessage();
    HEADMESSAGE("Vaccination Management System");
    login();

    return 0;
}

