#ifndef RFID_H_
#define RFID_H_
//RFID Constants  
const int enable_pin = 2; //pin that /enable is plugged into
const int msValidate_length = 250; //time to wait checking tag for noise
const int msWait_time = 1000; //time to wait for user to remove tag after scanning ms.

const byte startByte = 0x0A; //bytes to stop and start RFID tags
const byte stopByte = 0x0D;
const int code_length = 10; //length of RFID tags

char tag[code_length];

void startRFID();
void RFIDEnable();
void RFIDDisable();
void RFIDReset();

void getTag();
boolean isValid();

void printCode(File& file);
void clearCode();

#endif

//////////////////////////////////////////
///////////////RFID.cpp///////////////////
//////////////////////////////////////////
void startRFID()
{
    pinMode(enable_pin, OUTPUT); // RFID
    Serial.print("Welcome to the RFID reader\n"); //RFID
}

void clearCode()
{
  for(int i = 0; i<code_length; ++i)
  {
    tag[i] = 0;
  }
}
void printCode(File& file)
{
   for(int i = 0; i<code_length; ++i)
   {
     file.print(tag[i]);
   }
}

//Functions for enabling(red light) and disabling(green light)
//the RFID scanner
void RFIDEnable()
{
    digitalWrite(enable_pin, LOW);
}
void RFIDDisable()
{
    digitalWrite(enable_pin, HIGH);
}
void RFIDReset()
{
  Serial.flush();
  clearCode();
}
//Functions for getting 10 digit tag and verifying that it is not 
//just noise
void getTag()
{
  byte next_byte = Serial.read();
  if(next_byte == startByte) 
  {      
    for(byte bytesread = 0; bytesread < code_length;) 
    {
      if(Serial.available())  
      { 
          next_byte = Serial.read();
          if(next_byte == startByte) break;       
          tag[bytesread++] = next_byte;         
      } 
    } 
    Serial.read(); //throw away extra STOP_BYTE    
  }
}


bool isValid()
{
  byte next_byte; 
  int count = 0;
  while (!(Serial.available()))
  {  
    delay(1); //probably not a very pure millisecond
    if(count++ > msValidate_length) return false;
  }
  
  next_byte = Serial.read();
  if (next_byte == startByte) 
  {  
    byte bytes_read = 0; 
    while (bytes_read < code_length) 
    {
      if (Serial.available())  //wait for the next byte
      {      
          next_byte = Serial.read();
          if (next_byte == stopByte) break;
          if (tag[bytes_read++] != next_byte) return false;                     
      }
    }                
  }
  return true;   
}

void startRFID()
{
    pinMode(enable_pin, OUTPUT); // RFID
    Serial.print("Welcome to the RFID reader\n"); //RFID
}

void clearCode()
{
  for(int i = 0; i<code_length; ++i)
  {
    tag[i] = 0;
  }
}
void printCode(File& file)
{
   for(int i = 0; i<code_length; ++i)
   {
     file.print(tag[i]);
   }
}

//Functions for enabling(red light) and disabling(green light)
//the RFID scanner
void RFIDEnable()
{
    digitalWrite(enable_pin, LOW);
}
void RFIDDisable()
{
    digitalWrite(enable_pin, HIGH);
}
void RFIDReset()
{
  Serial.flush();
  clearCode();
}
//Functions for getting 10 digit tag and verifying that it is not 
//just noise
void getTag()
{
  byte next_byte = Serial.read();
  if(next_byte == startByte) 
  {      
    for(byte bytesread = 0; bytesread < code_length;) 
    {
      if(Serial.available())  
      { 
          next_byte = Serial.read();
          if(next_byte == startByte) break;       
          tag[bytesread++] = next_byte;         
      } 
    } 
    Serial.read(); //throw away extra STOP_BYTE    
  }
}


bool isValid()
{
  byte next_byte; 
  int count = 0;
  while (!(Serial.available()))
  {  
    delay(1); //probably not a very pure millisecond
    if(count++ > msValidate_length) return false;
  }
  
  next_byte = Serial.read();
  if (next_byte == startByte) 
  {  
    byte bytes_read = 0; 
    while (bytes_read < code_length) 
    {
      if (Serial.available())  //wait for the next byte
      {      
          next_byte = Serial.read();
          if (next_byte == stopByte) break;
          if (tag[bytes_read++] != next_byte) return false;                     
      }
    }                
  }
  return true;   
}

void startRFID()
{
    pinMode(enable_pin, OUTPUT); // RFID
    Serial.print("Welcome to the RFID reader\n"); //RFID
}

void clearCode()
{
  for(int i = 0; i<code_length; ++i)
  {
    tag[i] = 0;
  }
}
void printCode(File& file)
{
   for(int i = 0; i<code_length; ++i)
   {
     file.print(tag[i]);
   }
}

//Functions for enabling(red light) and disabling(green light)
//the RFID scanner
void RFIDEnable()
{
    digitalWrite(enable_pin, LOW);
}
void RFIDDisable()
{
    digitalWrite(enable_pin, HIGH);
}
void RFIDReset()
{
  Serial.flush();
  clearCode();
}
//Functions for getting 10 digit tag and verifying that it is not 
//just noise
void getTag()
{
  byte next_byte = Serial.read();
  if(next_byte == startByte) 
  {      
    for(byte bytesread = 0; bytesread < code_length;) 
    {
      if(Serial.available())  
      { 
          next_byte = Serial.read();
          if(next_byte == startByte) break;       
          tag[bytesread++] = next_byte;         
      } 
    } 
    Serial.read(); //throw away extra STOP_BYTE    
  }
}


bool isValid()
{
  byte next_byte; 
  int count = 0;
  while (!(Serial.available()))
  {  
    delay(1); //probably not a very pure millisecond
    if(count++ > msValidate_length) return false;
  }
  
  next_byte = Serial.read();
  if (next_byte == startByte) 
  {  
    byte bytes_read = 0; 
    while (bytes_read < code_length) 
    {
      if (Serial.available())  //wait for the next byte
      {      
          next_byte = Serial.read();
          if (next_byte == stopByte) break;
          if (tag[bytes_read++] != next_byte) return false;                     
      }
    }                
  }
  return true;   
}







