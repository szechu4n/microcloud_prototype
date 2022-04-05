#include "c3Node.h"

IPAddress getLocalIP()
{
    return IPAddress(mesh.getStationIP());
}

void mqttCallback(char* topic, byte* payload, unsigned int length)
{
    char* cleanPayload = (char*) malloc(length+1);
    memcpy(cleanPayload, payload, length);
    cleanPayload[length] = '\0';
    String msg = String(cleanPayload);
    free(cleanPayload);

    //c3ProcessMqttMessage(msg);
    // message specific processing goes here.
}

/*void MicroCloudNode::C3Node::c3ProcessMqttMessage(const String & msg)
{
    if (msg)
}*/

void MicroCloudNode::C3Node::c3Setup()
{
    //mesh.stationManual();
    //mesh.setHostname();
    mesh.setRoot(true);
    mesh.setContainsRoot(true);
}

void MicroCloudNode::C3Node::c3Update()
{
    c3Setup();
    mqttClient.loop();

    if(myIP != getLocalIP())
    {
        myIP = getLocalIP();
        //Serial.printf("My IP is ")
        if(mqttClient.connect("painlessMeshClient"))
        {
            mqttClient.publish("painlessMesh/from/gateway", "System Online.");
            mqttClient.subscribe("painlessMesh/to/#");
        }
    }
}
