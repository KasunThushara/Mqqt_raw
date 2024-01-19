#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Dialog 4G xxx";
const char* password = "xxxxxxx";
const char* mqtt_server = "192.168.8.151";
const char* mqtt_username = "pi";
const char* mqtt_password = "kasun1234";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
    delay(10);
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);

    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP32Client", mqtt_username, mqtt_password)) {
            Serial.println("connected");
            client.subscribe("rpi/data");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void setup() {
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    // Example: Publish data from ESP32 to "esp32/data" topic
    int sensorValue = 36;  // Replace this with your actual sensor data
    client.publish("esp32/data", String(sensorValue).c_str());
  Serial.println(sensorValue);
    delay(5000);  // Adjust delay as needed
}
