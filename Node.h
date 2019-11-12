//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003 Ahmet Sekercioglu
// Copyright (C) 2003-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include <string.h>
#include <omnetpp.h>
#include <string>
#include <gmp.h>
#include <stdio.h>

#include "ChordMessages_m.h"

class SuccessorList;
class FingerTable;
class NodeHandle;
class GlobalNodeList;

using namespace omnetpp;
using namespace std;


#ifndef NODE_H_INCLUDED__
#define NODE_H_INCLUDED__


class Node : public cSimpleModule
{
public:
    const std::string& getIp() const {
        return IP;
    }

    void setIp(const std::string& ip) {
        IP = ip;
    }

    const std::string& getOverlayKey() const {
        return overlayKey;
    }

    void setOverlayKey(const std::string& overlayKey) {
        this->overlayKey = overlayKey;
    }
    Node& operator=(const Node& rhs)
    {
        this->overlayKey = rhs.overlayKey;
        this->IP = rhs.IP;

        return *this;
    }

    const Node* getBoostrapNode() const {
        return bootstrapNode;
    }

    void setBoostrapNode(Node* boostrapNode) {
        this->bootstrapNode = boostrapNode;

    }

public:
    std::string IP;
    std::string overlayKey;
    Node* bootstrapNode;
    Node* predecessor;
    Node* thisNode = this;


    enum States {
        INIT      = 0,
        BOOTSTRAP = 1,
        DISCOVERY = 2,
        PREJOIN   = 3,
        JOIN      = 4,
        POSTJOIN  = 5,
        READY     = 6,
        REFRESH   = 7,
        SHUTDOWN  = 8,
        FAILED    = 9,
    };

    States state;
    GlobalNodeList* boostrapListNode;
    static Node* UNSPECIFIED_NODE;

    FingerTable* fingertable;
    SuccessorList* successorlist;



protected:
    Node * failedSuccessor;

    // timer messages
    cMessage* join_timer; /**< */
    cMessage* stabilize_timer; /**< */
    cMessage* fixfingers_timer; /**< */
    cMessage* checkPredecessor_timer;
    PingTimeout* timeout_stabilize;
    PingTimeout* timeout_notify;
    PingTimeout* ping_timeout;

    cMessage * failed;
    cMessage * stabilization_check;

    //delays

    double stabilizeDelay;
    double fixfingersDelay;
    double firstJoinDelay;
    double checkPredecessorDelay;
    double ping_timeoutdelay;
    double stabilization_check_delay;
    double failing_delay;
    double timeout_stabilize_delay;
    double timeout_notify_delay;

    int joinretry;
    bool failed_check;

    int successorListSize;
    int countFIxFinger = 0;
    void initializeNodeinfo();
    void send_chord(cMessage* msg, cModule* targetModule);
    double compute_distance(string ip, bool debug = false);
    virtual void initialize() override;
    virtual void changeState(int toState);
    void initializeFriendModules();
    void findFriendModules();
    ~Node();
    void joinOverlay();


    void findSuccessor(string key, cMessage* msg);
    void findPredecessor(string key, cMessage* msg);
    string closestPrecedingNode(string key);

    // handle message : from this all following methods are called
    virtual void handleMessage(cMessage *msg) override;  // base

    //void handleFirstNode(cMessage* msg); //  TODO
    void handleTimerEvent(cMessage* msg);                 //base (self message)
    void handleJoinTimerExpired(cMessage* msg);
    void handleStabilizeTimerExpired(cMessage* msg);
    virtual void handleFixFingersTimerExpired(cMessage* msg);
    void handleCheckPredecessorTimerExpired(cMessage* msg);
    void handlePingTimeoutExpired(cMessage * msg); // da call deve essere in grado di capire qual'era il dst e così chiamare handleFailedNode

    //call or forward of actions to be performed by this node, eventually this must be performed by other nodes
    void handleCall(BaseCallMessage* msg); // base method
    void handleFixfingers(FixFingerCall* call);
    virtual void handleJoin(JoinCall* call);
    void handleNotify(NotifyCall* call);
    void handleStabilize(StabilizeCall* call);
    void handlePingCall(PingCall * pc);

    //responses to calls
    virtual void handleResponse(BaseResponseMessage* msg);
    virtual void handleJoinResponse(JoinResponse* joinResponse);
    virtual void handleNotifyResponse(NotifyResponse* notifyResponse);
    virtual void handleStabilizeResponse(StabilizeResponse* stabilizeResponse);
    virtual void handleFixfingersResponse(FixFingerResponse* fixfingersResponse);
    void handlePingResponse(PingResponse * pr);

    bool handleFailedNode(Node* failed);
    void handleStabilizationMsg(BaseNetworkPacket* ms);


public:
    bool isUnspecified(Node* nhandle);
    bool isUnspecified();
    bool isBetweenNodes(Node* n1, Node* n2, Node* n3);


};

#endif

