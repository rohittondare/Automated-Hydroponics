#include <Ticker.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <dht11.h>

// Set these to run example. 
#define FIREBASE_HOST "h2gro-a9352.firebaseio.com"
#define FIREBASE_AUTH "IwzlWVheacyt3Z2x3QmVyrems1LSy5xCMMoGORwR"
#define WIFI_SSID "Emma"
#define WIFI_PASSWORD "81458145"

#define On 1
#define Off 0

#define Sensor_Input A0
#define PH_Increase 0
#define PH_Decrease 1
#define Nutrients_Increase 2
#define Nutrients_Decrease 3
#define Water_Pump 4
#define Lights 5
#define DHT_Input 6
#define Select_Line 7

dht11 DHT11;                          //DHT11 Object
Ticker ticker;
volatile int seconds = 0; //make it volatile because it is used inside the interrupt

int get_PH();
int get_EC();

void setup() { 
  //Serial.begin(9600); 

 ticker.attach(1,isrFunc);//tickerObj.attach(timeInSecs,isrFunction)
  // connect to wifi. 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
  Serial.print("connecting"); 
  while (WiFi.status() != WL_CONNECTED) { 
    Serial.print("."); 
    delay(500); 
  } 
  Serial.println(); 
  Serial.print("connected: "); 
  Serial.println(WiFi.localIP()); 
   
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 

  pinMode(PH_Increase, OUTPUT);             //Relay controlled
  pinMode(PH_Decrease, OUTPUT);             //Relay controlled
  pinMode(Nutrients_Increase, OUTPUT);      //Relay controlled
  pinMode(Nutrients_Decrease, OUTPUT);      //Relay controlled
  pinMode(Water_Pump, OUTPUT);              //Relay controlled
  pinMode(Lights, OUTPUT);                  //Relay controlled
  pinMode(DHT_Input, INPUT);                //Use DHT11 lib.
  pinMode(Sensor_Input, INPUT);             //Connected to MUX to get input from 2 sensors
  pinMode(Select_Line, OUTPUT);             //Select line to control MUX

  
  digitalWrite(PH_Increase, Off);           //Turn OFF Relay
  digitalWrite(PH_Decrease, Off);           //Turn OFF Relay
  digitalWrite(Nutrients_Increase, Off);    //Turn OFF Relay
  digitalWrite(Nutrients_Decrease, Off);    //Turn OFF Relay
  digitalWrite(Water_Pump, Off);            //Turn OFF Relay
  digitalWrite(Lights, On);                 //Turn ON Relay for Lights


  // set value 
  Firebase.setInt("PH_Increase", Off); 
  // handle error 
  if (Firebase.failed()) { 
      Firebase.setString("Error", Firebase.error());
      Serial.print("setting /number failed:"); 
      Serial.println(Firebase.error());   
      return; 
  } 
  delay(100);
      // set value 
  Firebase.setInt("PH_Decrease", Off); 
  // handle error 
  if (Firebase.failed()) { 
      Firebase.setString("Error", Firebase.error());
      Serial.print("setting /number failed:"); 
      Serial.println(Firebase.error());   
      return; 
  } 
  delay(100);
      // set value 
  Firebase.setInt("Nutrients_Increase", Off); 
  // handle error 
  if (Firebase.failed()) { 
      Firebase.setString("Error", Firebase.error());
      Serial.print("setting /number failed:"); 
      Serial.println(Firebase.error());   
      return; 
  } 
  delay(100);
      // set value 
  Firebase.setInt("Nutrients_Decrease", Off); 
  // handle error 
  if (Firebase.failed()) { 
      Firebase.setString("Error", Firebase.error());
      Serial.print("setting /number failed:"); 
      Serial.println(Firebase.error());   
      return; 
  } 
  delay(100);
      // set value 
  Firebase.setInt("Water_Pump", Off); 
  // handle error 
  if (Firebase.failed()) { 
      Firebase.setString("Error", Firebase.error());
      Serial.print("setting /number failed:"); 
      Serial.println(Firebase.error());   
      return; 
  } 
  delay(100);
      // set value 
  Firebase.setInt("Lights", Off); 
  // handle error 
  if (Firebase.failed()) { 
      Firebase.setString("Error", Firebase.error());
      Serial.print("setting /number failed:"); 
      Serial.println(Firebase.error());   
      return; 
  } 
  delay(100);

      // set value 
  Firebase.setInt("PH_val", Off); 
  // handle error 
  if (Firebase.failed()) { 
      Firebase.setString("Error", Firebase.error());
      Serial.print("setting /number failed:"); 
      Serial.println(Firebase.error());   
      return; 
  } 
  delay(100);

      // set value 
  Firebase.setInt("Conductivity_val", Off); 
  // handle error 
  if (Firebase.failed()) { 
      Firebase.setString("Error", Firebase.error());
      Serial.print("setting /number failed:"); 
      Serial.println(Firebase.error());   
      return; 
  } 
  delay(100);
      // set value 
  Firebase.setFloat("Temp_val", Off); 
  // handle error 
  if (Firebase.failed()) { 
      Firebase.setString("Error", Firebase.error());
      Serial.print("setting /number failed:"); 
      Serial.println(Firebase.error());   
      return; 
  } 
  delay(100);
      // set value 
  Firebase.setFloat("Humidity_val", Off); 
  // handle error 
  if (Firebase.failed()) { 
      Firebase.setString("Error", Firebase.error());
      Serial.print("setting /number failed:"); 
      Serial.println(Firebase.error());   
      return; 
  } 
  delay(100);
    Firebase.setString("Error", "No Error"); 
  // handle error 
  if (Firebase.failed()) { 
    Firebase.setString("Error", Firebase.error());
      Serial.print("setting /number failed:"); 
      Serial.println(Firebase.error());   
      return; 
  } 
  delay(100);
} 

