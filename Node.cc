#include <omnetpp.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <algorithm>
#include "gmp.h"

#include "utils.h"
#include "sha1.h"
#include "GlobalNodeList.h"
#include "NodeHandle.h"
#include "Node.h"
#include "FingerTable.h"
#include "SuccessorList.h"

#include "ChordMessages_m.h"
using namespace omnetpp;
using namespace inet;
#define COMPILETIME_LOGLEVEL LOGLEVEL_INFO

Node* Node::UNSPECIFIED_NODE;


// The module class needs to be registered with OMNeT++
Define_Module(Node);

void Node::initialize()
{


    this->initializeNodeinfo();
    successorListSize = par("successorListSize");

    stabilizeDelay = par("stabilizeDelay");
    fixfingersDelay = par("fixfingersDelay");
    checkPredecessorDelay = par("checkPredecessorDelay");
    ping_timeoutdelay = par("ping_timeoutdelay");
    this->stabilization_check_delay = par("stabilization_check_delay");
    failing_delay = par("failing_delay");
    timeout_stabilize_delay = par("timeout_stabilize_delay");
    timeout_notify_delay = par("timeout_notify_delay");


    join_timer = new cMessage("join_timer");
    stabilize_timer = new cMessage("stabilize_timer");
    fixfingers_timer = new cMessage("fixfingers_timer");
    checkPredecessor_timer = new cMessage("checkPredecessor_timer");
    ping_timeout = new PingTimeout("ping_timeout");
    stabilization_check = new cMessage("stabilization_check");
    failed = new cMessage("failed");
    timeout_notify = new PingTimeout("timeout_notify");
    timeout_stabilize = new PingTimeout("timeout_stabilize");

    joinretry = 0;
    firstJoinDelay = par("firstJoinDelay");



    // self-messages
    this->join_timer = new cMessage("join_timer");
    scheduleAt(simTime()+firstJoinDelay, join_timer);

}

void Node::initializeNodeinfo(){
    int i1 = intuniform(0,255);
    std::string i1s = std::to_string(i1);
    int i2 = intuniform(0,255);
    std::string i2s = std::to_string(i2);
    int i3 = intuniform(0,255);
    std::string i3s = std::to_string(i3);
    int i4 = intuniform(0,255);
    std::string i4s = std::to_string(i4);
    std::string input = i1s + '.' + i2s + '.' + i3s + '.' +i4s;

    SHA1 checksum;
    checksum.update(input);
    std::string hash = checksum.final();
    hash = hash.erase(0, min(hash.find_first_not_of('0'), hash.size()-1));
    std::transform(hash.begin(), hash.end(),hash.begin(), ::toupper);
    EV_DEBUG << " nodeIP is " << input << " \n";
    EV_DEBUG << "node key is " << hash << " \n";

    cPar& pkey = par("key");
    cPar& pIP = par("IP");
    this->setOverlayKey(hash);
    this->setIp(input);
    pkey.setStringValue(hash);
    pIP.setStringValue(input);
    cPar& parentIp = this->getParentModule()->par("IP");
    cPar& parentKey = this->getParentModule()->par("KEY");
    parentIp.setStringValue(input);  // this is something that must be done after globalNodeList has initialized its list.
    parentKey.setStringValue(hash);

    this->findFriendModules();

    bootstrapNode = Node::UNSPECIFIED_NODE;
    failedSuccessor = Node::UNSPECIFIED_NODE;


    refreshDisplay();


}

void Node::handleMessage(cMessage *msg)
{
    if(state == FAILED)
        return;

    if (msg->isSelfMessage()){
        handleTimerEvent(msg);
    }else if (dynamic_cast<BaseChordMessage*>(msg)){
        BaseChordMessage* bcm =  check_and_cast<BaseChordMessage*>(msg);
        if(dynamic_cast<BaseCallMessage*>(bcm)){
            BaseCallMessage* call =  check_and_cast<BaseCallMessage*>(bcm);
            this->handleCall(call);
        }else if(dynamic_cast<BaseResponseMessage*>(bcm)){
            BaseResponseMessage* resp =  check_and_cast<BaseResponseMessage*>(bcm);
            this->handleResponse(resp);
        }
    }else if(dynamic_cast<BaseNetworkPacket*>(msg)){
        BaseNetworkPacket* sm =  check_and_cast<BaseNetworkPacket*>(msg);
        this->handleStabilizationMsg(sm);

    }
}



