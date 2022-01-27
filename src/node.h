#ifndef NODE_H
#define NODE_H

#include <Arduino.h>
#include <painlessMesh.h>

Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;

namespace MicroCloudNode
{

    struct heartBeatType
    {

    };

    struct nodeType
    {
        const char* nodeName;
        void * task;
    };

    void heartBeat();
    Task taskHeartBeat(TASK_SECOND * 1 , TASK_FOREVER, &heartBeat);

    void receivedCallback( uint32_t from, String &msg );
    void newConnectionCallback(uint32_t nodeId);
    void changedConnectionCallback();
    void nodeTimeAdjustedCallback(int32_t offset);

    class Node
    {
        public:
            Node();
            ~Node();
            void setHeartBeat(heartBeatType);
            heartBeatType getHeartBeat();
            void startHeartBeat();
            void setNodeType(nodeType);
            nodeType getNodeType();

        private:
            heartBeatType heartBeatMessage;
            nodeType nodeMode;
            void setTask(Task);
            bool startTask();
            bool startTask(Task* const &task);
            bool endTask();
    };

    Node node;
}
#endif // NODE_H