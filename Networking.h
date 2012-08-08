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
void startConnection(EthernetClient& client)
{
  boolean sentHeader = false;  
  if(client.connected()) 
  {
      if (client.available()) 
      {
         if(!sentHeader)
         {
            // send a standard http response header
           // client.println("HTTP/1.1 200 OK");
           // client.println("Content-Type: text/html");
            //client.println();
            sentHeader = true;
         }
      }
  }
}

void sendData(File& dataFile, EthernetClient& client, const int pos)
{
 
      //client.print("<data>");
      const int dataLength = 50;
      Serial.print("Position: ");
      Serial.print(pos);
      char data[dataLength]; 
      int dataRead = getData(data, dataLength, dataFile, pos);
      if(dataRead)
      {
        Serial.println(dataRead);
        for(int i = 0; i<dataRead; ++i)
        { 
        //  client.print(data[i]);
          Serial.print(data[i]);
        }
       // client.println("</data>");
      }
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
void handleRequest(File& data, EthernetClient& client)
{
  const int requestLength = 15;
  char request[requestLength];
  getRequest(data, client, request, requestLength);
  if(!strcmp(request, "tag"))
  {
     const int tagPos = 0;
     sendData(data, client, tagPos);
  }
  else if(!strcmp(request, "name"))
  {
    const int namePos = 1;
    sendData(data, client, namePos);
  }
  else if(!strcmp(request, "time"))
  {
    const int timePos = 2;
    sendData(data, client, timePos);
  }
}

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

#if 0
void readEntity(File& data, File& config, EthernetClient& client)
{
  const int lineSize = 128;
  const int entitySize = 15;
  const int tagLength = 10;
  const int nameLength = 50;

  char entity[entitySize];
  char nextByte;
  
  unsigned long repeatPos;
  boolean repeat = false;
  
  if(config.available())
  {
    nextByte = config.read();
  }
  int i = 0;
 
  while(config.available() && nextByte != ';')
  {
    entity[i] = nextByte;
    nextByte = config.read();
    i++;
  }  
  entity[i] = 0;
  
  if(!strcmp(entity, "Repeat"))
  {
    repeatPos = config.position();
    repeat = true;
  }
  
  else if(!strcmp(entity, "End"))
  {
    if(repeat)
    {
      config.seek(repeatPos);
    }
  }
  
  else if(!strcmp(entity, "NextLine"))
  {
    char line[lineSize];
    GetLine(dataFile, line, lineSize);
  }
  
  else if(!strcmp(entity,"RFID"))
  {
    const int location = 0;
    const int tagLength = 10;
    
    char tag[tagLength]; 
    int dataRead = GetData(tag, tagLength, dataFile, location);
    if(dataRead)
    {
      for(int i = 0; i<dataRead; ++i)
      { 
        client.print(tag[i]);
      }
    }
  }
  else if(!strcmp(entity,"Name"))
  {
    const int location = 0;
    const int nameLength = 50;
    char name[nameLength]; 
    int dataRead = GetData(name, nameLength, dataFile, location);
    if(dataRead)
    {
      for(int i = 0; i<dataRead; ++i)
      { 
        client.print(name[i]);
      }
    }
  }
  else if(!strcmp(entity, "Time"))
  {
    const int location = 0;
    const int timeLength = 20;
    
    char time[timeLength]; 
    int dataRead = GetData(time, timeLength, dataFile, location);
    if(dataRead)
    {
      for(int i = 0; i<dataRead; ++i)
      { 
        client.print(time[i]);
      }
    }
  }
}
#endif



