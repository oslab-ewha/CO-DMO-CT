#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "MQTTClient.h"

#define ADDRESS    "ssl://0.0.0.0:8883"
#define CLIENTID   "EdgeGateway"
#define TOPIC      "iot/data"
#define QOS        1

int
on_message(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    char *payload = (char *)message->payload;
    printf("Received MQTT message: %s\n", payload);

    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);

    return 0;
}

int main() {
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);

    // TLS Option
    MQTTClient_SSLOptions ssl_opts = MQTTClient_SSLOptions_initializer;
    ssl_opts.trustStore = "ca.pem";
    ssl_opts.keyStore = "server.pem";
    ssl_opts.privateKey = "server.key";

    conn_opts.ssl = &ssl_opts;
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    // MQTTBroker
    MQTTClient_setCallbacks(client, NULL, NULL, on_message, NULL);
    MQTTClient_connect(client, &conn_opts);
    MQTTClient_subscribe(client, TOPIC, QOS);

#if 0
    while (1) { sleep(1); }
#endif

    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return 0;
}
