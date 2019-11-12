/*
 * NodeHandle.h
 *
 *  Created on: 3 set 2019
 *      Author: Albo
 */


#include <omnetpp.h>
#include <string.h>
#include <string>
#include "inet/mobility/base/MobilityBase.h"
#include "inet/mobility/static/StationaryMobility.h"
using namespace std;
using namespace omnetpp;


#ifndef NODEHANDLE_H_
#define NODEHANDLE_H_

class NodeHandle: public cModule {

public:
    string ip;
protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;

    //void handleMessage(cMessage *msg);
};


#endif /* NODEHANDLE_H_ */
