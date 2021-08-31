#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>
#include<errno.h>
#include<limits.h>

#define code 120
#define size 100

//FUNCTIONS
void printdata(char un[size]);
int day(int y,int dn);
int daynum(int d,int m, int y);
void input(char un[size]);
int password(char un[size]);
int checkun(char un[size]);
void creatpassword(char un[size]);
void encrypt(char pswd[size]);
void decrypt(char pswd[size]);
void welcome(char un[size]);
void date(char un[size]);
int changePass(char un[size]);
int settings(char un[size]);
int theam(char un[size]);
void setTime();
void menu(char un[size]);
void encryptFile(char un[size], char text[500]);
void decryptFile(char un[size], char text[500]);
int deleteFiles(char un[size]);

//======================================================================================

int main()
{
    int tmp,pass,chun,count=1,x,count1=0,tth;
    char un[size];
    for(;;)
    {
    printf("\n\n*******  WELCOME !!  *******\n\n");
    printf("Please Enter User Name : ");
    scanf("%s",un);
    welcome(un);
    for(;;)
    {
        chun=checkun(un);
        if(chun==1)
        {
            break;
        }
        if(chun==0)
        {
        	printf("Close the program only after creating and saving your password!!\n");
            printf("You have not created password \n");
            creatpassword(un);
        }
    }
    tth=theam(un);
    if(tth)
    {
        system("COLOR 70");
    }
    for(;;)
    {
        if(count>3)
        {
        	
            x=changePass(un);
            if(x==0)
            {
                welcome(un);
            }
            else
            {
                return 0;
            }
        }
        printf("\n\nPlease Enter The Password : ");
        pass=password(un);
        if(pass==0)
        {
            welcome(un);
            count = 0;
            printf("\n\nPassword Matched  !!  WELCOME !!!!! \n\n");
            break;
        }
        if(pass==1)
        {
            welcome(un);
            printf("\n\nYou Have Entered Wrong Password Please Try Again :(");
            count++;
        }
    }
    menu(un);
	}
}
//=======================================================================================

int daynum(int d,int m,int y)
{
    int arr1[12]= {0,31,59,90,120,151,181,212,243,273,304,334};

    int dn;
    if(y%4==0 && y%100!=0)
    {
        if(m>2)
        {
            dn=(arr1[m-1]+d +1);
        }
        else
        {
            dn=(arr1[m-1]+d);
        }
    }
    else
    {
        if(y%400==0)
        {
            dn=(arr1[m-1]+d +1);
        }
        else
        {
            dn=(arr1[m-1]+d);
        }
    }
    return dn;
}

//====================================================================================================
int day(int y,int dn)
{
    int tmp1=1,i;
    int y1=y-2000;
    if(y>2001)
    {
        for(i=2; i<=y1; i++)
        {
            tmp1++;
            if((i-1)%4==0)
            {
                tmp1++;
            }
            if(tmp1>6)
            {
                tmp1=tmp1-7;
            }
        }
    }
    dn=(dn-1)%7;
    tmp1=tmp1+dn;
    if(tmp1>6)
    {
        tmp1=tmp1-7;
    }
    return tmp1;
}

//==========================================================================================================
void printdata(char un[size])
{

    welcome(un);
    FILE *ptr;
    int len1=strlen(un),len,i,dd,mm,yy,DN,D;
    char text[size];

    date( un);
    len=strlen(un);
    un[len]='.';
    un[len+1]='t';
    un[len+2]='x';
    un[len+3]='t';
    un[len+4]='\0';
    ptr=fopen(un,"r");
    if(ptr==NULL)
    {
        printf("File is empty Creating a file...");
        sleep(2); // sleep for 3 seconds
        un[len1] = '\0';
        input(un);
    }
    else
    {

        printf("\n\n");
        while(fgets(text,sizeof(text),ptr))
        {
            decryptFile(un,text);
            printf("%s",text);
        }
        fclose(ptr);
    }
    un[len1]='\0';
}

//============================================================================================


