/********************************************************************
 * Author: Austin Nelson
 *
 * Project: This project is one that I got from a friend. He put the
 *    Calendar project together without passing any functions and I want
 *    to see if I can do the same here.
 *    1. Can't pass parameters into any functions
 *    2. Must use multiple functions
 *    3. Can't use globabl variables
 *    4. Can't use classes
 *
 * Original Source Code:
 *    https://github.com/akahmann/scopeIsForWimps/blob/master/scopeIsForWimps.cpp
 * NOTE:
 *    Throughout the code there is a SEARCH variable. That's where we start
 *    Searching through the stack to find the year and month in every function.
 *    Since every function requires a different index to the year and the month
 *    we use 9999 as the starting point.
 ********************************************************************/

#include <iostream>
#include <iomanip>
using std::cout;
using std::cin;
using std::endl;
using std::setw;

/********************************************************************
 * GETMONTH
 * Gets the month
 ********************************************************************/
int getMonth()
{
   int month;
   // check for valid month and get it
   while (month > 12 || month < 1)
   {
      cout << "What is the month? ";
      cin >> month;
      if (month > 12 || month < 1)
      {
         cout << "Enter a month between 1 and 12\n";
      }
   }
   return month;
}

/********************************************************************
 * GETYEAR
 * Gets the year
 ********************************************************************/
int getYear()
{
   int year;
   // check for valid year and get it
   while (year <= 1753)
   {
      cout << "What is the year? ";
      cin >> year;
      if (year <= 1753)
      {
         cout << "Enter a year after 1753\n";
      }
   }
   return year;
}


/********************************************************************
 * CALCULATEOFFSET
 * Calculates the offset based off the date put in.
 * Algorithm: Zeller's Congruence (Gregorian)
 * https://en.wikipedia.org/wiki/Zeller%27s_congruence#Implementation_in_software
 ********************************************************************/
int calculateOffset()
{
   int search = 9999;

   int month = *(&search + 18);
   int year = *(&search + 19);

   if (month == 1)
   {
      month = 13;
      --year;
   }
   if (month == 2)
   {
      month = 14;
      --year;
   }
   int k = year % 100;
   int j = year / 100;

   // here we deviate from the algorithm a bit because we
   // are looking for the 0th day for the offset. We do not add 1
   // at the beginning for this reason
   int offset = 13 * (month + 1) / 5 + k + k / 4 + j / 4 + 5 * j;
   offset %= 7;

   return offset;
}

/********************************************************************
 * ISLEAPYEAR
 * Returns yes or no based off the date put in.
 ********************************************************************/
bool isLeapYear()
{
   int search = 9999;

   int year = *(&search + 27);

   return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

/********************************************************************
 * GETDAYSINMONTH
 * Returns the number of days in a month
 ********************************************************************/
int getDaysInMonth()
{
   int search = 9999;

   int month = *(&search + 15);
   int daysInMonth = 0;

   if (month == 4 || month == 6 || month == 9 || month == 11)
   {
      daysInMonth = 30;
   }
   else if (month == 2)
   {
      if (isLeapYear())
      {
         daysInMonth = 29;
      }
      else
      {
         daysInMonth = 28;
      }
   }
   else
   {
      daysInMonth = 31;
   }

   return daysInMonth;
}

/********************************************************************
 * DISPLAYMONTH
 * Displays the month the user submits
 ********************************************************************/
void displayMonth()
{
   int search = 9999;

   int month = *(&search + 14);

   if (month == 1)
   {
      cout << "January";
   }
   else if (month == 2)
   {
      cout << "February";
   }
   else if (month == 3)
   {
      cout << "March";
   }
   else if (month == 4)
   {
      cout << "April";
   }
   else if (month == 5)
   {
      cout << "May";
   }
   else if (month == 6)
   {
      cout << "June";
   }
   else if (month == 7)
   {
      cout << "July";
   }
   else if (month == 8)
   {
      cout << "August";
   }
   else if (month == 9)
   {
      cout << "September";
   }
   else if (month == 10)
   {
      cout << "October";
   }
   else if (month == 11)
   {
      cout << "November";
   }
   else if (month == 12)
   {
      cout << "December";
   }

}

/********************************************************************
 * DISPLAY
 * Finally outputs the calendar
 ********************************************************************/
void display()
{
   int search = 9999;

   int month = *(&search + 15);
   int year = *(&search + 6);
   int offset = calculateOffset();

   cout << endl;
   displayMonth();
   cout << ", " << year << endl;

   cout << "  Su  Mo  Tu  We  Th  Fr  Sa\n";
   // need the days and the offset
   for (int i = 0; i < offset % 7; ++i)
   {
      cout << "    ";
   }

   int numDays = getDaysInMonth();
   for (int i = 1; i <= numDays; ++i)
   {
      cout << setw(4) << i;
      // new line if Saturday
      if ((i + offset) % 7 == 0)
      {
         cout << endl;
      }
   }
   // new line if not Saturday at the end of the month
   if (numDays + 1 % 7 != 0)
   {
      cout << endl;
   }

}

/********************************************************************
 * MAIN
 * for simplicity I want to do the first values to set in main for now
 ********************************************************************/
int main()
{
   int month = getMonth();
   int year = getYear();
   display();

   return 0;
}
