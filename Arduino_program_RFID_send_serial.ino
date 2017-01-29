// 
#define SERIAL_TX_BUFFER_SIZE 64
// 
#define SERIAL_RX_BUFFER_SIZE 64
// definicia spi zbernice 9600 baudrate
#include <SPI.h>
#include <RFID.h>
// 
#define SDA_DIO 10
// 
#define RESET_DIO 9
// 
RFID RC522(SDA_DIO, RESET_DIO);

#include <Wire.h>
// button definovany na

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete


const int buttonPin = 3;
const int ledPin = 5;
const int piezoPin = 7;
//stlacene tlacitko
int buttonState = 0;     

//
char button[1]="";
//**dsc


//**dsc
void setup() {
inputString.reserve(2);
  // definovanie buttonPinu na ktorom bude tlacitko , tlacitka
pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  // aktivuje komunikaciu
  Wire.begin();
  // aktivuje spi
  SPI.begin(); //inicializacia spi zbernice pre RFID
  //aktivuje seriovu zbernicu
  Serial.begin(9600); //inicializacia serioveho rozhrania pre priebeh programu
     RC522.init();
  //if (Serial.available() > 0) {
  // ak bolo stlacene tlacitko
  //
  //}
  //Serial.print("inicializating...");
  //Serial.println("Version RFID dochadzkovy V1");
  }
void loop() {
  //
  delay(50);
  
  parsovanie();
  push_button();
  odozva();
//  paket pri na4itani karty
// ID= identifikacia karta
// - oddelovac
// x=seriovecislokarty - 9 atribut
// - oddelovac
// zz= zapis niecoho - 2 atribut
// - oddelovac
// y=zapisatdata - 9 atribut

//odosleme paket ID-xxxxxxxxx-zz-yyyyyyyyy



}
void parsovanie(){
byte i;
if (RC522.isCard())
{
RC522.readCardSerial();
/* Output the serial number to the UART */
for(i = 0; i <= 4; i++)
{
Serial.print(RC522.serNum[i],HEX);
//treba doprogramovat
//dsc3231 ako cas pre arduino
}
 Serial.print(',');
 Serial.print(button[1]);
 Serial.println();

}
Serial.flush();

}
void push_button(){
buttonState = digitalRead(buttonPin);
if (buttonState == LOW) {
    // ak tak 
   button[1]= "z";
  } else {
    // ak tak
   button[1]= "v";
  }

}

void odozva(){
  if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  
    //beep(
    digitalWrite(ledPin,HIGH);
    beep(50);
    delay(100);
    digitalWrite(ledPin,LOW);
    //pin
    //zapis na pin 3 led HIGH
    }
  
  }


  void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void beep(unsigned char delayms){
  analogWrite(piezoPin, 20);      // Almost any value can be used except 0 and 255
                           // experiment to get the best tone
  delay(delayms);          // wait for a delayms ms
  analogWrite(piezoPin, 0);       // 0 turns it off
  delay(delayms);          // wait for a delayms ms   
}  