void Node::handleTimerEvent(cMessage* msg)
{

    // catch JOIN timer
    if (msg == join_timer) {

        changeState(INIT);
        handleJoinTimerExpired(msg);
    }
    // catch STABILIZE timer
    else if (msg == stabilize_timer) {
        handleStabilizeTimerExpired(msg);
    }
    // catch FIX_FINGERS timer
    else if (msg == fixfingers_timer) {
        handleFixFingersTimerExpired(msg);
    }
    // catch CHECK_PREDECESSOR timer
    else if (msg == checkPredecessor_timer) {
        cancelEvent(checkPredecessor_timer);
        scheduleAt(simTime() + checkPredecessorDelay,
                checkPredecessor_timer);
        if (!isUnspecified(predecessor)){
            //throw cRuntimeError("handlepred");
            handleCheckPredecessorTimerExpired(msg);
        }
    }else if (msg == ping_timeout) {
        //throw cRuntimeError("pingtimeout");

        handlePingTimeoutExpired(msg);
    }else if (msg == timeout_stabilize) {
        //throw cRuntimeError("timeoutstabilize");

        handlePingTimeoutExpired(msg);
    }else if (msg == timeout_notify) {
        //throw cRuntimeError("notifytimeout");

        handlePingTimeoutExpired(msg);
    }else if (msg == failed) {
        changeState(FAILED);
    }else if (msg == stabilization_check){
        if(this->successorlist->getSuccessor() != this){
            Stabilization * sm = new Stabilization();
            sm->setSrc(this->getOverlayKey().c_str());
            sm->setHops(0);
            sm->setStart(simTime());
            sm->setRingArraySize(1);
            sm->setRing(0, this->getOverlayKey().c_str());
            send_chord(sm, this->successorlist->getSuccessor()->getParentModule());
        }
        cancelEvent(stabilization_check);
        scheduleAt(simTime() + stabilization_check_delay, stabilization_check);
    }
    // unknown self message
    else {
        error("Chord::handleTimerEvent(): received self message of "
                "unknown type!");
    }
}

void Node::handleJoinTimerExpired(cMessage* msg){
    // only process timer, if node is not joined yet ( quindi ci sono i messaggi timer inizializzati anche se non siamo dentro chord
    // poi però si cambia stato, non so chi, o cosa ma in qualche modo viene cambiato lo stato
    if(state == FAILED)
        return;
    if (state == READY)
        return;
    // enter state JOIN
    if(state == JOIN){
        changeState(JOIN);
    }
    if (state != JOIN)
        changeState(JOIN);
    //cancelEvent(join_timer);


    // TODO da valutare questa cosa  --> serve se il boostrapnode fallisce!!!
    // change bootstrap node from time to time
    //joinRetry--;
    //if (joinRetry == 0) {
    //joinRetry = par("joinRetry");
    //changeState(JOIN);
    //return;
    //}
}
// call JOIN RPC
//}


void Node::findFriendModules()
{
    fingertable = check_and_cast<FingerTable*>(getParentModule()->getSubmodule("fingertable"));


    successorlist = check_and_cast<SuccessorList*>
    (getParentModule()->getSubmodule("successorlist"));

    boostrapListNode = check_and_cast<GlobalNodeList*>(this->getParentModule()->getParentModule()->getSubmodule("globalNodelist"));
}


void Node::initializeFriendModules()
{
    // initialize finger table
    this->fingertable->initializeFingerTable(this, false);

    // initialize successor list
    successorlist->initializeList(successorListSize, this);
}


void Node::findSuccessor(string key, cMessage* msg){
    if(dynamic_cast<JoinCall*>(msg)){
        JoinCall* jc = check_and_cast<JoinCall*>(msg);

        //inizializzazione risposta generica
        JoinResponse* response = new  JoinResponse("join_response");
        response->setSuccessorNum(this->successorlist->getSize());
        string requester(jc->getRequester());
        response->setSuccessorNodeArraySize(this->successorlist->getSize());
        response->setSrc(this->IP.c_str());
        for (int k = 0; k < this->successorlist->getSize(); k++) {
            response->setSuccessorNode(k, successorlist->getSuccessor(k)->getOverlayKey().c_str());
        }


        if(Utils::isBetweenR(key, this->getOverlayKey(), this->successorlist->getSuccessor()->getOverlayKey())){

            if (isUnspecified(predecessor) && successorlist->isEmpty()) {

                // we are the only node in the ring
                response->setPredecessorNode(this->getOverlayKey().c_str());
            } else {
                response->setPredecessorNode(predecessor->getOverlayKey().c_str());
            }

            cModule* targetModule = Utils::getModule(requester, false);
            send_chord(response, targetModule);



        }else{

            string closest = this->closestPrecedingNode(key);

            if (closest == this->getOverlayKey()){
                string requester(jc->getRequester());
                cModule* targetModule = Utils::getModule(requester, false);
                // we are the only node in the ring
                response->setPredecessorNode(this->getOverlayKey().c_str());
                send_chord(response, targetModule);
            }else{
                cModule* targetModule = Utils::getModule(closest, false, false);
                send_chord(jc, targetModule);

                delete response;
            }
        }
    }else if( dynamic_cast<FixFingerCall*>(msg)){
        FixFingerCall* fc = check_and_cast<FixFingerCall*>(msg);
        FixFingerResponse* response = new  FixFingerResponse("fix_response");
        response->setFinger(fc->getFinger());

        string requester(fc->getRequester());
        if(Utils::isBetweenR(key, this->getOverlayKey(), this->successorlist->getSuccessor()->getOverlayKey())){


            cModule* targetModule = Utils::getModule(requester, false, false);
            response->setSuccessorNode(this->getOverlayKey().c_str());
            EV_DEBUG << "Response fields:" << endl;
            EV_DEBUG << "fingerposition: " << response->getFinger() <<
                    "successortoset " << response->getSuccessorNode() << endl;
            send_chord(response, targetModule);

        }else{

            string closest = this->closestPrecedingNode(key);

            if (closest == this->getOverlayKey()){
                cModule* targetModule = Utils::getModule(requester, false, false);
                // we are the only node in the ring
                response->setSuccessorNode(closest.c_str());
                EV_DEBUG << "Response fields:" << endl;
                EV_DEBUG << "fingerposition: " << response->getFinger() <<
                        "successortoset " << response->getSuccessorNode() << endl;
                send_chord(response, targetModule);
            }else{
                cModule* targetModule = Utils::getModule(closest, false, false);
                send_chord(fc, targetModule);

                delete response;
            }
        }


    }
}

