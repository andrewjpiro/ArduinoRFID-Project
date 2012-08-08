#ifndef NAMES_H_
#define NAMES_H_

//Global String for names
const int nameLength = 50;
char name[nameLength];
const int lineLength = 128;

void printName(File& file);
boolean matchName(char* tag, const int tagLength,
                  char* name, const int nameLength, 
                  File& file);

//////////////////////////////////////////////
/////////////////Names.cpp////////////////////
//////////////////////////////////////////////
void printName(File& file)
{
  for(int i = 0; i<nameLength; i++)
  {
    if(name[i] == 0)
    {
      break;
    }
    file.print(name[i]);
  }
}

boolean matchName(char* RFIDTag, const int tagLength, 
                  char* name,const int nameLength,  
                  File& file)
{
  unsigned long initPos = file.position();
  char* endTag = RFIDTag + tagLength;
  char tag[tagLength + 1]; 
  bool returnVal = false;
  for(int i = 0; RFIDTag <= endTag && i<tagLength; ++RFIDTag)
  {
    tag[i] = *RFIDTag;
    ++i;
  }
  tag[tagLength] = 0;
  while(file.available())
  {
    char readTag[tagLength+1];
    for(int i = 0; i<tagLength; ++i)
    {
      readTag[i] = file.read();
    }
    readTag[tagLength] = 0;
    if(!(strcmp(tag, readTag)))
    {
       if(file.read() != '\t')
       {
         file.seek(initPos); 
         return returnVal;
       }
       char nextByte = file.read();
       char* begName = name;
       char* endName = name + nameLength;
       for(; name<=endName && nextByte != '\n'  ; ++name)
       { 
         *name = nextByte;
         nextByte = file.read();
       }
       ++name = 0;
       returnVal = true; 
    }
    else
    {      
      char garbage[lineLength];
      getLine(file, garbage, lineLength);
    }
  }
  file.seek(initPos);
  return returnVal;
}

#endif
