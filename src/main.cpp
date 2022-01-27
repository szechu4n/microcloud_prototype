#include <Arduino.h>
#include "painlessMesh.h"

#include "smartCaravanNode.h"

#define   MESH_PREFIX     "MicroCloudMesh"
#define   MESH_PASSWORD   "microcloud"
#define   MESH_PORT       5555

using namespace MicroCloudNode;

// User stub
void powerOnSelfTest();

// Needed for painless library

void setup()
{
  Serial.begin(115200);
  delay(15000);
  powerOnSelfTest();
  long secondsToWait = random(1,10000);
  //mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
  
  heartBeatType hb = {

  };

  node.setHeartBeat(hb);
  node.startHeartBeat();
  //userScheduler.addTask();
  //taskSendMessage.enable();
}

void loop()
{
  // it will run the user scheduler as well
  mesh.update();
}