void Node::findPredecessor(string key, cMessage* msg){

}

string Node::closestPrecedingNode(string key)
{
    string temp;
    // if this is the first and only node on the ring, it is responsible
    if ((isUnspecified(predecessor)) &&
            (successorlist->getSuccessor() == thisNode)) {
        string res =  thisNode->getOverlayKey();
        return res;
    }
    // find the closest preceding node in the successor list
    for (int j = successorlist->getSize() - 1; j >= 0; j--) {
        // return a predecessor of the key, unless we know a node with an Id = destKey

        if (Utils::isBetweenL(successorlist->getSuccessor(j)->getOverlayKey(),thisNode->getOverlayKey(), key)) {

            temp = successorlist->getSuccessor(j)->getOverlayKey();
            break;
        }
    }

    if(temp.empty()) {
        std::stringstream ss;
        ss << "Chord::closestPreceedingNode(): Successor list broken for node: \n "
                << thisNode->getOverlayKey() << " " << key;
        throw cRuntimeError(ss.str().c_str());
    }

    string next;


    for (int i = fingertable->getSize() - 1; i >= 0; i--) {
        // return a predecessor of the key, unless we know a node with an Id = destKey

        if (!(isUnspecified(fingertable->getFinger(i))) && (Utils::isBetweenLR(fingertable->getFinger(i)->getOverlayKey(), temp, key))) {

            next = fingertable->getFinger(i)->getOverlayKey();

            EV_DEBUG << "[Chord::closestPreceedingNode() @ " << thisNode->getIp() << " (" << thisNode->getOverlayKey() << ")]\n" <<
                    "    ClosestPreceedingNode: node " << thisNode <<
                    " for key " << key << "\n" <<
                    "    finger " << fingertable->getFinger(i)->getOverlayKey()<<
                    " better than \n"<<
                    "    " << next<< endl;
            return next;
        }
    }

    EV_DEBUG << "[Chord::closestPreceedingNode() @ " <<
            thisNode->getIp() <<
            " (" << thisNode->getOverlayKey() <<
            ")]\n" << "No finger found in fingerTable"<< endl;

    for (int i = successorlist->getSize() - 1; i >= 0; i--) {
        if (Utils::isBetween(successorlist->getSuccessor(i)->getOverlayKey(),thisNode->getOverlayKey(), key)) {
            next = successorlist->getSuccessor(i)->getOverlayKey();
        }
    }

    if (!next.empty()) {

        return next;
    }

    // if this is the first and only node on the ring, it is responsible
    if ((isUnspecified(predecessor)) &&
            (successorlist->getSuccessor() == thisNode)) {
        return thisNode->getOverlayKey();
    }

    EV_DEBUG << "closest preceding node found: "<< next << endl;
    // if there is still no node found throw an exception
    throw cRuntimeError("Error in Chord::closestPreceedingNode()!");
    return next;
}

void Node::changeState(int toState)
{
    //
    // Defines tasks to be executed when a state change occurs.
    //

    switch (toState) {
    case INIT:{
        if(this->boostrapListNode->willFail(this->getIp())){
            failed_check = true;
        }else{
            failed_check = false;
        }
        state = INIT;
        // initialize predecessor pointer
        predecessor = Node::UNSPECIFIED_NODE;
        //init the node finger table and successor list
        initializeFriendModules();
        getParentModule()->bubble("Enter INIT state.");
        break;
    }
    case JOIN:{
        cPar& pIP = par("IP");
        refreshDisplay();
        predecessor = Node::UNSPECIFIED_NODE;
        state = JOIN;

        getParentModule()->bubble("Enter JOIN state.");

        // find a new bootstrap node and enroll to the bootstrap list
        string bootstrapNode_string;
        bootstrapNode_string = boostrapListNode->getBootstrapNode();
        EV_DEBUG << "BOOSTRAPLISTNODE: "<< endl;
        boostrapListNode->printList();

        //if return a null str this is the first node to enter chord
        if (bootstrapNode_string.empty()){     // this is a dynamic cast because if it's the first node in CHord it must return nullptr
            thisNode = check_and_cast<Node*>(this);
            assert(isUnspecified(predecessor));
            this->bootstrapNode = thisNode;
            cancelEvent(join_timer);
            changeState(READY);
        }else {
            EV_DEBUG << "boostrapNode found!: " << bootstrapNode_string << " \n";
            JoinCall* joincall = new JoinCall();
            joincall->setRequester(IP.c_str());
            joincall->setKey(overlayKey.c_str());
            cModule* targetModule = Utils::getModule(bootstrapNode_string, false);
            send_chord(joincall, targetModule);
            cancelEvent(join_timer);
            this->join_timer = new cMessage("join_timer");
            scheduleAt(simTime()+firstJoinDelay, join_timer);


        }
        break;

    }

    case READY:{


        cancelEvent(join_timer);
        state = READY;
        boostrapListNode->addBooststrapNode(this);

        // initiate stabilization protocol
        cancelEvent(stabilize_timer);
        scheduleAt(simTime() + stabilizeDelay, stabilize_timer);

        // initiate finger repair protocol
        cancelEvent(fixfingers_timer);
        scheduleAt(simTime() + fixfingersDelay,
                fixfingers_timer);
        this->countFIxFinger ++;
        getParentModule()->bubble("Enter READY state.");


        // initiate predecessor check
        cancelEvent(checkPredecessor_timer);
        if (checkPredecessorDelay > 0) {
            scheduleAt(simTime() + checkPredecessorDelay,
                    checkPredecessor_timer);

            cancelEvent(stabilization_check);
            scheduleAt(simTime() + stabilization_check_delay, stabilization_check);
        }

        cancelEvent(failed);
        if(this->failed_check){
            scheduleAt(simTime() + failing_delay, failed);
        }

        // debug message
        EV_DEBUG << "[Chord::changeState() @ " << thisNode->getIp()<<
                " (" << thisNode->getOverlayKey() << ")]\n"<<
                "  Entered READY stage"<< endl;
        break;

    }case FAILED:{
        state = FAILED;
        cDisplayString& dispStr = getParentModule()->getDisplayString();
        dispStr.parse("i=status/stop");
        //cancella eventi
        cancelEvent(stabilize_timer);
        cancelEvent(fixfingers_timer);
        cancelEvent(checkPredecessor_timer);
        cancelEvent(stabilization_check);
        cancelEvent(ping_timeout);
        cancelEvent(failed);
        cancelEvent(this->timeout_notify);
        cancelEvent(this->timeout_stabilize);
        getParentModule()->bubble("FAILED.");
        // possibile implementazione di send a predecessor e a successor delle proprie successorlist
        break;

    }



    }
}

