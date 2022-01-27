#include "node.h"

namespace MicroCloudNode
{

    void heartBeat()
    {

    }

    void receivedCallback( uint32_t from, String &msg ) 
    {
        Serial.printf("startHere: Received from %u msg=%s\n\r", from, msg.c_str());
    }

    void newConnectionCallback(uint32_t nodeId) 
    {
        Serial.printf("--> startHere: New Connection, nodeId = %u\n\r", nodeId);
    }

    void changedConnectionCallback() 
    {
        Serial.printf("Changed connections\n\r");
    }

    void nodeTimeAdjustedCallback(int32_t offset) 
    {
        Serial.printf("Adjusted time %u. Offset = %d\n\r", mesh.getNodeTime(),offset);
    }

    Node::Node()
    {

    }

    Node::~Node()
    {

    }

    void Node::setHeartBeat(heartBeatType hb)
    {

    }

    heartBeatType Node::getHeartBeat()
    {

    }

    void Node::startHeartBeat()
    {
        userScheduler.addTask(taskHeartBeat);
        taskHeartBeat.enable();
    }

    void Node::setNodeType(const nodeType newNodeMode)
    {
        nodeMode.nodeName = newNodeMode.nodeName;
        nodeMode.task = newNodeMode.task;
        endTask();
        startTask((Task*) nodeMode.task);
    }

    void Node::setTask(Task task)
    {

    }

    bool Node::startTask()
    {

    }

    bool Node::startTask(Task* const &task)
    {
        userScheduler.addTask(*task);
        task->enable();
    }

    bool Node::endTask()
    {
        Task* task = (Task*) nodeMode.task;
        userScheduler.deleteTask(*task);
    }
}