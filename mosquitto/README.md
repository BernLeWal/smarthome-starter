# Eclipse Mosquitto MQTT Broker

A Mosquitto MQTT-Broker is contained here in order to provide a docker container running your own instance of the broker.

## How to use

- Start the container: ```docker compose up -d```
- Check the ip address of your host: ```ipconfig``` --> remember your IPv4 address
- Update the broker-settings in your config.h files
    - mqtt_broker = "<your ipv4 address>"
    - mqtt_port     = 1883
    - mqtt_user = shs-sensor
    - mqtt_pwd = shs-pass
- Build and upload your firmares to your sensors

Remarks: in order to change the credentials see the following section.

## Setup

- Connect to the container and to create the pwfile
```shell
mosquitto_passwd -c -b /mosquitto/config/pwfile shs-sensor shs-pass
mosquitto_passwd -b /mosquitto/config/pwfile shs-client shs-pass
```

## References

- https://medium.com/@tomer.klein/docker-compose-and-mosquitto-mqtt-simplifying-broker-deployment-7aaf469c07ee