Node::~Node()
{
    // destroy self timer messages
    //cancelAndDelete(join_timer);
    //cancelAndDelete(stabilize_timer);
    //cancelAndDelete(fixfingers_timer);
    //cancelAndDelete(checkPredecessor_timer);
}

void Node::joinOverlay()
{
    changeState(INIT);
    changeState(JOIN);
}


bool Node::isUnspecified(Node* node){
    if(node == Node::UNSPECIFIED_NODE)
    {
        return true;
    }else {
        return false;
    }
}

bool Node::isUnspecified() {
    if(this == Node::UNSPECIFIED_NODE)
        return true;
    else{
        return false;
    }
}

void Node::handleCall(BaseCallMessage* msg) {
    if (state != READY) {
        EV_DEBUG <<   "[Chord::handleRpcCall() @ " << thisNode->getIp() <<
                " (" << thisNode->getOverlayKey() << ")]\n" <<
                "    Received RPC call and state != READY" << endl;
    }else{
        if(dynamic_cast<JoinCall*>(msg)){
            JoinCall* jc = check_and_cast<JoinCall*>(msg);
            this->handleJoin(jc);
        }else if(dynamic_cast<StabilizeCall*>(msg)){
            StabilizeCall* sc = check_and_cast<StabilizeCall*>(msg);
            this->handleStabilize(sc);
        }else if(dynamic_cast<NotifyCall*>(msg)){
            NotifyCall* sc = check_and_cast<NotifyCall*>(msg);
            this->handleNotify(sc);
        }else if(dynamic_cast<FixFingerCall*>(msg)){
            FixFingerCall* sc = check_and_cast<FixFingerCall*>(msg);
            this->handleFixfingers(sc);
        }else if(dynamic_cast<PingCall*>(msg)){
            PingCall* pc = check_and_cast<PingCall*>(msg);
            this->handlePingCall(pc);
        }else   throw cRuntimeError("not implemented!");

    }

}

void Node::handleJoin(JoinCall* call) {
    string requestor = call->getRequester();
    string targetkey = call->getKey();
    findSuccessor(targetkey,call);
    string requestorNode = call->getRequester();

    /*
     * HERE ADD AGGRESSIVE MODE
     * */
    // it was a part of the aggressive mode, but it seems ok:
    if (isUnspecified(predecessor) || (predecessor->getOverlayKey() != requestorNode)) {
        // the requestor is our new predecessor
        Node* oldPredecessor = predecessor;
        cModule* requestor = Utils::getModule(requestorNode, true);
        predecessor = check_and_cast<Node*>(requestor);
        cancelEvent(checkPredecessor_timer);
        scheduleAt(simTime() + checkPredecessorDelay,
                checkPredecessor_timer);
    }
    // if we don't have a successor, the requestor is also our new successor
    if (successorlist->isEmpty()){
        Node* r = check_and_cast<Node*>(Utils::getModule(requestorNode, true));
        successorlist->addSuccessor(r, true);
    }
}

