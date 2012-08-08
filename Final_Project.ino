#include <SD.h>
#include <Ethernet.h>
#include <SPI.h>
#include "Wire.h"

#include "FileSystem.h"
#include "Names.h"
#include "DataClass.h"
#include "Networking.h"
#include "RFID.h"
#include "RTC.h"


void setup()
{
  Serial.begin(2400);   
  Wire.begin(); //RTC
  startFileSystem(); // creates dataFile, configFile, and nameFile if they don't exist
                  // and opens configFile and nameFile in read only mode
  startRFID();
  Ethernet.begin(mac);
  server.begin();
  Serial.println(Ethernet.localIP());
  Serial.print("Ready for Business!\n"); 
}

void loop()
{

  EthernetClient client = server.available();
  if(client)
  {
     Serial.println("Got a Client!");
     dataFile = SD.open("Data.txt"); //opens dataFile in read only mode
     sendCode(dataFile, configFile, client); //sends html coding from configFile
     handleRequest(dataFile, client);
     
     client.stop();   
     dataFile.close();
  }
  
  RFIDEnable();
  if(Serial.available())
  {    
    dataFile = SD.open("Data.txt", FILE_WRITE); //opens dataFile in write mode
    getTag();
    
    if(matchName(tag, code_length, name, nameLength, nameFile))
    {
      RFIDDisable();
    
      printCode(dataFile);
      dataFile.print('\t');
      
      printName(dataFile); 
      dataFile.print('\t');
      
      printTime(dataFile);
      dataFile.print('\n');
      delay(msWait_time);
    }
    else
    {
      RFIDDisable();
      Serial.println("Error:Invalid Tag");
    }
    RFIDReset();
    dataFile.close();
  }
  
}
