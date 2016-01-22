#include <AltSoftSerial.h>
#include <Keypad.h>

AltSoftSerial altSerial;

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 11, 10, 7, 6 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 5, 4, 3, 2 }; 

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//Code stuffs
char codeFromMobile[4];
char codeFromKeypad[4];
char pin[4] = {1,2,3,4};
int actualChar = 0;
int actualIndex = 0;

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("AltSoftSerial Test Begin");
  altSerial.begin(9600);
  altSerial.println("h");
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {

  char key = kpd.getKey();
  if(key)  // Check for a valid key.
  {
    switch (key)
    {
      case '*':
      actualChar = 0;
      if(compareCharArrays(codeFromKeypad, codeFromMobile)) {
        digitalWrite(12, HIGH);
        }
        break;
      case '#':
      //Send the code to mobile
      actualChar = 0;
      if(compareCharArrays(codeFromKeypad, pin)){
        digitalWrite(13, HIGH);
        altSerial.println(1);
        }
      emptyCharArray(codeFromKeypad);
        break;
      default:
        Serial.println(key);
        if(actualChar < 4 && actualIndex == 0) 
          {
          codeFromKeypad[actualChar] = key;
          actualChar++;
          }
          if(actualChar < 4 && actualIndex == 4) 
          {
            codeFromKeypad[actualChar] = key;
            actualChar++;
          }
    }
  }
  
  char c;
  
  if (altSerial.available()) {
    c = altSerial.read();
    codeFromMobile[actualIndex] = c;
    actualIndex++;
  }
}

boolean compareCharArrays(char a[], char b[]) {
  for(int i=0; i<sizeof(a); i++) {
    if(a[i] != b[i]) return false;
    }
    return true;
  }

void emptyCharArray(char a[]) {
  for(int i=0; i<sizeof(a); i++) {
    a[i] = -1;
    }
  }
