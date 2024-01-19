import paho.mqtt.client as mqtt
import time

mqtt_server = "192.168.8.151"
mqtt_port = 1883
mqtt_username = "pi"
mqtt_password = "kasun1234"

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("esp32/data")

def on_message(client, userdata, msg):
    print(f"Received message on topic {msg.topic}: {msg.payload.decode()}")

def main():
    client = mqtt.Client()
    client.username_pw_set(mqtt_username, mqtt_password)
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect(mqtt_server, mqtt_port, 60)

    client.loop_start()

    try:
        while True:
            # Your Raspberry Pi code here for publishing messages to ESP32
            client.publish("rpi/data", "Hello from Raspberry Pi")
            time.sleep(5)  # Adjust delay according to your requirements

    except KeyboardInterrupt:
        client.disconnect()
        print("Disconnected from MQTT broker")

if __name__ == "__main__":
    main()

