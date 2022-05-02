#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <Servo.h>




const char* ssid = "Naren";//put your wifi network name here
const char* password = "password@0987654321";//put your wifi password here
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

Servo myservo;
String amount="";
String passcode="";
String myPasscode="2113"; //predefined passcode, change as per your desire
 
void setup(){
  Serial.begin(115200);
  myservo.attach(15); //attach the servo on pin D8)
  myservo.write(150);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}


void setup_wifi() {
    delay(100);
  // We start by connecting to a WiFi network
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) 
{
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  String message;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    message+=(char)payload[i];
}
   if(message==myPasscode)
  { 
    publish("Approved");

      dispatchMoney();}
  else
  {
    publish("Denied");
  }
  Serial.println();
  Serial.println("-----------------------");
}
void publish(String msg){

     char message[100];
     msg.toCharArray(message,100);
    client.publish("/ABC/ATM/ACK", message);
    delay(100);
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    //if you MQTT broker has clientID,username and password
    //please change following line to    if (client.connect(clientId,userName,passWord))
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
     //once connected to MQTT broker, subscribe command if any
      client.subscribe("/ABC/ATM/RCV");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 6 seconds before retrying
      delay(6000);
    }
  }
} //end reconnect()
void dispatchMoney() {
  Serial.println("Dispatching money...");
  myservo.write(90); //rotates the motor counterclockwise at slow speed
  delay(5000);
  myservo.write(150); //rotates the motor counterclockwise at slow speed
  
}
