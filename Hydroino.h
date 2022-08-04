/*
 TODO: 
 La parte hardware dovrebbe essere apposto, manca ottenere gli indirizzi, i permessi ed i fogli google drive
 
 https://www.youtube.com/watch?v=OiluixmbkRM&ab_channel=paoloaliverti
 **/


// SAMPLING PERIOD
// periodo di campionamento espresso in minuti
#define MIN 20 //minuti

// WIFI
// id del wifi e password 
#define SECRET_SSID ""
#define SECRET_PASS ""

// LIV WATER
// pin in cui è inserito il sensore dell'acqua ( analogico )
#define LIVPIN 36
#define VALUE_MIN 0 //cm 
#define VALUE_MAX 15 //cm

// DHT
// pin a cui è inserito il DHT
#define DHTPIN 4

// API
// parametri necessari per il protocollo http (gli stessi parametri del file .gs)
String path = ""; 
String pathbase = "/macros/s/AKfycbzY3Xz4m6gP5h3B99DzJz9jrbKXFEmivMrjr6mNlPG6hGa0ZDkZTQ4yeU6pcyTxzSk0Mg/exec";