void Node::handleJoinResponse(JoinResponse* joinResponse) {

    /// determine the numer of successor nodes to add
    int sucNum = successorListSize - 1;

    if (joinResponse->getSuccessorNum() < successorListSize - 1) {
        sucNum = joinResponse->getSuccessorNum();
    }
    // add successor getNode(s)
    for (int k = 0; k < sucNum; k++) {
        cModule* successor = Utils::getModule(joinResponse->getSuccessorNode(k), true, false);

        Node* successorNode = check_and_cast<Node*>(successor);
        successorlist->addSuccessor(successorNode);
    }

    // the sender of this message is our new successor

    Node* successor = check_and_cast<Node*>(joinResponse->getArrivalModule());
    EV_DEBUG << "the sender of this message is our new successor" << successor->getOverlayKey() << endl;
    successorlist->addSuccessor(successor);
    if (strcmp(joinResponse->getPredecessorNode(),"")!= 0){
        if (!isUnspecified(predecessor)) {
            //newhintsuccessor message
        }
        Node* oldPredecessor = predecessor;
        Node* n = check_and_cast<Node*>(Utils::getModule(joinResponse->getPredecessorNode(), true, false));// prendo il nodo con una certa chiave
        predecessor = n;
        cancelEvent(checkPredecessor_timer);
        scheduleAt(simTime() + checkPredecessorDelay,
                checkPredecessor_timer);

    }

    changeState(READY);
    // immediate stabilization protocol
    cancelEvent(stabilize_timer);
    scheduleAt(simTime(), stabilize_timer);

    // immediate finger repair protocol
    cancelEvent(fixfingers_timer);
    scheduleAt(simTime(), fixfingers_timer);
}

void Node::handleResponse(BaseResponseMessage* msg){
    if(dynamic_cast<JoinResponse*>(msg)){
        JoinResponse* jc = check_and_cast<JoinResponse*>(msg);
        this->handleJoinResponse(jc);
    }else if(dynamic_cast<StabilizeResponse*>(msg)){
        StabilizeResponse* sr = check_and_cast<StabilizeResponse*>(msg);
        this->handleStabilizeResponse(sr);
    }else if(dynamic_cast<NotifyResponse*>(msg)){
        NotifyResponse* sr = check_and_cast<NotifyResponse*>(msg);
        this->handleNotifyResponse(sr);
    }else if(dynamic_cast<FixFingerResponse*>(msg)){
        FixFingerResponse* fr = check_and_cast<FixFingerResponse*>(msg);
        this->handleFixfingersResponse(fr);
    }else if(dynamic_cast<PingResponse*>(msg)){
        PingResponse* pr = check_and_cast<PingResponse*>(msg);
        this->handlePingResponse(pr);
    }else throw cRuntimeError("not implemented!!");

}

double Node::compute_distance(string ip, bool debug){
    cModule* m = Utils::getModule(ip, false);
    StationaryMobility* s = check_and_cast<StationaryMobility*>(this->getParentModule()->getSubmodule("positionModule"));
    Coord c1 = s->getCurrentPosition();
    StationaryMobility* others = check_and_cast<StationaryMobility*>(m->getSubmodule("positionModule"));
    Coord c2 = others->getCurrentPosition();
    if (debug) {EV_DEBUG << "distance between: "<< this->IP
        << " @: " << c1<<" and " << ip
        << " @: "<<c2 <<" is: "
        << c1.distance(c2) << endl;
    }
    return c1.distance(c2);
}

void Node::send_chord(cMessage* msg, cModule* targetModule){
    /*
     * this represents a send with propagationDelay as uniform(0,1)s and
     * mbps as normal distribution of 10 with std 1
     */

    simtime_t propagationDelay = uniform(0, 1);
    simtime_t duration;
    simtime_t mbps = normal(1000, 1);
    double distance = compute_distance(targetModule->par("IP").stdstringValue(), true);
    duration = distance / mbps;
    sendDirect(msg,propagationDelay,duration,targetModule,"io");  // to set propagationDelay,duration
}

void Node::handleStabilizeTimerExpired(cMessage* msg) {

    if (state != READY)
        return;
    successorlist->print();

    if (!successorlist->isEmpty()) {
        // call STABILIZE RPC
        StabilizeCall* call = new StabilizeCall("StabilizeCall");

        this->send_chord(call, successorlist->getSuccessor()->getParentModule());
    }

    // schedule next stabilization process
    cancelEvent(stabilize_timer);
    scheduleAt(simTime() + stabilizeDelay, msg);
    cancelEvent(timeout_stabilize);
    timeout_stabilize->setFailed(successorlist->getSuccessor()->getOverlayKey().c_str());
    scheduleAt(simTime() + timeout_stabilize_delay, timeout_stabilize);


}

void Node::handleStabilize(StabilizeCall* call) {
    // reply with StabilizeResponse message
    StabilizeResponse* stabilizeResponse =
            new StabilizeResponse("StabilizeResponse");
    if (!isUnspecified(predecessor)){
        // if we have a valid key for our predecessor we send it back to the requester
        stabilizeResponse->setPredecessorNode(predecessor->getOverlayKey().c_str());
        stabilizeResponse->setPredecessorNodeIP(predecessor->getIp().c_str());
        cModule * targetModule = call->getSenderModule()->getParentModule();
        send_chord(stabilizeResponse,targetModule);
    }else{
        //if we don't have a valid key for our predecessor we send a fake key
        //it's in requestor interest to check if we sent a fake / valid key at handleStabilizeResponse()
        stabilizeResponse->setPredecessorNode("");
        stabilizeResponse->setPredecessorNodeIP("");
        cModule * targetModule = call->getSenderModule()->getParentModule();
        send_chord(stabilizeResponse,targetModule);
    }


}


