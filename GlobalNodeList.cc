/*
 * GlobalNodeList.h
 *
 *  Created on: 29 ago 2019
 *      Author: Albo
 */

#include "GlobalNodeList.h"

#include <omnetpp/checkandcast.h>
#include <omnetpp/clog.h>
#include <omnetpp/cmessage.h>
#include <omnetpp/cobjectfactory.h>
#include <omnetpp/cpar.h>
#include <omnetpp/csimulation.h>
#include <omnetpp/regmacros.h>
#include <omnetpp/simtime.h>
#include <__tree>
#include <cstdlib>
#include <list>
#include <utility>
#include <string.h>
#include <string>
#include <algorithm>

#include "Node.h"

using namespace omnetpp;

#define COMPILETIME_LOGLEVEL LOGLEVEL_INFO

Define_Module(GlobalNodeList);

void GlobalNodeList::initialize() {
    EV_DEBUG << "global list initialized \n" ;
    int numberOfNodes = this->par("numNodes").intValue();
    this->setNumberOfNodes(numberOfNodes);
    cMessage *msg = new cMessage("msg");
    scheduleAt(simTime()+ 1, msg);
}

void GlobalNodeList::handleMessage(cMessage *msg){
    if (msg->isSelfMessage()){
        int j = this->par("numNodes").intValue();
        for (int i=0; i<j; i++){
            Node *m = check_and_cast<Node*>(getParentModule()->getSubmodule("array",i)->getSubmodule("node"));
            std::string ip = m->par("IP").stringValue();
            if (this->setNode.find(ip) == this->getSetNode().end()){
                std::set<std::string>::iterator it;
                // set di tutti i nodi presenti nella rete
                this->setNode.insert(ip);

                EV_DEBUG << "NODE WITH IP: " << ip << " REGISTERED TO GLOBAL SET OF NODES \n" ;
            } else {
                EV_DEBUG << "NODE WITH IP: " << ip << " ALREADY EXISTS ---------------------------- \n" ;

            }
        }
        this->pickFailed();

    }else {
        //questo modulo riceve messaggi dai nodi quando questi ultimi entrano in chord
        //questo messaggio conterrà solo la chiave del nodo
        //NotifyBoostrapList* notification = check_and_cast<NotifyBoostrapList*>(msg);

    }
    cancelAndDelete(msg);
}




string GlobalNodeList::getBootstrapNode() {


    //si prende un nodo che è dentro chord
    std::list<std::string>::iterator it;
    if(this->boostrapList.empty()){
        return "";
    }else{
        int pos = rand() % this->boostrapList.size();
        return this->boostrapList[pos];
    }

}



void GlobalNodeList::addBooststrapNode(Node* boot){
    EV_DEBUG << "adding this node: " << boot->getIp() << endl;
    this->boostrapList.push_back(boot->getIp());
}

void GlobalNodeList::printList(){
    for(int i = 0; i< boostrapList.size(); i++ ){
        EV_DEBUG << boostrapList[i] << endl;
    }
}

void GlobalNodeList::pickFailed(){
    int toPick = getParentModule()->par("failedNodes");
    EV << toPick << endl;
    for (int i=0; i< toPick; i++){
        int pos = rand() % this->setNode.size();
        auto it = std::begin(this->setNode);
        std::advance(it,pos);
        failedNodes.push_back(*it);
        EV << *it << " is gonna leave/fail" << endl;
    }
}

bool GlobalNodeList::willFail(string key){
    for(int i=0; i<this->failedNodes.size(); i++){
        if(strcmp(failedNodes[i].c_str(),key.c_str())==0){
            EV << key << " is gonna leave/fail" << endl;
            return true;
        }
    }
    return false;
}
