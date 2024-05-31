# SmartHome-Starter (SHS) FiWare integration

Based on https://git.technikum-wien.at/cs-praktika/if23x161/interreg/fiwareweathersensor

## FIWARE

FIWARE ​is the open source platform of choice for building Smart Solutions in multiple sectors.
It provides a simple yet powerful set of enablers and royalty free and open source APIs.

Technology: the FIWARE platform

For an introduction see: https://www.fiware.org/about-us/

## SHS FIWARE Platform

This project sets up an IoT data processing and visualization platform using Docker containers. It includes components for data ingestion, storage, processing, and visualization. The platform utilizes FIWARE components.

### Components Overview

- (**Mosquitto:** MQTT-Broker for message-based transfer of data from the IoT-sensors to the platform. see [Mosquitto.md](Mosquitto.md))
- **Orion-LD:** Context broker for managing context data in NGSI-LD format, see [Orion-LD.md](Orion-LD.md).
- **QuantumLeap:** Stores time-series data received from Orion-LD, see [QuantumLeap.md](QuantumLeap.md).
- **Grafana:** Dashboard visualization tool for analyzing data stored in CrateDB, see [Grafana.md](Grafana.md).
- **MongoDB:** Database for storing non-time-series data.
- **CrateDB:** Distributed SQL database for storing large volumes of time-series data efficiently, see [CrateDB.md](CrateDB.md).
- **Python App:** Subscribes to MQTT messages, processes them, and updates context data in Orion-LD, see [app.py](../src/app.py)

## Running

- ```docker compose up -d```
- Prepare SHS as metioned in [README.md](./README.md): The SHS Sensors should successfully transfer their data to the MQTT Broker and you should be able to subscribe and visualize them using a MQTT client.

