#include <Arduino.h>
#include "painlessMesh.h"

#include "smartCaravanNode.h"
#include "wifiSecurity.h"
#include "sdCardOps.h"


using namespace MicroCloudNode;

Node node;
painlessMesh mesh;
Scheduler userScheduler;
IPAddress myIP(0,0,0,0);
IPAddress mqttBroker(192,168,1,1);
WiFiClient wifiClient;
PubSubClient mqttClient(mqttBroker, 1883, mqttCallback, wifiClient);

void powerOnSelfTest();
void heartBeat();
Task taskHeartBeat(TASK_SECOND * 1 , TASK_FOREVER, &heartBeat);

// Specific Task Definitions go here
Task C3Node::c3Task(TASK_SECOND * 1 , TASK_FOREVER, &C3Node::c3Loop);

void setup()
{
  delay(10000); // delay 10 seconds in order to setup serial
  Serial.begin(115200);
  powerOnSelfTest();
  node.randomizeSeed();
  //mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages

  mesh.init(MESH_PREFIX, 
          MESH_PASSWORD, 
          &userScheduler, 
          MESH_PORT,
          WIFI_AP_STA, // Added this line, need to test to be sure it doesnt break anything.
          WIFI_CHANNEL);
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  // nodes need to assign tasks to self during this period
  userScheduler.addTask(taskHeartBeat);
  taskHeartBeat.enable();
}

void loop()
{
  // it will run the user scheduler as well
  mesh.update();
}

void heartBeat()
{
  String msg = "HB_";
  msg += node.getNodeType().nodeName;
  mesh.sendBroadcast(msg);
}

void powerOnSelfTest()
{
  Serial.println("***********************************************");
  Serial.println("*-------------MicroCloud System Test----------*");
  Serial.println("***********************************************");

  // system chip check
  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);
  if(chip_info.model != CHIP_ESP32)
  {
    Serial.println("* > Unsupported Chip Model.");
    Serial.println("***********************************************");
    while(1);
  }
  else
  {
    Serial.println("* > Chip Model:\t\tCHIP_ESP32");
    Serial.println("* > Feature Mask:\t\t" + chip_info.features);
    Serial.println("* > Cores:\t\t" + chip_info.cores);
    Serial.println("* > Revision:\t\t" + chip_info.revision);
  }

  Serial.println("***********************************************"); // End system chip check
  Serial.println("*---------------File System Test--------------*");
  Serial.println("***********************************************");
  if(!SD.begin(5))
  {
    Serial.println("* > Card Mount Failed.");
    Serial.println("***********************************************");
    while(1);
  }
  uint8_t cardType = SD.cardType();
  if(cardType == CARD_NONE)
  {
    Serial.println("* > No SD Card attached.");
    Serial.println("***********************************************");
    while(1);
  }
  switch (cardType)
  {
  case CARD_MMC:
    Serial.println("* > Card Type:\t\tmicroSD_MMC");
    break;
  case CARD_SD:
    Serial.println("* > Card Type:\t\tmicroSD");
    break;
  case CARD_SDHC:
    Serial.println("* > Card Type:\t\tmicroSD_HC");
    break;
  default:
    Serial.println("* > Unsupported/Unknown Card Type.");
    Serial.println("***********************************************");
    while(1);
    break;
  }
  uint64_t cardSize = SD.cardSize()/(1024 * 1024);
  Serial.println("* > SD Card Size:\t\t" + cardSize);
  Serial.println("***********************************************");
  Serial.println("* > Performing list directory test...");
  if(!listDir(SD, "/", 0))
  {
    Serial.println("* > Critical Test Failed.");
    Serial.println("***********************************************");
    while(1);
  }
  Serial.println("* > Performing directory creation test...");
  if(!createDir(SD, "/mydir"))
  {
    Serial.println("* > Critical Test Failed.");
    Serial.println("***********************************************");
    while(1);
  }
  Serial.println("* > Performing second list directory test...");
  if(!listDir(SD, "/", 0))
  {
    Serial.println("* > Critical Test Failed.");
    Serial.println("***********************************************");
    while(1);
  }
  Serial.println("* > Performing directory removal test...");
  if(!removeDir(SD, "/mydir"))
  {
    Serial.println("* > Critical Test Failed.");
    Serial.println("***********************************************");
    while(1);
  }
  Serial.println("* > Performing third list directory test...");
  if(!listDir(SD, "/", 2))
  {
    Serial.println("* > Critical Test Failed.");
    Serial.println("***********************************************");
    while(1);
  }
  Serial.println("* > Performing file write test...");
  if(!writeFile(SD, "/hello.txt", "Hello "))
  {
    Serial.println("* > Critical Test Failed.");
    Serial.println("***********************************************");
    while(1);
  }
  Serial.println("* > Performing file append test...");
  if(!appendFile(SD, "/hello.txt", "World!\n"))
  {
    Serial.println("* > Critical Test Failed.");
    Serial.println("***********************************************");
    while(1);
  }
  Serial.println("* > Performing file read test...");
  if(!readFile(SD, "/hello.txt"))
  {
    Serial.println("* > Critical Test Failed.");
    Serial.println("***********************************************");
    while(1);
  }
  Serial.println("* > Performing file rename test...");
  if(!renameFile(SD, "/hello.txt", "/foo.txt"))
  {
    Serial.println("* > Critical Test Failed.");
    Serial.println("***********************************************");
    while(1);
  }
  Serial.println("* > Performing file deletion test...");
  if(!deleteFile(SD, "/foo.txt"))
  {
    Serial.println("* > Critical Test Failed.");
    Serial.println("***********************************************");
    while(1);
  }
  Serial.println("* > Performing final IO test...");
  if(!testFileIO(SD, "/test.txt"))
  {
    Serial.println("* > Critical Test Failed.");
    Serial.println("***********************************************");
    while(1);
  }
  Serial.println("* > Total space: " + SD.totalBytes()/(1024 * 1024));
  Serial.println("* > Total space: " + SD.usedBytes()/(1024 * 1024));
  Serial.println("***********************************************");
  // test rf?

  // test FPGA
  //    load basic bitstream onto FPGA
  //    communicate with FPGA QSPI to tell it to flash LED certain colors
  // 
  Serial.println("***********************************************");
  Serial.println("*---------------End System Test---------------*");
  Serial.println("***********************************************");
}