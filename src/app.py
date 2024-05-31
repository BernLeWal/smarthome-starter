#! /usr/bin/env python3
"""This script subscribes to the MQTT broker and listens for messages from the sensors. 
It then processes the messages and sends them to the Context Broker."""
import random
import string
import json
import os
import requests
import paho.mqtt.client as paho
from dotenv import load_dotenv

from functions import humitemp_message_to_entity
from orion import create_subscription, post_or_update_entity


# Settings
load_dotenv()
ORION_URL = os.getenv("ORION_URL")
MQTT_BROKER = os.getenv("MQTT_BROKER")


# Function to generate a random ID
def generate_random_id(length : int):
    """Generate a random ID of a given length."""
    letters_and_digits = string.ascii_letters + string.digits
    return ''.join(random.choice(letters_and_digits) for i in range(length))

# Subscriber
def on_connect_subscriber(client : paho.Client, userdata, flags, rc):
    """Callback for when the subscriber connects to the MQTT broker."""
    topic = "/raskeytar/shs/humitemp/+"
    client.subscribe(topic, 0)

def on_message_subscriber(client : paho.Client, userdata, message):
    """Callback for when the subscriber receives a message from the MQTT broker."""
    message = json.loads(message.payload.decode("utf-8"))
    ngsi_entity = humitemp_message_to_entity(message)
    post_or_update_entity(ngsi_entity)


def main():
    """Main function to subscribe to the MQTT broker and listen for messages."""
    response = requests.get(f"{ORION_URL}/subscriptions/urn:ngsi-ld:Subscription:1", timeout=10)
    if response.status_code == 404:
        create_subscription()
    else:
        print("Subscription already exists.")

    uid_subscriber = generate_random_id(16)
    client_subscriber = paho.Client(paho.CallbackAPIVersion.VERSION1, uid_subscriber)
    client_subscriber.on_connect = on_connect_subscriber
    client_subscriber.on_message = on_message_subscriber

    print("Connecting to broker for subscribing...")
    # client_subscriber.tls_set(cert_reqs=ssl.CERT_NONE)
    # client_subscriber.tls_insecure_set(True)
    client_subscriber.username_pw_set("shs-sensor", "shs-pass")
    client_subscriber.connect(MQTT_BROKER, 1883, 60)
    client_subscriber.loop_start()
    print("Connected for subscribing - loop started")

    # uncomment to keep the script running
    while True:
        pass

    #uncomment to stop after 60 seconds
    # time.sleep(60)
    # # Stopping subscriber loop
    # client_subscriber.loop_stop()
    # client_subscriber.disconnect()
    # print("Disconnected for subscribing.")


if __name__ == "__main__":
    main()