void input(char un[size])
{

    welcome(un);
    FILE *ptr;
    int len,len1,l1,i;
    char name[size],text[size];
    len=strlen(un);
    len1=strlen(un);

    date(un);
    len=strlen(un);
    un[len]='.';
    un[len+1]='t';
    un[len+2]='x';
    un[len+3]='t';
    un[len+4]='\0';

    ptr = fopen (un,"r");
    if(ptr==NULL)
    {
        ptr = fopen(un,"w");
    }
    else
    {
        printf("File has content adding the content......\n");
        while(fgets(text,sizeof(text),ptr))
        {
            decryptFile(un,text);
            printf("%s",text);
        }
        ptr = fopen(un,"a");
    }
    printf("--------------------\n");
    printf("(Enter 'Thank you' on new line to end writing)\n");
    printf("\nEnter the text : \n");

    for(;;)
    {
        gets(text);
        int flag = strcmp(text,"Thank you");
        if(!flag)
        {
            break;
        }
        encryptFile(un,text);
        fputs(text, ptr);
        fputs("\n", ptr);

    }

    fclose (ptr);
    //encryptFile(un);
    un[len1]='\0';
    welcome(un);
}

//=================================================================================================


int password(char un[size])
{
    FILE *ptr=NULL;
    int pass,len=strlen(un);
    char entpas[size],orgpas[size];
    un[len]='.';
    un[len+1]='t';
    un[len+2]='x';
    un[len+3]='t';
    un[len+4]='\0';

    scanf("%s",entpas);
    ptr=fopen(un,"r");

    fscanf(ptr,"%s", orgpas);
    //printf("%s",orgpas);
    decrypt(orgpas);

    pass=strcmp(orgpas,entpas);
    fclose(ptr);
    un[len]='\0';

    if(pass==0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
//========================================================================================================
int checkun(char un[size])
{
    FILE *ptr=NULL;
    int len=strlen(un),tmp;
    un[len]='.';
    un[len+1]='t';
    un[len+2]='x';
    un[len+3]='t';
    un[len+4]='\0';
    ptr=fopen(un,"r");
    if(ptr==NULL)
    {
        tmp=0;
    }
    else
    {
        tmp=1;
    }
    fclose(ptr);
    un[len]='\0';
    return tmp;
}
//======================================================================
void creatpassword(char un[size])
{
	int flag1 =0 ,flag2 = 0;
    char pswd[size],dob[50],i,emailID[size],emailID2[size];
    int len=strlen(un),l1,dd,mm,yy;
    un[len]='.';
    un[len+1]='t';
    un[len+2]='x';
    un[len+3]='t';
    un[len+4]='\0';
    FILE *ptr=NULL;
    ptr=fopen(un,"w");
    printf("\nPassword size should be less than 100 charcters \nShould contain special charcters and number\nCreating Your Password .Enter Your Password : ");
    pass:scanf("%s",pswd);
    for(i=0;i<strlen(pswd);i++)
    {
    	if(isdigit(pswd[i]))
    	{
    		flag1 ++;
		}
		if(!isalpha(pswd[i]))
		{
			if(!isdigit(pswd[i]))
			{
				flag2 ++;
			}
		}
	}
	if(flag1>0&&flag2>0)
	{
		printf("Strong Password\n");
	}
	else
	{
		printf("Enter a Strong password with special characters and numbers:");
		goto pass;
	}
    encrypt(pswd);

    for(;;)
    {
        printf("Enter Your Birth date :\n");
        printf("Date  : ");
        scanf("%d",&dd);
        printf("month : ");
        scanf("%d",&mm);
        printf("year  : ");
        scanf("%d",&yy);
        if(yy<2000)
        {
            printf("You have Entered Invalid date(year must be after 2000) . Please Enter Again\n ");
            continue;
        }
        else
        {
            if(mm>12||mm<1)
            {
                printf("The Date You Have Entered Is Invalid (month is improper ) . Please Enter Again\n ");
                continue;
            }
            else
            {
                if(mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12)
                {
                    if(dd<1 || dd>31)
                    {
                        printf("The Date You Have Entered Is Invalid (This month can have 1 to 31 Dates ) . Please Enter Again\n ");
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    if(mm==4 || mm== 6 	|| mm== 9 || mm==11 )
                    {
                        if(dd<1 || dd>30)
                        {
                            printf("The Date You Have Entered Is Invalid (This month can have 1 to 30 Dates ) . Please Enter Again\n ");
                            continue;
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        if(yy%4)
                        {
                            if(dd<1 || dd>28)
                            {
                                printf("The Date You Have Entered Is Invalid (This month can have 1 to 28 Dates ) . Please Enter Again\n ");
                                continue;
                            }
                            else
                            {
                                break;
                            }
                        }
                        else
                        {
                            if(dd<1 || dd>29)
                            {
                                printf("The Date You Have Entered Is Invalid (This month can have 1 to 29 Dates ) . Please Enter Again\n ");
                                continue;
                            }
                        }
                    }
                }

            }
        }
    }
    l1=strlen(pswd);
    pswd[l1]=' ';
    pswd[l1+1]='0';
    l1=l1+2;
    pswd[l1+0]=dd/10 + 48;
    pswd[l1+1]=dd%10 + 48;
    pswd[l1+2]=mm/10 + 48;
    pswd[l1+3]=mm%10 + 48;
    pswd[l1+4]=yy/1000 + 48;
    pswd[l1+5]=yy/100-(yy/1000)*10 + 48;
    pswd[l1+6]=yy/10 - (yy/100)*10 + 48;
    pswd[l1+7]=yy%10 + 48;
    
    //welcome(un);
    /*email:printf("Enter your emailID:");
    scanf("%s",emailID);
    printf("Enter again to confirm:");
    scanf("%s",emailID2);
    if(!strcmp(emailID,emailID2))
    {
    	strcat(pswd," ");
    	strcat(pswd,emailID);
	}
	else
	{
		goto email;
	}*/
	fputs(pswd,ptr);
    fclose(ptr);
    un[len]='\0';
    welcome(un);
    printf("Your Password Has Been Saved Successfully !!! \n\n");
}
//================================================================================
void encrypt(char pswd[size])
{
    int len = strlen(pswd);
    int i;

    for(i=0; i<len; i++)
    {
        if(pswd[i]=='\n')
        {

        }
        else
        {
            //code = (1 + len)/2;
            pswd[i] = pswd[i]+ code;
        }
    }
}
//==========================================================================
void decrypt(char pswd[size])
{
    int len = strlen(pswd);
    int i;

    for(i=0; i<len; i++)
    {
        if(pswd[i]=='\n')
        {

        }
        else
        {
            //code = (1 + len)/2;
            pswd[i] = pswd[i] - code;
        }
    }

}
//==================================================================================
void welcome(char un[size])
{
    system("cls");
    printf("\n\n___ * ___ * ___ * ___ * ___ * ___ * ___ * ___ *___\n\n\n\n");
    printf("\n\n___ * ___ *  Personal Diary V5.0  * ___ * ___\n\n\n\n");
    printf("User:%s",un);
    setTime();
    printf("\n\n");
}
//=====================================================================================
void date(char un[size])
{
    int dd,mm,yy,len=strlen(un),DN,D,yyy;
    for(;;)
    {
        printf("Enter date :\n");
        printf("Date  : ");
        scanf("%d",&dd);
        printf("month : ");
        scanf("%d",&mm);
        printf("year  : ");
        scanf("%d",&yy);
        if(yy<2000)
        {
            printf("You have Enterd Invalid date(year must be after 2000) . Please Enter Aagain\n ");
            continue;
        }
        else
        {
            if(mm>12||mm<1)
            {
                printf("The Date You Have Enterd Is Invalid (month is improper ) . Please Enter Aagain\n ");
                continue;
            }
            else
            {
                if(mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12)
                {
                    if(dd<1 || dd>31)
                    {
                        printf("The Date You Have Entered Is Invalid (This month can have 1 to 31 Dates ) . Please Enter Again\n ");
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    if(mm==4 || mm== 6 	|| mm== 9 || mm==11 )
                    {
                        if(dd<1 || dd>30)
                        {
                            printf("The Date You Have Entered Is Invalid (This month can have 1 to 30 Dates ) . Please Enter Again\n ");
                            continue;
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        if(yy%4)
                        {
                            if(dd<1 || dd>28)
                            {
                                printf("The Date You Have Entered Is Invalid (This month can have 1 to 28 Dates ) . Please Enter Again\n ");
                                continue;
                            }
                            else
                            {
                                break;
                            }
                        }
                        else
                        {
                            if(dd<1 || dd>29)
                            {
                                printf("The Date You Have Entered Is Invalid (This month can have 1 to 29 Dates ) . Please Enter Again\n ");
                                continue;
                            }
                        }
                    }
                }

            }
        }
    }

    yyy=yy;
    un[len]=dd/10 + '0';
    un[len+1]=dd%10 + '0';
    un[len+2]='.';
    un[len+3]=mm/10 + '0';
    un[len+4]=mm%10 + '0';
    un[len+5]='.';
    un[len+6]=yy/1000 + '0';
    yy=yy%1000;
    un[len+7]=yy/100 + '0';
    yy=yy%100;
    un[len+8]=yy/10 + '0';
    yy=yy%10;
    un[len+9]=yy + '0';
    un[len+10]='\0';
    DN=daynum(dd,mm,yyy);
    D=day(yyy,DN);
    switch (D)
    {
    case 0:
        printf("Day : Sunday.");
        break;
    case 1:
        printf("Day : Monday.");
        break;
    case 2:
        printf("Day : Tuesday.");
        break;
    case 3:
        printf("Day : Wednesday.");
        break;
    case 4:
        printf("Day : Thursday.");
        break;
    case 5:
        printf("Day : Friday.");
        break;
    case 6:
        printf("Day : Saturday.");
        break;
    }
}
//========================================================================================================================
int changePass(char un[size])
{
    int x,dd,mm,yy,j,i,l1=0,len=strlen(un);
    char dob[size],endob[size],ddmmyy[size],pswd[size];
    FILE *ptr=NULL;
    un[len]='.';
    un[len+1]='t';
    un[len+2]='x';
    un[len+3]='t';
    un[len+4]='\0';

    printf("Enter Your Date of Birth : \n");
    printf("Date  : ");
    scanf("%d",&dd);
    printf("Month : ");
    scanf("%d",&mm);
    printf("Year  : ");
    scanf("%d",&yy);
    endob[0]=dd/10 + 48;
    endob[1]=dd%10 + 48;
    endob[2]=mm/10 + 48;
    endob[3]=mm%10 + 48;
    endob[4]=yy/1000 + 48;
    endob[5]=yy/100-(yy/1000)*10 + 48;
    endob[6]=yy/10 - (yy/100)*10 + 48;
    endob[7]=yy%10 + 48;


    ptr=fopen(un,"r");
    fgets(dob,sizeof(dob),ptr);
    for(i=0;; i++)
    {
        if(dob[i]==' ')
        {
            i=i+2;
            break;
        }
    }
    for(j=0; j<8; i++,j++)
    {
        if(dob[i]=='\0')
        {
            ddmmyy[j]='\0';
            break;
        }
        ddmmyy[j]=dob[i];
        ddmmyy[8]='\0';
    }

    x=strcmp(ddmmyy,endob);
    un[len]='\0';
    fclose(ptr);
    if(x==0)
    {
        printf("* Date of birth matched ! *\n\n");
        creatpassword(un);
        return 0;
    }
    else
    {
        return 1;
    }

}
//============================================================================
int settings(char un[size])
{
    int ch,cht,tth,dF,isDeleted = 0;
    char unn[size],x;
    char pswd[size];
    int i;
    int len=strlen(un);
    FILE *ptr=NULL;
    strcpy(unn,un);
    unn[len]='.';
    unn[len+1]='t';
    unn[len+2]='x';
    unn[len+3]='t';
    unn[len+4]='\0';


    for(;;)
    {
        welcome(un);
        printf("Enter \n 1. For change Password \n 2. For change theme \n 3. For Deleting all your files \n 0. For exit settings \n\nEnter your choice : ");
        scanf("%d",&ch);
        if(ch>=0 && ch<4)
        {
            if(ch == 0)
            {
                welcome(un);
                return ;
            }
            break;
        }
        else
        {
            printf("\n ## Sorry You have Entered wrong choice please try again ##\n");
        }

    }
    switch (ch)
    {
    case 1:
        creatpassword(un);
        break;
    case 2:
        ptr=fopen(unn,"r");
        fgets(pswd,sizeof(pswd),ptr);
        fclose(ptr);
        ptr=fopen(unn,"w");
        for(i=0;; i++)
        {
            if(pswd[i]==' ')
            {
                i=i+1;
                break;
            }
        }
        for(;;)
        {
            printf("Enter The choice of Theme \n 0. for dark \n 1. for light \nEnter choice : ");
            scanf("%d",&cht);
            if(cht<2 && cht>=0)
            {
                break;
            }
            else
            {
                printf("You have Entered wrong choice please try again \n");
            }

        }

        pswd[i]=cht+48;
        fputs(pswd,ptr);
        fclose(ptr);
        unn[len]='\0';
        welcome(un);
        break;
    case 3:
        dF = deleteFiles(un);
        if(dF == 0)
        {
            printf("\nSuccessful in deleting Files.");
            sleep(3);
            system("cls");
            //main();
            isDeleted = 1;
            break;
        }
        else if(dF == 2)
        {
            printf("Deletion cancelled!!");
        }
        else
        {
            printf("\nSomething Went wrong.");
        }
        sleep(2);
        break;
    }
    tth=theam(un);
    if(tth)
    {
        system("COLOR 70");
    }
    else
    {
        system("COLOR 07");
    }
	    if(isDeleted)
	    {
	    	return isDeleted;
		}
		else
		{
	    	settings(un);
		}
}
//=============================================================================================
int theam(char un[size])
{
    int x,len=strlen(un),i;
    char unn[size],pswd[size];
    FILE *ptr=NULL;
    strcpy(unn,un);
    unn[len]='.';
    unn[len+1]='t';
    unn[len+2]='x';
    unn[len+3]='t';
    unn[len+4]='\0';
    ptr=fopen(unn,"r");
    fgets(pswd,sizeof(pswd),ptr);
    fclose(ptr);
    unn[len]='\0';
    for(i=0;; i++)
    {
        if(pswd[i]==' ')
        {
            i=i+1;
            break;
        }
    }
    x=pswd[i]-'0';
    return x;

}
//===============================================================================================
void setTime()
{
    // variables to store the date and time components
    int hours, minutes, seconds, day, month, year;

    // `time_t` is an arithmetic time type
    time_t now;

    // Obtain current time
    // `time()` returns the current time of the system as a `time_t` value
    time(&now);

    // Convert to local time format and print to stdout
    //printf("Today is %s", ctime(&now));

    // localtime converts a `time_t` value to calendar time and
    // returns a pointer to a `tm` structure with its members
    // filled with the corresponding values
    struct tm *local = localtime(&now);

    hours = local->tm_hour;         // get hours since midnight (0-23)
    minutes = local->tm_min;        // get minutes passed after the hour (0-59)
    seconds = local->tm_sec;        // get seconds passed after a minute (0-59)

    day = local->tm_mday;            // get day of month (1 to 31)
    month = local->tm_mon + 1;      // get month of year (0 to 11)
    year = local->tm_year + 1900;   // get year since 1900

    // print local time
    if (hours < 12)
    {
        printf("\nTime is %02d:%02d:%02d am\n", hours, minutes, seconds);
    }
    else
    {
        printf("\nTime is %02d:%02d:%02d pm\n", hours - 12, minutes, seconds);
    }
    printf("Date is: %02d/%02d/%d\n", day, month, year);
}
//=====================================================================================
void menu(char un[size])
{

    int tth,tmp,isDeleted;
    for(;;)
    {
        tth=theam(un);
        if(tth)
        {
            system("COLOR 70");
        }
        else
        {
            system("COLOR 07");
        }
        tmp=5;
        printf("\n\n  == /  == /  == /  == /  == /  == /  == /  == /  == /  == \n\n\n");
        printf(" For Writing Text Please Enter 1 \n For Reading Text Please Enter 2 \n To open settings Please Enter 3 \n To exit from Diary Please Enter 4\n\n");
        printf(" Please Enter Your Choice Here : ");
        scanf("%d",&tmp);
        if(tmp>4 || tmp<1)
        {
            printf("\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\n");
            printf(" You Have Entered Wrong Input Please Try Again \n Please Enter Your Response :");
            scanf("%d",&tmp);
        }
        printf("\n\n=========================================\n\n");

        if(tmp==4)
        {
            welcome(un);
            printf("\n\n*******  THANK YOU  !!  *******\n\n");
            printf("\n\n*******  DIARY EXITED!  *******\n\n");
            exit(0);
        }
        else
        {
            if(tmp==1)
            {
                printf("\n\n================================================================================================================================\n\n");

                if(tth)
                {
                    system("COLOR 70");
                }
                input(un);
                if(tth)
                {
                    system("COLOR 70");
                }
                welcome(un);

            }
            if(tmp==2)
            {
                printf("\n\n================================================================================================================================\n\n");
                if(tth)
                {
                    system("COLOR 70");
                }
                printdata(un);
                if(tth)
                {
                    system("COLOR 70");
                }
                printf("\n\n================================================================================================================================\n\n");
            }
            if(tmp==3)
            {
                printf("\n\n================================================================================================================================\n\n");
                if(tth)
                {
                    system("COLOR 70");
                }
                
                isDeleted = settings(un);
                /*if(tth)
                {
                    system("COLOR 70");
                }*/
            }
        }
        if(isDeleted == 1)
        {
        	isDeleted =0;
        	break;
		}
    }
}
//=======================================================================================================
void encryptFile(char un[size],char text[500])
{
    FILE *fptr;
    int i;
    for(i=0; i<strlen(text); i++)
    {
        if(text[i] == '\0' || text[i] == '\n')
        {
            continue;
        }
        else
        {
            text[i] = text[i] + code;
        }
    }
}
//=========================================================================================================
void decryptFile(char un[size], char text[500])
{
    int i;
    for(i=0; i<strlen(text); i++)
    {
        if(text[i] == '\0' || text[i] == '\n')
        {
            continue;
        }
        else
        {
            text[i] = text[i] -code;
        }
    }
}
//=======================================================================================================
int deleteFiles(char un[size])
{
    int pass,d,len;
    char confirm;
    while(1)
    {
        printf("\nTo confirm press 'y' or 'n' for No.\nAction cannot be reversed\nTo go back enter 0:");
        scanf(" %c",&confirm);
        if(confirm == 'n' || confirm == 'N')
        {
            return 2;
        }
        else if(confirm == 'y'|| confirm == 'Y')
        {
            printf("Enter your password:");
            pass = password(un);
            if(pass == 0)
            {
                break;
            }
            else
            {
                printf("\nWrong Pass try again!");
            }
        }
        else if(confirm == '0')
        {
            return 2;
        }
        else
        {
            printf("Enter correct choice");
        }
    }
    int i;
    char fileName[size],fbuffer[size],unBuffer[size];
    struct dirent *de;
    DIR *dr = opendir(".");

    if (dr == NULL)
    {
        return 1;
    }
    while ((de = readdir(dr)) != NULL)
    {
        strcpy(fbuffer,de->d_name);
        strcpy(fileName,fbuffer);
        strcpy(unBuffer,un);
        strcat(unBuffer,".txt");
        strcmp(un,fbuffer);
        if(!strcmp(unBuffer,fbuffer))
        {

            remove(fbuffer);
        }
        for(i=strlen(fbuffer); i!=0; i--)
        {
            len = strlen(fbuffer) - 14;
            fbuffer[len] = '\0';
            if(!strcmp(un,fbuffer))
            {
                remove(fileName);
            }
        }
    }
    closedir(dr);
    return 0;
}
//==================================================================================================
