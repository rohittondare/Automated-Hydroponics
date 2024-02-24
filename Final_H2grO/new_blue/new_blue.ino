/* Connections for I2C between Arduino and NodeMCU (H2grO) 
 *  
 *  RTC will also be connected to I2C. Bluetooth will be connected to Serial (Tx Rx)
 *  
 *  Connection --> 0 - Bluetooth , 1 - NodeMCU/ESP8266
 *  
 *  NodeMCU -- Arduino                        ESP8266 --  Arduino
 *     D1   --   A4   (SDA)                    GPIO5  --    A4    (SDA)
 *     D2   --   A5   (SCL)                    GPIO4  --    A5    (SCL)
 *    GND   --   GND                            GND   --    GND
 *    
 *    Connections for Arduino : 
 *    
 *    A0 - pH Input                            A3 - 
 *    A1 - EC Input                            A4 - SDA
 *    A2 - Temp Input                          A5 - SCL
 *    
 *    D0 - Tx (Bluetooth)                      D7 - Lights (Relay)
 *    D1 - Rx (Bluetooth)                      D8 - Humidifier (Relay)
 *    D2 - pH Increase Pump (Relay)            D9 - Fans (Relay)
 *    D3 - pH Decrease Pump (Relay)            D10 - DHT Input
 *    D4 - Nutrients Increase Pump (Relay)     D11 - Water Level pin 1 
 *    D5 - Nutrients Decrease Pump (Relay)     D12 - Water Level pin 2
 *    D6 - Water Pump (Relay)                  D13 - 
 *    
 */

#include <Wire.h>
#include <dht11.h>
#include <ArduinoJson.h>

//#include <ESP8266WiFi.h>
//#include <FirebaseArduino.h>

#define On 0
#define Off 1

#define pH_Input A0
#define EC_Input A1
#define Temp_Input A2

#define PH_Increase 2
#define PH_Decrease 3
#define Nutrients_Incearse 4
#define Nutrients_Decrease 5
#define Water_Pump 6
#define Lights 7
#define Humidifier 8
#define Fans 9
#define DHT_Input 10
//#define Select_Line 10
//#define RTC and NodeMCU on I2C bus


dht11 DHT11;                          //DHT11 Object
                                                                //Add Interrupt !!!!!!!!!!
int Connection = 0;                   // 0 - Bluetooth , 1 - NodeMCU/ESP8266

float get_PH();
int get_EC();
int n = 0;                              //used to control ISR based on app input.

float PH;
int PH_decimal;
int Conductivity;
float Humidity;
float temperature;
int temperatureDecimal;

int state = 0;
int gpio = 0;
void setup() {
 Wire.begin(8);                /* join i2c bus with address 8 */
 Wire.onReceive(receiveEvent); /* register receive event */
 Wire.onRequest(requestEvent); /* register request event */
 Serial.begin(9600);           /* start serial for debug */

  pinMode(DHT_Input, INPUT);                //Use DHT11 lib.
  pinMode(pH_Input, INPUT);                 //pH sensor input
  pinMode(EC_Input, INPUT);                 //EC input    
  pinMode(Temp_Input, INPUT);               //temp probe input
  
  pinMode(PH_Increase, OUTPUT);             //Relay controlled
  pinMode(PH_Decrease, OUTPUT);             //Relay controlled
  pinMode(Nutrients_Incearse, OUTPUT);      //Relay controlled
  pinMode(Nutrients_Decrease, OUTPUT);      //Relay controlled
  pinMode(Water_Pump, OUTPUT);              //Relay controlled
  pinMode(Lights, OUTPUT);                  //Relay controlled
  pinMode(Humidifier,OUTPUT);               //Relay controlled
  pinMode(Fans,OUTPUT);                     //Relay controlled
  
  //pinMode(13,OUTPUT);
  //digitalWrite(13,LOW);
  digitalWrite(PH_Increase, On);           //Turn OFF Relay
  digitalWrite(PH_Decrease, Off);           //Turn OFF Relay
  digitalWrite(Nutrients_Incearse, Off);    //Turn OFF Relay
  digitalWrite(Nutrients_Decrease, Off);    //Turn OFF Relay
  digitalWrite(Water_Pump, Off);            //Turn OFF Relay
  digitalWrite(Humidifier, Off);            //Turn OFF Relay
  digitalWrite(Fans, Off);                  //Turn OFF Relay
  digitalWrite(Lights, On);                 //Turn ON Relay for Lights
}

void isrFunc(){                                                   // ISR !!!!!!!!
  if(n==1)
  {
    digitalWrite(Water_Pump,!digitalRead(Water_Pump));
    Serial.println(digitalRead(Water_Pump));
  }
  else
  {
    digitalWrite(Water_Pump,HIGH);
    Serial.println("Water Pump OFF");
  }
}


