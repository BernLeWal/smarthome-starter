# Mosquitto

Mosquitto is a **lightweight, open-source message broker** that implements the **MQTT (Message Queuing Telemetry Transport) protocol**. Developed by the Eclipse Foundation, Mosquitto is designed to facilitate simple, efficient communication between devices, making it ideal for Internet of Things (IoT) applications. 

The primary goal of Mosquitto is to enable **efficient and reliable communication between devices in a lightweight manner**. It aims to support a wide range of environments, from low-power sensors to full-scale servers. By implementing the MQTT protocol, Mosquitto ensures that messages are delivered promptly and accurately, making it suitable for scenarios where **bandwidth and power consumption are critical** considerations.

## Links

### Mosquitto Broker:
- Official Page: https://mosquitto.org/
- A Testserver: https://test.mosquitto.org/  
  Can be used without registration, but will only work for clients a few minutes long.
- Official Docker Image: https://hub.docker.com/_/eclipse-mosquitto

### MQTT Protocol:
- Official Page of MQTT-protocol: https://mqtt.org/

### Tools
- **Online MQTT-Client**: https://testclient-cloud.mqtt.cool/  
This will only work for MQTT-Brokers which are available over the internet, like test.mosquitto.org.
- **Offline MQTT-Client** (to be installed on your computer): https://mqttx.app/
This will also work for the local MQTT-Broker in this project.

## Architecture & Function

### Features

- **MQTT Protocol Support**: Fully compliant with MQTT versions 3.1, 3.1.1, and 5.0, supporting both publish-subscribe and request-response messaging patterns.
- **Lightweight and Efficient**: Designed to be resource-efficient, suitable for embedded systems and low-power devices.
- **Scalability**: Capable of handling thousands of simultaneous connections, making it suitable for large-scale IoT deployments.
- **Security**: Supports SSL/TLS for secure communications, along with authentication mechanisms such as username/password and certificate-based authentication.
- **Persistence**: Provides options for message persistence to ensure message delivery even if the broker or clients are temporarily offline.
- **Quality of Service (QoS)**: Supports QoS levels 0, 1, and 2, allowing clients to specify the desired level of delivery assurance.
- **Bridging**: Allows connecting multiple Mosquitto brokers together to form a larger, distributed network.

### Architecture Overview 
![MQTT Architecture Overview](mqtt-architecture-function.png)

### Topics

- Topic level is a name (like a directories in a Path/Url)
- Topic levels are separated via "/" 
- Topic levels are hierarchically organized

Best practices:
- No spaces in Topic level names!
- Don't use capital letters (Topic Levels are case sensitive)
- The Topic should not start with "/" (because the first Topic-Level, which is left of the "/", will be an empty string)

## HOWTO

Integration into a Python Application:

1. Install Mosquitto Broker, f.e. using Docker
```docker
  mosquitto:
    image: eclipse-mosquitto:latest
    hostname: mosquitto
    container_name: mosquitto
    restart: unless-stopped
    ports:
      - "1883:1883" #default MQTT port
      - "9001:9001" #default MQTT websocket port
    volumes:    
      - ./mosquitto/mosquitto.conf:/mosquitto/config/mosquitto.conf
      - ./mosquitto/pwfile:/mosquitto/config/pwfile
      - ./mosquitto/data:/mosquitto/data:rw
      - ./mosquitto/log:/mosquitto/log:rw
```
  See [docker-compose.yml](../docker-compose.yml)

2. Install the Paho MQTT Python client library using pip:
```shell
pip install paho-mqtt
```

3. Configure your Mosquitto Broker, 
```
allow_anonymous true
listener 1883
listener 9001
```
  See [mosquitto.conf](../mosquitto/mosquitto.conf)

4. Python Client
Import the Paho MQTT Library:
```python
import paho.mqtt.client as mqtt
```
Register callback-functions:
```python
def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")
    client.subscribe("topic/test")

def on_message(client, userdata, msg):
    print(f"{msg.topic} {msg.payload}")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
```
Connect to the Broker:
```python
client.connect("localhost", 1883, 60)
```
Publish a message to a topic
```python
client.publish("topic/test", "Hello, Mosquitto!")
```
Start the network loop to process incoming and outgoing messages:
```python
client.loop_forever()
```