#ifndef FILE_SYSTEM_H_
#define FILE_SYSTEM_H_
//SD Constants 
const int chipSelect = 4;
//Global Files
File dataFile;
File configFile;
File nameFile;

void startSD();
void startFileSystem();  
int getLine(File& file, char* buffer, int length);
char* findChar(char* buffer, const int start,const int length,const char target);
char* tabOver(char* buffer, const int length, const int numberOfTabs = 1);

///////////////////////////////////////////
//////////////FileSystem.cpp///////////////
///////////////////////////////////////////
void startSD()
{
   pinMode(10, OUTPUT); 
   SD.begin(chipSelect);
}

void startFileSystem()  
{ 
  startSD();
  dataFile = SD.open("Data.txt", FILE_WRITE);
  dataFile.close();
  configFile = SD.open("Config.txt", FILE_WRITE);//Create if it doesn't exist
  configFile.close();
  configFile = SD.open("Config.txt");//Open in read mode
  nameFile = SD.open("Names.txt", FILE_WRITE);//Create if it doesn't exist
  nameFile.close();
  nameFile = SD.open("Names.txt");//Open in read mode
}

int getLine(File& file, char* buffer, int length)
{
   char* endbuf = buffer+length;  
   char* begbuf = buffer;
   for(; buffer<=endbuf; ++buffer)
   {
     if(file.available())
     {
       *buffer = file.read();
       if(*buffer == '\n')
       {
         break;
       }
     }
     else 
     {  
       break;
     }
   }
   return buffer - begbuf;
}

//Returns first position of a character in an array from start to ending
//Returns negative for unsuccesful find
char* findChar(char* buffer, const int start,const int length,const char target)
{
   char* begbuf = buffer + start;
   char* endbuf = buffer + length;
   for(;*begbuf != target; ++begbuf)
   {
     if(begbuf == endbuf)
     {
       return NULL;
     }
   }
   return begbuf;
}

//Moves 1 past a tab character in an array
//Can move past multiple tabs at once
char* tabOver(char* buffer, const int length, const int numberOfTabs)
{ 
  int start = 0;
  char* seeker  = buffer;
  char* endbuf = buffer + length;
  for(int tabs = 0; tabs < numberOfTabs; ++tabs)
   {
     seeker = findChar(buffer, start, length, '\t');
     if(!(seeker))
     {
        return NULL;
     }
     else if(seeker < endbuf)
     {
       ++seeker; //move 1 past tab
     }
     start = seeker - buffer; //move the start of the next search
   }
   return seeker;
}

#endif

