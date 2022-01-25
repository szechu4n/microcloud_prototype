#include <Arduino.h>
#include "painlessMesh.h"

#include "smartCaravanNode.h"

#define   MESH_PREFIX     "MicroCloudMesh"
#define   MESH_PASSWORD   "microcloud"
#define   MESH_PORT       5555

Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;

// User stub
void sendMessage() ; // Prototype so PlatformIO doesn't complain
void powerOnSelfTest();

Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );

void sendMessage() {
  String msg = "Hi from node2";
  msg += mesh.getNodeId();
  mesh.sendBroadcast( msg );
  taskSendMessage.setInterval( random( TASK_SECOND * 1, TASK_SECOND * 5 ));
}

// Needed for painless library
void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("startHere: Received from %u msg=%s\n\r", from, msg.c_str());
}

void newConnectionCallback(uint32_t nodeId) {
    Serial.printf("--> startHere: New Connection, nodeId = %u\n\r", nodeId);
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n\r");
}

void nodeTimeAdjustedCallback(int32_t offset) {
    Serial.printf("Adjusted time %u. Offset = %d\n\r", mesh.getNodeTime(),offset);
}

void setup()
{
  Serial.begin(115200);
  delay(15000);
  powerOnSelfTest();
  long secondsToWait = random(1,10000);
  // This is a test
  //mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  userScheduler.addTask( taskSendMessage );
  //userScheduler.addTask();
  taskSendMessage.enable();
}

void loop()
{
  // it will run the user scheduler as well
  mesh.update();
}