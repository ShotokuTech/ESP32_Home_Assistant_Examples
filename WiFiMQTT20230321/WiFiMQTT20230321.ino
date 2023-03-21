#include <WiFi.h>
#include <MQTTPubSubClient.h>

const char* ssid = "WiFiSSID";
const char* pass = "Password";

WiFiClient client;
MQTTPubSubClient mqtt;

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, pass);

    Serial.print("connecting to wifi...");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println(" connected!");

    Serial.print("connecting to host...");
    while (!client.connect("192.168.1.39", 1883)) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println(" connected!");

    // initialize mqtt client
    mqtt.begin(client);

    Serial.print("connecting to mqtt broker...");
    while (!mqtt.connect("devicename", "MQTTuser", "MQTTpassword")) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println(" connected!");
    // subscribe topic and callback which is called when /hello has come
    mqtt.subscribe("/shotokutech/twatch/touchscreen", [](const String& payload, const size_t size) {
        Serial.print("/shotokutech/twatch/touchscreen ");
        Serial.println(payload);
    });
    
}

void loop() {
    mqtt.update();  // should be called
    delay(5000);
    mqtt.publish("/shotokutech/twatch/touchscreen", "on");
    mqtt.update();  // should be called
    delay(5000);
    mqtt.publish("/shotokutech/twatch/touchscreen", "off");
}
