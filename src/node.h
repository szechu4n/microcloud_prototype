#ifndef NODE_H
#define NODE_H

// Task Scheduler Sleep Mode Declaration:
#define _TASK_SLEEP_ON_IDLE_RUN

#include <Arduino.h>
#include <painlessMesh.h>

extern Scheduler userScheduler; // to control your personal task
extern painlessMesh  mesh;

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

    void receivedCallback( uint32_t from, String &msg );
    void newConnectionCallback(uint32_t nodeId);
    void changedConnectionCallback();
    void nodeTimeAdjustedCallback(int32_t offset);

    class Node
    {
        public:
            Node();
            // void setHeartBeat(heartBeatType);
            // heartBeatType getHeartBeat();
            // void startHeartBeat();
            void setNodeType(nodeType);
            nodeType getNodeType();
            void randomizeSeed();
            void declareTask();

        private:
            heartBeatType heartBeatMessage;
            nodeType nodeMode;
            void startTask(Task* const &task);
            void endCurrentTask();
    };
}
#endif // NODE_H