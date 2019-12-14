const int CO2 = A5; //5V
const int Gas = A0; //5V
const int R0 = 86.972;//5V
const int CO2_2 = A4;//5V

int CO2val = 0;
int Gasval = 0;
float m = -0.000106;//propane & lpg:-0.000106  || CO: -0.00014
float b = 1.1751;//propane & lpg:1.175  || CO: 2.49417
int CO2val_2= 0;

int dustpin = 4;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 5000;//current 3 sec, original 30 sec (30000 ms) ;
unsigned long delaytime = 1000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

int temp_CO2readraw = 0;
int temp_Gasreadraw = 0;
int temp_CO2_2readraw= 0;

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

const int CO2Thresh = 360;

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
  //Serial.println("If reading over 360, dangerous");
  pinMode(dustpin,INPUT);
  starttime = millis();
}
void loop()
{
    float sensor_volt;
    float RS_gas; 
    float ratio_gas;
    duration = pulseIn(dustpin, LOW);
    lowpulseoccupancy = lowpulseoccupancy+duration;
    
    temp_CO2readraw = analogRead(CO2)+temp_CO2readraw;
    temp_Gasreadraw = analogRead(Gas) +temp_Gasreadraw;
    temp_CO2_2readraw= analogRead(CO2_2)+temp_CO2_2readraw;

    if ((millis()-starttime) > sampletime_ms)//if the sampel time == 30s
    {
        CO2val = temp_CO2readraw/(sampletime_ms/delaytime);
        //Serial.println("CO2 test");
        Serial.println(CO2val);
        
        float Co2sensorValue = temp_CO2_2readraw/(sampletime_ms/delaytime);
        float voltage = Co2sensorValue*(5000/1024.0);
        int voltage_diference=voltage-400;
        CO2val_2=voltage_diference*50.0/16.0;
        //Serial.println("CO2_2 ppm");
        //Serial.println(CO2val_2);

        //gas
        int sensorValue = temp_Gasreadraw/(sampletime_ms/delaytime);
        sensor_volt=(float)sensorValue/1024*5.0;
        RS_gas = (5.0-sensor_volt)/sensor_volt;
        ratio = RS_gas/R0;
        Gasval = m*ratio +b;
        //Serial.println("Gas ppm");
        //Serial.println(Gasval);
        
        //dust
        ratio = lowpulseoccupancy/((sampletime_ms)*100);  // Integer percentage 0=>100
        concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
        //Serial.print("\ndust ppm\n");
        //Serial.print(concentration);

        if(CO2val>CO2Thresh){
        const char text[] = "Dangerous";
        radio.write(&text, sizeof(text));
        //Serial.println("Message sent: Turn On");
        }
        else{
        const char text[] = "Safe";
        radio.write(&text, sizeof(text));
        //Serial.println("Message sent: Turn Off");
        }

        lowpulseoccupancy = 0;
        temp_CO2readraw = 0;
        temp_Gasreadraw = 0;
        temp_CO2_2readraw= 0;
        starttime = millis();
    }
    delay(delaytime);
}
