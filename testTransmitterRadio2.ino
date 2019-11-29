//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

const int CO2Thresh = 360;
const int CO2 = A5;
int CO2val = 0;
bool fanON = false;

const int WaitFor = 15; 
int tot = 0;
int pollNum = 0;


void setup()
{
  while (!Serial);
    Serial.begin(9600);
  radio.begin();
  //set the address
  radio.openWritingPipe(address);
  //Set module as transmitter
  radio.stopListening();
  Serial.println("If reading over 360, dangerous");
}
void loop()
{
  //Send message to receiver
  CO2val = analogRead(CO2); 
  Serial.println(CO2val);
  if(CO2val>CO2Thresh){
    const char text[] = "Dangerous";
    radio.write(&text, sizeof(text));
    Serial.println("Message sent: Turn On");
    fanON = true; 
  }
  else{
    const char text[] = "Safe";
    radio.write(&text, sizeof(text));
    Serial.println("Message sent: Turn Off");
  }
  
  delay(1000);
}

/*  if(fanON){
    tot = tot+CO2val;
    pollNum = pollNum +1;
    while((pollNum < WaitFor) && (tot/pollNum < CO2Thresh)){
       const char text[] = "Safe";
       radio.write(&text, sizeof(text));
       Serial.println("Message sent: Turn Off");
    }
    fanON = false;
    pollNum = 0;
    tot = 0;
    }*/