void loop() {
  
  if(gpio == 1){
    Connection = 1;                             // NodeMCU/ESP8266 is connected
    gpio = 0;
    Serial.println("NodeMCU Connected");
  }
  else{
    Connection = 0;
  }
  int chk = DHT11.read(DHT_Input);              // Get value from DHT11 sensor
  Humidity = DHT11.humidity;  
  temperature = DHT11.temperature;
  //Humidity = 40;
  //temperature = 27;

  PH = get_PH();
  Conductivity = get_EC();
/*  float PH_Lower_Range = 6.5;
  float PH_Upper_Range = 7.5;
  int EC_Lower_Range = 500;
  int EC_Upper_Range = 600;
*/
  float PH_Lower_Range = PH - 0.5;
  float PH_Upper_Range = PH + 0.5;
  int EC_Lower_Range = Conductivity - 50;
  int EC_Upper_Range = Conductivity + 50;
  

  if(PH < PH_Lower_Range || gpio == 2)
  {
    Serial.println("PH_inc on");
    digitalWrite(PH_Increase, LOW);
    digitalWrite(13,HIGH);
    delay(1000);                              //Use timer interrupt!!
    digitalWrite(PH_Increase, HIGH); 
    digitalWrite(13,LOW);
    Serial.println("PH_inc off");
    gpio = 0;
  }
  if(PH > PH_Upper_Range || gpio == 3)
  {
    Serial.println("PH_dec on");
    digitalWrite(PH_Decrease, LOW);
    delay(1000);                              //Use timer interrupt!!
    digitalWrite(PH_Decrease, HIGH);   
    Serial.println("PH_dec off");
    gpio = 0;
  }
  
  if(Conductivity < EC_Lower_Range || gpio == 4)
  {
    Serial.println("nu_inc on");
    digitalWrite(Nutrients_Incearse, LOW);
    delay(1000);                              //Use timer interrupt!!
    digitalWrite(Nutrients_Incearse, HIGH);       
    Serial.println("nu_inc off");
    gpio = 0;
  }
  
  if(Conductivity > EC_Upper_Range || gpio == 5)
  {
    Serial.println("nu_dec on");
    digitalWrite(Nutrients_Decrease, LOW);
    delay(1000);                               //Use timer interrupt!!
    digitalWrite(Nutrients_Decrease, HIGH);       
    Serial.println("nu_dec off");
    gpio = 0;
  }
  if(gpio == 6)                                 //Water Pump
  {
    n=1;
    gpio = 0; 
  }
  if(gpio == 7)
  {
    n=0;
    gpio = 0;  
  }
  
  if(gpio == 8)
  {
//    Serial.println("Lights on");
    digitalWrite(Lights, On);
    gpio = 0;
  }
  else if(gpio == 9)
  {
//    Serial.println("Lights off");
    digitalWrite(Lights, Off);
    gpio = 0;
  }

 //delay(100);
}

float get_PH()
{
  digitalWrite(pH_Input, LOW);
  float PH = analogRead(pH_Input);
  //PH = 7;
  //Firebase.setInt("PH", PH);
  return PH;
}

int get_EC()
{
 // digitalWrite(EC_Input, HIGH);
  int Conductivity = analogRead(EC_Input);  
  Conductivity = 550;
  //Firebase.setInt("Conductivity", Conductivity);
  return Conductivity;
}

void processCall(String command){
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root= jsonBuffer.parseObject(command);
      
  if (root.success()) {
    gpio = atoi(root["gpio"]);
//    Serial.println(gpio);
    state = atoi(root["state"]);
//    Serial.println(state);

    //set GPIO state  
    //digitalWrite(gpio, state);
  }
}


// function that executes whenever data is received from master
void receiveEvent(int howMany) {
  String data="";
 while (0 <Wire.available()) {
    char c = Wire.read();      /* receive byte as a character */
    data += c;
    
  }
//    Serial.println(data);           /* print the request data */
    processCall(data);         /* to newline */
}

// function that executes whenever data is requested from master
void requestEvent() {
  PH = 13.5;
  int PHint = (int)(PH*10);
  PH_decimal = PHint%10;
  
  Conductivity = 20;
  Humidity = 67;
  temperature = 24.67;
  int temperatureInt = (int)(temperature*10);
  temperatureDecimal = temperatureInt%10;
  
 Wire.write((byte)PH);  /*send string on request */
 Wire.write((byte)PH_decimal);
 Wire.write((byte)Conductivity);
 Wire.write((byte)Humidity);
 Wire.write((byte)temperature);
 Wire.write((byte)temperatureDecimal);
}
