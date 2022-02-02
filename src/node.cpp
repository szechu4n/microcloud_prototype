#include "node.h"


namespace MicroCloudNode
{

    void receivedCallback( uint32_t from, String &msg ) 
    {
        // should split into different bws, where certain messages have a generic
        //      ID, application specific messages each have a special ID set.
        Serial.println("** > Received from " + String(from) + " : "  + msg.c_str());
    }

    void newConnectionCallback(uint32_t nodeId) 
    {
        // believe nodes automatically know all nodes connected to the network, need to test.
        Serial.println("** > New Connection, nodeId = " + nodeId);
    }

    void changedConnectionCallback() 
    {
        // check if anyone dropped or joined
        // if someone dropped
        // check dropped task
        // check current task
        // consult priority list
        // if must support task
        // collect necessary data from other nodes
        // start task
        // check for other dropped tasks
        Serial.printf("Changed connections\n\r");
    }

    void nodeTimeAdjustedCallback(int32_t offset) 
    {
        Serial.printf("Adjusted time %u. Offset = %d\n\r", mesh.getNodeTime(),offset);
    }

    Node::Node()
    {
        nodeMode.nodeName = "None";
        nodeMode.task = NULL;
    }

    void Node::declareTask()
    {
        
    }

    /*void Node::setHeartBeat(heartBeatType hb)
    {

    }

    heartBeatType Node::getHeartBeat()
    {

    }

    void Node::startHeartBeat()
    {
        userScheduler.addTask(taskHeartBeat);
        taskHeartBeat.enable();
    }*/

    void Node::setNodeType(const nodeType newNodeMode)
    {
        if(strcmp(newNodeMode.nodeName,nodeMode.nodeName) == 0)
            return;
        endCurrentTask();
        nodeMode.nodeName = newNodeMode.nodeName;
        nodeMode.task = newNodeMode.task;
        startTask((Task*) nodeMode.task);
    }

    nodeType Node::getNodeType()
    {
        return nodeMode;
    }

    void Node::randomizeSeed()
    {
        randomSeed(analogRead(A0));
    }

    void Node::startTask(Task* const &task)
    {
        userScheduler.addTask(*task);
        task->enable();
    }

    void Node::endCurrentTask()
    {
        Task* task = (Task*) nodeMode.task;
        userScheduler.deleteTask(*task);
    }
}