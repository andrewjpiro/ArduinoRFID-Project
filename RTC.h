#ifndef RTC_H_
#define RTC_H_
//I2C Header for RTC
#include "Wire.h"
#define DS1307_I2C_ADDRESS 0x68

void setTime(char second,        // 0-59
             char minute,        // 0-59
             char hour,          // 1-23
             char dayOfWeek,     // 1-7
             char dayOfMonth,    // 1-28/29/30/31
             char month,         // 1-12
             char year);          // 0-99

void getTime(char *second,
             char *minute,
             char *hour,
             char *dayOfWeek,
             char *dayOfMonth,
             char *month,
             char *year);

void printTime(File& file);

// Conversions from normal decimal numbers to binary coded decimal and back
char decToBcd(char val);
char bcdToDec(char val);
#endif

//////////////////////////////////////////////
/////////////////RTC.h////////////////////////
//////////////////////////////////////////////
char decToBcd(char val)
{
  return ( (val/10*16) + (val%10) );
}

char bcdToDec(char val)
{
  return ( (val/16*10) + (val%16) );
}


// 1) Sets the date and time on the ds1307
// 2) Starts the clock
// 3) Sets hour mode to 24 hour clock
// Assumes you're passing in valid numbers
void setTime(char second,        // 0-59
                   char minute,        // 0-59
                   char hour,          // 1-23
                   char dayOfWeek,     // 1-7
                   char dayOfMonth,    // 1-28/29/30/31
                   char month,         // 1-12
                   char year)          // 0-99
{
   Wire.beginTransmission(DS1307_I2C_ADDRESS);
   Wire.write(0);
   Wire.write(decToBcd(second));    // 0 to bit 7 starts the clock
   Wire.write(decToBcd(minute));
   Wire.write(decToBcd(hour));      // If you want 12 hour am/pm you need to set
                                   // bit 6 (also need to change readDateDs1307)
   Wire.write(decToBcd(dayOfWeek));
   Wire.write(decToBcd(dayOfMonth));
   Wire.write(decToBcd(month));
   Wire.write(decToBcd(year));
   Wire.endTransmission();
}

// Gets the date and time from the ds1307
void getTime(char *second,
          char *minute,
          char *hour,
          char *dayOfWeek,
          char *dayOfMonth,
          char *month,
          char *year)
{
  // Reset the register pointer
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);

  // A few of these need masks because certain bits are control bits
  *second     = bcdToDec(Wire.read() & 0x7f);
  *minute     = bcdToDec(Wire.read());
  *hour       = bcdToDec(Wire.read() & 0x3f);  // Need to change this if 12 hour am/pm
  *dayOfWeek  = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month      = bcdToDec(Wire.read());
  *year       = bcdToDec(Wire.read());
}

void printTime(File& file)
{
  char second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  getTime(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year); 
  if(hour <10)
  {
    file.print('0');
  } 
  file.print(hour, DEC);
  file.print(":");
  if(minute <10)
  {
    file.print('0');
  } 
  file.print(minute, DEC);
  file.print(":");
  if(second <10)
  {
    file.print('0');
  } 
  file.print(second, DEC);
  file.print("  ");
  if(month <10)
  {
    file.print('0');
  } 
  file.print(month, DEC);
  file.print("/");
  if(dayOfMonth <10)
  {
    file.print('0');
  } 
  file.print(dayOfMonth, DEC);
  file.print("/");
  if(year <10)
  {
    file.print('0');
  } 
  file.print(year, DEC);
}
