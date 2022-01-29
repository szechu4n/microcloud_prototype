#ifndef C3NODE_H
#define C3NODE_H

#include "node.h"
#include "Arduino.h"
#include "painlessMesh.h"
#include <PubSubClient.h>
#include <WiFiClient.h>

void mqttCallback(char* topic, byte* payload, unsigned int length);
IPAddress getLocalIP();
IPAddress myIP(0,0,0,0);
IPAddress mqttBroker(192,168,1,1);
WiFiClient wifiClient;
PubSubClient mqttClient(mqttBroker, 1883, mqttCallback, wifiClient);

namespace MicroCloudNode
{
    namespace C3Node
    {
        void c3Setup();
        void c3Loop();
        Task c3Task(TASK_SECOND * 1 , TASK_FOREVER, &c3Loop);
    }
}
#endif // C3NODE_H