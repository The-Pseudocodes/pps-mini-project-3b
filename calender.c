#include<stdio.h>
#include<conio.h>
#include<windows.h>

int getkey();
void display(int,int,int,int[]);
void calendar(int,int);

void gotoxy(int x,int y)
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

char *month[]={"January","February","March","April","May","June","July","August","September","October","November","December"};
char *week[]={"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};

int main()
{
    int month,year,ch;
    enteryear:
    while(1)
    {
        printf("Enter year and month(number):" );
        scanf("%d%d",&year,&month);
        if(year<1945)
        {
            //If year less than 1945
            printf("\n\t Please enter year above 1945\n");
            continue;
        }
        else
        {
            //If year greater than equal to 1945
            calendar(year,month);
        }
        while(1)
        {
        gotoxy(20,20);printf("(*) Use LEFT, RIGHT, UP and DOWN arrow.");
        gotoxy(20,22);printf("(*) Press P to go to particular year and month.");
        gotoxy(20,24);printf("(*) Press ESC to Exit.");
        ch=getkey();
        switch(ch)
        {
        case 80: //down arrow
               //Increasing month
                if(month==12)
                {
                    //Jump to next year if month is december
                    month=1;
                    year++;
                }
                else
                {
                    month++;
                }
                calendar(year,month);
                break;
        case 77: //right arrow
            //Increasing Year
                year++;
                calendar(year,month);
                break;
        case 72: //up arrow
            // Decreasing Month
                if(month==1)
                {
                    // Jump to previous year if month is january
                    year--;
                    month=12;
                }
                else
                    month--;
                calendar(year,month);
                break;
        case 75: //left arrow
            //Decreasing year
                if(year==1945)
                {
                    //If year is 1945 and we click left arrow than
                  gotoxy(15,2);printf("Year below 1945 not available");
                }
                else
                {
                    year--;
                    calendar(year,month);
                }

                break;
        case 27: //esc key
            //Exit program
                system("cls");
                gotoxy(50,14);printf("Exiting program.\n\n\n\n\n");
                exit(0);
        case 112://p key
            //Go to particular year and month
                system("cls");
                goto enteryear;
        }
        }
        break;

    }
    getch();
    return 0;
}

void display(int yr_no,int month_no,int day,int days[])
{
    int i,j,pos;
    gotoxy(56,6);printf("%s %d",month[month_no-1],yr_no); //displaying year and month
    for(i=0,pos=30;i<7;i++,pos+=10)
    {
        gotoxy(pos,8);printf("%s",week[i]);
    }
    day++; //incrementing the day by 1
    if(day==0 || day==7)
        pos=91; //if tdays is 0 or 7, position is sunday
    if(day==1)
        pos=31; //if tdays is 1, position is monday
    if(day==2)
        pos=41;  //if tdays is 2, position is tuesday
    if(day==3)
        pos=51;  //if tdays is 3, position is wednesday
    if(day==4)
        pos=61;  //if tdays is 4, position is thursday
    if(day==5)
        pos=71;  //if tdays is 5, position is friday
    if(day==6)
        pos=81;  //if tdays is 6, position is saturday

    for(i=0,j=10,pos;i<days[month_no-1];i++,pos+=10)
    {
        gotoxy(pos,j);printf("%d",i+1);
        if(pos==91)
        {
            pos=21; //Moving position to monday
            j++;  //Increasing j by 10 if position is sunday
        }
    }
    //Drawing horizontal line
    for(i=22;i<102;i++)
    {
        gotoxy(i,4);printf("%c",196);
        gotoxy(i,17);printf("%c",196);
    }

    //Drawing all the corner of the rectangle
    gotoxy(21,4);printf("%c",218);
    gotoxy(102,4);printf("%c",191);
    gotoxy(21,17);printf("%c",192);
    gotoxy(102,17);printf("%c",217);

    //Drawing vertical line
    for(i=5;i<17;i++)
    {
        gotoxy(21,i);printf("%c",179);
        gotoxy(102,i);printf("%c",179);
    }
    //Drawing left and the right navigation symbol
    gotoxy(24,11);printf("%c",174);
    gotoxy(98,11);printf("%c",175);
}

int getkey()
{
    int c;
    c=getch();
     if(c==0)
    {
        printf("zero");
        c=getch();

        return c;
    }
    return c;
}

void calendar(int yr_no,int month_no)
{
    int days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int tdays=0,k,myear;
    system("cls");
    myear=yr_no-1; //Decreasing year by 1
            if(myear>=1945)
            {
                for(k=1945;k<=myear;k++)
                {
                    if(k%4==0) //If the year is a leap year than total no of days is 366
                        tdays=tdays+366;  //counting all the days till nyr - 1
                    else //If the year is a leap year than total no of days is 365
                        tdays=tdays+365;  //counting all the days till nyr - 1
                }
            }

            if(yr_no%4==0)
                days[1]=29; //changing value in days array from 28 to 29 since leap year
            else
                days[1]=28; //changing value in days array from 29 to 28 since not a leap year

            for(k=0;k<(month_no-1);k++)
            {

                tdays=tdays+days[k]; //Adding nmonth-1 days to tdays
            }

            tdays=tdays%7; //Finding the remainder of tdays so it can calculate the position to display
            display(yr_no,month_no,tdays,days); //Passing the value to display
}
