#include <SoftwareSerial.h>
 
SoftwareSerial Genotronex(7, 8); // TX, RX

#define MAX_BUFFER 4

char data;
char* buffer;
boolean receiving = false;
int pos;

void setup()  { 
  Genotronex.begin(9600);
  Serial.begin(9600);
   buffer = new char[MAX_BUFFER];
   pinMode(13, OUTPUT);
   digitalWrite(13, LOW);
   Genotronex.println("LASD");
} 

void loop()  {
  
   while (Genotronex.available()){
        
        data=Genotronex.read();
        
         switch(data) {
            //3: End of transmission
            case 3:
                    receiving = false;
                    if(buffer[0] == 'a') {
                    digitalWrite(13,HIGH);
                    }
                    if(buffer[0] == 'b') {
                      digitalWrite(13, LOW);
                      }
                      Genotronex.println("G");
                     break; //end message
            default: if (receiving == false) resetData();
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