void Node::handleNotifyResponse(NotifyResponse* notifyResponse) {

    if (state != READY) {
        return;
    }
    cancelEvent(timeout_notify);
    Node* sender = check_and_cast<Node*>(notifyResponse->getSenderModule());

    if (successorlist->getSuccessor()->getOverlayKey() != sender->getOverlayKey()) {
        EV_DEBUG << "[Chord::handleRpcNotifyResponse() @ " << this->IP <<
                " (" << this->getOverlayKey() << ")]\n"  <<
                "    The srcNode of the received NotifyResponse is not our "  <<
                " current successor" << endl;
        return;
    }

    // replace our successor list by our successor's successor list
    successorlist->updateList(notifyResponse);
}

void Node::handleStabilizeResponse(StabilizeResponse* stabilizeResponse) {

    if (state != READY) {
        return;
    }

    cancelEvent(timeout_stabilize);
    //if this is the only node in the ring we just end this subroutine.
    if(stabilizeResponse->getSenderModule() == this){
        return;
    }

    // Otherwise we fetch the successor's predecessor
    string node_key = stabilizeResponse->getPredecessorNode();
    string node_Ip = stabilizeResponse->getPredecessorNodeIP();
    Node * successor;
    if(node_Ip.empty()){
        successor = Node::UNSPECIFIED_NODE;
    }else {
        successor = check_and_cast<Node*>(Utils::getModule(node_Ip,true));
    }

    // is the successor's predecessor a new successor for this node?

    if ((successorlist->isEmpty() )||((Utils::isBetween(node_key, this->getOverlayKey(),successorlist->getSuccessor()->getOverlayKey())))){
        if (isUnspecified(failedSuccessor) || (failedSuccessor != successor)){ // se node_ip è empty non devo neanche
            // controllare failedSuccessor
            if (successorlist->isEmpty() && node_Ip.empty()) {
                // successor is emptry and the sender of the response has
                // no predecessor => take the sender as new successor
                Node* nodeToAdd = check_and_cast<Node*>(stabilizeResponse->getSenderModule());
                successorlist->addSuccessor(nodeToAdd);
            } else {
                // add the successor's predecessor to the successor list
                Node* nodeToAdd = check_and_cast<Node*>(Utils::getModule(node_Ip,true));
                successorlist->addSuccessor(nodeToAdd);
            }

        }
    }


    // compile NOTIFY RPC
    NotifyCall* notifyCall = new NotifyCall("NotifyCall");
    if(!isUnspecified(failedSuccessor)){
        notifyCall->setFailed(failedSuccessor->getIp().c_str());
        send_chord(notifyCall, successorlist->getSuccessor()->getParentModule());
    }else {
        notifyCall->setFailed(""); // assunzione
        send_chord(notifyCall, successorlist->getSuccessor()->getParentModule());
        cancelEvent(timeout_notify);
        timeout_notify->setFailed(successorlist->getSuccessor()->getOverlayKey().c_str());
        scheduleAt(simTime() + timeout_notify_delay, timeout_notify);
    }

    failedSuccessor = Node::UNSPECIFIED_NODE;

}

void Node::handleNotify(NotifyCall* call) {
    // our predecessor seems to be alive

    Node* newPredecessor = check_and_cast<Node*>(call->getSenderModule());

    Node* sendedFailed;
    if((strlen(call->getFailed()) == 0)){
        sendedFailed = Node::UNSPECIFIED_NODE;
    }
    else{
        sendedFailed = check_and_cast<Node*>(Utils::getModule(call->getFailed(), true, true));
    }
    // is the new predecessor closer than the current one?
    if (isUnspecified(predecessor) ||
            isBetweenNodes(newPredecessor,predecessor,this) ||
            (!isUnspecified(sendedFailed) &&
                    sendedFailed == predecessor)) {

        if ((isUnspecified(predecessor)) ||
                (newPredecessor != predecessor)) {

            // set up new predecessor
            Node* oldPredecessor = predecessor;
            predecessor = newPredecessor;
            cancelEvent(checkPredecessor_timer);
            scheduleAt(simTime() + checkPredecessorDelay,
                    checkPredecessor_timer);

            if (successorlist->isEmpty()) { // nel caso in cui ci sono solo due nodi della rete
                successorlist->addSuccessor(newPredecessor);
            }
        }
    }

    // compile NOTIFY response
    NotifyResponse* notifyResponse = new NotifyResponse("NotifyResponse");

    int sucNum = successorlist->getSize();
    notifyResponse->setSuccessorNum(sucNum);
    notifyResponse->setSuccessorNodeArraySize(sucNum);
    for (int k = 0; k < sucNum; k++) {
        notifyResponse->setSuccessorNode(k, successorlist->getSuccessor(k)->getOverlayKey().c_str());
    }
    send_chord(notifyResponse, newPredecessor->getParentModule());

}

bool Node::isBetweenNodes(Node* n1, Node* n2, Node* n3){

    if (isUnspecified(n1) || isUnspecified(n2) || isUnspecified(n3))
        return false;
    else{
        return Utils::isBetween(n1->getOverlayKey(), n2->getOverlayKey(), n3->getOverlayKey());
    }

}


