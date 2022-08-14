
//---------------------------- S E T T I N G S ---------------------------------
 
// SAMPLING PERIOD
// sampling period
#define MIN 15 //min

// LEVEL WATER
#define LIVPIN 36
#define VALUE_MIN_LV 0  
#define VALUE_MAX_LV 743

// DHT
#define DHTPIN 4

// hum soil pin
#define HUMPIN1 32
#define HUMPIN2 34
#define VALUE_S_A_H_11 1566.7
#define VALUE_S_H_11 80 
#define VALUE_S_A_H_12 2629 
#define VALUE_S_H_12 30 
#define VALUE_S_A_H_21 1572.40
#define VALUE_S_H_21 80 
#define VALUE_S_A_H_22 2745.5 
#define VALUE_S_H_22 30 

// transistor as switch
#define TRANSPIN 25
//---------------------------------------------------------------------

//---------------------- W I F I --------------------------------------
//ENTER_GOOGLE_DEPLOYMENT_ID
const char * ssid = "WIFI_NAME";
const char * password = "WIFI_PASSWORD";
const String GOOGLE_SCRIPT_ID = "WIFI_GOOGLE_APPS_ID";
//---------------------------------------------------------------------

//----------------- L I B R A R I E S ---------------------------------
//#include <Adafruit_Sensor.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
//---------------------------------------------------------------------

/************************************************************************************
 *  setup function starts
 **********************************************************************************/
 void setup() {
  
  //---------------------------------------------------------------------

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  int count=0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    count=+1;
    if (count==10){
      esp_sleep_enable_timer_wakeup(10 * 1000000);
      esp_deep_sleep_start();
    }
  }
  //---------------------------------------------------------------------

  
  delay(10);
  
  // TRANSPIN LGPTQ+
  pinMode(TRANSPIN, OUTPUT);
  // switch on 
  switchNPN(1);
  
  // inizialization dht sensor
  pinMode(DHTPIN, INPUT);
  dht.begin();
  
  delay(10);
  
  // send data
  upload_data();

  // switch off 
  switchNPN(0);

  // Good night!
  goToDeepSleep();
}

/************************************************************************************
 *  loop function starts
 **********************************************************************************/
void loop() { 
  // Give papa a cup of proper coffe in a copper coffe cup
}


/************************************************************************************
 *  loop function starts
 **********************************************************************************/
void upload_data()
{
  //------------ leggo i sensori -----------------
  delay(1000);
  //-------------- Water level---------------------
  int z_A0 = analogRead(LIVPIN);
  float temp_ext0 = dht.readTemperature();
  float hum_ext0 = dht.readHumidity();
  int hum1_A0=analogRead(HUMPIN1);
  int hum2_A0=analogRead(HUMPIN2);
  
  delay(1000);
  
  int z_A1 = analogRead(LIVPIN);
  float temp_ext1 = dht.readTemperature();
  float hum_ext1 = dht.readHumidity();
  int hum1_A1=analogRead(HUMPIN1);
  int hum2_A1=analogRead(HUMPIN2);
  
  delay(1000);
  
  int z_A2 = analogRead(LIVPIN);
  float temp_ext2 = dht.readTemperature();
  float hum_ext2 = dht.readHumidity();
  int hum1_A2=analogRead(HUMPIN1);
  int hum2_A2=analogRead(HUMPIN2);

  //---------- Calcolo i valori medi -----------------
  //-------------- Water level------------------------
  int z_A=(z_A0+z_A1+z_A2)/3;

  // int z_water=z_A;
  float z_water = map(z_A, VALUE_MIN_LV, VALUE_MAX_LV,0,4);
  if (z_water > 4){
    z_water=4;
  }
  if (z_water <0) {
    z_water=0;
  }
  
  //----------------- DHT11 ------------------------
  
  float temp_ext = (temp_ext0+temp_ext1+temp_ext2)/3;

  float hum_ext = (hum_ext0+hum_ext1+hum_ext2)/3;

  //----------------- Soil ---------------------------

  int hum1_A=(hum1_A0+hum1_A1+hum1_A2)/3;

  float hum1 = map(hum1_A, VALUE_S_A_H_11 ,VALUE_S_A_H_12, VALUE_S_H_11, VALUE_S_H_12);

  if(hum1>100){
    hum1=100;
  }
  if(hum1<0){
    hum1=0; 
  }
  
  //----------------- Soil 2 ---------------------------

  int hum2_A=(hum2_A0+hum2_A1+hum2_A2)/3;
  
  float hum2 = map(hum1_A, VALUE_S_A_H_21 ,VALUE_S_A_H_22, VALUE_S_H_21, VALUE_S_H_22);

  if(hum2>100){
    hum2=100;
  }
  if(hum2<0){
    hum2=0; 
  }
  
  //------------------- Send data -------------------------
  String param;
  param  = "temp="+String(temp_ext);
  param += "&hum_ext="+String(hum_ext);
  param += "&z_water="+String(z_water);
  param += "&hum1="+String(hum1);
  param += "&hum2="+String(hum2);

  write_to_google_sheet(param);  

}


/************************************************************************************
 *  loop function starts
 **********************************************************************************/
void write_to_google_sheet(String params) {
   HTTPClient http;
   String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?"+params;
   //Serial.print(url);
    //---------------------------------------------------------------------
    //starts posting data to google sheet
    http.begin(url.c_str());
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpCode = http.GET();  
    //---------------------------------------------------------------------
    //getting response from google sheet
    String payload;
    if (httpCode > 0) {
        payload = http.getString();     
    }
    //---------------------------------------------------------------------
    http.end();
}

/************************************************************************************
 *  loop function starts
 **********************************************************************************/
void goToDeepSleep(){

  esp_sleep_enable_timer_wakeup(MIN * 60 * 1000000);
  esp_deep_sleep_start();
  
}

/************************************************************************************
 *  loop function starts
 **********************************************************************************/
void switchNPN(bool onoff){
  if (onoff == 1){
    digitalWrite(TRANSPIN, HIGH);
  }
  else{
    digitalWrite(TRANSPIN, LOW);
  }
}
