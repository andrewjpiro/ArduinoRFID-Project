#ifndef NETWORKING_H_
#define NETWORKING_H_
////////////////////////////////////////////////////////////////////////
//CONFIGURE
////////////////////////////////////////////////////////////////////////
  byte ip[] = { 192, 168, 0, 2 };   //Manual setup only
  byte gateway[] = { 192, 168, 0, 1 }; //Manual setup only
  byte subnet[] = { 255, 255, 255, 0 }; //Manual setup only

  // if need to change the MAC address (Very Rare)
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

  EthernetServer server = EthernetServer(80); //port 80
////////////////////////////////////////////////////////////////////////
void sendCode(File& data, File& config, EthernetClient& client);
void handleRequest(File& file, EthernetClient& client);
void getRequest(File& data, EthernetClient& client, char* request, const int requestLength);

//////////////////////////////////////////////////////
///////////////Networking.cpp/////////////////////////
//////////////////////////////////////////////////////
void sendCode(File& data, File& config, EthernetClient& client)
{
  while(client.connected())
   { 
      if(config.available())
      {  
        char charRead = config.read();
        client.print(charRead); 
      }
      else
      {
        break;
      }
   }
}

void handleRequest(File& file, EthernetClient& client)
{
  const int requestLength = 15;
  char request[requestLength];
  static int currentRow = 0;
  
  getRequest(file, client, request, requestLength);
  
  Data responseData(file, Data::kRFIDTag); 
  if(!strcmp(request, "tag"))
  {
     responseData.setType(Data::kRFIDTag);
  }
  else if(!strcmp(request, "name"))
  {
     responseData.setType(Data::kStudentName);
  }
  else if(!strcmp(request, "time"))
  {
    responseData.setType(Data::kTimeStamp);
  }
  else
  {
    return;
  }
  responseData.getData(currentRow);
  responseData.sendData(client);  
}

void getRequest(File& data, EthernetClient& client, char* request, const int requestLength)
{  
  boolean reading = false;
  int i = 0;
  while (client.connected()) 
  {
      if (client.available()) 
      {
        char c = client.read();
   
        if(reading && c == ' ') reading = false;
        if(reading)
        {
          //c is part of request  
          if(i< requestLength) 
           {
             request[i] = c;
             ++i;
           }
        }
        if(c == '?') reading = true; 
      }
      else
      {
        break;
      }
   }
   request[i] = 0;
   for(int i2 = 0; i2<requestLength && request[i2] != 0; ++i2)
   {
     Serial.print(request[i2]);
   }
}

#endif
