#include <SoftwareSerial.h>
 
SoftwareSerial bluetooth(7, 8); // TX, RX

#define MAX_BUFFER 4

char data;
char* buffer;
boolean receiving;
int pos;

void setup()  { 
  buffer = new char[MAX_BUFFER];
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  bluetooth.begin(9600);
  bluetooth.println('s');
  receiving = true;
} 

void loop()  
{
  if (bluetooth.available())
  {
    data = bluetooth.read();
    if(data == 3)
    {
        if(buffer[0] == 'a') 
        {
          digitalWrite(13,HIGH);
        }
        else if (buffer[0] == 'b') 
        {
          digitalWrite(13, LOW);
        }
        bluetooth.println('r');
        receiving = false;
    }
    else
    {
      if (receiving == false) 
      {
        resetData();
      }
      buffer[pos] = data;
      pos++;
      receiving = true; 
    }
  }                      
}

 void resetData(){
   for (int i=0; i<=pos; i++) buffer[i] = 0; 
   pos = 0;
}