void isrFunc(){
  digitalWrite(4,!digitalRead(4));
}

//int n = 0; 
 //use setint default 0 value .. push value
void loop() { 
  int chk = DHT11.read(DHT_Input);              //Get value from DHT11 sensor
  float Humidity_val = DHT11.humidity;  
  float temp_val = DHT11.temperature;
  Firebase.setFloat("Humidity_val", Humidity_val);
  Firebase.setFloat("temp_val", temp_val);

  int PH_val = get_PH();
  int Conductivity_val = get_EC();
  int PH_Lower_Range = 6.5;
  int PH_Upper_Range = 7.5;
  int EC_Lower_Range = 500;
  int EC_Upper_Range = 600;
  
  
  if(PH_val < PH_Lower_Range || Firebase.getInt("PH_Increase") == On)
  {
    digitalWrite(PH_Increase, LOW);
    delay(1000);                              //Use timer interrupt!!
    digitalWrite(PH_Increase, HIGH); 
    Firebase.setInt("PH_Increase",Off);                         //WORKS!!
    if (Firebase.failed()) { 
      Firebase.setString("Error", Firebase.error());
      Serial.print("setting /number failed:"); 
      Serial.println(Firebase.error());   
      return; 
    } 
  }
  if(PH_val > PH_Upper_Range || Firebase.getInt("PH_Decrease") == On)
  {
    digitalWrite(PH_Decrease, LOW);
    delay(1000);                              //Use timer interrupt!!
    digitalWrite(PH_Decrease, HIGH);   
    
    Firebase.setInt("PH_Decrease",Off);                         //WORKS!!
    if (Firebase.failed()) { 
      Firebase.setString("Error", Firebase.error());
      Serial.print("setting /number failed:"); 
      Serial.println(Firebase.error());   
      return; 
    } 
    
  /*  //String name = Firebase.pushInt("PH_Decrease", 0);         //Does not work!! creates a new entry in the database
    // handle error 
    if (Firebase.failed()) { 
      Serial.print("pushing /logs failed:"); 
      Serial.println(Firebase.error());   
      return; 
    } */
  }
  
  if(Conductivity_val < EC_Lower_Range || Firebase.getInt("Nutrients_Increase") == On)
  {
    digitalWrite(Nutrients_Increase, LOW);
    delay(1000);                              //Use timer interrupt!!
    digitalWrite(Nutrients_Increase, HIGH);       
    Firebase.setInt("Nutrients_Increase",Off);                         //WORKS!!
    if (Firebase.failed()) { 
      Firebase.setString("Error", Firebase.error());
      Serial.print("setting /number failed:"); 
      Serial.println(Firebase.error());   
      return; 
    } 
  }
  
  if(Conductivity_val > EC_Upper_Range || Firebase.getInt("Nutrients_Decrease") == On)
  {
    digitalWrite(Nutrients_Decrease, LOW);
    delay(1000);                               //Use timer interrupt!!
    digitalWrite(Nutrients_Decrease, HIGH);       
    Firebase.setInt("Nutrients_Decrease",Off);                         //WORKS!!
    if (Firebase.failed()) { 
      Firebase.setString("Error", Firebase.error());
      Serial.print("setting /number failed:"); 
      Serial.println(Firebase.error());   
      return; 
    } 
  }
  
                                              // add isr for Main Pump.!!!!!
}


int get_PH()
{
  digitalWrite(Select_Line, LOW);
  int PH_val = analogRead(Sensor_Input);  
  Firebase.setInt("PH_val", PH_val);
  if (Firebase.failed()) { 
    Firebase.setString("Error", Firebase.error());
  }
  return PH_val;
}


int get_EC()
{
  digitalWrite(Select_Line, HIGH);
  int Conductivity_val = analogRead(Sensor_Input);  
  Firebase.setInt("Conductivity_val", Conductivity_val);
  if (Firebase.failed()) { 
      Firebase.setString("Error", Firebase.error());
  }
  return Conductivity_val;
}