void Node::handleFixFingersTimerExpired(cMessage* msg)
{
    fingertable->printTable();


    if ((state != READY) || successorlist->isEmpty())
        return;
    string offset, lookupKey;
    for (uint32_t nextFinger = 0; nextFinger < 160;
            nextFinger++) { // perché la finger table è lunga m
        lookupKey = Utils::getKeyInModule(nextFinger, thisNode->getOverlayKey(), false);
        EV_DEBUG << "fixing:" << lookupKey << endl;
        offset = Utils::getKeyInModule(nextFinger, "0", false);
        // send message only for non-trivial fingers
        if (!Utils::isBetween(lookupKey, thisNode->getOverlayKey(), successorlist->getSuccessor()->getOverlayKey())) {
            // call FIXFINGER RPC
            FixFingerCall* call = new FixFingerCall("FixFingerCall");
            call->setFingerKey(lookupKey.c_str());
            call->setFinger(nextFinger);
            call->setRequester(this->getOverlayKey().c_str());
            EV_DEBUG << "calling internal find successor on: "<< lookupKey << endl;
            findSuccessor(lookupKey, call);

        } else {
            // delete trivial fingers (points to the successor node)
            EV_DEBUG << "removing trivial finger at : " <<  nextFinger << endl;
            fingertable->removeFinger(nextFinger);
        }
    }

    // schedule next finger repair process
    cancelEvent(fixfingers_timer);
    scheduleAt(simTime() + fixfingersDelay, msg);
    this->countFIxFinger++;
}

void Node::handleFixfingers(FixFingerCall* call) {
    if(state != READY || successorlist->isEmpty())
        return;
    string lookupKey = call->getFingerKey();
    findSuccessor(lookupKey, call);

}

void Node::handleFixfingersResponse(FixFingerResponse* fixfingersResponse) {

    if(state != READY){
        return;
    }
    Node* successor = check_and_cast<Node*>(Utils::getModule(fixfingersResponse->getSuccessorNode(), true, false));
    fingertable->setFinger(fixfingersResponse->getFinger(), successor);

}

void Node::handleCheckPredecessorTimerExpired(cMessage* msg) {

    PingCall * pc = new PingCall("ping_call");
    send_chord(pc, predecessor->getParentModule());
    //schedule timeout
    cancelEvent(checkPredecessor_timer);
    //checkPredecessor_timer = new cMessage("checkPredecessor_timer");
    //scheduleAt(simTime() + this->checkPredecessorDelay, ping_timeout);
    cancelEvent(ping_timeout);
    //ping_timeout = new cMessage("ping_timeout");
    ping_timeout->setFailed(predecessor->getOverlayKey().c_str());
    scheduleAt(simTime() + ping_timeoutdelay, ping_timeout);// questo timeout deve essere maggiore del checkpredecessor timeout


}

void Node::handlePingTimeoutExpired(cMessage* msg) {

    // aspetta che si resetti un predecessor per mandare il checkpredecessor
    cancelEvent(checkPredecessor_timer);
    PingTimeout* pto = check_and_cast<PingTimeout*>(msg);
    //chiama handleDFailedNode per modificare le sue strutture interne
    Node* failed = check_and_cast<Node*>(Utils::getModule(pto->getFailed(), true, false));
    handleFailedNode(failed); // non va bene devo fare un altro messaggio con dentro il destination
    // cambio predecessor -> rischeduling del check predecessor
    scheduleAt(simTime() + checkPredecessorDelay,
            checkPredecessor_timer);

}

void Node::handlePingCall(PingCall* pc) {
    if (state != FAILED){
        PingResponse * pr = new PingResponse("ping_response");

        send_chord(pr, pc->getSenderModule()->getParentModule());
    }
}

void Node::handlePingResponse(PingResponse* pr) {

    if(state!=READY){
        return;
    }
    // non devo fare nulla but scheduling del timer
    cancelEvent(checkPredecessor_timer);
    scheduleAt(simTime() + checkPredecessorDelay,
            checkPredecessor_timer);
    cancelEvent(ping_timeout);
}


bool Node::handleFailedNode(Node* failed)
{
    Enter_Method_Silent();

    if (!isUnspecified(predecessor) && failed->getOverlayKey() == predecessor->getOverlayKey())
        predecessor = Node::UNSPECIFIED_NODE;

    //TODO const reference -> trying to compare unspec NH
    Node* oldSuccessor = successorlist->getSuccessor();

    if (successorlist->handleFailedNode(failed->getIp()))
        // check pointer for koorde
        if (fingertable != NULL)
            fingertable->handleFailedNode(failed->getIp());

    // if we had a ring consisting of 2 nodes and our successor seems
    // to be dead. Remove also predecessor because the successor
    // and predecessor are the same node
    if ((!isUnspecified(predecessor)) &&
            oldSuccessor == predecessor) {
        predecessor = Node::UNSPECIFIED_NODE;
    }

    if (failed == oldSuccessor) {
        // schedule next stabilization process

        failedSuccessor = oldSuccessor;
        cancelEvent(stabilize_timer);
        scheduleAt(simTime(), stabilize_timer);
    }

    if (state != READY) return true;

    if (successorlist->isEmpty()) {
        // lost our last successor - cancel periodic stabilize tasks
        // and wait for rejoin
        cancelEvent(stabilize_timer);
        cancelEvent(fixfingers_timer);
    }

    return !(successorlist->isEmpty());
}

