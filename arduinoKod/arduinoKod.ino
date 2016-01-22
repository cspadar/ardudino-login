#include <AltSoftSerial.h>
 
AltSoftSerial BT;

#define MAX_BUFFER 4

char data;
char* buffer;
boolean receiving;
int pos;

void setup()  { 
  BT.begin(9600);
  Serial.begin(9600);
   buffer = new char[MAX_BUFFER];
   pinMode(13, OUTPUT);
   digitalWrite(13, LOW);
} 

void loop()  {
  
   while (BT.available()){
        
        data=BT.read();
        
         switch(data) {
            //3: End of transmission
            case 3:
                    receiving = false;
                    if(buffer[0] == 'a') {
                    digitalWrite(13,HIGH);
                    BT.println('g');
                    }
                    if(buffer[0] == 'b') {
                      digitalWrite(13, LOW);
                      }
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
