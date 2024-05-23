"""Module to interact with Orion Context Broker."""
import os
import requests
from dotenv import load_dotenv


# Settings
load_dotenv()
ORION_URL = os.getenv("ORION_URL")
NGSI_LD_CONTEXT = os.getenv("NGSI_LD_CONTEXT")
QUANTUMLEAP_URL = os.getenv("QUANTUMLEAP_URL")


def create_subscription():
    """Create a subscription in Orion Context Broker."""
    headers = {
        "Content-Type": "application/ld+json",
    }
    subscription = {
        "id": "urn:ngsi-ld:Subscription:1",
        "description": "Notify QuantumLeap",
        "type": "Subscription",
        "entities": [
            {
                "type": "SensorReading"
            }
        ],
        "watchedAttributes": ["temperature"],
        "notification": {
            "attributes": ["temperature", "humidity", "pressure"],
            "endpoint": {
                "uri": QUANTUMLEAP_URL,
                "accept": "application/json",
            }
        },
        "@context": NGSI_LD_CONTEXT,        
    }

    response = requests.post(f"{ORION_URL}/subscriptions",
        headers=headers, json=subscription, timeout=10)
    if response.status_code == 201:
        print("Subscription created successfully.")
    else:
        print("Failed to create subscription:", response.status_code, response.text)


def post_or_update_entity(entity : dict):
    """Post or update an NGSI-LD entity in Orion Context Broker."""
    headers = {
        "Content-Type": "application/ld+json",
    }

    response = requests.patch(f"{ORION_URL}/entities/{entity['id']}/attrs",
        headers=headers, json=entity, timeout=10)
    if response.status_code in [200, 204]:
        print(f"Updated Entity {entity['id']}:", response.status_code, response.text)

    if response.status_code == 404:
        response = requests.post(f"{ORION_URL}/entities", headers=headers, json=entity, timeout=10)
        print(f"Posted  Entity {entity['id']}:", response.status_code, response.text)

    return response.status_code
