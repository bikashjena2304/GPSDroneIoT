#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";
const char* topic = "/hello";

WiFiClient espClient;
PubSubClient client(espClient);

void setup(){
	Serial.begin(115200);
	WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
	delay(50);
	client.setServer("192.168.1.200",1883);
	client.connect("nodemcu");
	client.setCallback(printMessage);
	client.subscribe(topic);
}

void loop(){
	client.loop();
}

void printMessage(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
