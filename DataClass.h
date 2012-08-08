#ifndef DATA_H_
#define DATA_H_

#define dataSize 50
class Data 
{
  public:
    enum Datatype{kRFIDTag, kStudentName, kTimeStamp};    
    Data(File& file, Datatype type);    
    int getData(int rowNumber);
    void setType(Datatype);
    void sendData(EthernetClient& client);
    char mData[dataSize];
  private:
    int mPosition; 
    File mFile;
};

///////////////////////////////////////////////////////
////////////////////DataClass.cpp//////////////////////
///////////////////////////////////////////////////////
Data::Data(File& file, Datatype type)
:mPosition(type), mFile(file)
{
}
int Data::getData(int rowNumber)
{
     unsigned long initPos = dataFile.position();  
     const int lineSize = 128;
     char line[lineSize];
     
     for(int i = 1; i<rowNumber; ++i) //move to desired row
     {
       getLine(mFile, line, lineSize);
     }
     
     int actualSize = getLine(dataFile, line, lineSize);
     char* lineReader = tabOver(line, actualSize, mPosition);
     if(!(lineReader))
     {
       return 0;
     }
     char* dataReader = mData;
     char* endData = mData + dataSize;
     for(; *lineReader != '\t' && *lineReader != '\n' && dataReader < endData; lineReader++)
     {
        *dataReader = *lineReader;
        ++dataReader;
     }
     return dataReader-mData; //Successful completion!
     //Return number of characters in buffer
     dataFile.seek(initPos); //resets to beginning of line
}

void Data::setType(Datatype type)
{
  mPosition = type;
}

void Data::sendData(EthernetClient& client)
{
      client.print("<data>");
      for(int i = 0; i<dataSize; ++i)
      {
        client.print(mData[i]);
      }
      client.print("</data>");
}

#endif
