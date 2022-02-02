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
            void setHeartBeat(heartBeatType);
            heartBeatType getHeartBeat();
            void startHeartBeat();
            void setNodeType(nodeType);
            nodeType getNodeType();
            void randomizeSeed();
            void declareTask();

        private:
            heartBeatType heartBeatMessage;
            nodeType nodeMode;
            bool startTask(Task* const &task);
            bool endCurrentTask();
    };

    Node node;
}
#endif // NODE_H