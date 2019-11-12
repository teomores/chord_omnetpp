//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003 Ahmet Sekercioglu
// Copyright (C) 2003-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//
package chord_proj;
package inet.mobility.static;

import inet.mobility.static.StationaryMobility;


simple Node
{
    parameters:
        @display("i=device/pc");
        @display("p");

        string IP = default("0.0.0.0");
        string key = default("0");
        volatile int successorListSize = default(0);
        int stabilizeRetry; // retries before a successor is considered failed
        double ping_timeoutdelay @unit(s);
        //double joinDelay @unit(s); // delay between join retries (sec)
        double stabilizeDelay @unit(s); // stabilize interval (sec)
        double fixfingersDelay @unit(s); // fix_fingers interval (sec)
        double checkPredecessorDelay @unit(s); // checkPredecessor interval (sec)
        double stabilization_check_delay @unit(s);
        double failing_delay @unit(s);
        double firstJoinDelay @unit(s);
        double timeout_notify_delay @unit(s);
        double timeout_stabilize_delay @unit(s);
        // do not use failed sucessor again and inform new successor
        //bool memorizeFailedSuccessor;
    gates:
        input in @directIn;
}

simple FingerTable
{
    parameters:
        @display("i=block/table");
}

simple SuccessorList
{
    parameters:
        @display("i=block/queue");
}

module NodeHandle
{
    parameters:
        @display("p");
        @display("i=device/pc");
        string IP = default("0.0.0.0");
        string KEY = default("0");
    gates:
        input io @directIn;

    submodules:
        positionModule: StationaryMobility;
        fingertable: FingerTable {
            @display("p=97,42");
        }
        successorlist: SuccessorList;
        node: Node {
            @display("p=457,142");
        }
    connections:
        io --> node.in;

}


network Tictoc1
{
    parameters:
        int failedNodes;
        int numNodes;
        //bool debug;
    submodules:
        array[numNodes]: NodeHandle;
        globalNodelist: GlobalNodeList;
}
simple GlobalNodeList
	
{
    parameters:
        int numNodes = default(10);
        @display("i=device/router");

}

