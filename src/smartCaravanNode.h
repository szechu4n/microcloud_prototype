#ifndef SMARTCARAVANNODE_H
#define SMARTCARAVANNODE_H

#include "node.h"

// Top file for caravan specific functionality.
#include "c3Node.h"     // Communications, Command, and Control (C3) Node
#include "navNode.h"    // Navigation Node
#include "dataNode.h"     // Data Node

// The above header files are not classes, but libraries of functionalities. You should do
//  the following:
//      include all libraries you intend to use
//      define your helper functions here
//      define your primary task (would prefer if you implement a singular task)

const MicroCloudNode::nodeType nodeModes[] = 
{
    /*c3NodeStruct,
    navNodeStruct,
    dataNodeStruct*/
};


#endif // SMARTCARAVANNODE_H