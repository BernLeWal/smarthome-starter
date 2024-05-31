# Orion-LD

- Orion-LD is an advanced **context broker** implementation designed to **manage and distribute contextual information** in real-time.
- It is built on the principles of the **NGSI-LD (Next Generation Service Interface - Linked Data) standard**, which aims to facilitate the development of smart applications by **ensuring interoperability** and context management capabilities.
- The primary goal of Orion-LD is to enable efficient, scalable, and interoperable handling of contextual data, making it a cornerstone in the development of smart cities, IoT applications, and data-driven solutions.

## Features

- **Context Information Management**: Orion-LD allows for the creation, update, and retrieval of context information, ensuring real-time awareness and decision-making capabilities.
- **NGSI-LD Compliance**: Full adherence to the NGSI-LD standard ensures **interoperability with other compliant systems** and components, promoting a cohesive ecosystem.
- **Linked Data Integration**: Utilizes Linked Data principles to enhance **data connectivity** and **semantic relationships**, enabling *more insightful data analytics and integration*.
- **Scalability**: Designed to handle **large volumes of data** and **high-throughput** operations, making it suitable for large-scale applications.
- **Subscription and Notification**: Supports **subscription to context changes** and notifications, allowing *applications to react in real-time to changes in their environment*.
- **Federation Support**: Facilitates the federation of multiple context brokers, enabling the creation of distributed and collaborative environments.
- **Security and Privacy**: Implements robust security mechanisms to protect data integrity and privacy.

## Links

- Orion-LD GitHub Page: https://github.com/FIWARE/context.Orion-LD
- Quick-Start Guide: https://github.com/FIWARE/context.Orion-LD/blob/develop/doc/manuals-ld/quick-start-guide.md
- Official Docker Image: https://hub.docker.com/r/fiware/orion-ld
- Official FIWARE Orion Page: https://fiware-orion.readthedocs.io/en/master/


## Architecture & Function

A Context Broker acquires contextual information from heterogeneous sources and fuses into a coherent model that is then shared with computing entities in the space. 

![https://www.researchgate.net/figure/A-Context-Broker-acquires-contextual-information-from-heterogeneous-sources-and-fuses_fig1_228872565](context-broker.png)

 The Orion-LD Context Broker relies on open source MongoDB technology to keep persistence of the context data it holds.
 ![https://github.com/FIWARE/tutorials.NGSI-LD/blob/master/docs/subscriptions.md](Orion-LD-Components-with-Interactions.png)

 ## HOWTO

Integrating Orion-LD into a Python application

1. Deploy Orion-LD using Docker
```docker
  orion-ld:
    image: fiware/orion-ld
    ports:
      - "1026:1026"
    depends_on:
      - mongo-db
    command: -dbhost mongo-db

  mongo-db:
    image: mongo:4.4
    command: --nojournal
    ports:
      - "27017:27017"
```
See [docker-compose.yml](../docker-compose.yml)

2. Install required Libraries with pip
```shell
pip install requests fiware-orion
```

3. Connect and Interact with Orion-LD:
```python
import requests

ORION_LD_URL = "http://localhost:1026/ngsi-ld/v1/entities"

# Create a new entity
entity = {
    "id": "urn:ngsi-ld:Device:001",
    "type": "Device",
    "temperature": {"type": "Property", "value": 23.5}
}

response = requests.post(ORION_LD_URL, json=entity, headers={"Content-Type": "application/json"})
print(response.status_code, response.json())
```

4. Handle Notifications, e.g. using a Flask webserver who will receive the requests from Orion-LD
```python
import json
from flask import Flask, request

app = Flask(__name__)

@app.route('/notify', methods=['POST'])
def notify():
    notification = request.json
    print("Received notification:", json.dumps(notification, indent=2))
    return '', 204

if __name__ == '__main__':
    app.run(port=5000)
```