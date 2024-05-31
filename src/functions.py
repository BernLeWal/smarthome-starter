"""Functions to process messages and interact with Orion Context Broker."""
import os
from dotenv import load_dotenv

load_dotenv()

NGSI_LD_CONTEXT = os.getenv("NGSI_LD_CONTEXT")

def humitemp_message_to_entity(message : dict):
    """Process a message from the MQTT broker and return an NGSI-LD entity."""
    print("Received message:", message)
    print(" \tTemperature:", str(message["temp"]) + " °C" + " ")
    print(" \tHumidity:", str(message["hum"]) + " %" + " ")

    ngsi_entity = {
        "id": message["id"],
        "type": "SensorReading",
        "@context": NGSI_LD_CONTEXT,
        "temperature": {
            "type": "Property",
            "value": message["temp"],
        },
        "humidity": {
            "type": "Property",
            "value": message["hum"],
        },
        "pressure": {
            "type": "Property",
            "value": message["pressure"],
        },
    }
    return ngsi_entity
