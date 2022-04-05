#include <Arduino.h>
#include "painlessMesh.h"
#include "esp32-hal-bt.h"

#include "microCloudConstants.h"
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
Task taskHeartBeat(TASK_SECOND * 20 , TASK_FOREVER, &heartBeat);

// Specific Task Definitions go here
Task C3Node::c3Task(TASK_SECOND * 0.25 , TASK_FOREVER, &C3Node::c3Update);
//Task NavNode::navTask(TASK_SECOND * 1, TASK_FOREVER, &NavNode::navUpdate);
//Task DsNode::dataTask(TASK_SECOND * 1, TASK_FOREVER, &dsNode::dsUpdate);

void setup()
{
  delay(10000); // delay 10 seconds in order to setup serial
  Serial.begin(115200);
  btStop();
  //sdmmc_host_pullup_en(1,4);
  //powerOnSelfTest();
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

/*void powerOnSelfTest()
{
  Serial.println("***********************************************");
  Serial.println("*-------------MicroCloud System Test----------*");
  Serial.println("***********************************************");
  delay(250);
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
    Serial.println("* > Feature Mask:\t" + String(chip_info.features));
    Serial.println("* > Cores:\t\t" + String(chip_info.cores));
    Serial.println("* > Revision:\t\t" + String(chip_info.revision));
  }
  delay(250);
  Serial.println("***********************************************"); // End system chip check
  Serial.println("*---------------File System Test--------------*");
  Serial.println("***********************************************");
  if(!SD_MMC.begin())
  {
    Serial.println("* > Card Mount Failed.");
    Serial.println("***********************************************");
    while(1);
  }
  uint8_t cardType = SD_MMC.cardType();
  if(cardType == CARD_NONE)
  {
    Serial.println("* > No SD Card attached.");
    Serial.println("***********************************************");
    while(1);
  }
  delay(250); // delay to allow Serial to catch up
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
  delay(250); // delay to allow Serial to catch up
  uint64_t cardSize = SD_MMC.cardSize()/(1024 * 1024);
  Serial.printf("* > SD Card Size:\t\t%" PRIu64 "\n\r" + (cardSize));
  Serial.println("***********************************************");
#if DEBUG
  Serial.println("* > Performing list directory test...");
  if(!listDir(SD_MMC, "/", 0))
  {
    Serial.println("* > Critical Test Failed.");
    Serial.println("***********************************************");
    while(1);
  }
  Serial.println("* > Performing directory creation test...");
  if(!createDir(SD_MMC, "/mydir"))
  {
    Serial.println("* > Critical Test Failed.");
    Serial.println("***********************************************");
    while(1);
  }
  Serial.println("* > Performing second list directory test...");
  if(!listDir(SD_MMC, "/", 0))
  {
    Serial.println("* > Critical Test Failed.");
    Serial.println("***********************************************");
    while(1);
  }
  Serial.println("* > Performing directory removal test...");
  if(!removeDir(SD_MMC, "/mydir"))
  {
    Serial.println("* > Critical Test Failed.");
    Serial.println("***********************************************");
    while(1);
  }
  Serial.println("* > Performing third list directory test...");
  if(!listDir(SD_MMC, "/", 2))
  {
    Serial.println("* > Critical Test Failed.");
    Serial.println("***********************************************");
    while(1);
  }
  Serial.println("* > Performing file write test...");
  if(!writeFile(SD_MMC, "/hello.txt", "Hello "))
  {
    Serial.println("* > Critical Test Failed.");
    Serial.println("***********************************************");
    while(1);
  }
  Serial.println("* > Performing file append test...");
  if(!appendFile(SD_MMC, "/hello.txt", "World!\n"))
  {
    Serial.println("* > Critical Test Failed.");
    Serial.println("***********************************************");
    while(1);
  }
  Serial.println("* > Performing file read test...");
  if(!readFile(SD_MMC, "/hello.txt"))
  {
    Serial.println("* > Critical Test Failed.");
    Serial.println("***********************************************");
    while(1);
  }
  Serial.println("* > Performing file rename test...");
  if(!renameFile(SD_MMC, "/hello.txt", "/foo.txt"))
  {
    Serial.println("* > Critical Test Failed.");
    Serial.println("***********************************************");
    while(1);
  }
  Serial.println("* > Performing file deletion test...");
  if(!deleteFile(SD_MMC, "/foo.txt"))
  {
    Serial.println("* > Critical Test Failed.");
    Serial.println("***********************************************");
    while(1);
  }
  /*Serial.println("* > Performing final IO test...");
  if(!testFileIO(SD_MMC, "/test.txt"))
  {
    Serial.println("* > Critical Test Failed.");
    Serial.println("***********************************************");
    while(1);
  }
#endif
  Serial.printf("* > Total space: %" PRIu64 "\n\r", SD_MMC.totalBytes()/(1024 * 1024));
  Serial.printf("* > Used space: %" PRIu64 "\n\r", SD_MMC.usedBytes()/(1024 * 1024));
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
*/