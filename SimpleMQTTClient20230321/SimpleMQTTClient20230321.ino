#include "EspMQTTClient.h"
String message;

EspMQTTClient client(
  "WiFiSSID",
  "Password",
  "192.168.1.39",  // MQTT Broker server ip
  "MQTTuser",   // Can be omitted if not needed
  "MQTTpassword",   // Can be omitted if not needed
  "devicename",     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted
);

void setup()
{
  Serial.begin(115200);
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
}

void onConnectionEstablished()
{
    client.subscribe("/shotokutech/twatch/touchscreen", [](const String & payload) {
    Serial.println(payload);
  });
  client.publish("/shotokutech/twatch/touchscreen", message); // You can activate the retain flag by setting the third parameter to true
}

void loop()
{
  message="on";
  client.loop();
  onConnectionEstablished();  
  delay(5000);
  message="off";
  client.loop();
  onConnectionEstablished();
  delay(5000);
}
