#ifndef C3NODE_H
#define C3NODE_H

#include "node.h"
#include "Arduino.h"
#include "painlessMesh.h"
#include <PubSubClient.h>
#include <WiFiClient.h>

void mqttCallback(char* topic, byte* payload, unsigned int length);
IPAddress getLocalIP();
extern IPAddress myIP;
extern IPAddress mqttBroker;
extern WiFiClient wifiClient;
extern PubSubClient mqttClient;

namespace MicroCloudNode
{
    namespace C3Node
    {
        void c3Setup();
        void c3Update();
        extern Task c3Task;
            /*(TASK_SECOND * 1 , TASK_FOREVER, &c3Loop)*/
    }
}
#endif // C3NODE_H