/*void Node::handleStabilizationMsg(BaseNetworkPacket* ms) {
    Stabilization * sm = check_and_cast<Stabilization*>(ms);
    int hops = sm->getHops();
    int size = sm->getRingArraySize();
    int numNodes = this->getParentModule()->getParentModule()->par("numNodes");
    vector<string> listOfNodes;
    for (int k = 0; k < size; k++) {
        listOfNodes.push_back(sm->getRing(k));
    }
    listOfNodes.push_back(this->getOverlayKey());
    std::sort(listOfNodes.begin(), listOfNodes.end(), Utils::isSmaller);
    for (int k = 0; k < listOfNodes.size(); k++) {
                    EV<< listOfNodes[k] << endl;
                }
    std::vector<string>::iterator it;
    it = std::unique(listOfNodes.begin(), listOfNodes.end());
    listOfNodes.resize( std::distance(listOfNodes.begin(),it));
    EV << "number of hops: " << hops << endl;
    EV << "# of nodes: "<< listOfNodes.size() <<endl;
    simtime_t interval =  sm->getArrivalTime() - sm->getStart();
    if (listOfNodes.size()==numNodes && hops >= numNodes){
        //EV << "number of hops: " << hops << endl;
        EV<< "STABLE!" << endl;
        EV << "time for round: " << interval<<"%W"  << endl;
        for (int k = 0; k < listOfNodes.size(); k++) {
                //EV<< listOfNodes[k] << endl;
            }
        throw cRuntimeError("network stable");
    }else {
        sm->setRingArraySize(size+1);
        for (int k = 0; k <= size; k++) {
            sm->setRing(k,listOfNodes[k].c_str());
        }
        if(this->successorlist->getSuccessor() != this){
            sm->setHops(hops+1);
            send_chord(sm, this->successorlist->getSuccessor()->getParentModule());
        }
    }
}*/

void Node::handleStabilizationMsg(BaseNetworkPacket* ms) {
    Stabilization * sm = check_and_cast<Stabilization*>(ms);
    int hops = sm->getHops();
    int size = sm->getRingArraySize();
    int total = this->getParentModule()->getParentModule()->par("numNodes");
    int failedNodes = this->getParentModule()->getParentModule()->par("failedNodes");
    int numNodes = total - failedNodes;
    vector<string> listOfNodes;
    for (int k = 0; k < size; k++) {
        listOfNodes.push_back(sm->getRing(k));
    }
    // controlla se il nodo è già nella lista
    // due casi:
    // - se c'è e ci sono anche tutti gli altri nodi della rete è stabile
    // - altrimenti non è stabile
    // in nessuno dei due casi riforwarda il messaggio
    // se il nodo non è nella lista invece riforwarda
    // finché il numero di hops non è maggiore del numero di nodi altirmenti scoppia
    EV_DEBUG << "number of hops: " << hops << endl;
    EV_DEBUG << "Lista nodi da cui è passato : " << endl;
    for (int k = 0; k < listOfNodes.size(); k++) {
        EV<< listOfNodes[k] << endl;
    }
    if ((find(listOfNodes.begin(), listOfNodes.end(), this->getOverlayKey()) != listOfNodes.end())&& hops!=0){
        // se lo trova, controlla...
        std::sort(listOfNodes.begin(), listOfNodes.end(), Utils::isSmaller);
        EV_DEBUG << "Nodi percorsi: " << endl;
        for (int k = 0; k < listOfNodes.size(); k++) {
            EV<< listOfNodes[k] << endl;
        }
        int non_unique_size = listOfNodes.size(); // deve essere uguale a quella unica
        std::vector<string>::iterator it;
        it = std::unique(listOfNodes.begin(), listOfNodes.end());
        listOfNodes.resize( std::distance(listOfNodes.begin(),it));
        int unique_size = listOfNodes.size();
        // ora basta controllare se il numero tot di nodi è uguale al numero di hops
        // e al numero di elementi nella lista dei nodi
        // uso hops+1 perché di base è 0
        EV_DEBUG << "# of nodes: "<< numNodes <<endl;
        EV_DEBUG << "# of unique_size: "<< unique_size <<endl;
        EV_DEBUG << "# of non unique_size: "<< non_unique_size <<endl;

        if ((numNodes == (hops+1)) && (numNodes ==unique_size) && (unique_size == non_unique_size)){
            // allora è stabile
            simtime_t interval =  sm->getArrivalTime() - sm->getStart();
            EV << "time for round: " << interval<<"%W"  << endl;
            throw cRuntimeError("network stable");
        } else {
            simtime_t interval =  sm->getArrivalTime() - sm->getStart();
            EV << "The net is not stable after " << interval<<"%W" << endl;
        }
    } else {
        sm->setRingArraySize(size+1);
        for (int k = 0; k <= size; k++) {
            listOfNodes.push_back(this->getOverlayKey());
            sm->setRing(k,listOfNodes[k].c_str());
        }
        if(this->successorlist->getSuccessor() != this){
            EV_DEBUG << "Sending stabilize message to to the successor";
            EV_DEBUG << this->getOverlayKey() << endl;
            EV_DEBUG << this->successorlist->getSuccessor()->getOverlayKey() << endl;
            sm->setHops(hops+1);
            send_chord(sm, this->successorlist->getSuccessor()->getParentModule());
        } else {
            EV_DEBUG << "I'm my successor, wait next timer";
        }
    }
}
